

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include <math.h>

#define ADC_MODCLK 0x3 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3) = 25.0 MHz 1.//对系统时钟进行分频获得HSPCLK（高速外设时钟信号） 默认未分频时HSPCLK=SYSCLK/2；

extern DS18B20_ReadTemp();

void main(void)
{

// Step 1. Initialize System Control:

   InitSysCtrl();
  // ADC工作时钟设置
   EALLOW;
   SysCtrlRegs.HISPCP.all = ADC_MODCLK;
   EDIS;


// Step 2. Initialize GPIO:

   InitGpio();

// For this example, only enable the GPIO for McBSP-A McBSP-B

   InitMcbspGpio();

// For this example, only enable the GPIO for SPIA
   InitSpiGpio();
// For this example, only enable the GPIO for SCI
   InitSciGpio();

   InitEPwmGpio();

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2833x_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2833x_DefaultIsr.c.
// This function is found in DSP2833x_PieVect.c.
   InitPieVectTable();

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2833x_InitPeripherals.c

//   InitEPwmTimer();
   EPwmSetup();

   init_mcbsp_spi();

   init_spi();

   scia_init();
   scib_init();
   scic_init();
   InitAdc();

//   ADIS16488_init();
//   ADIS16405_init();

   SetSPIPORT();

   Uint16  PROD_ID = 0;
   Uint16  SBUS_DATA = 0;
   uchar  q;
   GpioDataRegs.GPCCLEAR.bit.GPIO75 = 1;

   while(1)
   	   {
//	   	   CheckSUM();
//	   	   q = SPI_RX(0xFF);
//	   	   scia_xmit(q);
//
//	   	   PROD_ID = PROD_ID_RX();
//	       scib_xmit(0xaa);
//	       PROD_ID =  scic_rx();
//	       PROD_ID = temout();
//	       SBUS_DATA = scib_rx();

//	   	   GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;   // iSensor_CS拉低
//	   	   DELAY_US(1000);
////	   Mcbspb_SPI_TX(0x0200);
//		   DELAY_US(2000);
//		   PROD_ID = Mcbspb_SPI_RX();
//		   GpioDataRegs.GPASET.bit.GPIO27 = 1;   // iSensor_CS拉高
//		   DELAY_US(2000);
//		   scia_xmit16(PROD_ID);

		   ADIS16405_data_conversion();
//		   DELAY_US(1000);
////	   	   data_conversion();

   	   }
}



