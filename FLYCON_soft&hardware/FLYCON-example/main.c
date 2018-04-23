#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include <math.h>

#define ADC_MODCLK 0x3 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3) = 25.0 MHz 1.//对系统时钟进行分频获得HSPCLK（高速外设时钟信号） 默认未分频时HSPCLK=SYSCLK/2；
//__interrupt void ECap5_INT_ISR(void);
//__interrupt void ECap6_INT_ISR(void);


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

   InitECanbGpio();

   InitECapGpio();

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

//   EPwmSetup();
//   InitECAP();

   init_mcbsp_spi();

   init_spi();

//   scia_init();
//   scib_init();
//   scic_init();
//   InitECanb();

//   Ad_Onechanneltime_Init();

//   ADIS16488_init();
//   ADIS16405_init();

//   InitCan();
//   sd_writedata();
// 中断服务地址重新映射
   EALLOW;
   PieVectTable.ECAP6_INT = & ECAP6_CTROVF_Isr;
   PieVectTable.ECAP5_INT = & ECAP5_CTROVF_Isr;
   EDIS;
   PieCtrlRegs.PIEIER4.bit.INTx6 = 1;         // 开启ECap6的PIE级中断
   PieCtrlRegs.PIEIER4.bit.INTx5 = 1;         // 开启ECap5的PIE级中断
   IER |= M_INT4;                             // 开启ECap的CPU级中断
   EINT;

//   uchar  q;
//   float BATT6S_VOLT,BATT_CURRENT,BATT2S_VOLT,SKY_SPEED;
//   uchar GPRMCBuffer[68];
//   GPS_INFO GPSData;
//   int16 temp = 0;
//   Uint16 PROD_ID;
//   sd_card_insertion();
   sd_writedata();
   while(1)
   	   {


//	   	   sd_card_insertion();
//	   	   Mcbspa_SPI_TX(0xF0);
//	   	   spi_xmit_byte(0x40);
//	   		Mcbspb_SPI_TX(0x7E00);
//	   		PROD_ID = Mcbspb_SPI_RX();

//	   	   ECap5_Cal();
//	   	   CheckSUM();
//	   	   q = scia_rx();
//	   	   q = SPI_RX(0xFF);
//	   	   scia_xmit(q);
//         GetGPRMC(GPRMCBuffer);
//	       ParseGPRMC(GPRMCBuffer,&GPSData);
//	   	   temp = DS18B20_ReadTemp();
//	   	   loop();

//	   	   BATT6S_VOLT = (Ad_Get(1)*3.0)/4096;
//	   	   BATT_CURRENT = (Ad_Get(0)*3.0)/4096;

//		   ADIS16405_data_conversion();
//		   DELAY_US(1000);
//	   	   data_conversion();

   	   }
}



