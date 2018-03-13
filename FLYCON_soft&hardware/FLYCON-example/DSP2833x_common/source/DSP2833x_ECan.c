// TI File $Revision: /main/6 $
// Checkin $Date: May 7, 2007   16:26:05 $
//###########################################################################
//
// FILE:	DSP2833x_ECan.c
//
// TITLE:	DSP2833x Enhanced CAN Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP28 Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP28 Examples Include File




//---------------------------------------------------------------------------
// Example: InitECanGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as eCAN pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// Only one GPIO pin should be enabled for CANTXA/B operation.
// Only one GPIO pin shoudl be enabled for CANRXA/B operation.
// Comment out other unwanted lines.


void InitECanGpio(void)
{
//   InitECanaGpio();
#if (DSP28_ECANB)
   InitECanbGpio();
#endif // if DSP28_ECANB
}

void InitECanaGpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected CAN pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAPUD.bit.GPIO30 = 0;	    // Enable pull-up for GPIO30 (CANRXA)
//	GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;	    // Enable pull-up for GPIO18 (CANRXA)

	GpioCtrlRegs.GPAPUD.bit.GPIO31 = 0;	    // Enable pull-up for GPIO31 (CANTXA)
//	GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;	    // Enable pull-up for GPIO19 (CANTXA)

/* Set qualification for selected CAN pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.
// This will select asynch (no qualification) for the selected pins.

    GpioCtrlRegs.GPAQSEL2.bit.GPIO30 = 3;   // Asynch qual for GPIO30 (CANRXA)
//  GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3;   // Asynch qual for GPIO18 (CANRXA)


/* Configure eCAN-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAN functional pins.

	GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;	// Configure GPIO30 for CANRXA operation
//  GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 3;	// Configure GPIO18 for CANRXA operation
	GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;	// Configure GPIO31 for CANTXA operation
//  GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 3;	// Configure GPIO19 for CANTXA operation

    EDIS;
}

#if (DSP28_ECANB)
void InitECanbGpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected CAN pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;     // GPIO75通用的IO
    GpioCtrlRegs.GPADIR.bit.GPIO19 = 1;      // GPIO75配置为输出口
//	GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;	  // Enable pull-up for GPIO8  (CANTXB)
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;   // Enable pull-up for GPIO12 (CANTXB)
//    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pull-up for GPIO16 (CANTXB)
//  GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;   // Enable pull-up for GPIO20 (CANTXB)

//	GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;	  // Enable pull-up for GPIO10 (CANRXB)
    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;   // Enable pull-up for GPIO13 (CANRXB)
//    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // Enable pull-up for GPIO17 (CANRXB)
//  GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;   // Enable pull-up for GPIO21 (CANRXB)

/* Set qualification for selected CAN pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAQSEL1.bit.GPIO10 = 3; // Asynch qual for GPIO10 (CANRXB)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3; // Asynch qual for GPIO13 (CANRXB)
//    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch qual for GPIO17 (CANRXB)
//  GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 3; // Asynch qual for GPIO21 (CANRXB)

/* Configure eCAN-B pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAN functional pins.

//	GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 2;   // Configure GPIO8 for CANTXB operation
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 2;  // Configure GPIO12 for CANTXB operation
//    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 2;  // Configure GPIO16 for CANTXB operation
//  GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 3;  // Configure GPIO20 for CANTXB operation

//	GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 2;  // Configure GPIO10 for CANRXB operation
    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 2;  // Configure GPIO13 for CANRXB operation
//    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 2;  // Configure GPIO17 for CANRXB operation
//  GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 3;  // Configure GPIO21 for CANRXB operation

    GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;

    EDIS;
}
#endif // if DSP28_ECANB

/******************************************************/
/* Bit configuration parameters for 150 MHz SYSCLKOUT */
/******************************************************/
/*

The table below shows how BRP(reg) field must be changed to achieve different bit
rates with a BT of 15, for a 80% SP:
---------------------------------------------------------------
BT = 15, TSEG1(reg) = 10, TSEG2(reg) = 2, Sampling Point = 80%
---------------------------------------------------------------
1   Mbps : BRP(reg)+1 = 10 		: CAN clock = 15 MHz
500 kbps : BRP(reg)+1 = 20 		: CAN clock = 7.5 MHz
250 kbps : BRP(reg)+1 = 40 		: CAN clock = 3.75 MHz
125 kbps : BRP(reg)+1 = 80 		: CAN clock = 1.875 MHz
100 kbps : BRP(reg)+1 = 100 	: CAN clock = 1.5 MHz
50  kbps : BRP(reg)+1 = 200 	: CAN clock = 0.75 MHz

The table below shows how to achieve different sampling points with a BT of 15:
----------------------------------------------------------------------
Achieving desired SP by changing TSEG1(reg) & TSEG2(reg) with BT = 15
----------------------------------------------------------------------

TSEG1(reg) = 10, TSEG2(reg) = 2, SP = 80%
TSEG1(reg) = 9, TSEG2(reg) = 3, SP = 73%
TSEG1(reg) = 8, TSEG2(reg) = 4, SP = 66%
TSEG1(reg) = 7, TSEG2(reg) = 5, SP = 60%

The table below shows how BRP(reg) field must be changed to achieve different bit
rates with a BT of 10, for a 80% SP:
--------------------------------------------------------------
BT = 10, TSEG1(reg) = 6, TSEG2(reg) = 1, Sampling Point = 80%
--------------------------------------------------------------
1   Mbps : BRP(reg)+1 = 15 	: CAN clock = 10 MHz
500 kbps : BRP(reg)+1 = 30 	: CAN clock = 5 MHz
250 kbps : BRP(reg)+1 = 60 	: CAN clock = 2.5 MHz
125 kbps : BRP(reg)+1 = 120	: CAN clock = 1.25 MHz
100 kbps : BRP(reg)+1 = 150 : CAN clock = 1 MHz
50  kbps : BRP(reg)+1 = 300 : CAN clock = 0.5 MHz

*/

