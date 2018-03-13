// TI File $Revision: /main/4 $
// Checkin $Date: July 30, 2007   14:15:53 $
//###########################################################################
//
// FILE:	DSP2833x_Adc.c
//
// TITLE:	DSP2833x ADC Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define ADC_usDELAY  5000L
#define ADC_CKPS 0x3      // ADC module clock = HSPCLK/2*ADC_CKPS = 25.0MHz/(1*2) = 12.5MHz 2.//对HSPCLK进行分频获得ADC模块时钟频率；
#define ADC_SHCLK 0xf     // S/H width in ADC module periods = 16 ADC clocks 3.//设置采样时间窗大小；
#define ADC_MODCLK 0x3 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3) = 25.0 MHz 1.//对系统时钟进行分频获得HSPCLK（高速外设时钟信号） 默认未分频时HSPCLK=SYSCLK/2
//---------------------------------------------------------------------------
// InitAdc:
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
void InitAdc(void)
{
    extern void DSP28x_usDelay(Uint32 Count);

    EALLOW;
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
	ADC_cal();
	EDIS;

	AdcRegs.ADCREFSEL.bit.REF_SEL = 0;  //选择内部参考源（默认）
//	AdcRegs.ADCREFSEL.bit.REF_SEL = 1;  //选择外部参考源（2.048v）
//	AdcRegs.ADCREFSEL.bit.REF_SEL = 2;  //选择外部参考源（1.500v）
//	AdcRegs.ADCREFSEL.bit.REF_SEL = 3;  //选择外部参考源（1.024v）
	AdcRegs.ADCTRL3.all = 0x00E0;  // Power up bandgap/reference/ADC circuits
	DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels
}

//---------------------------------------------------------------------------
// 单次转换模式
//---------------------------------------------------------------------------
void Ad_Onechanneltime_Init(void)
{
	EALLOW;
	SysCtrlRegs.HISPCP.all = ADC_MODCLK;
	// HSPCLK = SYSCLKOUT/ADC_MODCLK
	EDIS;
	InitAdc();         // For this example, init the ADC

	// Specific ADC setup for this example:
	AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;  // Sequential mode: Sample rate   = 1/[(2+ACQ_PS)*ADC
	 //clock in ns]
																					//  = 1/(3*40ns) =8.3MHz (for 150 MHz SYSCLKOUT)
										   //    = 1/(3*80ns) =4.17MHz (for 100 MHz SYSCLKOUT)
	   // If Simultaneous mode enabled: Sample rate = 1/[(3+ACQ_PS)*ADC clock in ns]
	AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;        // 1  级联模式

	AdcRegs.ADCTRL1.bit.CONT_RUN = 0;       //  启动停止模式
	AdcRegs.ADCTRL1.bit.SEQ_OVRD = 1;       // Enable Sequencer override feature

	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0x0;  // convert and store in 1 results registers
	DELAY_US(100);
}



//单通道单次转换0~7对应A0~A7，8~15对应B0~B7
Uint16  Ad_Get(Uint16 n)
{
	switch (n)
	{
		case 0:  AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;break;
		case 1:  AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;break;
		case 2:  AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;break;
		case 3:  AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;break;
		case 4:  AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4;break;
		case 5:  AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5;break;
		case 6:  AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6;break;
		case 7:  AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7;break;
		case 8:  AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x8;break;
		case 9:  AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x9;break;
		case 10: AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0x0A;break;
		case 11: AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0x0B;break;
		case 12: AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 0x0C;break;
		case 13: AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 0x0D;break;
		case 14: AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 0x0E;break;
		case 15: AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 0x0F;break;
		default :break;
	}

	//Start SEQ1
	AdcRegs.ADCTRL2.bit.SOC_SEQ1=1;
	while(AdcRegs.ADCST.bit.INT_SEQ1 == 0);
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;

	switch (n)
	{
		case 0: return ( (AdcRegs.ADCRESULT0)>>4);break;
		case 1: return ( (AdcRegs.ADCRESULT1)>>4);break;
		case 2: return ( (AdcRegs.ADCRESULT2)>>4);break;
		case 3: return ( (AdcRegs.ADCRESULT3)>>4);break;
		case 4:  return ( (AdcRegs.ADCRESULT4)>>4);break;
		case 5:  return ( (AdcRegs.ADCRESULT5)>>4);break;
		case 6:  return ( (AdcRegs.ADCRESULT6)>>4);break;
		case 7:  return ( (AdcRegs.ADCRESULT7)>>4);break;
		case 8:  return ( (AdcRegs.ADCRESULT8)>>4);break;
		case 9:  return ( (AdcRegs.ADCRESULT9)>>4);break;
		case 10: return ( (AdcRegs.ADCRESULT10)>>4);break;
		case 11: return ( (AdcRegs.ADCRESULT11)>>4);break;
		case 12: return ( (AdcRegs.ADCRESULT12)>>4);break;
		case 13: return ( (AdcRegs.ADCRESULT13)>>4);break;
		case 14: return ( (AdcRegs.ADCRESULT14)>>4);break;
		case 15: return ( (AdcRegs.ADCRESULT15)>>4);break;
		default: break;
	}
	return 0;
}

