#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "string.h"
#include "GPS.h"

//====================================================================//
// ʵ�ֹ��ܣ������ַ����и������ŵ�λ��
// ��    �������ҵڼ������ţ���Ҫ���ҵ��ַ���
// �� �� ֵ���ҵ��򷵻ض��ź�һ�ֽڵ�λ�ã����򷵻�0
//====================================================================//
uchar GetComma(uchar num,uchar *str)
{
  uchar i,j = 0;
  uchar len = strlen((char const*)str);

  for(i=0; i<len; i++)
  {
    if(str[i] == ',')
      j++;
    if(j == num)
      return i + 1;
  }

  return 0;
}

//====================================================================//
// ʵ�ֹ��ܣ���һ���ַ���ת�����޷�������
// ��    ������ת�����ַ���
// �� �� ֵ��ת������޷�������
//====================================================================//
Uint16 Str_To_Int(uchar *buf)
{
  Uint16 rev = 0;
  Uint16 dat;
  uchar *str = buf;
  while(*str != '\0')
  {
    switch(*str)
    {
    case '0':
      dat = 0;
      break;
    case '1':
      dat = 1;
      break;
    case '2':
      dat = 2;
      break;
    case '3':
      dat = 3;
      break;
    case '4':
      dat = 4;
      break;
    case '5':
      dat = 5;
      break;
    case '6':
      dat = 6;
      break;
    case '7':
      dat = 7;
      break;
    case '8':
      dat = 8;
      break;
    case '9':
      dat = 9;
      break;
    }

    rev = rev * 10 + dat;
    str ++;
  }

  return rev;
}

//====================================================================//
// ʵ�ֹ��ܣ���һ���ַ���ת���ɵ����ȸ�����
// ��    ������ת���ַ���
// �� �� ֵ��ת���󵥾��ȸ�����
//====================================================================//
float Str_To_Float(uchar *buf)
{
  float rev = 0;
  float dat;
  uchar integer = 1;
  uchar *str = buf;
  Uint16 i;
  while(*str != '\0')
  {
    switch(*str)
    {
    case '0':
      dat = 0;
      break;
    case '1':
      dat = 1;
      break;
    case '2':
      dat = 2;
      break;
    case '3':
      dat = 3;
      break;
    case '4':
      dat = 4;
      break;
    case '5':
      dat = 5;
      break;
    case '6':
      dat = 6;
      break;
    case '7':
      dat = 7;
      break;
    case '8':
      dat = 8;
      break;
    case '9':
      dat = 9;
      break;
    case '.':
      dat = '.';
      break;
    }

    if(dat == '.')
    {
      integer = 0;
      i = 1;
      str ++;
      continue;
    }

    if(integer == 1)
    {
      rev = rev * 10 + dat;
    }
    else
    {
      rev = rev + dat / (10 * i);
      i = i * 10 ;
    }
    str ++;
  }

  return rev;
}

//====================================================================//
// ʵ�ֹ��ܣ���һ���ַ���ת����˫���ȸ�����
// ��    ������ת���ַ���
// �� �� ֵ��ת����˫���ȸ�����
//====================================================================//
double Str_To_Double(uchar *buf)
{
  double rev = 0;
  double dat;
  uchar integer = 1;
  uchar *str = buf;
  Uint16 i;
  while(*str != '\0')
  {
    switch(*str)
    {
    case '0':
      dat = 0;
      break;
    case '1':
      dat = 1;
      break;
    case '2':
      dat = 2;
      break;
    case '3':
      dat = 3;
      break;
    case '4':
      dat = 4;
      break;
    case '5':
      dat = 5;
      break;
    case '6':
      dat = 6;
      break;
    case '7':
      dat = 7;
      break;
    case '8':
      dat = 8;
      break;
    case '9':
      dat = 9;
      break;
    case '.':
      dat = '.';
      break;
    }

    if(dat == '.')
    {
      integer = 0;
      i = 1;
      str ++;
      continue;
    }

    if(integer == 1)
    {
      rev = rev * 10 + dat;
    }
    else
    {
      rev = rev + dat / (10 * i);
      i = i * 10 ;
    }
    str ++;
  }

  return rev;
}

//====================================================================//
// ʵ�ֹ��ܣ��Ѹ����ַ�����һ������֮ǰ���ַ�ת�����޷�������
// ��    ������ת���ַ���
// �� �� ֵ��ת�����޷�������
//====================================================================//
Uint16 Get_Int_Number(uchar *s)
{
  uchar buf[10];
  uchar i;
  Uint16 rev;
  i = GetComma(1, s);
  i = i - 1;
  strncpy((char*)buf, (char const*)s, i);
  buf[i] = 0;
  rev = Str_To_Int(buf);
  return rev;
}

