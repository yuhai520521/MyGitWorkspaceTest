// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:46:25 $
//###########################################################################
//
// FILE:	DSP2833x_Gpio.c
//
// TITLE:	DSP2833x General Purpose I/O Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

//---------------------------------------------------------------------------
// InitGpio: 
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known (default) state.
//
// For more details on configuring GPIO's as peripheral functions,
// refer to the individual peripheral examples and/or GPIO setup example. 
void InitGpio(void)
{
   EALLOW;
   
   // Each GPIO pin can be: 
   // a) a GPIO input/output
   // b) peripheral function 1
   // c) peripheral function 2
   // d) peripheral function 3
   // By default, all are GPIO Inputs 

   GpioCtrlRegs.GPCMUX1.bit.GPIO75 = 0;     // GPIO75通用的IO
   GpioCtrlRegs.GPCMUX2.bit.GPIO86 = 0;     // GPIO86通用的IO
   GpioCtrlRegs.GPCMUX2.bit.GPIO87 = 0;     // GPIO87通用的IO

   GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;     // GPIO51通用的IO
   GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0;     // GPIO51通用的IO
   GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0;     // GPIO51通用的IO
   GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0;     // GPIO51通用的IO

   GpioCtrlRegs.GPBDIR.bit.GPIO50 = 0;      // GPIO50配置为输入口
   GpioCtrlRegs.GPBPUD.bit.GPIO50 = 0;      //开启上拉
   GpioCtrlRegs.GPBDIR.bit.GPIO51 = 0;      // GPIO51配置为输入口
   GpioCtrlRegs.GPBPUD.bit.GPIO51 = 0;      //开启上拉
   GpioCtrlRegs.GPBDIR.bit.GPIO52 = 0;      // GPIO52配置为输入口
   GpioCtrlRegs.GPBPUD.bit.GPIO52 = 0;      //开启上拉
   GpioCtrlRegs.GPBDIR.bit.GPIO53 = 0;      // GPIO53配置为输入口
   GpioCtrlRegs.GPBPUD.bit.GPIO53 = 0;      //开启上拉

   GpioCtrlRegs.GPCDIR.bit.GPIO75 = 1;      // GPIO75配置为输出口
   GpioCtrlRegs.GPCDIR.bit.GPIO86 = 1;      // GPIO86配置为输出口
   GpioCtrlRegs.GPCDIR.bit.GPIO87 = 1;      // GPIO87配置为输出口


   EDIS;

}	
	
//===========================================================================
// End of file.
//===========================================================================
