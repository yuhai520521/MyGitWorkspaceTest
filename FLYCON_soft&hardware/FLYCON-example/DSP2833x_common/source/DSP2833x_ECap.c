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

#define EC_RISING     0           //�����ص�ƽֵ
#define EC_FALLING    1            //�½��ص�ƽֵ
#define EC_ABS_MODE   0            //��CAPx�¼��в����ü�����
#define EC_ENABLE     1            //ʹ���ڲ����¼��м���CAP1-4�Ĵ�����ʱ��
#define EC_DIV1       00000      //�����źŷ�Ƶѡ�� ����Ƶ
#define EC_CAP_MODE   0            //ECAP�����ڲ�����ģʽ
#define EC_CONTINUOUS 0            //0Ϊ����ģʽ  1Ϊ����ģʽ
#define EC_SYNCO_DIS  2             //ͬ�����ѡ��  10��11����ͬ���ź����
#define EC_DISABLE    0            //����ͬ���������
#define EC_RUN        1            //1����������    0������ֹͣ


#define EC_RISING     0           //�����ص�ƽֵ
#define EC_FALLING    1            //�½��ص�ƽֵ
#define EC_ABS_MODE   0            //��CAPx�¼��в����ü�����
#define EC_ENABLE     1            //ʹ���ڲ����¼��м���CAP1-4�Ĵ�����ʱ��
#define EC_DIV1       00000      //�����źŷ�Ƶѡ�� ����Ƶ
#define EC_CAP_MODE   0            //ECAP�����ڲ�����ģʽ
#define EC_CONTINUOUS 0            //0Ϊ����ģʽ  1Ϊ����ģʽ
#define EC_SYNCO_DIS  2             //ͬ�����ѡ��  10��11����ͬ���ź����
#define EC_DISABLE    0            //����ͬ���������
#define EC_RUN        1            //1����������    0������ֹͣ
#define EC_STOP       0            //1����������    0������ֹͣ

Uint16 ECap5TsctrOverflowCnt = 0;
Uint16 Ecap6TsctrOverflowCnt = 0;
//float fre = 0.0,duty = 0.0;
//Uint16 OvfCnt1 = 0,OvfCnt2 = 0,OvfCnt3 = 0;


void InitECAP()
{

//    SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1;//ʹ��eCAP1
//    SysCtrlRegs.PCLKCR1.bit.ECAP2ENCLK = 1;//ʹ��eCAP2
//    SysCtrlRegs.PCLKCR1.bit.ECAP3ENCLK = 1;//ʹ��eCAP3
//    SysCtrlRegs.PCLKCR1.bit.ECAP4ENCLK = 1;//ʹ��eCAP4
    SysCtrlRegs.PCLKCR1.bit.ECAP5ENCLK = 1;//ʹ��eCAP5
    SysCtrlRegs.PCLKCR1.bit.ECAP6ENCLK = 1;//ʹ��eCAP6

    SetCap5();
    SetCap6();

}


void SetCap5()
{
	// ECapģʽ
	ECap5Regs.ECEINT.all = 0x0000;                         //�ر����� CAP �ж�
	ECap5Regs.ECCTL2.bit.TSCTRSTOP = EC_STOP;             //ֹͣ CAP ������
	ECap5Regs.ECCTL1.bit.CAPLDEN = EC_ENABLE;             //ʹ���¼���׽ʱ��׽�Ĵ���װ�ؼ�����ֵ
    ECap5Regs.ECCTL1.bit.CAP1POL = EC_RISING;             //һ���¼���׽������
    ECap5Regs.ECCTL1.bit.CAP2POL = EC_FALLING;             //�����¼���׽������
    ECap5Regs.ECCTL1.bit.CAP3POL = EC_RISING;             //�����¼���׽������

    ECap5Regs.ECCTL2.bit.CAP_APWM = EC_CAP_MODE;         //��׽ģʽECAP
    ECap5Regs.ECCTL2.bit.STOP_WRAP = 2;                  // �������κ�ֹͣ
    ECap5Regs.ECCTL2.bit.CONT_ONESHT = 1;                // ����ģʽ
    ECap5Regs.ECCLR.all=0xFFFF;                           //��������жϱ�־λ
    ECap5Regs.ECEINT.bit.CTROVF = 1;
    ECap5Regs.ECCTL2.bit.REARM = 1;                      // ��λ������MOD4������
    ECap5Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;             //���� CAP ������

	// PWMģʽ
//	ECap5Regs.ECEINT.all=0x0000;                         //�ر����� CAP �ж�
//	ECap5Regs.ECCTL2.bit.TSCTRSTOP = EC_STOP;             //���� CAP ������
//	ECap5Regs.ECCTL2.bit.CAP_APWM = 1;         //��׽ģʽECAP
//	ECap5Regs.ECCTL2.bit.APWMPOL = 0;
//	ECap5Regs.CAP1 = (Uint32)(150.0e6/freset);
//	ECap5Regs.CAP2 = (Uint32)(dutyset*ECap5Regs.CAP1);
//    ECap5Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;             //���� CAP ������


}


