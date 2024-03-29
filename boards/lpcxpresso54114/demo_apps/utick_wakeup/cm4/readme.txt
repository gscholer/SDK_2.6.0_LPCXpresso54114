Overview
========
The purpose of this demo is to show wakeup from deep sleep mode using MicroTick timer.
The demo sets the MicroTick Timer as a wake up source and puts the device in deep-sleep mode. 
The MicroTick timer wakes up the device. 

Toolchain supported
===================
- IAR embedded Workbench  8.32.3
- Keil MDK  5.27
- MCUXpresso  11.0.0
- GCC ARM Embedded  8.2.1

Hardware requirements
=====================
- Mini/micro USB cable
- LPCLPCXpresso54114 board
- Personal Computer

Board settings
==============
1. Pin P0_21 is used as a CLKOUT signal. Connect this pin to an Oscilloscope for viewing the signal.

Prepare the Demo
================

Running the demo
================
The demo sets the MicroTick Timer as a wake up source and puts the device in deep-sleep mode. 
The MicroTick timer wakes up the device. After wake up the Green LED on the board blinks and  a CLKOUT signal can be seen on pin P0_21.
Customization options
=====================

