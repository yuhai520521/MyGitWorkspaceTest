// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:46:19 $
//###########################################################################
//
// FILE:   DSP2833x_EPwm.c
//
// TITLE:  DSP2833x ePWM Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File


#if (CPU_FRQ_150MHZ)
  #define CPU_CLK   150e6
#endif
#if (CPU_FRQ_100MHZ)
  #define CPU_CLK   100e6
#endif
#define PWM_CLK   50                // PWMƵ������50Hz

//#define SP        CPU_CLK/(2*PWM_CLK)
#define SQ        CPU_CLK/(2*128*PWM_CLK)
#define TBCTLVAL  0x200E              // Up-down cnt, timebase = SYSCLKOUT

//---------------------------------------------------------------------------
// InitEPwm: 
//---------------------------------------------------------------------------
// This function initializes the ePWM(s) to a known state.
//
void InitEPwm(void)
{
   // Initialize ePWM1/2/3/4/5/6

   //tbd...
 
}

//---------------------------------------------------------------------------
// Example: InitEPwmGpio: 
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as ePWM pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 

void InitEPwmGpio(void)
{
   InitEPwm1Gpio();
   InitEPwm2Gpio();
   InitEPwm3Gpio();
   InitEPwm4Gpio();
   InitEPwm5Gpio();
   InitEPwm6Gpio();
}