void ECap5_Cal(void)    // ECAP-5
{
  // Insert ISR Code here
	float fre = 0.0,duty = 0.0;
	Uint16 OvfCnt1 = 0,OvfCnt2 = 0,OvfCnt3 = 0;
     Uint32 t1,t2,t3;
     while(ECap5Regs.ECFLG.bit.CEVT1!=1){}
     t1 = ECap5Regs.CAP1;
     OvfCnt1 = ECap5TsctrOverflowCnt;
     while(ECap5Regs.ECFLG.bit.CEVT2!=1){}
     t2 = ECap5Regs.CAP2;
     OvfCnt2 = ECap5TsctrOverflowCnt;
     while(ECap5Regs.ECFLG.bit.CEVT3!=1){}
     t3 = ECap5Regs.CAP3;
     OvfCnt3 = ECap5TsctrOverflowCnt;

     fre = 150.0e6/(4294967296.0L*(OvfCnt3-OvfCnt1)+t3-t1);
     duty = (4294967296.0L*(OvfCnt2-OvfCnt1)+t2-t1)/(4294967296.0L*(OvfCnt3-OvfCnt1)+t3-t1);
     ECap5TsctrOverflowCnt = 0;

     ECap5Regs.ECCLR.bit.CEVT1 = 1;
     ECap5Regs.ECCLR.bit.CEVT2 = 1;
     ECap5Regs.ECCLR.bit.CEVT3 = 1;
     ECap5Regs.ECCTL2.bit.REARM = 1;

}


void SetCap6()
{
	// ECapģʽ
	ECap6Regs.ECEINT.all = 0x0000;                         //�ر����� CAP �ж�
	ECap6Regs.ECCTL2.bit.TSCTRSTOP = EC_STOP;             //ֹͣ CAP ������
	ECap6Regs.ECCTL1.bit.CAPLDEN = EC_ENABLE;             //ʹ���¼���׽ʱ��׽�Ĵ���װ�ؼ�����ֵ
    ECap6Regs.ECCTL1.bit.CAP1POL = EC_RISING;             //һ���¼���׽������
    ECap6Regs.ECCTL1.bit.CAP2POL = EC_FALLING;             //�����¼���׽������
    ECap6Regs.ECCTL1.bit.CAP3POL = EC_RISING;             //�����¼���׽������

    ECap6Regs.ECCTL2.bit.CAP_APWM = EC_CAP_MODE;         //��׽ģʽECAP
    ECap6Regs.ECCTL2.bit.STOP_WRAP = 2;                  // �������κ�ֹͣ
    ECap6Regs.ECCTL2.bit.CONT_ONESHT = 1;                // ����ģʽ
    ECap6Regs.ECCLR.all=0xFFFF;                           //��������жϱ�־λ
    ECap6Regs.ECEINT.bit.CTROVF = 1;
    ECap6Regs.ECCTL2.bit.REARM = 1;                      // ��λ������MOD4������
    ECap6Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;             //���� CAP ������

	// PWMģʽ
//	ECap6Regs.ECEINT.all=0x0000;                         //�ر����� CAP �ж�
//	ECap6Regs.ECCTL2.bit.TSCTRSTOP = EC_STOP;             //���� CAP ������
//	ECap6Regs.ECCTL2.bit.CAP_APWM = 1;         //��׽ģʽECAP
//	ECap6Regs.ECCTL2.bit.APWMPOL = 0;
//	ECap6Regs.CAP1 = (Uint32)(150.0e6/freset);
//	ECap6Regs.CAP2 = (Uint32)(dutyset*ECap5Regs.CAP1);
//    ECap6Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;             //���� CAP ������

}


void ECap6_Cal(void)    // ECAP-6
{
  // Insert ISR Code here
	float fre = 0.0,duty = 0.0;
	Uint16 OvfCnt1 = 0,OvfCnt2 = 0,OvfCnt3 = 0;
     Uint32 t1,t2,t3;
     while(ECap6Regs.ECFLG.bit.CEVT1!=1){}
     t1 = ECap6Regs.CAP1;
     OvfCnt1 = Ecap6TsctrOverflowCnt;
     while(ECap6Regs.ECFLG.bit.CEVT2!=1){}
     t2 = ECap6Regs.CAP2;
     OvfCnt2 = Ecap6TsctrOverflowCnt;
     while(ECap6Regs.ECFLG.bit.CEVT3!=1){}
     t3 = ECap6Regs.CAP3;
     OvfCnt3 = Ecap6TsctrOverflowCnt;

     fre = 150.0e6/(4294967296.0L*(OvfCnt3-OvfCnt1)+t3-t1);
     duty = (4294967296.0L*(OvfCnt2-OvfCnt1)+t2-t1)/(4294967296.0L*(OvfCnt3-OvfCnt1)+t3-t1);
     Ecap6TsctrOverflowCnt = 0;

     ECap6Regs.ECCLR.bit.CEVT1 = 1;
     ECap6Regs.ECCLR.bit.CEVT2 = 1;
     ECap6Regs.ECCLR.bit.CEVT3 = 1;
     ECap6Regs.ECCTL2.bit.REARM = 1;

}

interrupt void ECAP5_CTROVF_Isr(void)
{
	ECap5TsctrOverflowCnt++;
	ECap5Regs.ECCLR.bit.CTROVF = 1;
	ECap5Regs.ECCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

}

interrupt void ECAP6_CTROVF_Isr(void)
{
	Ecap6TsctrOverflowCnt++;
	ECap6Regs.ECCLR.bit.CTROVF = 1;
	ECap6Regs.ECCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;

}



//===========================================================================
// End of file.
//===========================================================================
