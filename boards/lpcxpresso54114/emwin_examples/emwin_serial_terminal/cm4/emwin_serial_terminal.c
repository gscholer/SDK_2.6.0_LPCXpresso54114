/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*  Standard C Included Files */
#include <stdio.h>
#include <string.h>
#include "board.h"
#include "fsl_debug_console.h"
#include "emwin_support.h"

#include "GUI.h"
#include "GUIDRV_Lin.h"
#include "BUTTON.h"

#include "pin_mux.h"
#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

uint32_t SPI5_GetFreq(void)
{
    return CLOCK_GetFreq(kCLOCK_Flexcomm5);
}

uint32_t I2C4_GetFreq(void)
{
    return CLOCK_GetFreq(kCLOCK_Flexcomm4);
}

uint32_t I2C7_GetFreq(void)
{
    return CLOCK_GetFreq(kCLOCK_Flexcomm7);
}

int main(void)
{
    int termWidth;
    int termHeight;

    int charWidth;
    int lineHeight;

    int c      = 0;
    int c_prev = 0;

    /* Board pin, clock, debug console init */
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    /* attach 12 MHz clock to I2C0 */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM4);

    /* attach 12 MHz clock to I2C1 */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM5);

    /* attach 12 MHz clock to I2C1 */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM7);

    CLOCK_EnableClock(kCLOCK_Gpio1);

    /* reset FLEXCOMM for SPI and I2C */
    RESET_PeripheralReset(kFC4_RST_SHIFT_RSTn);
    RESET_PeripheralReset(kFC5_RST_SHIFT_RSTn);
    RESET_PeripheralReset(kGPIO1_RST_SHIFT_RSTn);

    BOARD_InitPins();
    BOARD_BootClockFROHF48M();
    BOARD_InitDebugConsole();

    /* emWin start */
    GUI_Init();

    WM_SetSize(WM_HBKWIN, LCD_WIDTH, LCD_HEIGHT);

    /* Solid color display */
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();

    WM_Exec();

    GUI_SetColor(GUI_BLACK);

    termWidth  = WM_GetWindowSizeX(0);
    termHeight = WM_GetWindowSizeY(0);

    GUI_SetFont(GUI_FONT_8X16);
    lineHeight = GUI_GetFontDistY();
    charWidth  = GUI_GetCharDistX('_');

    GUI_DispString("Waiting for data - connect using serial terminal\n>");

    for (;;)
    {
        /* show cursor */
        GUI_MULTIBUF_Begin();
        GUI_DispChar('_');
        GUI_GotoX(GUI_GetDispPosX() - charWidth);
        GUI_MULTIBUF_End();
        c = GETCHAR();
        if (c == '\r')
        {
            /* translate CR to LF */
            c_prev = c;
            c      = '\n';
        }
        else if (c == '\n' && c_prev == '\r')
        {
            /* ignore LF following CR */
            c_prev = c;
            continue;
        }
        c_prev = c;

        /* hide cursor */
        GUI_MULTIBUF_Begin();
        GUI_DispChar(' ');
        GUI_GotoX(GUI_GetDispPosX() - charWidth);

        GUI_DispChar(c);

        if (GUI_GetDispPosX() >= termWidth)
        {
            GUI_DispNextLine();
        }

        if (GUI_GetDispPosY() + lineHeight > termHeight)
        {
            GUI_Clear();
            GUI_GotoY(0);
        }
        GUI_MULTIBUF_End();
    }
}
