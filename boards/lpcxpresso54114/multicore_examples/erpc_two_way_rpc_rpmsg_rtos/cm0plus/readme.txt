Overview
========
The Multicore eRPC Two Way RPC RTOS project is a simple demonstration
program that uses the MCUXpresso SDK software and the Multicore SDK to show
how to implement the Remote Procedure Call between cores of the multicore system.
The primary core releases the secondary core from
the reset. RPMsg-Lite erpc transport layer is used in this
example application.

Shared memory usage
This multicore example uses the shared memory for data exchange. The shared memory region is
defined and the size can be adjustable in the linker file. The shared memory region start address
and the size have to be defined in linker file for each core equally. The shared memory start
address is then exported from the linker to the application.

eRPC documentation
eRPC specific files are stored in: middleware\multicore_<version>\erpc
eRPC documentation is stored in: middleware\multicore_<version>\erpc\doc
eRPC is open-source project stored on github: https://github.com/EmbeddedRPC/erpc
eRPC documentation can be also found in: http://embeddedrpc.github.io

Toolchain supported
===================
- IAR embedded Workbench  8.32.3
- MCUXpresso  11.0.0
- GCC ARM Embedded  8.2.1
- Keil MDK  5.27

Hardware requirements
=====================
- Mini/micro USB cable
- LPCXpresso54114 board
- Personal Computer

Board settings
==============
The Multicore eRPC Matrix Multiply RTOS project does not call for any special hardware configurations.
Although not required, the recommendation is to leave the development board jumper settings and
configurations in default state when running this demo.

Prepare the Demo
================
1.  Connect a micro USB cable between the PC host and the CMSIS DAP USB port (J7) on the board
2.  Open a serial terminal with the following settings (See Appendix A in Getting started guide for description how to determine serial port number):
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

For detailed instructions, see the appropriate board User's Guide.

Running the demo
================
The log below shows the output of the eRPC Matrix Multiply RTOS demo in the terminal window:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Primary core started
Get number from core1:
Got number: 4
Start normal rpc call example.
RPC call example finished.


Get number from core0:
getNumberFromCore0 function call: Actual number is 10
Got number: 10
Start nested rpc call example.
getNumberFromCore0 function call: Actual number is 10
RPC call example finished.


Get number from core1:
Got number: 15
Start normal rpc call example.
RPC call example finished.


Get number from core0:
getNumberFromCore0 function call: Actual number is 21
Got number: 21
Start nested rpc call example.
getNumberFromCore0 function call: Actual number is 21
RPC call example finished.


Get number from core1:
Got number: 27
Start normal rpc call example.
RPC call example finished.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Customization options
=====================

