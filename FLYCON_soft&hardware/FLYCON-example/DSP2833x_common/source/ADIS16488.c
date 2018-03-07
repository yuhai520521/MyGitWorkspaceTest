#include "adis16488.h"

/*
**********************************************************************
*　名　　称：ADIS16488_init()
*　功　　能：复位DS18B20
*　入口参数：无
*　出口参数：1--存在，0--不存在
*　说　　明：需要配置IO,软件延时要准确
*　范　　例：无
**********************************************************************
*/
#define ADIS16488_DATA_RDY  GpioDataRegs.GPBDAT.bit.GPIO51


#define ADIS16488_REG_SEQ_CNT			0x0600
#define ADIS16488_REG_SYS_E_FLA			0x0800
#define ADIS16488_REG_DIAG_STS			0x0A00
#define ADIS16488_REG_ALM_STS			0x0C00
#define ADIS16488_REG_TEMP_OUT			0x0E00
#define ADIS16488_REG_X_GYRO_OUT		0x1200
#define ADIS16488_REG_Y_GYRO_OUT		0x1600
#define ADIS16488_REG_Z_GYRO_OUT		0x1A00
#define ADIS16488_REG_X_ACCEL_OUT		0x1E00
#define ADIS16488_REG_Y_ACCEL_OUT		0x2200
#define ADIS16488_REG_Z_ACCEL_OUT		0x2600
#define ADIS16488_REG_X_MAGN_OUT		0x2800
#define ADIS16488_REG_Y_MAGN_OUT		0x2A00
#define ADIS16488_REG_Z_MAGN_OUT		0x2C00
#define ADIS16488_REG_BAROM_OUT			0x3000
#define ADIS16488_REG_X_DELTAANG_OUT		0x4000
#define ADIS16488_REG_Y_DELTAANG_OUT		0x4400
#define ADIS16488_REG_Z_DELTAANG_OUT		0x4800
#define ADIS16488_REG_X_DELTAVEL_OUT		0x4C00
#define ADIS16488_REG_Y_DELTAVEL_OUT		0x5000
#define ADIS16488_REG_Z_DELTAVEL_OUT		0x5400
#define ADIS16488_REG_PROD_ID			0x7E00

#define ADIS16488_REG_X_GYRO_SCALE		0x0402
#define ADIS16488_REG_Y_GYRO_SCALE		0x0602
#define ADIS16488_REG_Z_GYRO_SCALE		0x0802
#define ADIS16488_REG_X_ACCEL_SCALE		0x0A02
#define ADIS16488_REG_Y_ACCEL_SCALE		0x0C02
#define ADIS16488_REG_Z_ACCEL_SCALE		0x0E02
#define ADIS16488_REG_X_GYRO_BIAS		0x1002
#define ADIS16488_REG_Y_GYRO_BIAS		0x1402
#define ADIS16488_REG_Z_GYRO_BIAS		0x1802
#define ADIS16488_REG_X_ACCEL_BIAS		0x1C02
#define ADIS16488_REG_Y_ACCEL_BIAS		0x2002
#define ADIS16488_REG_Z_ACCEL_BIAS		0x2402
#define ADIS16488_REG_X_HARD_IRON		0x2802
#define ADIS16488_REG_Y_HARD_IRON		0x2A02
#define ADIS16488_REG_Z_HARD_IRON		0x2C02
#define ADIS16488_REG_BAROM_BIAS		0x4002
#define ADIS16488_REG_FLASH_CNT			0x7C02

#define ADIS16488_REG_GLOB_CMD			0x0203
#define ADIS16488_REG_FNCTIO_CTRL		0x0603
#define ADIS16488_REG_GPIO_CTRL			0x0803
#define ADIS16488_REG_CONFIG			0x0A03
#define ADIS16488_REG_DEC_RATE			0x0C03
#define ADIS16488_REG_SLP_CNT			0x1003
#define ADIS16488_REG_FILTER_BNK0		0x1603
#define ADIS16488_REG_FILTER_BNK1		0x1803
#define ADIS16488_REG_ALM_CNFG0			0x2003
#define ADIS16488_REG_ALM_CNFG1			0x2203
#define ADIS16488_REG_ALM_CNFG2			0x2403
#define ADIS16488_REG_XG_ALM_MAGN		0x2803
#define ADIS16488_REG_YG_ALM_MAGN		0x2A03
#define ADIS16488_REG_ZG_ALM_MAGN		0x2C03
#define ADIS16488_REG_XA_ALM_MAGN		0x2E03
#define ADIS16488_REG_YA_ALM_MAGN		0x3003
#define ADIS16488_REG_ZA_ALM_MAGN		0x3203
#define ADIS16488_REG_XM_ALM_MAGN		0x3403
#define ADIS16488_REG_YM_ALM_MAGN		0x3603
#define ADIS16488_REG_ZM_ALM_MAGN		0x3803
#define ADIS16488_REG_BR_ALM_MAGN		0x3A03
#define ADIS16488_REG_FIRM_REV			0x7803
#define ADIS16488_REG_FIRM_DM			0x7A03
#define ADIS16488_REG_FIRM_Y			0x7C03

