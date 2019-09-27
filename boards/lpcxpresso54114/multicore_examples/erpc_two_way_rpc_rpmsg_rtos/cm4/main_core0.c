/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "rpmsg_lite.h"
#include "erpc_arbitrated_client_setup.h"
#include "erpc_server_setup.h"
#include "erpc_error_handler.h"
#include "erpc_two_way_rpc_Core0Interface.h"
#include "erpc_two_way_rpc_Core1Interface_server.h"
#include "fsl_debug_console.h"
#include "FreeRTOS.h"
#include "task.h"
#include "mcmgr.h"

#include "fsl_common.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define ERPC_TRANSPORT_RPMSG_LITE_LINK_ID (RL_PLATFORM_LPC5411x_M4_M0_LINK_ID)

#define BUTTON_INIT() GPIO_PinInit(GPIO, BOARD_SW2_GPIO_PORT, BOARD_SW2_GPIO_PIN, &button_config)
#define IS_BUTTON_PRESSED() !GPIO_PinRead(GPIO, BOARD_SW2_GPIO_PORT, BOARD_SW2_GPIO_PIN)
#define BUTTON_NAME BOARD_SW2_NAME

/* Address of RAM, where the image for core1 should be copied */
#define CORE1_BOOT_ADDRESS (void *)0x20010000

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
extern uint32_t Image$$CORE1_REGION$$Base;
extern uint32_t Image$$CORE1_REGION$$Length;
#define CORE1_IMAGE_START &Image$$CORE1_REGION$$Base
#elif defined(__ICCARM__)
extern unsigned char core1_image_start[];
#define CORE1_IMAGE_START core1_image_start
#elif defined(__GNUC__)
extern const char m0_image_start[];
extern const char *m0_image_end;
extern int m0_image_size;
#define CORE1_IMAGE_START ((void *)m0_image_start)
#define CORE1_IMAGE_SIZE ((void *)m0_image_size)
#endif

extern char rpmsg_lite_base[];

#define MATRIX_ITEM_MAX_VALUE 50
#define APP_TASK_STACK_SIZE 256
#define APP_ERPC_READY_EVENT_DATA (1)

/*******************************************************************************
 * Variables
 ******************************************************************************/

static TaskHandle_t s_client_task_handle          = NULL;
static TaskHandle_t s_server_task_handle          = NULL;
static erpc_transport_t s_transportArbitrator     = NULL;
static erpc_transport_t s_transport               = NULL;
static getNumberCallback_t s_getNumberCallbackPtr = NULL;
static erpc_server_t s_server                     = NULL;
extern bool g_erpc_error_occurred;
static uint32_t s_number             = 0;
volatile uint16_t eRPCReadyEventData = 0;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

#ifdef CORE1_IMAGE_COPY_TO_RAM
uint32_t get_core1_image_size(void);
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

#ifdef CORE1_IMAGE_COPY_TO_RAM
uint32_t get_core1_image_size()
{
    uint32_t core1_image_size;
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
    core1_image_size = (uint32_t)&Image$$CORE1_REGION$$Length;
#elif defined(__ICCARM__)
#pragma section = "__sec_core"
    core1_image_size = (uint32_t)__section_end("__sec_core") - (uint32_t)&core1_image_start;
#elif defined(__GNUC__)
    core1_image_size = (uint32_t)m0_image_size;
#endif
    return core1_image_size;
}
#endif

/*!
 * @brief eRPC server side ready event handler
 */
static void eRPCReadyEventHandler(uint16_t eventData, void *context)
{
    eRPCReadyEventData = eventData;
}

/*!
 * @brief Application-specific implementation of the SystemInitHook() weak function.
 */
void SystemInitHook(void)
{
    /* Initialize MCMGR - low level multicore management library. Call this
       function as close to the reset entry as possible to allow CoreUp event
       triggering. The SystemInitHook() weak function overloading is used in this
       application. */
    MCMGR_EarlyInit();
}

/* Implementation of RPC function getNumberFromCore0. */
void getNumberFromCore0(uint32_t *number)
{
    *number = s_number;
    PRINTF("getNumberFromCore0 function call: Actual number is %d\n", *number);
}

/* Implementation of RPC function increaseNumber. */
void increaseNumber(uint32_t *number)
{
    *number += 1;
    s_number = *number;
}

