  // TI File $Revision: /main/15 $
// Checkin $Date: September 20, 2007   14:47:41 $
//###########################################################################
//
// FILE:	DSP2833x_McBSP.c
//
// TITLE:	DSP2833x Device McBSP Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

//---------------------------------------------------------------------------
// MCBSP_INIT_DELAY determines the amount of CPU cycles in the 2 sample rate
// generator (SRG) cycles required for the Mcbsp initialization routine.
// MCBSP_CLKG_DELAY determines the amount of CPU cycles in the 2 clock
// generator (CLKG) cycles required for the Mcbsp initialization routine.
// For the functions defined in Mcbsp.c, MCBSP_INIT_DELAY and MCBSP_CLKG_DELAY
// are based off of either a 150 MHz SYSCLKOUT (default) or a 100 MHz SYSCLKOUT.
//
// CPU_FRQ_100MHZ and CPU_FRQ_150MHZ are defined in DSP2833x_Examples.h
//---------------------------------------------------------------------------

#if CPU_FRQ_150MHZ                                          // For 150 MHz SYSCLKOUT(default)
  #define CPU_SPD              150E6
  #define MCBSP_SRG_FREQ       CPU_SPD/4                    // SRG input is LSPCLK (SYSCLKOUT/4) for examples
#endif
#if CPU_FRQ_100MHZ                                          // For 100 MHz SYSCLKOUT
  #define CPU_SPD              100E6
  #define MCBSP_SRG_FREQ       CPU_SPD/4                    // SRG input is LSPCLK (SYSCLKOUT/4) for examples
#endif

#define MCBSP_INIT_DELAY     2*(CPU_SPD/MCBSP_SRG_FREQ)                  // # of CPU cycles in 2 SRG cycles-init delay
#define CLKGDV_VAL           0
#define MCBSP_CLKG_DELAY     2*(CPU_SPD/(MCBSP_SRG_FREQ/(1+CLKGDV_VAL))) // # of CPU cycles in 2 CLKG cycles-init delay
//---------------------------------------------------------------------------
// InitMcbsp:
//---------------------------------------------------------------------------
// This function initializes the McBSP to a known state.
//

void delay_loop(void);		// Delay function used for SRG initialization
void clkg_delay_loop(void); // Delay function used for CLKG initialization

void InitMcbsp(void)
{
	InitMcbspa();
	#if DSP28_MCBSPB
	  InitMcbspb();
	#endif               // end DSP28_MCBSPB
}

void InitMcbspa(void)
{
// McBSP-A register settings

    McbspaRegs.SPCR2.all=0x0000;		// Reset FS generator, sample rate generator & transmitter
	McbspaRegs.SPCR1.all=0x0000;		// Reset Receiver, Right justify word
	McbspaRegs.SPCR1.bit.DLB = 0;       // Enable loopback mode for test. Comment out for normal McBSP transfer mode.

	McbspaRegs.MFFINT.all=0x0;			// Disable all interrupts

    McbspaRegs.RCR2.all=0x0;			// Single-phase frame, 1 word/frame, No companding	(Receive)
    McbspaRegs.RCR1.all=0x0;

    McbspaRegs.XCR2.all=0x0;			// Single-phase frame, 1 word/frame, No companding	(Transmit)
    McbspaRegs.XCR1.all=0x0;

    McbspaRegs.PCR.bit.FSXM = 1;		// FSX generated internally, FSR derived from an external source
	McbspaRegs.PCR.bit.CLKXM = 1;		// CLKX generated internally, CLKR derived from an external source

    McbspaRegs.SRGR2.bit.CLKSM = 1;		// CLKSM=1 (If SCLKME=0, i/p clock to SRG is LSPCLK)
	McbspaRegs.SRGR2.bit.FPER = 31;		// FPER = 32 CLKG periods

    McbspaRegs.SRGR1.bit.FWID = 0;              // Frame Width = 1 CLKG period
    McbspaRegs.SRGR1.bit.CLKGDV = CLKGDV_VAL;	// CLKG frequency = LSPCLK/(CLKGDV+1)

    delay_loop();                // Wait at least 2 SRG clock cycles

    McbspaRegs.SPCR2.bit.GRST=1; // Enable the sample rate generator
	clkg_delay_loop();           // Wait at least 2 CLKG cycles
	McbspaRegs.SPCR2.bit.XRST=1; // Release TX from Reset
	McbspaRegs.SPCR1.bit.RRST=1; // Release RX from Reset
    McbspaRegs.SPCR2.bit.FRST=1; // Frame Sync Generator reset

}


