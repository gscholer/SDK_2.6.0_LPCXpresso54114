/*
 * Copyright 2016, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_dmic.h"
#include <stdlib.h>
#include <string.h>

#include "pin_mux.h"
#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_LED_GPIO_PORT BOARD_LED_RED_GPIO_PORT
#define BOARD_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN
#define FIFO_DEPTH 15U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Call back for DMIC0 Interrupt
 */
void DMIC0_Callback(void)
{
    /* In this example this interrupt is disabled */
}

/*!
 * @brief Call back for DMIC0 HWVAD Interrupt
 */
void DMIC0_HWVAD_Callback(void)
{
    volatile int i;

    GPIO_PortToggle(GPIO, BOARD_LED_GPIO_PORT, 1 << BOARD_LED_GPIO_PIN);
    /* reset hwvad internal interrupt */
    DMIC_CtrlClrIntrHwvad(DMIC0, true);
    /* wait for HWVAD to settle */
    PRINTF("Just woke up\r\n");
    for (i = 0; i <= 500U; i++)
    {
    }
    /*HWVAD Normal operation */
    DMIC_CtrlClrIntrHwvad(DMIC0, false);

    GPIO_PortToggle(GPIO, BOARD_LED_GPIO_PORT, 1 << BOARD_LED_GPIO_PIN);
}

/*!
 * @brief Main function
 */

int main(void)
{
    dmic_channel_config_t dmic_channel_cfg;
    unsigned int i;
    /* Define the init structure for the output LED pin*/
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        0,
    };
    /* Board pin, clock, debug console init */
    CLOCK_EnableClock(kCLOCK_InputMux);
    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);

    /* USART0 clock */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    /* DMIC uses 12MHz FRO clock */
    CLOCK_AttachClk(kFRO12M_to_DMIC);

    /*12MHz divided by 15 = 800KHz PDM clock */
    CLOCK_SetClkDiv(kCLOCK_DivDmicClk, 14, false);

    BOARD_InitPins();
    BOARD_BootClockFROHF48M();
    BOARD_InitDebugConsole();
    GPIO_PinInit(GPIO, BOARD_LED_GPIO_PORT, BOARD_LED_GPIO_PIN, &led_config);
    GPIO_PinWrite(GPIO, BOARD_LED_GPIO_PORT, BOARD_LED_GPIO_PIN, 1U);

    PRINTF("Configure DMIC\r\n");

    dmic_channel_cfg.divhfclk            = kDMIC_PdmDiv1;
    dmic_channel_cfg.osr                 = 25U;
    dmic_channel_cfg.gainshft            = 3U;
    dmic_channel_cfg.preac2coef          = kDMIC_CompValueZero;
    dmic_channel_cfg.preac4coef          = kDMIC_CompValueZero;
    dmic_channel_cfg.dc_cut_level        = kDMIC_DcCut155;
    dmic_channel_cfg.post_dc_gain_reduce = 0U;
    dmic_channel_cfg.saturate16bit       = 1U;
    dmic_channel_cfg.sample_rate         = kDMIC_PhyFullSpeed;
    DMIC_Init(DMIC0);

    DMIC_SetIOCFG(DMIC0, kDMIC_PdmStereo);
    DMIC_Use2fs(DMIC0, true);
    DMIC_EnableChannelInterrupt(DMIC0, kDMIC_Channel0, true);
    DMIC_EnableChannelInterrupt(DMIC0, kDMIC_Channel1, true);
    DMIC_ConfigChannel(DMIC0, kDMIC_Channel0, kDMIC_Left, &dmic_channel_cfg);
    DMIC_ConfigChannel(DMIC0, kDMIC_Channel1, kDMIC_Right, &dmic_channel_cfg);
    DMIC_FifoChannel(DMIC0, kDMIC_Channel0, FIFO_DEPTH, true, true);
    DMIC_FifoChannel(DMIC0, kDMIC_Channel1, FIFO_DEPTH, true, true);

    /*Gain of the noise estimator */
    DMIC_SetGainNoiseEstHwvad(DMIC0, 0x02U);

    /*Gain of the signal estimator */
    DMIC_SetGainSignalEstHwvad(DMIC0, 0x01U);

    /* 00 = first filter by-pass, 01 = hpf_shifter=1, 10 = hpf_shifter=4 */
    DMIC_SetFilterCtrlHwvad(DMIC0, 0x01U);

    /*input right-shift of (GAIN x 2 -10) bits (from -10bits (0000) to +14bits (1100)) */
    DMIC_SetInputGainHwvad(DMIC0, 0x04U);

    DisableDeepSleepIRQ(HWVAD0_IRQn);
    DMIC_HwvadEnableIntCallback(DMIC0, DMIC0_HWVAD_Callback);
    DMIC_EnableChannnel(DMIC0, (DMIC_CHANEN_EN_CH0(1) | DMIC_CHANEN_EN_CH1(1)));

    /* reset hwvad internal interrupt */
    DMIC_CtrlClrIntrHwvad(DMIC0, true);
    /* To clear first spurious interrupt */
    for (i = 0; i < 0xFFFFU; i++)
    {
    }
    /*HWVAD Normal operation */
    DMIC_CtrlClrIntrHwvad(DMIC0, false);
    NVIC_ClearPendingIRQ(HWVAD0_IRQn);
    EnableDeepSleepIRQ(HWVAD0_IRQn);

    while (1)
    {
        PRINTF("Going into sleep\r\n");
        __WFI();
    }
}
