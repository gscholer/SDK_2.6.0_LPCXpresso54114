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
#include "fsl_inputmux.h"
#include "pin_mux.h"



/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: '31', peripheral: FLEXCOMM0, signal: RXD_SDA_MOSI, pin_signal: PIO0_0/FC0_RXD_SDA_MOSI/FC3_CTS_SDA_SSEL0/CTIMER0_CAP0/SCT0_OUT3, mode: inactive, invert: disabled,
    glitch_filter: disabled, slew_rate: standard, open_drain: disabled}
  - {pin_num: '32', peripheral: FLEXCOMM0, signal: TXD_SCL_MISO, pin_signal: PIO0_1/FC0_TXD_SCL_MISO/FC3_RTS_SCL_SSEL1/CTIMER0_CAP1/SCT0_OUT1, mode: inactive, invert: disabled,
    glitch_filter: disabled, slew_rate: standard, open_drain: disabled}
  - {pin_num: '62', peripheral: GPIO, signal: 'PIO1, 15', pin_signal: PIO1_15/PDM0_CLK/SCT0_OUT5/CTIMER1_CAP3/FC7_CTS_SDA_SSEL0, mode: inactive, invert: disabled,
    glitch_filter: disabled, slew_rate: standard, open_drain: disabled}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the undefined */
