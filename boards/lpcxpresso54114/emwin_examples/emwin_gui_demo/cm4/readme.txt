Overview
========
The example demonstrates graphical widgets of the emWin library.


Toolchain supported
===================
- IAR embedded Workbench  8.32.3
- Keil MDK  5.27
- MCUXpresso  11.0.0
- GCC ARM Embedded  8.2.1

Hardware requirements
=====================
- Micro USB cable
- LPCxpresso54114 board
- Adafruit TFT LCD shield w/Cap Touch
- Personal Computer

Board settings
==============
Attach the LCD shield to the LPC board.

Prepare the Demo
================
1.  Connect a micro USB cable between the PC host and the J7 micro USB port on the board.
2.  Build the project.
3.  Download the program to the target board.
4.  Reset the SoC and run the project.

Running the demo
================
Known issue: The MCU is not able to generate hardware reset of the LCD due to hardware limitation of the boards interconnection.
Because of this the LCD may not get initialized (stays blank) following a cold start (power on) of the board even if the demo was
correctly programmed to the FLASH memory. In such a case simply press the reset button to restart the demo.
Customization options
=====================