#if (DSP28_MCBSPB)
void InitMcbspb(void)
{

// McBSP-B register settings

    McbspbRegs.SPCR2.all=0x0000;		// Reset FS generator, sample rate generator & transmitter
	McbspbRegs.SPCR1.all=0x0000;		// Reset Receiver, Right justify word
	McbspbRegs.SPCR1.bit.DLB = 0;       // Enable loopback mode for test. Comment out for normal McBSP transfer mode.

	McbspbRegs.MFFINT.all=0x0;			// Disable all interrupts

    McbspbRegs.RCR2.all=0x0;			// Single-phase frame, 1 word/frame, No companding	(Receive)
    McbspbRegs.RCR1.all=0x0;

    McbspbRegs.XCR2.all=0x0;			// Single-phase frame, 1 word/frame, No companding	(Transmit)
    McbspbRegs.XCR1.all=0x0;

    McbspbRegs.SRGR2.bit.CLKSM = 1;		// CLKSM=1 (If SCLKME=0, i/p clock to SRG is LSPCLK)
	McbspbRegs.SRGR2.bit.FPER = 31;		// FPER = 32 CLKG periods

    McbspbRegs.SRGR1.bit.FWID = 0;              // Frame Width = 1 CLKG period
    McbspbRegs.SRGR1.bit.CLKGDV = CLKGDV_VAL;	// CLKG frequency = LSPCLK/(CLKGDV+1)

   	McbspbRegs.PCR.bit.FSXM = 1;		// FSX generated internally, FSR derived from an external source
	McbspbRegs.PCR.bit.CLKXM = 1;		// CLKX generated internally, CLKR derived from an external source
    delay_loop();                // Wait at least 2 SRG clock cycles
    McbspbRegs.SPCR2.bit.GRST=1; // Enable the sample rate generator
	clkg_delay_loop();           // Wait at least 2 CLKG cycles
	McbspbRegs.SPCR2.bit.XRST=1; // Release TX from Reset
	McbspbRegs.SPCR1.bit.RRST=1; // Release RX from Reset
    McbspbRegs.SPCR2.bit.FRST=1; // Frame Sync Generator reset

}


#endif // end DSP28_MCBSPB

// McBSP-A Data Lengths
void InitMcbspa8bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=0;     // 8-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=0;     // 8-bit word
}

void InitMcbspa12bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=1;     // 12-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=1;     // 12-bit word
}

void InitMcbspa16bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=2;      // 16-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=2;      // 16-bit word
}

void InitMcbspa20bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=3;     // 20-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=3;     // 20-bit word
}

void InitMcbspa24bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=4;     // 24-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=4;     // 24-bit word
}

void InitMcbspa32bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=5;     // 32-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=5;     // 32-bit word
}

// McBSP-B Data Lengths
#if (DSP28_MCBSPB)

void InitMcbspb8bit(void)
{
    McbspbRegs.RCR1.bit.RWDLEN1=0;     // 8-bit word
    McbspbRegs.XCR1.bit.XWDLEN1=0;     // 8-bit word
}

void InitMcbspb12bit(void)
{
    McbspbRegs.RCR1.bit.RWDLEN1=1;     // 12-bit word
    McbspbRegs.XCR1.bit.XWDLEN1=1;     // 12-bit word
}

void InitMcbspb16bit(void)
{
    McbspbRegs.RCR1.bit.RWDLEN1=2;      // 16-bit word
    McbspbRegs.XCR1.bit.XWDLEN1=2;      // 16-bit word
}

void InitMcbspb20bit(void)
{
    McbspbRegs.RCR1.bit.RWDLEN1=3;     // 20-bit word
    McbspbRegs.XCR1.bit.XWDLEN1=3;     // 20-bit word
}

void InitMcbspb24bit(void)
{
    McbspbRegs.RCR1.bit.RWDLEN1=4;     // 24-bit word
    McbspbRegs.XCR1.bit.XWDLEN1=4;     // 24-bit word
}

void InitMcbspb32bit(void)
{
    McbspbRegs.RCR1.bit.RWDLEN1=5;     // 32-bit word
    McbspbRegs.XCR1.bit.XWDLEN1=5;     // 32-bit word
}

#endif //end DSP28_MCBSPB



void InitMcbspGpio(void)
{
	InitMcbspaGpio();
	InitMcbspbGpio();
}