/***************************************************/
/* Bit configuration parameters for 100 MHz SYSCLKOUT*/
/***************************************************/
/*

The table below shows how BRP(reg) field must be changed to achieve different bit
rates with a BT of 10, for a 80% SP:
---------------------------------------------------
BT = 10, TSEG1 = 6, TSEG2 = 1, Sampling Point = 80%
---------------------------------------------------
1   Mbps : BRP(reg)+1 = 10 	: CAN clock = 10 MHz
500 kbps : BRP(reg)+1 = 20 	: CAN clock = 5 MHz
250 kbps : BRP(reg)+1 = 40 	: CAN clock = 2.5 MHz
125 kbps : BRP(reg)+1 = 80 	: CAN clock = 1.25 MHz
100 kbps : BRP(reg)+1 = 100 : CAN clock = 1 MHz
50  kbps : BRP(reg)+1 = 200 : CAN clock = 0.5 MHz

The table below shows how BRP(reg) field must be changed to achieve different bit
rates with a BT of 20:
---------------------------------------------------
BT = 20
---------------------------------------------------
1   Mbps : BRP(reg)+1 = 5
500 kbps : BRP(reg)+1 = 10
250 kbps : BRP(reg)+1 = 20
125 kbps : BRP(reg)+1 = 40
100 kbps : BRP(reg)+1 = 50
50  kbps : BRP(reg)+1 = 100

The table below shows how to achieve different sampling points with a BT of 20:
------------------------------------------------------------
Achieving desired SP by changing TSEG1 & TSEG2 with BT = 20
------------------------------------------------------------

TSEG1(reg) = 15, TSEG2(reg) = 2, SP = 85%
TSEG1(reg) = 14, TSEG2(reg) = 3, SP = 80%
TSEG1(reg) = 13, TSEG2(reg) = 4, SP = 75%
TSEG1(reg) = 12, TSEG2(reg) = 5, SP = 70%
TSEG1(reg) = 11, TSEG2(reg) = 6, SP = 65%
TSEG1(reg) = 10, TSEG2(reg) = 7, SP = 60%

Note: BRP(reg), TSEG1(reg) & TSEG2(reg) indicate the actual value that is written
 into the bit fields of the CAN control registers. These values are increased by 1
 by the CAN module when these registers are accessed.

*/