void client_task(void *param)
{
    int core = 0;
    uint32_t number;
    PRINTF("\r\nPrimary core started\r\n");

#ifdef CORE1_IMAGE_COPY_TO_RAM
    /* Calculate size of the image */
    uint32_t core1_image_size;
    core1_image_size = get_core1_image_size();
    PRINTF("Copy CORE1 image to address: 0x%x, size: %d\n", CORE1_BOOT_ADDRESS, core1_image_size);

    /* Copy application from FLASH to RAM */
    memcpy(CORE1_BOOT_ADDRESS, (void *)CORE1_IMAGE_START, core1_image_size);
#endif

    /* Initialize MCMGR before calling its API */
    MCMGR_Init();

    /* Register the application event before starting the secondary core */
    MCMGR_RegisterEvent(kMCMGR_RemoteApplicationEvent, eRPCReadyEventHandler, NULL);

    /* Boot source for Core 1 */
    MCMGR_StartCore(kMCMGR_Core1, CORE1_BOOT_ADDRESS, (uint32_t)rpmsg_lite_base, kMCMGR_Start_Synchronous);

    /* Wait until the secondary core application signals the rpmsg remote has been initialized and is ready to
     * communicate. */
    while (APP_ERPC_READY_EVENT_DATA != eRPCReadyEventData)
    {
    };

    /* RPMsg-Lite transport layer initialization */
    erpc_transport_t transport;

    transport = erpc_transport_rpmsg_lite_rtos_master_init(100, 101, ERPC_TRANSPORT_RPMSG_LITE_LINK_ID);

    s_transport = transport;

    /* MessageBufferFactory initialization */
    erpc_mbf_t message_buffer_factory;
    message_buffer_factory = erpc_mbf_rpmsg_init(transport);

    /* eRPC client side initialization */
    s_transportArbitrator = erpc_arbitrated_client_init(transport, message_buffer_factory);

    /* Set default error handler */
    erpc_arbitrated_client_set_error_handler(erpc_error_handler);

    /* Add server to client is necessary when do nesting RPC call. */
    while (s_server == NULL)
    {
        vTaskDelay(100);
    }
    erpc_arbitrated_client_set_server(s_server);
    erpc_arbitrated_client_set_server_thread_id(s_server_task_handle);

    s_getNumberCallbackPtr = &getNumberFromCore1;

    /* Simple synchronization system.
       To be sure that second core server is ready before rpc call. */
    vTaskDelay(500);

    while (g_erpc_error_occurred == kErpcStatus_Success)
    {
        /* RPC call to set callback function to second side. */
        setGetNumberFunction(s_getNumberCallbackPtr);

        /* Not necessary to set NULL. It is only for example purposes. */
        s_getNumberCallbackPtr = NULL;

        /* RPC call to get callback function from second side. */
        getGetNumberFunction(&s_getNumberCallbackPtr);

        /* Compare received address. */
        if (s_getNumberCallbackPtr == &getNumberFromCore1)
        {
            core = 1;
        }
        else
        {
            core = 0;
        }

        PRINTF("Get number from core%d:\n", core);
        s_getNumberCallbackPtr(&number);
        PRINTF("Got number: %d\n", number);

        PRINTF("Start ");
        if (core == 0)
        {
            PRINTF("nested");
        }
        else
        {
            PRINTF("normal");
        }
        PRINTF(" rpc call example.\n");
        nestedCallGetNumber(s_getNumberCallbackPtr);
        PRINTF("RPC call example finished.\n\n\n");

        if (s_getNumberCallbackPtr == &getNumberFromCore1)
        {
            s_getNumberCallbackPtr = &getNumberFromCore0;
        }
        else
        {
            s_getNumberCallbackPtr = &getNumberFromCore1;
        }

        vTaskDelay(700);
    }

    vTaskDelete(s_client_task_handle);
}

void server_task(void *param)
{
    /* Wait for client initialization. */
    while (s_transportArbitrator == NULL)
    {
        vTaskDelay(100);
    }

    /* MessageBufferFactory initialization. */
    erpc_mbf_t message_buffer_factory;
    message_buffer_factory = erpc_mbf_rpmsg_init(s_transport);

    /* eRPC server initialization */
    s_server = erpc_server_init(s_transportArbitrator, message_buffer_factory);
    erpc_add_service_to_server(create_Core1Interface_service());

    erpc_status_t status = erpc_server_run();
    if (status != kErpcStatus_Success)
    {
        PRINTF("Error occurred in server task. Task end with %d\n", status);
        erpc_error_handler(status, 0);
    }

    vTaskDelete(s_server_task_handle);
}

/*!
 * @brief Main function
 */
int main()
{
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM0);

    /* enable clock for GPIO*/
    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);

    BOARD_InitPins_Core0();
    BOARD_BootClockFROHF48M();
    BOARD_InitDebugConsole();

    if (xTaskCreate(client_task, "APP_TASK", APP_TASK_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &s_client_task_handle) !=
        pdPASS)
    {
        PRINTF("\r\nFailed to create application task\r\n");
        return -1;
    }

    if (xTaskCreate(server_task, "APP_TASK", APP_TASK_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &s_server_task_handle) !=
        pdPASS)
    {
        PRINTF("\r\nFailed to create application task\r\n");
        return -1;
    }

    vTaskStartScheduler();

    return 0;
}