#define ADIS16488_REG_SERIAL_NUM		0x0400


void ADIS16488_init(void)
{
		GpioDataRegs.GPASET.bit.GPIO27 = 1;   // iSensor_CS拉低
		DELAY_US(1000);
		GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;   // iSensor_CS拉低
		DELAY_US(1000);
	   Uint16 PROD_ID = 0;
	   Mcbspb_SPI_TX(0x8003);             // 转到第3页
	   Mcbspb_SPI_TX(0x8280);             // 软件复位配置
	   Mcbspb_SPI_TX(0x8300);
	   DELAY_US(500000);
	   Mcbspb_SPI_TX(0x8000);            // 转到第0页 读取数据
	   if(PROD_ID != 0x4068)
			   {
		   	   	   while(PROD_ID != 0x4068)
		   	   	   {
					   GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;   // iSensor_CS拉低
					   DELAY_US(1000);
					   Mcbspb_SPI_TX(0x7E00);
					   PROD_ID = Mcbspb_SPI_RX();
					   GpioDataRegs.GPASET.bit.GPIO27 = 1;   // iSensor_CS拉高
					   DELAY_US(1000);
		   	   	   }
			   }
	   GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;   // iSensor_CS拉低
	   DELAY_US(1000);
//	   Mcbspb_SPI_TX(0x8003);             // 转到第3页
//	   Mcbspb_SPI_TX(0x8280);             // 软件复位配置
//	   Mcbspb_SPI_TX(0x8300);
//	   Mcbspb_SPI_TX(0x8000);            // 转到第0页 读取数据

}

// 读取设备的PROD_ID 固定输出为16488

Uint16 PROD_ID_RX(void)
{

	   Uint16 PROD_ID = 0;
// 	   Mcbspb_SPI_TX(0x8000);
	   GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;
	   DELAY_US(2);
 	   Mcbspb_SPI_TX(ADIS16488_REG_PROD_ID);
 	   PROD_ID = Mcbspb_SPI_RX();
 	   DELAY_US(1000);
 	   Mcbspb_SPI_TX(0xffff);
 	   DELAY_US(1000);
 	   PROD_ID = Mcbspb_SPI_RX();
// 	   DELAY_US(1000);
 	   GpioDataRegs.GPASET.bit.GPIO27 = 1;
 	   DELAY_US(5);
 	   return(PROD_ID);

}
void ADIS16405_init(void)
{
	   Uint16 PROD_ID = 0;

	   if(PROD_ID != 0x4015)
			   {
		   	   	   while(PROD_ID != 0x4015)
		   	   	   {
					   GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;   // iSensor_CS拉低
					   DELAY_US(1000);
					   Mcbspb_SPI_TX(0x5600);
					   DELAY_US(1000);
					   PROD_ID = Mcbspb_SPI_RX();
					   GpioDataRegs.GPASET.bit.GPIO27 = 1;   // iSensor_CS拉高
					   DELAY_US(1000);
		   	   	   }
			   }
	   GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;   // iSensor_CS拉低
	   DELAY_US(1000);
//	   Mcbspb_SPI_TX(0xB601);
//	   DELAY_US(50);
//	   Mcbspb_SPI_TX(0xB806);
//	   DELAY_US(240000);
// 	   Mcbspb_SPI_TX(0xBE01);
// 	   DELAY_US(60000);


}