//===========================================================================
// End of file.
//===========================================================================

Uint32  ErrorCount;
Uint32  PassCount;
Uint32  MessageReceivedCount;
Uint32  TestMbox1 = 0;
Uint32  TestMbox2 = 0;
Uint32  TestMbox3 = 0;
void InitCan(void)		// Initialize eCAN-A module
{

	Uint16 j = 0;
	// Global variable for this example



	// eCAN control registers require 32-bit access.
	// If you want to write to a single bit, the compiler may break this
	// access into a 16-bit access.  One solution, that is presented here,
	// is to use a shadow register to force the 32-bit access.

	// Read the entire register into a shadow register.  This access
	// will be 32-bits.  Change the desired bit and copy the value back
	// to the eCAN register with a 32-bit write.

	// Configure the eCAN RX and TX pins for eCAN transmissions

    MessageReceivedCount = 0;
    ErrorCount = 0;
    PassCount = 0;
	struct ECAN_REGS ECanbShadow;

	EALLOW;
	ECanbShadow.CANTIOC.all = ECanbRegs.CANTIOC.all;
	ECanbShadow.CANTIOC.bit.TXFUNC = 1;
	ECanbRegs.CANTIOC.all = ECanbShadow.CANTIOC.all;

	ECanbShadow.CANRIOC.all = ECanbRegs.CANRIOC.all;
	ECanbShadow.CANRIOC.bit.RXFUNC = 1;
	ECanbRegs.CANRIOC.all = ECanbShadow.CANRIOC.all;
	EDIS;

	// Disable all Mailboxes
	// Since this write is to the entire register (instead of a bit
	// field) a shadow register is not required.
	ECanbRegs.CANME.all = 0;

	// Mailboxs can be written to 16-bits or 32-bits at a time
	// Write to the MSGID field of TRANSMIT mailboxes MBOX0 - 15
	ECanbMboxes.MBOX0.MSGID.all = 0x9555AAA0;
	ECanbMboxes.MBOX1.MSGID.all = 0x9555AAA1;
	ECanbMboxes.MBOX2.MSGID.all = 0x9555AAA2;
	ECanbMboxes.MBOX3.MSGID.all = 0x9555AAA3;
	ECanbMboxes.MBOX4.MSGID.all = 0x9555AAA4;
	ECanbMboxes.MBOX5.MSGID.all = 0x9555AAA5;
	ECanbMboxes.MBOX6.MSGID.all = 0x9555AAA6;
	ECanbMboxes.MBOX7.MSGID.all = 0x9555AAA7;
	ECanbMboxes.MBOX8.MSGID.all = 0x9555AAA8;
	ECanbMboxes.MBOX9.MSGID.all = 0x9555AAA9;
	ECanbMboxes.MBOX10.MSGID.all = 0x9555AAAA;
	ECanbMboxes.MBOX11.MSGID.all = 0x9555AAAB;
	ECanbMboxes.MBOX12.MSGID.all = 0x9555AAAC;
	ECanbMboxes.MBOX13.MSGID.all = 0x9555AAAD;
	ECanbMboxes.MBOX14.MSGID.all = 0x9555AAAE;
	ECanbMboxes.MBOX15.MSGID.all = 0x9555AAAF;

	// Write to the MSGID field of RECEIVE mailboxes MBOX16 - 31
	ECanbMboxes.MBOX16.MSGID.all = 0x9555AAA0;
	ECanbMboxes.MBOX17.MSGID.all = 0x9555AAA1;
	ECanbMboxes.MBOX18.MSGID.all = 0x9555AAA2;
	ECanbMboxes.MBOX19.MSGID.all = 0x9555AAA3;
	ECanbMboxes.MBOX20.MSGID.all = 0x9555AAA4;
	ECanbMboxes.MBOX21.MSGID.all = 0x9555AAA5;
	ECanbMboxes.MBOX22.MSGID.all = 0x9555AAA6;
	ECanbMboxes.MBOX23.MSGID.all = 0x9555AAA7;
	ECanbMboxes.MBOX24.MSGID.all = 0x9555AAA8;
	ECanbMboxes.MBOX25.MSGID.all = 0x9555AAA9;
	ECanbMboxes.MBOX26.MSGID.all = 0x9555AAAA;
	ECanbMboxes.MBOX27.MSGID.all = 0x9555AAAB;
	ECanbMboxes.MBOX28.MSGID.all = 0x9555AAAC;
	ECanbMboxes.MBOX29.MSGID.all = 0x9555AAAD;
	ECanbMboxes.MBOX30.MSGID.all = 0x9555AAAE;
	ECanbMboxes.MBOX31.MSGID.all = 0x9555AAAF;

	// Configure Mailboxes 0-15 as Tx, 16-31 as Rx
	// Since this write is to the entire register (instead of a bit
	// field) a shadow register is not required.
	ECanbRegs.CANMD.all = 0xFFFF0000;

	// Enable all Mailboxes */
	// Since this write is to the entire register (instead of a bit
	// field) a shadow register is not required.
	ECanbRegs.CANME.all = 0xFFFFFFFF;

	// Specify that 8 bits will be sent/received
	ECanbMboxes.MBOX0.MSGCTRL.bit.DLC = 8;
	ECanbMboxes.MBOX1.MSGCTRL.bit.DLC = 8;
	ECanbMboxes.MBOX2.MSGCTRL.bit.DLC = 8;
	ECanbMboxes.MBOX3.MSGCTRL.bit.DLC = 8;
	ECanbMboxes.MBOX4.MSGCTRL.bit.DLC = 8;
	ECanbMboxes.MBOX5.MSGCTRL.bit.DLC = 8;
	ECanbMboxes.MBOX6.MSGCTRL.bit.DLC = 8;
	ECanbMboxes.MBOX7.MSGCTRL.bit.DLC = 8;
	ECanbMboxes.MBOX8.MSGCTRL.bit.DLC = 8;
	ECanbMboxes.MBOX9.MSGCTRL.bit.DLC = 8;
	ECanbMboxes.MBOX10.MSGCTRL.bit.DLC = 8;
	ECanbMboxes.MBOX11.MSGCTRL.bit.DLC = 8;
	ECanbMboxes.MBOX12.MSGCTRL.bit.DLC = 8;
	ECanbMboxes.MBOX13.MSGCTRL.bit.DLC = 8;
	ECanbMboxes.MBOX14.MSGCTRL.bit.DLC = 8;
	ECanbMboxes.MBOX15.MSGCTRL.bit.DLC = 8;

	// No remote frame is requested
	// Since RTR bit is undefined upon reset,
	// it must be initialized to the proper value
	ECanbMboxes.MBOX0.MSGCTRL.bit.RTR = 0;
	ECanbMboxes.MBOX1.MSGCTRL.bit.RTR = 0;
	ECanbMboxes.MBOX2.MSGCTRL.bit.RTR = 0;
	ECanbMboxes.MBOX3.MSGCTRL.bit.RTR = 0;
	ECanbMboxes.MBOX4.MSGCTRL.bit.RTR = 0;
	ECanbMboxes.MBOX5.MSGCTRL.bit.RTR = 0;
	ECanbMboxes.MBOX6.MSGCTRL.bit.RTR = 0;
	ECanbMboxes.MBOX7.MSGCTRL.bit.RTR = 0;
	ECanbMboxes.MBOX8.MSGCTRL.bit.RTR = 0;
	ECanbMboxes.MBOX9.MSGCTRL.bit.RTR = 0;
	ECanbMboxes.MBOX10.MSGCTRL.bit.RTR = 0;
	ECanbMboxes.MBOX11.MSGCTRL.bit.RTR = 0;
	ECanbMboxes.MBOX12.MSGCTRL.bit.RTR = 0;
	ECanbMboxes.MBOX13.MSGCTRL.bit.RTR = 0;
	ECanbMboxes.MBOX14.MSGCTRL.bit.RTR = 0;
	ECanbMboxes.MBOX15.MSGCTRL.bit.RTR = 0;

	// Write to the mailbox RAM field of MBOX0 - 15
	ECanbMboxes.MBOX0.MDL.all = 0x9555AAA0;
	ECanbMboxes.MBOX0.MDH.all = 0x89ABCDEF;

	ECanbMboxes.MBOX1.MDL.all = 0x9555AAA1;
	ECanbMboxes.MBOX1.MDH.all = 0x89ABCDEF;

	ECanbMboxes.MBOX2.MDL.all = 0x9555AAA2;
	ECanbMboxes.MBOX2.MDH.all = 0x89ABCDEF;

	ECanbMboxes.MBOX3.MDL.all = 0x9555AAA3;
	ECanbMboxes.MBOX3.MDH.all = 0x89ABCDEF;

	ECanbMboxes.MBOX4.MDL.all = 0x9555AAA4;
	ECanbMboxes.MBOX4.MDH.all = 0x89ABCDEF;

	ECanbMboxes.MBOX5.MDL.all = 0x9555AAA5;
	ECanbMboxes.MBOX5.MDH.all = 0x89ABCDEF;

	ECanbMboxes.MBOX6.MDL.all = 0x9555AAA6;
	ECanbMboxes.MBOX6.MDH.all = 0x89ABCDEF;

	ECanbMboxes.MBOX7.MDL.all = 0x9555AAA7;
	ECanbMboxes.MBOX7.MDH.all = 0x89ABCDEF;

	ECanbMboxes.MBOX8.MDL.all = 0x9555AAA8;
	ECanbMboxes.MBOX8.MDH.all = 0x89ABCDEF;

	ECanbMboxes.MBOX9.MDL.all = 0x9555AAA9;
	ECanbMboxes.MBOX9.MDH.all = 0x89ABCDEF;

	ECanbMboxes.MBOX10.MDL.all = 0x9555AAAA;
	ECanbMboxes.MBOX10.MDH.all = 0x89ABCDEF;

	ECanbMboxes.MBOX11.MDL.all = 0x9555AAAB;
	ECanbMboxes.MBOX11.MDH.all = 0x89ABCDEF;

	ECanbMboxes.MBOX12.MDL.all = 0x9555AAAC;
	ECanbMboxes.MBOX12.MDH.all = 0x89ABCDEF;

	ECanbMboxes.MBOX13.MDL.all = 0x9555AAAD;
	ECanbMboxes.MBOX13.MDH.all = 0x89ABCDEF;

	ECanbMboxes.MBOX14.MDL.all = 0x9555AAAE;
	ECanbMboxes.MBOX14.MDH.all = 0x89ABCDEF;

	ECanbMboxes.MBOX15.MDL.all = 0x9555AAAF;
	ECanbMboxes.MBOX15.MDH.all = 0x89ABCDEF;

	// Since this write is to the entire register (instead of a bit
	// field) a shadow register is not required.
	EALLOW;
	ECanbRegs.CANMIM.all = 0xFFFFFFFF;

	// Request permission to change the configuration registers
	ECanbShadow.CANMC.all = ECanbRegs.CANMC.all;
	ECanbShadow.CANMC.bit.CCR = 1;
	ECanbRegs.CANMC.all = ECanbShadow.CANMC.all;
	EDIS;

	// Wait until the CPU has been granted permission to change the
	// configuration registers
	// Wait for CCE bit to be set..
	do
	{
	  ECanbShadow.CANES.all = ECanbRegs.CANES.all;
	} while(ECanbShadow.CANES.bit.CCE != 1 );

	// Configure the eCAN timing
	EALLOW;
	ECanbShadow.CANBTC.all = ECanbRegs.CANBTC.all;

	ECanbShadow.CANBTC.bit.BRPREG = 9;    // (BRPREG + 1) = 10 feeds a 15 MHz CAN clock
	ECanbShadow.CANBTC.bit.TSEG2REG = 5 ; // to the CAN module. (150 / 10 = 15)
	ECanbShadow.CANBTC.bit.TSEG1REG = 7;  // Bit time = 15
	ECanbRegs.CANBTC.all = ECanbShadow.CANBTC.all;

	ECanbShadow.CANMC.all = ECanbRegs.CANMC.all;
	ECanbShadow.CANMC.bit.CCR = 0;
	ECanbRegs.CANMC.all = ECanbShadow.CANMC.all;
	EDIS;

	// Wait until the CPU no longer has permission to change the
	// configuration registers
	do
	{
	  ECanbShadow.CANES.all = ECanbRegs.CANES.all;
	} while(ECanbShadow.CANES.bit.CCE != 0 );

	// Configure the eCAN for self test mode
	// Enable the enhanced features of the eCAN.
	EALLOW;
	ECanbShadow.CANMC.all = ECanbRegs.CANMC.all;
	ECanbShadow.CANMC.bit.STM = 0;    // 自测模式
//	ECanbShadow.CANMC.bit.STM = 0;    // 正常模式
	ECanbShadow.CANMC.bit.SCB = 1;    // eCAN mode (reqd to access 32 mailboxes)
	ECanbRegs.CANMC.all = ECanbShadow.CANMC.all;
	EDIS;
    // Begin transmitting
    for(;;)
    {

       ECanbRegs.CANTRS.all = 0x0000FFFF;  // Set TRS for all transmit mailboxes
       while(ECanbRegs.CANTA.all != 0x0000FFFF ) {}  // Wait for all TAn bits to be set..
       ECanbRegs.CANTA.all = 0x0000FFFF;   // Clear all TAn
       MessageReceivedCount++;

       //Read from Receive mailboxes and begin checking for data */
       for(j=0; j<16; j++)         // Read & check 16 mailboxes
       {
          mailbox_read(j);         // This func reads the indicated mailbox data
          mailbox_check(TestMbox1,TestMbox2,TestMbox3); // Checks the received data
       }

       if(MessageReceivedCount > 100)
       {
	      if(ErrorCount == 0)
		  {
			asm("      ESTOP0"); // OK
		  }
		  else
		  {
			asm("      ESTOP0"); // ERROR
		  }
       }
    }

}

void mailbox_read(int16 MBXnbr)
{
   volatile struct MBOX *Mailbox;
   Mailbox = &ECanbMboxes.MBOX0 + MBXnbr;
   TestMbox1 = Mailbox->MDL.all; // = 0x9555AAAn (n is the MBX number)
   TestMbox2 = Mailbox->MDH.all; // = 0x89ABCDEF (a constant)
   TestMbox3 = Mailbox->MSGID.all;// = 0x9555AAAn (n is the MBX number)

} // MSGID of a rcv MBX is transmitted as the MDL data.


void mailbox_check(int32 T1, int32 T2, int32 T3)
{
    if((T1 != T3) || ( T2 != 0x89ABCDEF))
    {
       ErrorCount++;
    }
    else
    {
       PassCount++;
    }
}
