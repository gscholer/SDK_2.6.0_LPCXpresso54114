/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "fsl_mailbox.h"
#include "static_queue.h"
#include "low_power.h"
#include "fsl_i2c.h"
#include "fsl_utick.h"
#include "fsl_clock.h"
#include "fsl_power.h"

#include "fsl_common.h"
#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define CORE_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)
#define APP_I2C_MASTER (I2C4)

#define QUEUE_ELEMENT_SIZE 40
#define QUEUE_ELEMENT_COUNT 200

#define UTICK_TIME 10000

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t volatile g_queue_buffer[QUEUE_ELEMENT_COUNT * QUEUE_ELEMENT_SIZE];
static_queue_t volatile g_dataBuff;
struct bmm050_t bmm050;
struct bma2x2_t bma2x2;
struct bmi160_t bmi160;
struct bmp280_t bmp280;
bool volatile g_readSensorsData = true;
bool volatile g_flashPowerUp    = true;

/*******************************************************************************
 * Code
 ******************************************************************************/

void MAILBOX_IRQHandler()
{
    core_cmd_t cmd = (core_cmd_t)MAILBOX_GetValue(MAILBOX, kMAILBOX_CM0Plus);
    if (cmd == kTurnOffFlash)
    {
        POWER_PowerDownFlash();
        g_flashPowerUp = false;
    }
    MAILBOX_ClearValueBits(MAILBOX, kMAILBOX_CM0Plus, 0xffffffff);
    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

/*!
 * @brief Time delay
 * Function waits desired time with accuracy 1us.
 */
void timeDelay_us(uint32_t delay)
{
    delay++;
    /* Wait desired time */
    while (delay > 0)
    {
        if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
        {
            delay--;
        }
    }
}

void timeDelay(uint32_t miliseconds)
{
    timeDelay_us(miliseconds * 1000);
}

void timeDelay16(uint16_t miliseconds)
{
    timeDelay_us(miliseconds * 1000);
}

void installTimeDelay()
{
    /* Disable SysTick timer */
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    /* Initialize Reload value to 1us */
    SysTick->LOAD = CORE_CLK_FREQ / 1000000;
    /* Set clock source to processor clock */
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    /* Enable SysTick timer */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

int8_t i2c_read(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t cnt)
{
    I2C_MasterStart(APP_I2C_MASTER, addr, kI2C_Write);
    I2C_MasterWriteBlocking(APP_I2C_MASTER, &reg, 1, kI2C_TransferNoStartFlag | kI2C_TransferNoStopFlag);
    I2C_MasterStart(APP_I2C_MASTER, addr, kI2C_Read);
    if (cnt > 0)
    {
        I2C_MasterReadBlocking(APP_I2C_MASTER, data, cnt, kI2C_TransferDefaultFlag);
    }
    return 0;
}

int8_t i2c_write(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t cnt)
{
    I2C_MasterStart(APP_I2C_MASTER, addr, kI2C_Write);
    I2C_MasterWriteBlocking(APP_I2C_MASTER, &reg, 1, kI2C_TransferNoStartFlag | kI2C_TransferNoStopFlag);
    if (cnt > 0)
    {
        I2C_MasterWriteBlocking(APP_I2C_MASTER, data, cnt, kI2C_TransferNoStartFlag | kI2C_TransferNoStopFlag);
    }
    I2C_MasterStop(APP_I2C_MASTER);
    return 0;
}

void init_sensors()
{
    /* init mag */
    bmm050.bus_write  = i2c_write;
    bmm050.bus_read   = i2c_read;
    bmm050.delay_msec = (void (*)(BMM050_MDELAY_DATA_TYPE))timeDelay;
    bmm050.dev_addr   = 0x12; // BMM050_I2C_ADDRESS;
    /* Structure used for read the mag xyz data with 32 bit output*/
    bmm050_init(&bmm050);
    bmm050_set_functional_state(BMM050_NORMAL_MODE);
    bmm050_set_data_rate(BMM050_DATA_RATE_02HZ);

    /* init accel */
    bma2x2.bus_write  = i2c_write;
    bma2x2.bus_read   = i2c_read;
    bma2x2.delay_msec = (void (*)(BMA2x2_MDELAY_DATA_TYPE))timeDelay;
    bma2x2.dev_addr   = 0x10;
    bma2x2_init(&bma2x2);
    bma2x2_set_power_mode(BMA2x2_MODE_NORMAL);
    bma2x2_set_bw(BMA2x2_BW_7_81HZ);

    /* init gyro */
    bmi160.bus_write  = i2c_write;
    bmi160.bus_read   = i2c_read;
    bmi160.delay_msec = (void (*)(BMI160_MDELAY_DATA_TYPE))timeDelay;
    bmi160.dev_addr   = 0x68; // BMI160_I2C_ADDR2;
    bmi160_init(&bmi160);
    bmi160_set_command_register(GYRO_MODE_NORMAL);
    timeDelay(1);
    bmi160_set_gyro_output_data_rate(BMI160_GYRO_OUTPUT_DATA_RATE_100HZ);
    bmi160_set_gyro_bw(BMI160_GYRO_NORMAL_MODE);
    bmi160_set_gyro_range(BMI160_GYRO_RANGE_125_DEG_SEC);

    /* bmp280 init */
    bmp280.bus_write  = i2c_write;
    bmp280.bus_read   = i2c_read;
    bmp280.delay_msec = (void (*)(BMP280_MDELAY_DATA_TYPE))timeDelay16;
    bmp280.dev_addr   = 0x76;
    bmp280_init(&bmp280);
    bmp280_set_soft_rst();
    timeDelay(1);
    bmp280_set_power_mode(BMP280_NORMAL_MODE);
    timeDelay(1);
    bmp280_set_work_mode(BMP280_ULTRA_LOW_POWER_MODE);
    bmp280_set_standby_durn(BMP280_STANDBY_TIME_1_MS);
}

void utick_cb()
{
    g_readSensorsData = true;
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Init board hardware. */
    /* attach 12 MHz clock to FLEXCOMM4 (I2C master) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM4);

    BOARD_InitPins_Core1();

    installTimeDelay();

    /* i2c init */
    i2c_master_config_t masterConfig;
    I2C_MasterGetDefaultConfig(&masterConfig);

    /* Change the default baudrate configuration */
    masterConfig.baudRate_Bps = 380000;

    /* Initialize the LPI2C master peripheral */
    I2C_MasterInit(APP_I2C_MASTER, &masterConfig, CORE_CLK_FREQ);

    /* initialize sensors */
    init_sensors();

    /* Init Mailbox */
    MAILBOX_Init(MAILBOX);

    /* Enable mailbox interrupt */
    NVIC_EnableIRQ(MAILBOX_IRQn);

    static_queue_init((static_queue_t *)&g_dataBuff, (uint8_t *)g_queue_buffer, QUEUE_ELEMENT_COUNT,
                      QUEUE_ELEMENT_SIZE);

    /* send to core0 address of shared memory - static queue (ring buffer) */
    MAILBOX_SetValue(MAILBOX, kMAILBOX_CM4, (uint32_t)(&g_dataBuff));

    /* Initialize UTICK */
    UTICK_Init(UTICK0);

    /* Set the UTICK timer to wake up the device from reduced power mode */
    UTICK_SetTick(UTICK0, kUTICK_Repeat, UTICK_TIME, utick_cb);

    sensor_data_t data;

    while (1)
    {
        bmm050_read_mag_data_XYZ_s32(&data.mag);
        bma2x2_read_accel_xyzt(&data.accel);
        bmi160_read_gyro_xyz(&data.gyro);
        bmp280_read_pressure_temperature((u32 *)&data.press, (s32 *)&data.temp);
        static_queue_add((static_queue_t *)&g_dataBuff, (void *)&data);

        g_readSensorsData = false;

        if (static_queue_size((static_queue_t *)&g_dataBuff) > QUEUE_ELEMENT_COUNT_TRIG)
        {
            MAILBOX_SetValue(MAILBOX, kMAILBOX_CM4, kProcessData);
        }

        if (!g_flashPowerUp)
        {
            /* Power up flash before waking CM4 */
            POWER_PowerUpFlash();
            timeDelay_us(150);
        }

        /* Send interrupt to CM4 to switch to deep sleep mode */
        MAILBOX_SetValue(MAILBOX, kMAILBOX_CM4, kGoToDeepSleep);

        if (!g_readSensorsData)
        {
            __WFI();
        }
    }
}
