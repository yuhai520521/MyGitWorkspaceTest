#ifndef __GPS_H_
#define __GPS_H_

#define LOCAL_TIME_DIFFERENCE  +8 //时差

typedef struct{
	Uint16 year;
	uchar month;
	uchar day;
	uchar hour;
	uchar minute;
	uchar second;
}DATE_TIME;

typedef struct{
	double latitude;          // 经度
	double longitude;         // 纬度
	float speed;              // 速度
	float direction;          // 航向
	uchar NS;
	uchar EW;
	DATE_TIME D;
}GPS_INFO;

extern void InitGPSSPI(void);
extern void GetGPRMC(uchar *store_add);
extern uchar ParseGPRMC(uchar *line,GPS_INFO *GPS);
void SetSPIPORT(void);
void CheckSUM(void);

#endif