void InitEPwm1Gpio(void)
{
   EALLOW;
   
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;    // Enable pull-up on GPIO1 (EPWM1B)   
   
/* Configure ePWM-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM1 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B
   
    EDIS;
}

void InitEPwm2Gpio(void)
{
   EALLOW;
	
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;    // Enable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;    // Enable pull-up on GPIO3 (EPWM3B)

/* Configure ePWM-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM2 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B
   
    EDIS;
}

void InitEPwm3Gpio(void)
{
   EALLOW;
   
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    // Enable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO5 (EPWM3B)
       
/* Configure ePWM-3 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM3 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B
	
    EDIS;
}


void InitEPwm4Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWM4A)
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;    // Enable pull-up on GPIO7 (EPWM4B)

/* Configure ePWM-4 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM4 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B
	
    EDIS;
}

void InitEPwm5Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;    // Enable pull-up on GPIO8 (EPWM5A)
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;    // Enable pull-up on GPIO9 (EPWM5B)

/* Configure ePWM-5 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM5 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   // Configure GPIO8 as EPWM5A
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   // Configure GPIO9 as EPWM5B
	
    EDIS;
}

void InitEPwm6Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;    // Enable pull-up on GPIO10 (EPWM6A)
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;    // Enable pull-up on GPIO11 (EPWM6B)

/* Configure ePWM-6 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM6 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;   // Configure GPIO10 as EPWM6A
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;   // Configure GPIO11 as EPWM6B
	
    EDIS;
}


//---------------------------------------------------------------------------
// Example: InitEPwm:
//---------------------------------------------------------------------------


void EPwmSetup()
{
	   EPwm1Setup();
	   EPwm2Setup();
	   EPwm3Setup();
	   EPwm4Setup();
	   EPwm5Setup();
	   EPwm6Setup();
}

void EPwm1Setup()
{
    InitEPwm1Gpio();
    // ����TBģ��
	EPwm1Regs.TBSTS.all=0;
	EPwm1Regs.TBPHS.half.TBPHS=0;
	EPwm1Regs.TBCTR=0;
	// ����CCģ��
	EPwm1Regs.CMPCTL.all=0x50;        // Immediate mode for CMPA and CMPB
	EPwm1Regs.CMPA.half.CMPA =SQ/2;
	EPwm1Regs.CMPB=0;
	// ����AQģ��
	EPwm1Regs.AQCTLA.all=0x60;        // EPWMxA = 1 when CTR=CMPA and counter inc
	                                  // EPWMxA = 0 when CTR=CMPA and counter dec
	EPwm1Regs.AQCTLB.all=0;
	EPwm1Regs.AQSFRC.all=0;
	EPwm1Regs.AQCSFRC.all=0;
	// ����DBģ��
	EPwm1Regs.DBCTL.all=0xb;          // EPWMxB is inverted
	EPwm1Regs.DBRED=0;
	EPwm1Regs.DBFED=0;
	// ����TZģ��
	EPwm1Regs.TZSEL.all=0;
	EPwm1Regs.TZCTL.all=0;
	EPwm1Regs.TZEINT.all=0;
	EPwm1Regs.TZFLG.all=0;
	EPwm1Regs.TZCLR.all=0;
	EPwm1Regs.TZFRC.all=0;
	// ����ETģ��
	EPwm1Regs.ETSEL.all=9;            // Interrupt when TBCTR = 0x0000
	EPwm1Regs.ETPS.all=1;	          // Interrupt on first event
	EPwm1Regs.ETFLG.all=0;
	EPwm1Regs.ETCLR.all=0;
	EPwm1Regs.ETFRC.all=0;
	// ����PCģ��  ���ڼ���һ����Ƶ�����ź�
	EPwm1Regs.PCCTL.all=0;           // CHPEN=0 ����PWMն������

	EPwm1Regs.TBCTL.all=0x0010+TBCTLVAL;			// Enable Timer
	EPwm1Regs.TBCTL.bit.HSPCLKDIV=1;                // 2��Ƶ
	EPwm1Regs.TBCTL.bit.CLKDIV=6;                   // 64��Ƶ
	EPwm1Regs.TBPRD=SQ;

}

void EPwm2Setup()
{
    InitEPwm2Gpio();
	EPwm2Regs.TBSTS.all=0;
	EPwm2Regs.TBPHS.half.TBPHS=0;
	EPwm2Regs.TBCTR=0;

	EPwm2Regs.CMPCTL.all=0x50;        // Immediate mode for CMPA and CMPB
	EPwm2Regs.CMPA.half.CMPA =SQ/2;
	EPwm2Regs.CMPB=0;

	EPwm2Regs.AQCTLA.all=0x60;        // EPWMxA = 1 when CTR=CMPA and counter inc
	                                  // EPWMxA = 0 when CTR=CMPA and counter dec
	EPwm2Regs.AQCTLB.all=0;
	EPwm2Regs.AQSFRC.all=0;
	EPwm2Regs.AQCSFRC.all=0;

	EPwm2Regs.DBCTL.all=0xb;          // EPWMxB is inverted
	EPwm2Regs.DBRED=0;
	EPwm2Regs.DBFED=0;

	EPwm2Regs.TZSEL.all=0;
	EPwm2Regs.TZCTL.all=0;
	EPwm2Regs.TZEINT.all=0;
	EPwm2Regs.TZFLG.all=0;
	EPwm2Regs.TZCLR.all=0;
	EPwm2Regs.TZFRC.all=0;

	EPwm2Regs.ETSEL.all=9;            // Interrupt when TBCTR = 0x0000
	EPwm2Regs.ETPS.all=1;	          // Interrupt on first event
	EPwm2Regs.ETFLG.all=0;
	EPwm2Regs.ETCLR.all=0;
	EPwm2Regs.ETFRC.all=0;

	EPwm2Regs.PCCTL.all=0;

	EPwm2Regs.TBCTL.all=0x0010+TBCTLVAL;			// Enable Timer
	EPwm2Regs.TBCTL.bit.HSPCLKDIV=1;
	EPwm2Regs.TBCTL.bit.CLKDIV=6;
	EPwm2Regs.TBPRD=SQ;
//	EPwm2Regs.TBPRD=SP;

}

void EPwm3Setup()
{
    InitEPwm3Gpio();
	EPwm3Regs.TBSTS.all=0;
	EPwm3Regs.TBPHS.half.TBPHS=0;
	EPwm3Regs.TBCTR=0;

	EPwm3Regs.CMPCTL.all=0x50;        // Immediate mode for CMPA and CMPB
	EPwm3Regs.CMPA.half.CMPA = SQ*3/40;
	EPwm3Regs.CMPB=0;

	EPwm3Regs.AQCTLA.all=0x60;        // EPWMxA = 1 when CTR=CMPA and counter inc
	                                  // EPWMxA = 0 when CTR=CMPA and counter dec
	EPwm3Regs.AQCTLB.all=0;
	EPwm3Regs.AQSFRC.all=0;
	EPwm3Regs.AQCSFRC.all=0;

	EPwm3Regs.DBCTL.all=0xb;          // EPWMxB is inverted
	EPwm3Regs.DBRED=0;
	EPwm3Regs.DBFED=0;

	EPwm3Regs.TZSEL.all=0;
	EPwm3Regs.TZCTL.all=0;
	EPwm3Regs.TZEINT.all=0;
	EPwm3Regs.TZFLG.all=0;
	EPwm3Regs.TZCLR.all=0;
	EPwm3Regs.TZFRC.all=0;

	EPwm3Regs.ETSEL.all=9;            // Interrupt when TBCTR = 0x0000
	EPwm3Regs.ETPS.all=1;	          // Interrupt on first event
	EPwm3Regs.ETFLG.all=0;
	EPwm3Regs.ETCLR.all=0;
	EPwm3Regs.ETFRC.all=0;

	EPwm3Regs.PCCTL.all=0;

	EPwm3Regs.TBCTL.all=0x0010+TBCTLVAL;			// Enable Timer
	EPwm3Regs.TBCTL.bit.HSPCLKDIV=1;
	EPwm3Regs.TBCTL.bit.CLKDIV=6;
	EPwm3Regs.TBPRD=SQ;


}

void EPwm4Setup()
{
    InitEPwm4Gpio();
	EPwm4Regs.TBSTS.all=0;
	EPwm4Regs.TBPHS.half.TBPHS=0;
	EPwm4Regs.TBCTR=0;

	EPwm4Regs.CMPCTL.all=0x50;        // Immediate mode for CMPA and CMPB
	EPwm4Regs.CMPA.half.CMPA =SQ*3/40;
	EPwm4Regs.CMPB=0;

	EPwm4Regs.AQCTLA.all=0x60;        // EPWMxA = 1 when CTR=CMPA and counter inc
	                                  // EPWMxA = 0 when CTR=CMPA and counter dec
	EPwm4Regs.AQCTLB.all=0;
	EPwm4Regs.AQSFRC.all=0;
	EPwm4Regs.AQCSFRC.all=0;

	EPwm4Regs.DBCTL.all=0xb;          // EPWMxB is inverted
	EPwm4Regs.DBRED=0;
	EPwm4Regs.DBFED=0;

	EPwm4Regs.TZSEL.all=0;
	EPwm4Regs.TZCTL.all=0;
	EPwm4Regs.TZEINT.all=0;
	EPwm4Regs.TZFLG.all=0;
	EPwm4Regs.TZCLR.all=0;
	EPwm4Regs.TZFRC.all=0;

	EPwm4Regs.ETSEL.all=9;            // Interrupt when TBCTR = 0x0000
	EPwm4Regs.ETPS.all=1;	          // Interrupt on first event
	EPwm4Regs.ETFLG.all=0;
	EPwm4Regs.ETCLR.all=0;
	EPwm4Regs.ETFRC.all=0;

	EPwm4Regs.PCCTL.all=0;

	EPwm4Regs.TBCTL.all=0x0010+TBCTLVAL;			// Enable Timer
	EPwm4Regs.TBCTL.bit.HSPCLKDIV=1;
	EPwm4Regs.TBCTL.bit.CLKDIV=6;
	EPwm4Regs.TBPRD=SQ;
//	EPwm4Regs.TBPRD=SP;

}

void EPwm5Setup()
{
    InitEPwm5Gpio();
	EPwm5Regs.TBSTS.all=0;
	EPwm5Regs.TBPHS.half.TBPHS=0;
	EPwm5Regs.TBCTR=0;

	EPwm5Regs.CMPCTL.all=0x50;        // Immediate mode for CMPA and CMPB
	EPwm5Regs.CMPA.half.CMPA =SQ/2;
	EPwm5Regs.CMPB=0;

	EPwm5Regs.AQCTLA.all=0x60;        // EPWMxA = 1 when CTR=CMPA and counter inc
	                                  // EPWMxA = 0 when CTR=CMPA and counter dec
	EPwm5Regs.AQCTLB.all=0;
	EPwm5Regs.AQSFRC.all=0;
	EPwm5Regs.AQCSFRC.all=0;

	EPwm5Regs.DBCTL.all=0xb;          // EPWMxB is inverted
	EPwm5Regs.DBRED=0;
	EPwm5Regs.DBFED=0;

	EPwm5Regs.TZSEL.all=0;
	EPwm5Regs.TZCTL.all=0;
	EPwm5Regs.TZEINT.all=0;
	EPwm5Regs.TZFLG.all=0;
	EPwm5Regs.TZCLR.all=0;
	EPwm5Regs.TZFRC.all=0;

	EPwm5Regs.ETSEL.all=9;            // Interrupt when TBCTR = 0x0000
	EPwm5Regs.ETPS.all=1;	          // Interrupt on first event
	EPwm5Regs.ETFLG.all=0;
	EPwm5Regs.ETCLR.all=0;
	EPwm5Regs.ETFRC.all=0;

	EPwm5Regs.PCCTL.all=0;

	EPwm5Regs.TBCTL.all=0x0010+TBCTLVAL;			// Enable Timer
	EPwm5Regs.TBCTL.bit.HSPCLKDIV=1;
	EPwm5Regs.TBCTL.bit.CLKDIV=6;
	EPwm5Regs.TBPRD=SQ;
//	EPwm5Regs.TBPRD=SP;

}

void EPwm6Setup()
{
    InitEPwm6Gpio();
	EPwm6Regs.TBSTS.all=0;
	EPwm6Regs.TBPHS.half.TBPHS=0;
	EPwm6Regs.TBCTR=0;

	EPwm6Regs.CMPCTL.all=0x50;        // Immediate mode for CMPA and CMPB
	EPwm6Regs.CMPA.half.CMPA =SQ/2;
	EPwm6Regs.CMPB=0;

	EPwm6Regs.AQCTLA.all=0x60;        // EPWMxA = 1 when CTR=CMPA and counter inc
	                                  // EPWMxA = 0 when CTR=CMPA and counter dec
	EPwm6Regs.AQCTLB.all=0;
	EPwm6Regs.AQSFRC.all=0;
	EPwm6Regs.AQCSFRC.all=0;

	EPwm6Regs.DBCTL.all=0xb;          // EPWMxB is inverted
	EPwm6Regs.DBRED=0;
	EPwm6Regs.DBFED=0;

	EPwm6Regs.TZSEL.all=0;
	EPwm6Regs.TZCTL.all=0;
	EPwm6Regs.TZEINT.all=0;
	EPwm6Regs.TZFLG.all=0;
	EPwm6Regs.TZCLR.all=0;
	EPwm6Regs.TZFRC.all=0;

	EPwm6Regs.ETSEL.all=9;            // Interrupt when TBCTR = 0x0000
	EPwm6Regs.ETPS.all=1;	          // Interrupt on first event
	EPwm6Regs.ETFLG.all=0;
	EPwm6Regs.ETCLR.all=0;
	EPwm6Regs.ETFRC.all=0;

	EPwm6Regs.PCCTL.all=0;

	EPwm6Regs.TBCTL.all=0x0010+TBCTLVAL;			// Enable Timer
	EPwm6Regs.TBCTL.bit.HSPCLKDIV=1;
	EPwm6Regs.TBCTL.bit.CLKDIV=6;
	EPwm6Regs.TBPRD=SQ;
//	EPwm6Regs.TBPRD=SP;

}


//===========================================================================
// End of file.
//===========================================================================