void ADIS16488_data_conversion(void)
{

	short gx[3];
	short gy[3];
	short gz[3];
	short ax[3];
	short ay[3];
	short az[3];
	short ba;
	short temp;

	Uint16 PROD_ID,comg,coma,comm,comb,comt;
	unsigned char i = 0;

	     Mcbspb_SPI_TX(ADIS16488_REG_PROD_ID);
	     DELAY_US(1000);
		 Mcbspb_SPI_TX(ADIS16488_REG_X_GYRO_OUT);
		 PROD_ID = Mcbspb_SPI_RX();
		 DELAY_US(1000);

		 Mcbspb_SPI_TX(ADIS16488_REG_Y_GYRO_OUT);
		 gx[0] = Mcbspb_SPI_RX();
		 DELAY_US(1000);
		 Mcbspb_SPI_TX(ADIS16488_REG_Z_GYRO_OUT);
		 gx[1] = Mcbspb_SPI_RX();
		 DELAY_US(1000);
		 Mcbspb_SPI_TX(ADIS16488_REG_X_ACCEL_OUT);
		 gx[2] = Mcbspb_SPI_RX();
		 DELAY_US(1000);

		 Mcbspb_SPI_TX(ADIS16488_REG_Y_ACCEL_OUT);
		 gy[0] = Mcbspb_SPI_RX();
		 DELAY_US(1000);
		 Mcbspb_SPI_TX(ADIS16488_REG_Z_ACCEL_OUT);
		 gy[1] = Mcbspb_SPI_RX();
		 DELAY_US(1000);
		 Mcbspb_SPI_TX(ADIS16488_REG_X_ACCEL_OUT);
		 gy[2] = Mcbspb_SPI_RX();
		 DELAY_US(1000);


		 Mcbspb_SPI_TX(ADIS16488_REG_Y_ACCEL_OUT);
		 gz[0] = Mcbspb_SPI_RX();
		 DELAY_US(1000);
		 Mcbspb_SPI_TX(ADIS16488_REG_Z_ACCEL_OUT);
		 gz[1] = Mcbspb_SPI_RX();
		 DELAY_US(1000);
		 Mcbspb_SPI_TX(ADIS16488_REG_BAROM_OUT);
		 gz[2] = Mcbspb_SPI_RX();
		 DELAY_US(1000);

		 Mcbspb_SPI_TX(ADIS16488_REG_TEMP_OUT);
		 ba = Mcbspb_SPI_RX();
		 DELAY_US(1000);

		 Mcbspb_SPI_TX(ADIS16488_REG_PROD_ID);
		 temp = Mcbspb_SPI_RX();
		 DELAY_US(1000);


	for(i=0;i<3;i++)
	{
		//陀螺仪数据转换                                                                 // 单位：°/sec
		comg=gx[i]&0x8000;
		if(comg)
		{
			ax[i]=(-(~(short )gx[i]+1))*0.02;
		}
		else
		{
			ax[i]=((short )gx[i]) * 0.02;
		}

		//加速度数据转换                                                               //单位：mg
		coma=gy[i]&0x8000;
		if(coma)
		{
			ay[i]=(-(~(short )gy[i]+1))*0.8;
		}
		else
		{
			ay[i]=((short )gy[i]) * 0.8;
		}

		//磁力计数据转换                                                                //单位：mgauss
		comm=gz[i]&0x8000;
		if(comm)
		{
			az[i]=(-(~(short )gz[i]+1))*0.1;
		}
		else
		{
			az[i]=((short )gz[i]) * 0.1;
		}

	}
	      //气压计数据转换                                                         //单位：ubar
	comb=ba&0x8000;
	if(comb)
	{
		ba=(-(~(short )ba+1))*40;
	}
	else
	{
		ba=((short )ba) * 40;
	}

	//温度数据转换                                                                               //单位：°C
	comt=temp&0x8000;
	if(comt)
	{
		temp=(-(~(short )temp+1))* 0.00565+25;
	}
	else
	{
		temp=((short )temp) * 0.00565+25;
	}


}