//====================================================================//
// ʵ�ֹ��ܣ��Ѹ����ַ�����һ������֮ǰ���ַ�ת���ɵ����ȸ�����
// ��    ������ת���ַ���
// �� �� ֵ��ת���󵥾��ȸ�����
//====================================================================//
float Get_Float_Number(uchar *s)
{
  uchar buf[10];
  uchar i;
  float rev;
  i = GetComma(1, s);
  i = i - 1;
  strncpy((char*)buf, (char const*)s, i);
  buf[i] = 0;
  rev = Str_To_Float(buf);
  return rev;
}

//====================================================================//
// ʵ�ֹ��ܣ��Ѹ����ַ�����һ������֮ǰ���ַ�ת����˫���ȸ�����
// ��    ������ת���ַ���
// �� �� ֵ��ת����˫���ȸ�����
//====================================================================//
double Get_Double_Number(uchar *s)
{
  uchar buf[11];
  uchar i;
  double rev;
  i=GetComma(1, s);
  i = i - 1;
  strncpy((char*)buf, (char const*)s, i);
  buf[i] = 0;
  rev=Str_To_Double(buf);
  return rev;
}

//====================================================================//
// ʵ�ֹ��ܣ���ʱ��ת��Ϊ����ʱ����ʱ��
// ��    �������ʱ��Ľṹ��
// �� �� ֵ����
//====================================================================//
void UTC2LTC(DATE_TIME *GPS)
{
  GPS->second ++;
  if(GPS->second > 59)
  {
    GPS->second = 0;
    GPS->minute ++;
    if(GPS->minute > 59)
    {
      GPS->minute = 0;
      GPS->hour ++;
    }
  }

  GPS->hour += (LOCAL_TIME_DIFFERENCE);
  if(GPS->hour > 23)
  {
    GPS->hour -= 24;
    GPS->day += 1;
    if(GPS->month == 2
     ||GPS->month == 4
     ||GPS->month == 6
     ||GPS->month == 9
     ||GPS->month == 11)
    {
      if(GPS->day > 30)
      {
        GPS->day = 1;
        GPS->month++;
      }
    }
    else
    {
      if(GPS->day > 31)
      {
        GPS->day = 1;
        GPS->month ++;
      }
    }
    if(GPS->year % 4 == 0 )
    {
      if(GPS->day > 29 && GPS->month == 2)
      {
        GPS->day = 1;
        GPS->month ++;
      }
    }
    else
    {
      if(GPS->day > 28 &&GPS->month == 2)
      {
        GPS->day = 1;
        GPS->month ++;
      }
    }
    if(GPS->month > 12)
    {
      GPS->month -= 12;
      GPS->year ++;
    }
  }
}
//====================================================================//
// ʵ�ֹ��ܣ�GPS��SPI�˿�����
// �� �� ֵ����
//====================================================================//

void SetSPIPORT(void)
{
//	Uint16 SPIPORT_command[28] = {0xB5,0x62,0x06,0x00,0x14,0x00,0x04,0x00,0x00,0x02,0x00,0x00,0x32,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x52,0x76};
//	Uint16 SPIPORT_command[28] = {0xB5,0x62,0x06,0x00,0x14,0x00,0x04,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0xBA};
//	Uint16 SPIPORT_command[8] = {0xB5,0x62,0x01,0x07,0x00,0x00,0x084,0x19};
	Uint16 SPIPORT_command[10] =  {0xB5,0x62,0x06,0x01,0x02,0x00,0xF0,0x04,0xFD,0x15};

	Uint16 *command = SPIPORT_command;
	Uint16 i;
	  for(i=0; i<10; i++)
	  {
		  SPI_TX(*command++);
	  }

}

//====================================================================//
// ʵ�ֹ��ܣ�8λУ��ͼ���
// �� �� ֵ����
//====================================================================//

void CheckSUM(void)
{

	uchar SPIPORT_command[6] = {0x06,0x01,0x02,0x00,0xF0,0x04};

	Uint16 CK_A = 0;
	Uint16 CK_B = 0;
	Uint16 i;
	  for(i=0; i<6; i++)
	  {
		  CK_A = CK_A+SPIPORT_command[i];
		  CK_B = CK_B+CK_A;

	  }
	 CK_A = CK_A & 0xff;
	 CK_B = CK_B & 0xff;
}