//---------------------------------------------------------------------------
// 连续转换模式
//---------------------------------------------------------------------------

void Ad_Contrun_Init(void)
{
	EALLOW;
		   SysCtrlRegs.HISPCP.all = ADC_MODCLK;  // HSPCLK = SYSCLKOUT/ADC_MODCLK
	EDIS;
	InitAdc();         // For this example, init the ADC
	// Specific ADC setup for this example:
	AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;   // Sequential mode: Sample rate   = 1/[(2+ACQ_PS)*ADC  //clock in ns]
					 // If Simultaneous mode enabled: Sample rate = 1/[(3+ACQ_PS)*ADC //clock in ns]
	AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;         // 1  级联模式
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0x1;   // 允许向CPU发出中断请求
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;
	AdcRegs.ADCTRL1.bit.CONT_RUN = 1;         // 连续模式
	AdcRegs.ADCTRL3.bit.SMODE_SEL= 0;          // 顺序采样
	AdcRegs.ADCTRL1.bit.SEQ_OVRD = 1;         // Enable Sequencer override feature
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0xF;   // 要转换的通道数
	AdcRegs.ADCCHSELSEQ1.all = 0x3210;        // Initialize all ADC channel
	AdcRegs.ADCCHSELSEQ2.all = 0x7654;        // 每个通道对应相应的结果寄存器
	AdcRegs.ADCCHSELSEQ3.all = 0xBA98;
	AdcRegs.ADCCHSELSEQ4.all = 0xFEDC;

	AdcRegs.ADCTRL2.bit.SOC_SEQ1=1;
	DELAY_US(100);
}

//级联顺序转换，根据初始化的通道数可以改变相应要获取的结果寄存器
void Ad_Contrun_Get(Uint16 *value)
{
    value[0] = ( (AdcRegs.ADCRESULT0)>>4);
    value[1] = ( (AdcRegs.ADCRESULT1)>>4);
    value[2] = ( (AdcRegs.ADCRESULT2)>>4);
    value[3] = ( (AdcRegs.ADCRESULT3)>>4);
    value[4] = ( (AdcRegs.ADCRESULT4)>>4);
    value[5] = ( (AdcRegs.ADCRESULT5)>>4);
    value[6] = ( (AdcRegs.ADCRESULT6)>>4);
    value[7] = ( (AdcRegs.ADCRESULT7)>>4);
    value[8] = ( (AdcRegs.ADCRESULT8)>>4);
    value[9] = ( (AdcRegs.ADCRESULT9)>>4);
    value[10] = ( (AdcRegs.ADCRESULT10)>>4);
    value[11] = ( (AdcRegs.ADCRESULT11)>>4);
    value[12] = ( (AdcRegs.ADCRESULT12)>>4);
    value[13] = ( (AdcRegs.ADCRESULT13)>>4);
    value[14] = ( (AdcRegs.ADCRESULT14)>>4);
    value[15] = ( (AdcRegs.ADCRESULT15)>>4);
}


//===========================================================================
// End of file.
//===========================================================================
