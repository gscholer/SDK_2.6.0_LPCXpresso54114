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
#include "erpc_two_way_rpc_Core1Interface.h"
#include "erpc_two_way_rpc_Core0Interface_server.h"
#include "erpc_error_handler.h"
#include "FreeRTOS.h"
#include "task.h"
#include "fsl_debug_console.h"

#include "fsl_common.h"
#include "pin_mux.h"
#include "mcmgr.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define ERPC_TRANSPORT_RPMSG_LITE_LINK_ID (RL_PLATFORM_LPC5411x_M4_M0_LINK_ID)
#define MCMGR_USED
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
static uint32_t s_number = 0;
#ifdef MCMGR_USED
uint32_t startupData;
mcmgr_status_t mcmgrStatus;
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
#ifdef MCMGR_USED
static void SignalReady(void)
{
    /* Signal the other core we are ready by triggering the event and passing the APP_ERPC_READY_EVENT_DATA */
    MCMGR_TriggerEvent(kMCMGR_RemoteApplicationEvent, APP_ERPC_READY_EVENT_DATA);
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
#endif

/* Implementation of RPC function setGetNumberFunction. */
void setGetNumberFunction(const getNumberCallback_t getNumberCallbackParam)
{
    s_getNumberCallbackPtr = getNumberCallbackParam;
}

/* Implementation of RPC function getGetNumberFunction. */
void getGetNumberFunction(getNumberCallback_t *getNumberCallbackParam)
{
    *getNumberCallbackParam = s_getNumberCallbackPtr;
}

/* Implementation of RPC function nestedCallGetNumber. */
void nestedCallGetNumber(const getNumberCallback_t getNumberCallbackParam)
{
    uint32_t number;
    getNumberCallbackParam(&number);
}

/* Implementation of RPC function getNumberFromCore1. */
void getNumberFromCore1(uint32_t *number)
{
    *number = s_number;
}

void client_task(void *param)
{
    PRINTF("\r\nSecondary core started\r\n");

    /* RPMsg-Lite transport layer initialization */
    erpc_transport_t transport;

#ifdef MCMGR_USED
    transport = erpc_transport_rpmsg_lite_rtos_remote_init(101, 100, (void *)startupData,
                                                           ERPC_TRANSPORT_RPMSG_LITE_LINK_ID, SignalReady, NULL);
#elif defined(RPMSG_LITE_MASTER_IS_LINUX)
    transport              = erpc_transport_rpmsg_lite_tty_rtos_remote_init(101, 1024, (void *)RPMSG_LITE_SHMEM_BASE,
                                                               ERPC_TRANSPORT_RPMSG_LITE_LINK_ID, NULL,
                                                               RPMSG_LITE_NS_ANNOUNCE_STRING);
#else
    transport = erpc_transport_rpmsg_lite_rtos_remote_init(101, 100, (void *)RPMSG_LITE_SHMEM_BASE,
                                                           ERPC_TRANSPORT_RPMSG_LITE_LINK_ID, NULL, NULL);
#endif

    s_transport = transport;

    /* MessageBufferFactory initialization */
    erpc_mbf_t message_buffer_factory;
#ifdef RPMSG_LITE_MASTER_IS_LINUX
    message_buffer_factory = erpc_mbf_rpmsg_tty_init(transport);
#else
    message_buffer_factory = erpc_mbf_rpmsg_init(transport);
#endif

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
       To be sure that first core server is ready before rpc call. */
    vTaskDelay(500);

    while (g_erpc_error_occurred == kErpcStatus_Success)
    {
        /* This client only requests increasing of number. */
        increaseNumber(&s_number);
        vTaskDelay(500);
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

    /* MessageBufferFactory initialization */
    erpc_mbf_t message_buffer_factory;
#ifdef RPMSG_LITE_MASTER_IS_LINUX
    message_buffer_factory = erpc_mbf_rpmsg_tty_init(s_transport);
#else
    message_buffer_factory = erpc_mbf_rpmsg_init(s_transport);
#endif

    /* eRPC server initialization */
    s_server = erpc_server_init(s_transportArbitrator, message_buffer_factory);
    erpc_add_service_to_server(create_Core0Interface_service());

#ifdef RPMSG_LITE_MASTER_IS_LINUX
    /* ignore first hello world message from RPMSG tty device */
    erpc_server_run();
#endif

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
    BOARD_InitPins_Core1();
    BOARD_InitDebugConsole_Core1();

#ifdef MCMGR_USED

    /* Initialize MCMGR before calling its API */
    MCMGR_Init();

    /* Get the startup data */
    do
    {
        mcmgrStatus = MCMGR_GetStartupData(&startupData);
    } while (mcmgrStatus != kStatus_MCMGR_Success);
#endif

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