void ADIS16405_data_conversion(void)
{

	Uint16 gx[12];
	Uint16 ax[12];
	float vcc_out,XGYRO_OUT,YGYRO_OUT,ZGYRO_OUT,XACCEL_OUT,YACCEL_OUT, ZACCEL_OUT,XMAGN_OUT,YMAGN_OUT,ZMAGN_OUT,TEMP_OUT,AUX_ADC;
	Uint16 w = 0;

	   DELAY_US(1000);

	   Mcbspb_SPI_TX(0x3E00);
	   w = Mcbspb_SPI_RX();
	   DELAY_US(1000);

	   Mcbspb_SPI_TX(0x3E00);
	   gx[0] = Mcbspb_SPI_RX();
	   DELAY_US(1000);

	   Mcbspb_SPI_TX(0x3E00);
	   gx[1] = Mcbspb_SPI_RX();
	   DELAY_US(1000);

	   Mcbspb_SPI_TX(0x3E00);
	   gx[2] = Mcbspb_SPI_RX();
	   DELAY_US(1000);

	   Mcbspb_SPI_TX(0x3E00);
	   gx[3] = Mcbspb_SPI_RX();
	   DELAY_US(1000);

	   Mcbspb_SPI_TX(0x3E00);
	   gx[4] = Mcbspb_SPI_RX();
	   DELAY_US(1000);

	   Mcbspb_SPI_TX(0x3E00);
	   gx[5] = Mcbspb_SPI_RX();
	   DELAY_US(1000);

	   Mcbspb_SPI_TX(0x3E00);
	   gx[6] = Mcbspb_SPI_RX();
	   DELAY_US(1000);

	   Mcbspb_SPI_TX(0x3E00);
	   gx[7] = Mcbspb_SPI_RX();
	   DELAY_US(1000);

	   Mcbspb_SPI_TX(0x3E00);
	   gx[8] = Mcbspb_SPI_RX();
	   DELAY_US(1000);

	   Mcbspb_SPI_TX(0x3E00);
	   gx[9] = Mcbspb_SPI_RX();
	   DELAY_US(1000);

	   Mcbspb_SPI_TX(0x3E00);
	   gx[10] = Mcbspb_SPI_RX();
	   DELAY_US(1000);

	   Mcbspb_SPI_TX(0x3E00);
	   gx[11] = Mcbspb_SPI_RX();
	   DELAY_US(1000);

	   //供电电压数据转换                                                                 // 单位：v
	   vcc_out = (gx[0]&0x3fff)*0.002418;

		//陀螺仪数据转换                                                                 // 单位：°/sec
		if(gx[1]&0x2000)
		{
			XGYRO_OUT = -((~gx[1]+1)&0x3fff)*0.05;
		}
		else
		{
			XGYRO_OUT = (gx[1]&0x3fff)* 0.05;
		}


		if(gx[2]&0x2000)
		{
			YGYRO_OUT = -((~gx[2]+1)&0x3fff)*0.05;
		}
		else
		{
			YGYRO_OUT = (gx[2]&0x3fff)* 0.05;
		}


		if(gx[3]&0x2000)
		{
			ZGYRO_OUT = -((~gx[3]+1)&0x3fff)*0.05;
		}
		else
		{
			ZGYRO_OUT = (gx[3]&0x3fff)* 0.05;
		}

		//加速度数据转换                                                               //单位：mg

		if(gx[4]&0x2000)
		{
			XACCEL_OUT = -((~gx[4]+1)&0x3fff)*0.00333;
		}
		else
		{
			XACCEL_OUT = (gx[4]&0x3fff)* 0.00333;
		}


		if(gx[5]&0x2000)
		{
			YACCEL_OUT = -((~gx[5]+1)&0x3fff)*0.00333;
		}
		else
		{
			YACCEL_OUT = (gx[5]&0x3fff)* 0.00333;
		}


		if(gx[6]&0x2000)
		{
			ZACCEL_OUT = -((~gx[6]+1)&0x3fff)*0.00333;
		}
		else
		{
			ZACCEL_OUT = (gx[6]&0x3fff)* 0.00333;
		}

		//磁力计数据转换                                                                //单位：mgauss
		if(gx[7]&0x2000)
		{
			XMAGN_OUT = -((~gx[7]+1)&0x3fff)*0.5;
		}
		else
		{
			XMAGN_OUT = (gx[7]&0x3fff)* 0.5;
		}


		if(gx[8]&0x2000)
		{
			YMAGN_OUT = -((~gx[8]+1)&0x3fff)*0.5;
		}
		else
		{
			YMAGN_OUT = (gx[8]&0x3fff)* 0.5;
		}


		if(gx[9]&0x2000)
		{
			ZMAGN_OUT = -((~gx[9]+1)&0x3fff)*0.5;
		}
		else
		{
			ZMAGN_OUT = (gx[9]&0x3fff)* 0.5;
		}

		//温度                                                               //单位：°C
		if(gx[10]&0x0800)
		{
			TEMP_OUT = -((~gx[10]+1)&0x0fff)*0.14+25;
		}
		else
		{
			TEMP_OUT = (gx[10]&0x0fff)* 0.14+25;
		}

		//外部辅助AD采样电压引脚输入值                                                               //单位：v
		AUX_ADC = (gx[11]&0x0fff)*0.000806;


}
