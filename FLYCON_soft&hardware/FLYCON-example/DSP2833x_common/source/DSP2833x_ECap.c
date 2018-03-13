// TI File $Revision: /main/2 $
// Checkin $Date: March 15, 2007   16:54:36 $
//###########################################################################
//
// FILE:   DSP2833x_ECap.c
//
// TITLE:  DSP2833x eCAP Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

//---------------------------------------------------------------------------
// InitECap:
//---------------------------------------------------------------------------
// This function initializes the eCAP(s) to a known state.
//
void InitECap(void)
{
   // Initialize eCAP1/2/3

   //tbd...

}

//---------------------------------------------------------------------------
// Example: InitECapGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as ECAP pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// For each eCAP peripheral
// Only one GPIO pin should be enabled for ECAP operation.
// Comment out other unwanted lines.

void InitECapGpio()
{
#if DSP28_ECAP1
   InitECap1Gpio();
#endif // endif DSP28_ECAP1
#if (DSP28_ECAP2)
   InitECap2Gpio();
#endif // endif DSP28_ECAP2
#if (DSP28_ECAP3)
   InitECap3Gpio();
#endif // endif DSP28_ECAP3
#if (DSP28_ECAP4)
   InitECap4Gpio();
#endif // endif DSP28_ECAP4
//#if (DSP28_ECAP5)
   InitECap5Gpio();
//#endif // endif DSP28_ECAP5
//#if (DSP28_ECAP6)
   InitECap6Gpio();
//#endif // endif DSP28_ECAP6
}
#if DSP28_ECAP1
void InitECap1Gpio(void)
{


   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;      // Enable pull-up on GPIO5 (CAP1)
   GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;     // Enable pull-up on GPIO24 (CAP1)
// GpioCtrlRegs.GPBPUD.bit.GPIO34 = 0;     // Enable pull-up on GPIO34 (CAP1)


// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAQSEL1.bit.GPIO5 = 0;    // Synch to SYSCLKOUT GPIO5 (CAP1)
   GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0;   // Synch to SYSCLKOUT GPIO24 (CAP1)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO34 = 0;   // Synch to SYSCLKOUT GPIO34 (CAP1)

/* Configure eCAP-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP1 functional pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 3;     // Configure GPIO5 as CAP1
   GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 1;    // Configure GPIO24 as CAP1
// GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 1;    // Configure GPIO24 as CAP1

    EDIS;
}
#endif // endif DSP28_ECAP1

#if DSP28_ECAP2
void InitECap2Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;     // Enable pull-up on GPIO7 (CAP2)
// GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;    // Enable pull-up on GPIO25 (CAP2)
// GpioCtrlRegs.GPBPUD.bit.GPIO37 = 0;    // Enable pull-up on GPIO37 (CAP2)

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 0;    // Synch to SYSCLKOUT GPIO7 (CAP2)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 0;   // Synch to SYSCLKOUT GPIO25 (CAP2)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO37 = 0;   // Synch to SYSCLKOUT GPIO37 (CAP2)

/* Configure eCAP-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP2 functional pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 3;    // Configure GPIO7 as CAP2
// GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 1;   // Configure GPIO25 as CAP2
// GpioCtrlRegs.GPBMUX1.bit.GPIO37 = 3;   // Configure GPIO37 as CAP2

    EDIS;
}
#endif // endif DSP28_ECAP2

#if DSP28_ECAP3
void InitECap3Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;      // Enable pull-up on GPIO9 (CAP3)
// GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;     // Enable pull-up on GPIO26 (CAP3)

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO9 = 0;    // Synch to SYSCLKOUT GPIO9 (CAP3)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 0;   // Synch to SYSCLKOUT GPIO26 (CAP3)

/* Configure eCAP-3 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP3 functional pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 3;     // Configure GPIO9 as CAP3
// GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 1;    // Configure GPIO26 as CAP3

    EDIS;
}
#endif // endif DSP28_ECAP3


#if DSP28_ECAP4
void InitECap4Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;   // Enable pull-up on GPIO11 (CAP4)
// GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;   // Enable pull-up on GPIO27 (CAP4)

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 0; // Synch to SYSCLKOUT GPIO11 (CAP4)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 0; // Synch to SYSCLKOUT GPIO27 (CAP4)

/* Configure eCAP-4 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAP4 functional pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 3;  // Configure GPIO11 as CAP4
// GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 1;  // Configure GPIO27 as CAP4

    EDIS;
}
#endif // endif DSP28_ECAP4


#if DSP28_ECAP5
void InitECap5Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//   GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;     // Enable pull-up on GPIO3 (CAP5)
	 GpioCtrlRegs.GPBPUD.bit.GPIO48 = 0;    // Enable pull-up on GPIO48 (CAP5)

	// Inputs are synchronized to SYSCLKOUT by default.
	// Comment out other unwanted lines.

	//   GpioCtrlRegs.GPAQSEL1.bit.GPIO3 = 0;  // Synch to SYSCLKOUT GPIO3 (CAP5)
	 GpioCtrlRegs.GPBQSEL2.bit.GPIO48 = 0; // Synch to SYSCLKOUT GPIO48 (CAP5)

	/* Configure eCAP-5 pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be eCAP5 functional pins.
	// Comment out other unwanted lines.

	//   GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 2;   // Configure GPIO3 as CAP5
	 GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 1;  // Configure GPIO48 as CAP5

    EDIS;
}
#endif // endif DSP28_ECAP5


#if DSP28_ECAP6
void InitECap6Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

	//   GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;     // Enable pull-up on GPIO1 (CAP6)
	 GpioCtrlRegs.GPBPUD.bit.GPIO49 = 0;    // Enable pull-up on GPIO49 (CAP6)

	// Inputs are synchronized to SYSCLKOUT by default.
	// Comment out other unwanted lines.

	//   GpioCtrlRegs.GPAQSEL1.bit.GPIO1 = 0;  // Synch to SYSCLKOUT GPIO1 (CAP6)
	 GpioCtrlRegs.GPBQSEL2.bit.GPIO49 = 0; // Synch to SYSCLKOUT GPIO49 (CAP6)

	/* Configure eCAP-5 pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be eCAP6 functional pins.
	// Comment out other unwanted lines.

	//   GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 2;   // Configure GPIO1 as CAP6
	 GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 1;  // Configure GPIO49 as CAP6

    EDIS;
}
#endif // endif DSP28_ECAP6

void InitECAP()
{

//    SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1;//使能eCAP1
//    SysCtrlRegs.PCLKCR1.bit.ECAP2ENCLK = 1;//使能eCAP2
//    SysCtrlRegs.PCLKCR1.bit.ECAP3ENCLK = 1;//使能eCAP3
//    SysCtrlRegs.PCLKCR1.bit.ECAP4ENCLK = 1;//使能eCAP4
    SysCtrlRegs.PCLKCR1.bit.ECAP5ENCLK = 1;//使能eCAP5
    SysCtrlRegs.PCLKCR1.bit.ECAP6ENCLK = 1;//使能eCAP6
    IER |= M_INT4;//
//    PieCtrlRegs.PIEIER4.bit.INTx1 = 1;
    ECap1Regs.ECEINT.all = 0x0000;             // Disable all capture interrupts
    ECap1Regs.ECCLR.all = 0xFFFF;              // Clear all CAP interrupt flags
    ECap1Regs.ECCTL1.bit.CAPLDEN = 0;          // Disable CAP1-CAP4 register loads
    ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;        // Make sure the counter is stopped
    SetCap5();
    SetCap6();

}
#define EC_RISING     0           //上升沿电平值
#define EC_FALLING    1            //下降沿电平值
#define EC_ABS_MODE   0            //在CAPx事件中不重置计数器
#define EC_ENABLE     1            //使能在捕获事件中加载CAP1-4寄存器的时间
#define EC_DIV1       00000      //输入信号分频选择 不分频
#define EC_CAP_MODE   0            //ECAP工作于捕获工作模式
#define EC_CONTINUOUS 0            //0为连续模式  1为单次模式
#define EC_SYNCO_DIS  2             //同步输出选择：  10、11屏蔽同步信号输出
#define EC_DISABLE    0            //屏蔽同步输入操作
#define EC_RUN        1            //1计数器启动    0计数器停止


#define EC_RISING     0           //上升沿电平值
#define EC_FALLING    1            //下降沿电平值
#define EC_ABS_MODE   0            //在CAPx事件中不重置计数器
#define EC_ENABLE     1            //使能在捕获事件中加载CAP1-4寄存器的时间
#define EC_DIV1       00000      //输入信号分频选择 不分频
#define EC_CAP_MODE   0            //ECAP工作于捕获工作模式
#define EC_CONTINUOUS 0            //0为连续模式  1为单次模式
#define EC_SYNCO_DIS  2             //同步输出选择：  10、11屏蔽同步信号输出
#define EC_DISABLE    0            //屏蔽同步输入操作
#define EC_RUN        1            //1计数器启动    0计数器停止

void SetCap5()
{
    ECap5Regs.ECCTL1.bit.CAP1POL = EC_RISING;             //一级事件捕捉上升沿
    ECap5Regs.ECCTL1.bit.CAP2POL = EC_RISING;             //二级事件捕捉上升沿
    ECap5Regs.ECCTL1.bit.CAP3POL = EC_RISING;             //三级事件捕捉上升沿
    ECap5Regs.ECCTL1.bit.CAP4POL = EC_RISING;             //四级事件捕捉上升沿
    ECap5Regs.ECCTL1.bit.CTRRST1 = EC_ABS_MODE;         //一级事件捕捉后不清零计数器
    ECap5Regs.ECCTL1.bit.CTRRST2 = EC_ABS_MODE;         //二级事件捕捉后不清零计数器
    ECap5Regs.ECCTL1.bit.CTRRST3 = EC_ABS_MODE;         //三级事件捕捉后不清零计数器
    ECap5Regs.ECCTL1.bit.CTRRST4 = EC_ABS_MODE;         //四级事件捕捉后不清零计数器
    ECap5Regs.ECCTL1.bit.CAPLDEN = EC_ENABLE;             //使能事件捕捉时捕捉寄存器装载计数器值
    ECap5Regs.ECCTL1.bit.PRESCALE = EC_DIV1;             //对外部信号不分频

    ECap5Regs.ECCTL2.bit.CAP_APWM = EC_CAP_MODE;         //捕捉模式ECAP
    ECap5Regs.ECCTL2.bit.CONT_ONESHT = EC_CONTINUOUS;     //连续模式
    ECap5Regs.ECCTL2.bit.SYNCO_SEL = EC_SYNCO_DIS;        //屏蔽同步信号输出
    ECap5Regs.ECCTL2.bit.SYNCI_EN = EC_DISABLE;            //屏蔽同步输入操作
    ECap5Regs.ECEINT.all=0x0000;                         //关闭所有 CAP 中断
    ECap5Regs.ECCLR.all=0xFFFF;                         //清除所有中断标志位
    ECap5Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;             //启动 CAP 计数器
    ECap5Regs.ECEINT.bit.CEVT4=1;                         //使能四级事件中断，即当发生第四次捕捉时进入中断
}

interrupt void ECap5_INT_ISR(void)    // ECAP-5
{
  // Insert ISR Code here
     Uint32 t1,t2,t3,t4,T1,T2;

     t1 = ECap5Regs.CAP1;
     t2 = ECap5Regs.CAP2;
     t3 = ECap5Regs.CAP3;
     t4 = ECap5Regs.CAP4;
     T1 = t2-t1;
     T2 = t4-t3;
  // To receive more interrupts from this PIE group, acknowledge this interrupt
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
     ECap5Regs.ECCLR.all=0xFFFF;                //clare all flag
}

void SetCap6()
{
    ECap6Regs.ECCTL1.bit.CAP1POL = EC_RISING;             //一级事件捕捉上升沿
    ECap6Regs.ECCTL1.bit.CAP2POL = EC_RISING;             //二级事件捕捉上升沿
    ECap6Regs.ECCTL1.bit.CAP3POL = EC_RISING;             //三级事件捕捉上升沿
    ECap6Regs.ECCTL1.bit.CAP4POL = EC_RISING;             //四级事件捕捉上升沿
    ECap6Regs.ECCTL1.bit.CTRRST1 = EC_ABS_MODE;         //一级事件捕捉后不清零计数器
    ECap6Regs.ECCTL1.bit.CTRRST2 = EC_ABS_MODE;         //二级事件捕捉后不清零计数器
    ECap6Regs.ECCTL1.bit.CTRRST3 = EC_ABS_MODE;         //三级事件捕捉后不清零计数器
    ECap6Regs.ECCTL1.bit.CTRRST4 = EC_ABS_MODE;         //四级事件捕捉后不清零计数器
    ECap6Regs.ECCTL1.bit.CAPLDEN = EC_ENABLE;             //使能事件捕捉时捕捉寄存器装载计数器值
    ECap6Regs.ECCTL1.bit.PRESCALE = EC_DIV1;             //对外部信号不分频

    ECap6Regs.ECCTL2.bit.CAP_APWM = EC_CAP_MODE;         //捕捉模式ECAP
    ECap6Regs.ECCTL2.bit.CONT_ONESHT = EC_CONTINUOUS;     //连续模式
    ECap6Regs.ECCTL2.bit.SYNCO_SEL = EC_SYNCO_DIS;        //屏蔽同步信号输出
    ECap6Regs.ECCTL2.bit.SYNCI_EN = EC_DISABLE;            //屏蔽同步输入操作
    ECap6Regs.ECEINT.all=0x0000;                         //关闭所有 CAP 中断
    ECap6Regs.ECCLR.all=0xFFFF;                         //清除所有中断标志位
    ECap6Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;             //启动 CAP 计数器
    ECap6Regs.ECEINT.bit.CEVT4=1;                         //使能四级事件中断，即当发生第四次捕捉时进入中断
}

interrupt void ECap6_INT_ISR(void)    // ECAP-6
{
  // Insert ISR Code here
     Uint32 t1,t2,t3,t4,T1,T2;

     t1 = ECap6Regs.CAP1;
     t2 = ECap6Regs.CAP2;
     t3 = ECap6Regs.CAP3;
     t4 = ECap6Regs.CAP4;
     T1 = t2-t1;
     T2 = t4-t3;
  // To receive more interrupts from this PIE group, acknowledge this interrupt
     PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
     ECap6Regs.ECCLR.all=0xFFFF;                //clare all flag
}

//===========================================================================
// End of file.
//===========================================================================
