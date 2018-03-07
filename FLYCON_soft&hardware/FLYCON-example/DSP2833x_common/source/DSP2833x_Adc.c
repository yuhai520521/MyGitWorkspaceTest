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
#define ADC_CKPS 0x3      // ADC module clock = HSPCLK/2*ADC_CKPS = 25.0MHz/(1*2) = 12.5MHz 2.//��HSPCLK���з�Ƶ���ADCģ��ʱ��Ƶ�ʣ�
#define ADC_SHCLK 0xf     // S/H width in ADC module periods = 16 ADC clocks 3.//���ò���ʱ�䴰��С��
//---------------------------------------------------------------------------
// InitAdc:
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
void InitAdc(void)
{
    extern void DSP28x_usDelay(Uint32 Count);


    // *IMPORTANT*
	// The ADC_cal function, which  copies the ADC calibration values from TI reserved
	// OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs automatically in the
	// Boot ROM. If the boot ROM code is bypassed during the debug process, the
	// following function MUST be called for the ADC to function according
	// to specification. The clocks to the ADC MUST be enabled before calling this
	// function.
	// See the device data manual and/or the ADC Reference
	// Manual for more information.

	    EALLOW;
		SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
		ADC_cal();
		EDIS;
		AdcRegs.ADCREFSEL.bit.REF_SEL = 0;  //ѡ���ڲ��ο�Դ��Ĭ�ϣ�
//		AdcRegs.ADCREFSEL.bit.REF_SEL = 1;  //ѡ���ⲿ�ο�Դ��2.048v��
//		AdcRegs.ADCREFSEL.bit.REF_SEL = 2;  //ѡ���ⲿ�ο�Դ��1.500v��
//		AdcRegs.ADCREFSEL.bit.REF_SEL = 3;  //ѡ���ⲿ�ο�Դ��1.024v��


    // To powerup the ADC the ADCENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap, reference circuitry, and ADC core.
    // Before the first conversion is performed a 5ms delay must be observed
	// after power up to give all analog circuits time to power up and settle

    // Please note that for the delay function below to operate correctly the
	// CPU_CLOCK_SPEED define statement in the DSP2833x_Examples.h file must
	// contain the correct CPU clock period in nanoseconds.

    AdcRegs.ADCTRL3.all = 0x00E0;  // Power up bandgap/reference/ADC circuits
    DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels
    // ADC������ʽ����
    AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;   //���ò���ʱ�䴰��С���˴�ACQ_PSʮ����15������ʱ�䴰��С=ADCLOCK*��15+1��
    AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;  //�ں�ʱ�ӷ�Ƶ����HSPCLK���з�Ƶ���ADCģ��ʱ��Ƶ��
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;         // 1ͨ��ģʽ
    AdcRegs.ADCTRL1.bit.CONT_RUN = 1;         // ��������ת��ģʽ
    AdcRegs.ADCTRL1.bit.SEQ_OVRD = 1;         // ʹ�����򸲸�
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0;             // A0Ϊ����ͨ��
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 1;             // A1Ϊ����ͨ��
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 2;             // A2Ϊ����ͨ��
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 3;             // A3Ϊ����ͨ��


    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0X3;          // ���ɼ�ͨ��������Ϊ�õ�A0\0A1\A2\A3�ĸ�ͨ����������ֵΪ3
}

void Adc_start(void)
{
	Uint16 array_index = 0;
	Uint16 SampleTable[10] = 0;

	while(AdcRegs.ADCST.bit.INT_SEQ1 == 0){}   // ��ѯת���Ƿ����
	AdcRegs.ADCST.bit.INT_SEQ2_CLR = 1;        // ����жϱ�־λ
	SampleTable[array_index++] = ((AdcRegs.ADCRESULT0)>>4);

}

//===========================================================================
// End of file.
//===========================================================================