void BOARD_InitPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    const uint32_t port0_pin0_config = (/* Pin is configured as FC0_RXD_SDA_MOSI */
                                        IOCON_PIO_FUNC1 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Standard mode, output slew rate control is enabled */
                                        IOCON_PIO_SLEW_STANDARD |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN0 (coords: 31) is configured as FC0_RXD_SDA_MOSI */
    IOCON_PinMuxSet(IOCON, 0U, 0U, port0_pin0_config);

    const uint32_t port0_pin1_config = (/* Pin is configured as FC0_TXD_SCL_MISO */
                                        IOCON_PIO_FUNC1 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Standard mode, output slew rate control is enabled */
                                        IOCON_PIO_SLEW_STANDARD |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN1 (coords: 32) is configured as FC0_TXD_SCL_MISO */
    IOCON_PinMuxSet(IOCON, 0U, 1U, port0_pin1_config);

    const uint32_t port1_pin15_config = (/* Pin is configured as PIO1_15 */
                                         IOCON_PIO_FUNC0 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN15 (coords: 62) is configured as PIO1_15 */
    IOCON_PinMuxSet(IOCON, 1U, 15U, port1_pin15_config);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
I2C4_InitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: '4', peripheral: FLEXCOMM4, signal: CTS_SDA_SSEL0, pin_signal: PIO0_26/FC4_CTS_SDA_SSEL0/CTIMER0_CAP3, invert: disabled, glitch_filter: disabled, i2c_slew: i2c,
    i2c_drive: low, i2c_filter: enabled}
  - {pin_num: '3', peripheral: FLEXCOMM4, signal: RTS_SCL_SSEL1, pin_signal: PIO0_25/FC4_RTS_SCL_SSEL1/FC6_CTS_SDA_SSEL0/CTIMER0_CAP2/CTIMER1_CAP1, invert: disabled,
    glitch_filter: disabled, i2c_slew: i2c, i2c_drive: low, i2c_filter: enabled}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : I2C4_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the undefined */
void I2C4_InitPins(void)
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

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
I2C4_DeinitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: '4', peripheral: GPIO, signal: 'PIO0, 26', pin_signal: PIO0_26/FC4_CTS_SDA_SSEL0/CTIMER0_CAP3}
  - {pin_num: '3', peripheral: GPIO, signal: 'PIO0, 25', pin_signal: PIO0_25/FC4_RTS_SCL_SSEL1/FC6_CTS_SDA_SSEL0/CTIMER0_CAP2/CTIMER1_CAP1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : I2C4_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the undefined */
void I2C4_DeinitPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    IOCON->PIO[0][25] = ((IOCON->PIO[0][25] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.: PORT025 (pin 3) is configured as PIO0_25 */
                         | IOCON_PIO_FUNC(PIO025_FUNC_ALT0)

                         /* Select Analog/Digital mode.: Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO025_DIGIMODE_DIGITAL));

    IOCON->PIO[0][26] = ((IOCON->PIO[0][26] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.: PORT026 (pin 4) is configured as PIO0_26 */
                         | IOCON_PIO_FUNC(PIO026_FUNC_ALT0)

                         /* Select Analog/Digital mode.: Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO026_DIGIMODE_DIGITAL));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
SPI5_InitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: '15', peripheral: FLEXCOMM5, signal: SSEL2, pin_signal: PIO1_1/SWO/SCT0_OUT4/FC5_SSEL2/FC4_TXD_SCL_MISO/ADC0_4, mode: pullUp, invert: disabled, glitch_filter: disabled,
    open_drain: disabled}
  - {pin_num: '58', peripheral: FLEXCOMM5, signal: TXD_SCL_MISO, pin_signal: PIO0_18/FC5_TXD_SCL_MISO/SCT0_OUT0/CTIMER0_MAT0, mode: pullUp, invert: disabled, glitch_filter: disabled,
    slew_rate: standard, open_drain: disabled}
  - {pin_num: '59', peripheral: FLEXCOMM5, signal: SCK, pin_signal: PIO0_19/FC5_SCK/SCT0_OUT1/CTIMER0_MAT1, mode: pullUp, invert: disabled, glitch_filter: disabled,
    slew_rate: standard, open_drain: disabled}
  - {pin_num: '60', peripheral: FLEXCOMM5, signal: RXD_SDA_MOSI, pin_signal: PIO0_20/FC5_RXD_SDA_MOSI/FC0_SCK/CTIMER3_CAP0, mode: pullUp, invert: disabled, glitch_filter: disabled,
    slew_rate: standard, open_drain: disabled}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : SPI5_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the undefined */
void SPI5_InitPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    const uint32_t port0_pin18_config = (/* Pin is configured as FC5_TXD_SCL_MISO */
                                         IOCON_PIO_FUNC1 |
                                         /* Selects pull-up function */
                                         IOCON_PIO_MODE_PULLUP |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN18 (coords: 58) is configured as FC5_TXD_SCL_MISO */
    IOCON_PinMuxSet(IOCON, 0U, 18U, port0_pin18_config);

    const uint32_t port0_pin19_config = (/* Pin is configured as FC5_SCK */
                                         IOCON_PIO_FUNC1 |
                                         /* Selects pull-up function */
                                         IOCON_PIO_MODE_PULLUP |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN19 (coords: 59) is configured as FC5_SCK */
    IOCON_PinMuxSet(IOCON, 0U, 19U, port0_pin19_config);

    const uint32_t port0_pin20_config = (/* Pin is configured as FC5_RXD_SDA_MOSI */
                                         IOCON_PIO_FUNC1 |
                                         /* Selects pull-up function */
                                         IOCON_PIO_MODE_PULLUP |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN20 (coords: 60) is configured as FC5_RXD_SDA_MOSI */
    IOCON_PinMuxSet(IOCON, 0U, 20U, port0_pin20_config);

    const uint32_t port1_pin1_config = (/* Pin is configured as FC5_SSEL2 */
                                        IOCON_PIO_FUNC4 |
                                        /* Selects pull-up function */
                                        IOCON_PIO_MODE_PULLUP |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN1 (coords: 15) is configured as FC5_SSEL2 */
    IOCON_PinMuxSet(IOCON, 1U, 1U, port1_pin1_config);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
SPI5_DeinitPins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: '15', peripheral: DMA0, signal: 'TRIG, 10', pin_signal: PIO1_1/SWO/SCT0_OUT4/FC5_SSEL2/FC4_TXD_SCL_MISO/ADC0_4, mode: no_init, invert: no_init, glitch_filter: no_init,
    open_drain: no_init}
  - {pin_num: '58', peripheral: DMA0, signal: 'TRIG, 11', pin_signal: PIO0_18/FC5_TXD_SCL_MISO/SCT0_OUT0/CTIMER0_MAT0, mode: no_init, invert: no_init, glitch_filter: no_init,
    slew_rate: no_init, open_drain: no_init}
  - {pin_num: '59', peripheral: DMA0, signal: 'TRIG, 12', pin_signal: PIO0_19/FC5_SCK/SCT0_OUT1/CTIMER0_MAT1, mode: no_init, invert: no_init, glitch_filter: no_init,
    slew_rate: no_init, open_drain: no_init}
  - {pin_num: '60', peripheral: DMA0, signal: 'TRIG, 13', pin_signal: PIO0_20/FC5_RXD_SDA_MOSI/FC0_SCK/CTIMER3_CAP0, mode: no_init, invert: no_init, glitch_filter: no_init,
    slew_rate: no_init, open_drain: no_init}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : SPI5_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the undefined */
void SPI5_DeinitPins(void)
{
    /* Enables the clock for the input muxes. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_InputMux);
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Pin interrupt 1 is selected as trigger input for DMA channel 10 */
    INPUTMUX_AttachSignal(INPUTMUX, 10U, kINPUTMUX_PinInt1ToDma);
    /* Pin interrupt 2 is selected as trigger input for DMA channel 11 */
    INPUTMUX_AttachSignal(INPUTMUX, 11U, kINPUTMUX_PinInt2ToDma);
    /* Pin interrupt 3 is selected as trigger input for DMA channel 12 */
    INPUTMUX_AttachSignal(INPUTMUX, 12U, kINPUTMUX_PinInt3ToDma);
    /* Pin interrupt 0 is selected as trigger input for DMA channel 13 */
    INPUTMUX_AttachSignal(INPUTMUX, 13U, kINPUTMUX_PinInt0ToDma);
    /* PIO0_20 is selected for PINT input 0 */
    INPUTMUX_AttachSignal(INPUTMUX, 0U, kINPUTMUX_GpioPort0Pin20ToPintsel);
    /* PIO1_1 is selected for PINT input 1 */
    INPUTMUX_AttachSignal(INPUTMUX, 1U, kINPUTMUX_GpioPort1Pin1ToPintsel);
    /* PIO0_18 is selected for PINT input 2 */
    INPUTMUX_AttachSignal(INPUTMUX, 2U, kINPUTMUX_GpioPort0Pin18ToPintsel);
    /* PIO0_19 is selected for PINT input 3 */
    INPUTMUX_AttachSignal(INPUTMUX, 3U, kINPUTMUX_GpioPort0Pin19ToPintsel);

    IOCON->PIO[0][18] = ((IOCON->PIO[0][18] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.: PORT018 (pin 58) is configured as PIO0_18 */
                         | IOCON_PIO_FUNC(PIO018_FUNC_ALT0)

                         /* Select Analog/Digital mode.: Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO018_DIGIMODE_DIGITAL));

    IOCON->PIO[0][19] = ((IOCON->PIO[0][19] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.: PORT019 (pin 59) is configured as PIO0_19 */
                         | IOCON_PIO_FUNC(PIO019_FUNC_ALT0)

                         /* Select Analog/Digital mode.: Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO019_DIGIMODE_DIGITAL));

    IOCON->PIO[0][20] = ((IOCON->PIO[0][20] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.: PORT020 (pin 60) is configured as PIO0_20 */
                         | IOCON_PIO_FUNC(PIO020_FUNC_ALT0)

                         /* Select Analog/Digital mode.: Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO020_DIGIMODE_DIGITAL));

    IOCON->PIO[1][1] = ((IOCON->PIO[1][1] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.: PORT11 (pin 15) is configured as PIO1_1 */
                        | IOCON_PIO_FUNC(PIO11_FUNC_ALT0)

                        /* Select Analog/Digital mode.: Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO11_DIGIMODE_DIGITAL));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
