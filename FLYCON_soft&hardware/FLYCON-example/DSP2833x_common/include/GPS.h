#ifndef __GPS_H_
#define __GPS_H_

#define LOCAL_TIME_DIFFERENCE  +8 //ʱ��

typedef struct{
	Uint16 year;
	uchar month;
	uchar day;
	uchar hour;
	uchar minute;
	uchar second;
}DATE_TIME;

typedef struct{
	double latitude;          // ����
	double longitude;         // γ��
	float speed;              // �ٶ�
	float direction;          // ����
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