//====================================================================//
// ʵ�ֹ��ܣ�����GPS��GPRMC����
// ��    �������GPRMC���ݵĵ�ַ
// �� �� ֵ����
//====================================================================//
void GetGPRMC(uchar *store_add)
{
	  uchar GPRMC_command[16] = {0xB5,0x62,0x06,0x01,0x08,0x00,0xF0,0x04,0x01,0x01,0x01,0x01,0x01,0x01,0x09,0x54};
	  uchar *command = GPRMC_command;
	  Uint16 i;
	  uchar header_found_flag = 0;
	  uchar temp;

	  for(i=0; i<16; i++)
	  {
		  SPI_RX(*command++);
	  }

	  for(i=0; i<65535; i++)
	  {
	    if(header_found_flag)
	    {
	      temp = SPI_RX(0xff);
	      if(temp != '$')
	      {
//	    	  scia_xmit(temp);
	        *store_add++ = temp;
	      }
	      else
	      {
	        break;
	      }
	    }
	    else
	    {
	      temp = SPI_RX(0xff);
	      if(temp == '$')
	      {
//	    	  scia_xmit(temp);
	        header_found_flag = 1;
	        *store_add++ = temp;
	      }
	    }
	  }

  DELAY_US(1000);
}

//====================================================================//
// ʵ�ֹ��ܣ���gpsģ���GPRMC��Ϣ����Ϊ��ʶ�������
// ��    �������ԭʼ��Ϣ�ַ����顢�洢��ʶ�����ݵĽṹ��
// �� �� ֵ��1: ����GPRMC��ϣ�0: û�н��н�������������Ч
//$GPRMC,(1),(2),(3),(4),(5),(6),(7),(8),(9),(10),(11),(12)*hh(CR)(LF)
//(1) UTCʱ�䣬hhmmss��ʱ���룩
//(2) ��λ״̬��A=��Ч��λ��V=��Ч��λ
//(3) γ��ddmm.mmmmm���ȷ֣�
//(4) γ�Ȱ���N�������򣩻�S���ϰ���
//(5) ����dddmm.mmmmm���ȷ֣�
//(6) ���Ȱ���E����������W��������
//(7) �������ʣ�000.0~999.9�ڣ�
//(8) ���溽��000.0~359.9�ȣ����汱��Ϊ�ο���׼��
//(9) UTC���ڣ�ddmmyy�������꣩
//(10)��ƫ�ǣ�000.0~180.0�ȣ�ǰ��λ��������0��
//(11) ��ƫ�Ƿ���E��������W������
//(12) ģʽָʾ��A=������λ��D=��֣�E=���㣬N=������Ч��
//====================================================================//
uchar ParseGPRMC(uchar *line,GPS_INFO *GPS)
{
  uchar ch, status, tmp;
  float speed_tmp;
  uchar *buf = line;
  ch = buf[5];
  status = buf[GetComma(2, buf)];

  if (ch == 'C')          // ���������ַ���C��($GPRMC)
  {
    if (status == 'A')    // ���������Ч�������
    {
      GPS -> NS = buf[GetComma(4, buf)];
      GPS -> EW = buf[GetComma(6, buf)];

      GPS->latitude   = Get_Double_Number(&buf[GetComma(3, buf)]);
      GPS->longitude  = Get_Double_Number(&buf[GetComma(5, buf)]);

      speed_tmp       = Get_Float_Number(&buf[GetComma(7, buf)]);          // �ٶ�(��λ������/ʱ)
      GPS->speed      = speed_tmp * 1.852;                                 // 1����=1.852����
      GPS->direction  = Get_Float_Number(&buf[GetComma(9, buf)]);          // �Ƕ�

      GPS->D.hour     = (buf[7]  - '0') * 10 + (buf[8]  - '0');		   // ʱ��
      GPS->D.minute   = (buf[9]  - '0') * 10 + (buf[10] - '0');
      GPS->D.second   = (buf[11] - '0') * 10 + (buf[12] - '0');

      tmp = GetComma(9, buf);
      GPS->D.day      = (buf[tmp + 0] - '0') * 10 + (buf[tmp + 1] - '0');  // ����
      GPS->D.month    = (buf[tmp + 2] - '0') * 10 + (buf[tmp + 3] - '0');
      GPS->D.year     = (buf[tmp + 4] - '0') * 10 + (buf[tmp + 5] - '0')+2000;

      UTC2LTC(&GPS->D);

      return 1;
    }
  }

  return 0;
}
