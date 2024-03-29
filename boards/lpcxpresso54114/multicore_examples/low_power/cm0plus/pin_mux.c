/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v3.0
processor: LPC54114J256
package_id: LPC54114J256BD64
mcu_data: ksdk2_0
processor_version: 0.0.13
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_iocon.h"
#include "pin_mux.h"



/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins_Core1:
- options: {coreID: cm0plus, enableClock: 'true'}
- pin_list:
  - {pin_num: '3', peripheral: FLEXCOMM4, signal: RTS_SCL_SSEL1, pin_signal: PIO0_25/FC4_RTS_SCL_SSEL1/FC6_CTS_SDA_SSEL0/CTIMER0_CAP2/CTIMER1_CAP1, invert: disabled,
    glitch_filter: disabled, i2c_slew: i2c, i2c_drive: low, i2c_filter: enabled}
  - {pin_num: '4', peripheral: FLEXCOMM4, signal: CTS_SDA_SSEL0, pin_signal: PIO0_26/FC4_CTS_SDA_SSEL0/CTIMER0_CAP3, invert: disabled, glitch_filter: disabled, i2c_slew: i2c,
    i2c_drive: low, i2c_filter: enabled}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins_Core1
 *
 * END ****************************************************************************************************************/
/* Function assigned for the undefined */
void BOARD_InitPins_Core1(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    const uint32_t port0_pin25_config = (/* Pin is configured as FC4_RTS_SCL_SSEL1 */
                                         IOCON_PIO_FUNC1 |
                                         /* I2C mode */
                                         IOCON_PIO_I2CSLEW_I2C |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Low drive: 4 mA */
                                         IOCON_PIO_I2CDRIVE_LOW |
                                         /* I2C 50 ns glitch filter enabled */
                                         IOCON_PIO_I2CFILTER_EN);
    /* PORT0 PIN25 (coords: 3) is configured as FC4_RTS_SCL_SSEL1 */
    IOCON_PinMuxSet(IOCON, 0U, 25U, port0_pin25_config);

    const uint32_t port0_pin26_config = (/* Pin is configured as FC4_CTS_SDA_SSEL0 */
                                         IOCON_PIO_FUNC1 |
                                         /* I2C mode */
                                         IOCON_PIO_I2CSLEW_I2C |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Low drive: 4 mA */
                                         IOCON_PIO_I2CDRIVE_LOW |
                                         /* I2C 50 ns glitch filter enabled */
                                         IOCON_PIO_I2CFILTER_EN);
    /* PORT0 PIN26 (coords: 4) is configured as FC4_CTS_SDA_SSEL0 */
    IOCON_PinMuxSet(IOCON, 0U, 26U, port0_pin26_config);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