void InitMcbspaGpio(void)
{
	EALLOW;

/* Configure McBSP-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be McBSP functional pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 2;	// GPIO20 is MDXA pin
	GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 2;	// GPIO21 is MDRA pin
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 2;	// GPIO22 is MCLKXA pin

    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;	// GPIO23 is SD_CS pin
	GpioCtrlRegs.GPADIR.bit.GPIO23 = 1;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;     // Enable pull-up on GPIO20 (MDXA)
	GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;     // Enable pull-up on GPIO21 (MDRA)
	GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;     // Enable pull-up on GPIO22 (MCLKXA)


/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.


    GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 3;   // Asynch input GPIO21 (MDRA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO22 = 3;   // Asynch input GPIO22 (MCLKXA)

//    GpioDataRegs.GPACLEAR.bit.GPIO23 = 1;   // SD_CS拉低

	EDIS;
}


void InitMcbspbGpio(void)
{
    EALLOW;
/* Configure McBSP-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be McBSP functional pins.
// Comment out other unwanted lines.


	GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 3;	// GPIO24 is MDXB pin (Comment as needed)
 	GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 3;	// GPIO25 is MDRB pin (Comment as needed)
 	GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 3;	// GPIO26 is MCLKXB pin (Comment as needed)


	GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;	// GPIO27 is iSensor_CS pin (Comment as needed)
	GpioCtrlRegs.GPADIR.bit.GPIO27 = 1;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.
	GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;	    // Enable pull-up on GPIO24 (MDXB) (Comment as needed)
	GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;	    // Enable pull-up on GPIO25 (MDRB) (Comment as needed)
 	GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;	    // Enable pull-up on GPIO26 (MCLKXB) (Comment as needed)
 	GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;	    // Enable pull-up on GPIO27 (MCLKXB) (Comment as needed)


/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.
    GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 3;   // Asynch input GPIO25 (MDRB) (Comment as needed)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 3;   // Asynch input GPIO26(MCLKXB) (Comment as needed)

    GpioDataRegs.GPASET.bit.GPIO27 = 1;   // iSensor_CS拉高
    DELAY_US(1000);
//    GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;   // iSensor_CS拉低
//    DELAY_US(1000);

   	EDIS;
}


void delay_loop(void)
{
    long      i;
    for (i = 0; i < MCBSP_INIT_DELAY; i++) {} //delay in McBsp init. must be at least 2 SRG cycles
}

void clkg_delay_loop(void)
{
    long      i;
    for (i = 0; i < MCBSP_CLKG_DELAY; i++) {} //delay in McBsp init. must be at least 2 SRG cycles
}

void init_mcbsp_spi()
{
	init_mcbspa_spi();
	init_mcbspb_spi();
}


void init_mcbspa_spi()
{


	//  复位McBSP
	    McbspaRegs.SPCR2.all=0x0000;		// Reset FS generator, sample rate generator & transmitter
		McbspaRegs.SPCR1.all=0x0000;		// Reset Receiver, Right justify word

	// 配置SPI模式0
	//    McbspaRegs.SPCR1.bit.CLKSTP = 0 or 1;     // 关闭时钟停止模式
	    McbspaRegs.SPCR1.bit.CLKSTP = 3;     // 开启时钟停止模式延时半周期
//	    McbspaRegs.SPCR1.bit.CLKSTP = 2;     // 开启时钟停止模式无延时
	    McbspaRegs.PCR.bit.CLKXP = 0;		 // CPOL = 0, CPHA = 1 rising edge
		McbspaRegs.PCR.bit.CLKRP = 0;        // Receive data on the rising edge of MCLKR
	//  配置主从模式
		McbspaRegs.PCR.bit.CLKXM = 1;        //配置为主机模式
	//  配置时钟为LSPCLK默认为150/4=37.5MHz
		McbspaRegs.PCR.bit.SCLKME = 0;
		McbspaRegs.SRGR2.bit.CLKSM = 1;
	//  配置传输波特率150/4/(49+1)=750KHz
		McbspaRegs.SRGR1.bit.CLKGDV= 49;
	//  配置帧同步信号
		McbspaRegs.PCR.bit.FSXM = 1;
		McbspaRegs.SRGR2.bit.FSGM = 0; 	 	 // CLKSM=1, FPER = 1 CLKG periods
	    McbspaRegs.PCR.bit.FSXP = 1;
	//  配置数据格式
	    McbspaRegs.RCR2.bit.RDATDLY = 1;      // FSX setup time 1 in master mode. 0 for slave mode (Receive)
	    McbspaRegs.RCR2.bit.RCOMPAND = 0;      // 不用压扩任何长度数据，先接收MSB
	//    McbspaRegs.RCR2.bit.RCOMPAND=1;      // 不用压扩8位长度数据，先接收LSB
	//    McbspaRegs.RCR2.bit.RCOMPAND = 2;      // 用u-律压扩8位长度数据，先接收MSB
	//    McbspaRegs.RCR2.bit.RCOMPAND = 3;      // 用A-律压扩8位长度数据，先接收MSB

	    McbspaRegs.XCR2.bit.XDATDLY=1;      // FSX setup time 1 in master mode. 0 for slave mode (Transmit)
	    McbspaRegs.XCR2.bit.XCOMPAND=0;      // 不用压扩任何长度数据，先发送MSB
//	    McbspaRegs.XCR2.bit.XCOMPAND=1;      // 不用压扩8位长度数据，先发送LSB
	//    McbspaRegs.XCR2.bit.RCOMPAND = 2;      // 用u-律压扩8位长度数据，先发送MSB
	//    McbspaRegs.XCR2.bit.RCOMPAND = 3;      // 用A-律压扩8位长度数据，先发送MSB

	  	McbspaRegs.SPCR1.bit.RJUST = 0;
//		McbspaRegs.RCR1.bit.RWDLEN1=2;     // 16-bit word
//	    McbspaRegs.XCR1.bit.XWDLEN1=2;     // 16-bit word
		McbspaRegs.RCR1.bit.RWDLEN1=0;     // 8-bit word
		McbspaRegs.XCR1.bit.XWDLEN1=0;     // 8-bit word
	//	McbspaRegs.RCR1.bit.RWDLEN1=1;     // 12-bit word
	//  McbspaRegs.XCR1.bit.XWDLEN1=1;     // 12-bit word

	//	McbspaRegs.RCR1.bit.RWDLEN1=3;     // 20-bit word
	//  McbspaRegs.XCR1.bit.XWDLEN1=3;     // 20-bit word
	//	McbspaRegs.RCR1.bit.RWDLEN1=4;     // 24-bit word
	//  McbspaRegs.XCR1.bit.XWDLEN1=4;     // 24-bit word
	//	McbspaRegs.RCR1.bit.RWDLEN1=5;     // 32-bit word
	//  McbspaRegs.XCR1.bit.XWDLEN1=5;     // 32-bit word
	    //  配置中断
		McbspaRegs.SPCR1.bit.RINTM = 0;
		McbspaRegs.MFFINT.bit.RINT = 1;


	    McbspaRegs.SPCR2.bit.GRST=1;         // Enable the sample rate generator
		delay_loop();                        // Wait at least 2 SRG clock cycles
		McbspaRegs.SPCR2.bit.XRST=1;         // 使能发送器Release TX from Reset
		McbspaRegs.SPCR1.bit.RRST=1;         // 使能接收器Release RX from Reset
	    McbspaRegs.SPCR2.bit.FRST=1;         // 使能帧同步Frame Sync Generator reset
	    McbspaRegs.SPCR2.bit.SOFT=2;



}

void init_mcbspb_spi()
{

//  复位McBSP
    McbspbRegs.SPCR2.all=0x0000;		// Reset FS generator, sample rate generator & transmitter
	McbspbRegs.SPCR1.all=0x0000;		// Reset Receiver, Right justify word

// 配置SPI模式3 CPOL = 1, CPHA = 1
//    McbspbRegs.SPCR1.bit.CLKSTP = 0 or 1;     // 关闭时钟停止模式
//    McbspbRegs.SPCR1.bit.CLKSTP = 3;     // 开启时钟停止模式延时半周期
    McbspbRegs.SPCR1.bit.CLKSTP = 2;     // 开启时钟停止模式无延时
    McbspbRegs.PCR.bit.CLKXP = 1;		 // CPOL = 1, CPHA = 1 falling edge
	McbspbRegs.PCR.bit.CLKRP = 0;        // Receive data on the rising edge of MCLKR
//  配置主从模式
	McbspbRegs.PCR.bit.CLKXM = 1;        //配置为主机模式
//  配置时钟为LSPCLK默认为150/4=37.5MHz
	McbspbRegs.PCR.bit.SCLKME = 0;
	McbspbRegs.SRGR2.bit.CLKSM = 1;
//  配置传输波特率150/4/(49+1)=750KHz
	McbspbRegs.SRGR1.bit.CLKGDV= 49;
//  配置帧同步信号
	McbspbRegs.PCR.bit.FSXM = 1;
	McbspbRegs.SRGR2.bit.FSGM = 0; 	 	 // CLKSM=1, FPER = 1 CLKG periods
    McbspbRegs.PCR.bit.FSXP = 1;
//  配置数据格式
    McbspbRegs.RCR2.bit.RDATDLY = 1;      // FSX setup time 1 in master mode. 0 for slave mode (Receive)
    McbspbRegs.RCR2.bit.RCOMPAND = 0;      // 不用压扩任何长度数据，先接收MSB
//    McbspbRegs.RCR2.bit.RCOMPAND=1;      // 不用压扩8位长度数据，先接收LSB
//    McbspbRegs.RCR2.bit.RCOMPAND = 2;      // 用u-律压扩8位长度数据，先接收MSB
//    McbspbRegs.RCR2.bit.RCOMPAND = 3;      // 用A-律压扩8位长度数据，先接收MSB

    McbspbRegs.XCR2.bit.XDATDLY=1;      // FSX setup time 1 in master mode. 0 for slave mode (Transmit)
    McbspbRegs.XCR2.bit.XCOMPAND=0;      // 不用压扩任何长度数据，先发送MSB
//    McbspbRegs.XCR2.bit.XCOMPAND=1;      // 不用压扩8位长度数据，先发送LSB
//    McbspbRegs.XCR2.bit.RCOMPAND = 2;      // 用u-律压扩8位长度数据，先发送MSB
//    McbspbRegs.XCR2.bit.RCOMPAND = 3;      // 用A-律压扩8位长度数据，先发送MSB

  	McbspbRegs.SPCR1.bit.RJUST = 0;
	McbspbRegs.RCR1.bit.RWDLEN1=2;     // 16-bit word
    McbspbRegs.XCR1.bit.XWDLEN1=2;     // 16-bit word
//	McbspbRegs.RCR1.bit.RWDLEN1=0;     // 8-bit word
//  McbspbRegs.XCR1.bit.XWDLEN1=0;     // 8-bit word
//	McbspbRegs.RCR1.bit.RWDLEN1=1;     // 12-bit word
//  McbspbRegs.XCR1.bit.XWDLEN1=1;     // 12-bit word

//	McbspbRegs.RCR1.bit.RWDLEN1=3;     // 20-bit word
//  McbspbRegs.XCR1.bit.XWDLEN1=3;     // 20-bit word
//	McbspbRegs.RCR1.bit.RWDLEN1=4;     // 24-bit word
//  McbspbRegs.XCR1.bit.XWDLEN1=4;     // 24-bit word
//	McbspbRegs.RCR1.bit.RWDLEN1=5;     // 32-bit word
//  McbspbRegs.XCR1.bit.XWDLEN1=5;     // 32-bit word
    //  配置中断
	McbspbRegs.SPCR1.bit.RINTM = 0;
	McbspbRegs.MFFINT.bit.RINT = 1;


    McbspbRegs.SPCR2.bit.GRST=1;         // Enable the sample rate generator
	delay_loop();                        // Wait at least 2 SRG clock cycles
	McbspbRegs.SPCR2.bit.XRST=1;         // 使能发送器Release TX from Reset
	McbspbRegs.SPCR1.bit.RRST=1;         // 使能接收器Release RX from Reset
    McbspbRegs.SPCR2.bit.FRST=1;         // 使能帧同步Frame Sync Generator reset
    McbspbRegs.SPCR2.bit.SOFT=2;
//    GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;   // iSensor_CS拉低
//    DELAY_US(1000);

}


	/* Mcbspa_spi 发送和接受*/

void Mcbspa_SPI_TX(Uint16 a)
{
   	while( McbspaRegs.SPCR2.bit.XRDY == 0 ) {}         // Master waits until TX data is ready
	McbspaRegs.DXR1.all = a<<8;
    McbspaRegs.DRR1.all = McbspaRegs.DRR1.all;
}


Uint16 Mcbspa_SPI_RX(void)
{
	Uint16 Temp = 0;
//    McbspaRegs.DXR1.all= 0x00;
	while( McbspaRegs.SPCR1.bit.RRDY == 0 ) {}         // Master waits until RX data is ready
    Temp = McbspaRegs.DRR1.all;                      // Then read DRR1 to complete receiving of data
	return(Temp);			 								// Check that correct data is received.
}


/* Mcbspb_spi 发送和接受*/

void Mcbspb_SPI_TX(Uint16 a)
{

	while( McbspbRegs.SPCR2.bit.XRDY == 0 ) {}         // Master waits until TX data is ready
	 McbspbRegs.DXR1.all = a;
    McbspbRegs.DRR1.all = McbspbRegs.DRR1.all;         // 清除标志位

}

Uint16 Mcbspb_SPI_RX(void)
{
	Uint16 Temp = 0;
	while( McbspbRegs.SPCR1.bit.RRDY == 0 ) {}         // Master waits until RX data is ready
    Temp = McbspbRegs.DRR1.all;                      // Then read DRR1 to complete receiving of data
	return(Temp);			 								// Check that correct data is received.
}


//===========================================================================
// No more.
//===========================================================================











