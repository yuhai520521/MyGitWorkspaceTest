/******************************************************************************
  * @file    adis16488.h
  * @author  gaby_gaojia
  * @version V1.0
  * @date    19-09-2016
  * @brief   adis16488 module driver.
  *****************************************************************************
  *
  *
  ******************************************************************************
	*/
	/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __adis16488_H
#define __adis16488_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include <stdbool.h>
#include <math.h>

//extern SPI_HandleTypeDef hspi1;

typedef struct
{
	 Uint16 msgWhat;
	 Uint16 state;
	 Uint16 accel[3];
	 Uint16 gyro[3];
	 Uint16 magn[3];
	 Uint16 barometer;
	 Uint16 temp;
//	 RTC_TimeTypeDef RTC_TimeStruct;
//	 RTC_DateTypeDef RTC_DateStruct;
}ADISDATA;

typedef struct
{
	float accel[3];
	 float gyro[3];
	 float magn[3];
	 float barometer;
	 float temp;
}ADISD;
typedef 	enum
{
	ADIS_OK,
	ADIS_ERR0R
}ADIS_STATE;

extern bool adis16488_init_status;

#define ADIS16488_PAGE_SIZE ADIS_PAGE_SIZE
#define DEVICE_ID  0x4068
#define ADIS16488_SAMPLE_RATE     2640
	 

	 
/* Each filter coefficent bank spans two pages */
#define ADIS16488_FIR_COEF(page) (x < 60 ? ADIS16488_REG(page, (x) + 8) : \
				ADIS16488_REG((page) + 1, (x) - 60 + 8))
#define ADIS16488_FIR_COEF_A(x)			ADIS16488_FIR_COEF(0x05, (x))
#define ADIS16488_FIR_COEF_B(x)			ADIS16488_FIR_COEF(0x07, (x))
#define ADIS16488_FIR_COEF_C(x)			ADIS16488_FIR_COEF(0x09, (x))
#define ADIS16488_FIR_COEF_D(x)			ADIS16488_FIR_COEF(0x0B, (x))

struct adis_data {

	unsigned int glob_cmd_reg;
	unsigned int msc_ctrl_reg;
	unsigned int diag_stat_reg;

	unsigned int self_test_mask;
	bool self_test_no_autoclear;
	unsigned int startup_delay;

	const char * const *status_error_msgs;
	unsigned int status_error_mask;

	int (*enable_irq)(bool enable);

};

#define ADIS16488_DIAG_STAT_XGYRO_FAIL 0
#define ADIS16488_DIAG_STAT_YGYRO_FAIL 1
#define ADIS16488_DIAG_STAT_ZGYRO_FAIL 2
#define ADIS16488_DIAG_STAT_XACCL_FAIL 3
#define ADIS16488_DIAG_STAT_YACCL_FAIL 4
#define ADIS16488_DIAG_STAT_ZACCL_FAIL 5
#define ADIS16488_DIAG_STAT_XMAGN_FAIL 8
#define ADIS16488_DIAG_STAT_YMAGN_FAIL 9
#define ADIS16488_DIAG_STAT_ZMAGN_FAIL 10
#define ADIS16488_DIAG_STAT_BARO_FAIL 11


void ADIS16488_init(void);
void ADIS16405_init(void);
void ADIS16488_data_conversion(void);
void ADIS16405_data_conversion(void);
Uint16 PROD_ID_RX(void);
Uint16 temout(void);


#ifdef __cplusplus
}
#endif

#endif /*__adis16488_H */
