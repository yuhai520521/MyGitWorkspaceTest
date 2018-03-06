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

   GpioCtrlRegs.GPCMUX1.bit.GPIO75 = 0;     // GPIO75ͨ�õ�IO
   GpioCtrlRegs.GPCMUX2.bit.GPIO86 = 0;     // GPIO86ͨ�õ�IO
   GpioCtrlRegs.GPCMUX2.bit.GPIO87 = 0;     // GPIO87ͨ�õ�IO

   GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;     // GPIO51ͨ�õ�IO
   GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0;     // GPIO51ͨ�õ�IO
   GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 0;     // GPIO51ͨ�õ�IO
   GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 0;     // GPIO51ͨ�õ�IO

   GpioCtrlRegs.GPBDIR.bit.GPIO50 = 0;      // GPIO50����Ϊ�����
   GpioCtrlRegs.GPBPUD.bit.GPIO50 = 0;      //��������
   GpioCtrlRegs.GPBDIR.bit.GPIO51 = 0;      // GPIO51����Ϊ�����
   GpioCtrlRegs.GPBPUD.bit.GPIO51 = 0;      //��������
   GpioCtrlRegs.GPBDIR.bit.GPIO52 = 0;      // GPIO52����Ϊ�����
   GpioCtrlRegs.GPBPUD.bit.GPIO52 = 0;      //��������
   GpioCtrlRegs.GPBDIR.bit.GPIO53 = 0;      // GPIO53����Ϊ�����
   GpioCtrlRegs.GPBPUD.bit.GPIO53 = 0;      //��������

   GpioCtrlRegs.GPCDIR.bit.GPIO75 = 1;      // GPIO75����Ϊ�����
   GpioCtrlRegs.GPCDIR.bit.GPIO86 = 1;      // GPIO86����Ϊ�����
   GpioCtrlRegs.GPCDIR.bit.GPIO87 = 1;      // GPIO87����Ϊ�����


   EDIS;

}	
	
//===========================================================================
// End of file.
//===========================================================================
