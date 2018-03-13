// TI File $Revision: /main/2 $
// Checkin $Date: March 1, 2007   16:06:07 $
//###########################################################################
//
// FILE:	DSP2833x_Sci.c
//
// TITLE:	DSP2833x SCI Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

//interrupt void sciaTxIsr(void);
//interrupt void sciaRxIsr(void);
//interrupt void scibTxIsr(void);
//interrupt void scibRxIsr(void);
//---------------------------------------------------------------------------
// InitSci: 
//---------------------------------------------------------------------------
// This function initializes the SCI(s) to a known state.
//
void InitSci(void)
{
	// Initialize SCI-A:

	//tbd...
 	

	// Initialize SCI-B:

	//tbd...
  
      // Initialize SCI-C:

      //tbd...
}	

//---------------------------------------------------------------------------
// Example: InitSciGpio: 
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as SCI pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 
// Caution: 
// Only one GPIO pin should be enabled for SCITXDA/B operation.
// Only one GPIO pin shoudl be enabled for SCIRXDA/B operation. 
// Comment out other unwanted lines.

void InitSciGpio()
{

   InitSciaGpio();
   InitScibGpio();
#if DSP28_SCIC
   InitScicGpio();
#endif // if DSP28_SCIC
}

void InitSciaGpio()
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled disabled by the user.  
// This will enable the pullups for the specified pins.

	GpioCtrlRegs.GPBPUD.bit.GPIO36 = 0;    // Enable pull-up for GPIO36 (SCIRXDA)
	GpioCtrlRegs.GPBPUD.bit.GPIO35 = 0;	   // Enable pull-up for GPIO35 (SCITXDA)

/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.
// This will select asynch (no qualification) for the selected pins.

	GpioCtrlRegs.GPBQSEL1.bit.GPIO36 = 3;  // Asynch input GPIO36 (SCIRXDA)

/* Configure SCI-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SCI functional pins.

	GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 1;   // Configure GPIO36 for SCIRXDA operation
	GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 1;   // Configure GPIO35 for SCITXDA operation

    EDIS;
}


#if DSP28_SCIC
void InitScicGpio()
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled disabled by the user.  
// This will enable the pullups for the specified pins.

	GpioCtrlRegs.GPBPUD.bit.GPIO62 = 0;    // Enable pull-up for GPIO62 (SCIRXDC)
	GpioCtrlRegs.GPBPUD.bit.GPIO63 = 0;	   // Enable pull-up for GPIO63 (SCITXDC)

/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.  
// This will select asynch (no qualification) for the selected pins.

	GpioCtrlRegs.GPBQSEL2.bit.GPIO62 = 3;  // Asynch input GPIO62 (SCIRXDC)

/* Configure SCI-C pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SCI functional pins.

	GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 1;   // Configure GPIO62 for SCIRXDC operation
	GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 1;   // Configure GPIO63 for SCITXDC operation
	
    EDIS;
}
#endif // if DSP28_SCIC 

void scia_init()
{
	SciaRegs.SCICCR.all = 0x0007; // no stop,no parity,no loopback,idle line mode and 8bits data.
	SciaRegs.SCICTL1.all = 0x0003; // 接收和发送使能
//	SciaRegs.SCIHBAUD = 0x01;
//	SciaRegs.SCILBAUD = 0xe7;  // 9600baud
	SciaRegs.SCIHBAUD = 0x00;
	SciaRegs.SCILBAUD = 0x28;  // 115200baud
//	SciaRegs.SCICCR.bit.LOOPBKENA = 1;
	SciaRegs.SCICTL2.all = 0x0003;  // 接收中断和发送中断使能

	SciaRegs.SCICTL1.bit.SWRESET = 1;
}

void scia_xmit(Uint16 a)           // 发送8位长度数据
{
	while (SciaRegs.SCICTL2.bit.TXRDY == 0);
    SciaRegs.SCITXBUF=a;
}

void scia_xmit16(Uint16 a)         // 发送16位长度数据
{
	while (SciaRegs.SCICTL2.bit.TXRDY == 0);
    SciaRegs.SCITXBUF=a>>8;
    SciaRegs.SCITXBUF=a&0xff;
}

Uint16 scia_rx(void)
{
	while (SciaRegs.SCIRXST.bit.RXRDY == 0){}
	SciaRegs.SCIRXBUF.all = SciaRegs.SCIRXBUF.all;
    return (SciaRegs.SCIRXBUF.all);
}

void scia_fifo_init()
{
    SciaRegs.SCIFFTX.all=0xE040;
    SciaRegs.SCIFFRX.all=0x204f;
    SciaRegs.SCIFFCT.all=0x0;
}


void scic_init()
{
	ScicRegs.SCICCR.all = 0x0017; // no stop,no parity,no loopback,idle line mode and 8bits data.
	ScicRegs.SCICTL1.all = 0x0003;
	ScicRegs.SCIHBAUD = 0x01;
	ScicRegs.SCILBAUD = 0xe7;  // 9600baud

	ScicRegs.SCICTL2.all = 0x0003;

	ScicRegs.SCICTL1.bit.SWRESET = 1;
}

void scic_xmit(Uint16 a)
{
	while (ScicRegs.SCICTL2.bit.TXRDY == 0);
    ScicRegs.SCITXBUF=a;
}

Uint16 scic_rx(void)
{
	while (ScicRegs.SCIRXST.bit.RXRDY == 0){}
	ScicRegs.SCIRXBUF.all = ScicRegs.SCIRXBUF.all;
    return (ScicRegs.SCIRXBUF.all);
}

//===========================================================================
// End of file.
//===========================================================================
