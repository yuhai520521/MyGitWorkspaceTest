// TI File $Revision: /main/2 $
// Checkin $Date: March 1, 2007   16:06:07 $
//###########################################################################
//
// FILE:	DSP2833x_Sci.c
//
// TITLE:	DSP2833x SCI Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x Header Files V1.01 $
// $Release Date: September 26, 2007 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define SBUS_SIGNAL_OK 0x00
#define SBUS_SIGNAL_LOST 0x01
#define SBUS_SIGNAL_FAILSAFE 0x03

//---------------------------------------------------------------------------
// Example: InitSciGpio: 
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as SCI pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 
// Caution: 
// Only one GPIO pin should be enabled for SCITXDA/B operation.
// Only one GPIO pin shoudl be enabled for SCIRXDA/B operation. 
// Comment out other unwanted lines.


void InitScibGpio()
{
   EALLOW;
	
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled disabled by the user.  
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;    // Enable pull-up for GPIO14 (SCITXDB)
   GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;    // Enable pull-up for GPIO15 (SCIRXDB)


/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.


    GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;  // Asynch input GPIO15 (SCIRXDB)

/* Configure SCI-B pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SCI functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 2;   // Configure GPIO14 for SCITXDB operation
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 2;   // Configure GPIO15 for SCIRXDB operation

    EDIS;
}


void scib_init()
{

	ScibRegs.SCICCR.all = 0xe7; // 2位stop,偶校验,no loopback,idle line mode and 8bits data.
	ScibRegs.SCICTL1.all = 0x0003;  // 接收和发送使能
	ScibRegs.SCIHBAUD = 0x00;
	ScibRegs.SCILBAUD = 0x2e;  // 100000baud
	ScibRegs.SCICTL2.all = 0x0003;  // 接收中断和发送中断使能
	ScibRegs.SCICTL1.bit.SWRESET = 1;
}

void scib_fifo_init()
{
    ScibRegs.SCIFFTX.all=0xE040;
    ScibRegs.SCIFFRX.all=0x204f;
    ScibRegs.SCIFFCT.all=0x0;
}

void scib_xmit(Uint16 a)
{
	while (ScibRegs.SCICTL2.bit.TXRDY == 0);
    ScibRegs.SCITXBUF=a;
}

Uint16 scib_rx(void)
{
	while (ScibRegs.SCIRXST.bit.RXRDY == 0){}
	ScibRegs.SCIRXBUF.all = ScibRegs.SCIRXBUF.all;
    return (ScibRegs.SCIRXBUF.all);
}

#define SBUS_SIGNAL_OK          0x00
#define SBUS_SIGNAL_LOST        0x01
#define SBUS_SIGNAL_FAILSAFE    0x03

Uint16 sbus_data[25] =
{
  0x0f,0x01,0x04,0x20,0x00,0xff,0x07,0x40,0x00,0x02,0x10,0x80,0x2c,0x64,0x21,0x0b,0x59,0x08,0x40,0x00,0x02,0x10,0x80,0x00,0x00
};
Uint16 channels[18]  =
{
  1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,0,0
};
Uint16 servos[18]    =
{
  1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,0,0
};
Uint16  failsafe_status = SBUS_SIGNAL_FAILSAFE;
Uint16 sbus_passthrough = 1;
Uint16 byte_in_sbus;
Uint16 bit_in_sbus;
Uint16 ch;
Uint16 bit_in_channel;
Uint16 bit_in_servo;
Uint16 inBuffer[25];
Uint16 bufferIndex=0;
Uint16 inData;
Uint16 toChannels = 0;
Uint16 result[16];

void loop()
{
  feedLine();
  if(toChannels==1)
  {
	  update_channels();
	  toChannels=0;
  }

}


void update_channels(void)
{
  Uint16 x,i,t;

  // clear channels[]
  for (i=0; i<16; i++)
  {
	  channels[i] = 0;
  }

  // reset counters
  byte_in_sbus = 1;
  bit_in_sbus = 0;
  ch = 0;
  bit_in_channel = 0;

  // process actual sbus data
  for (i=0; i<176; i++)
  {
    if (sbus_data[byte_in_sbus] & (1<<bit_in_sbus))
    {
    	channels[ch] |= (1<<bit_in_channel);
    }
    bit_in_sbus++;
    bit_in_channel++;

    if (bit_in_sbus == 8)
    {
    	bit_in_sbus =0;
        byte_in_sbus++;
    }
    if (bit_in_channel == 11)
    {
    	bit_in_channel =0;
    	ch++;
    }
  }
  if((channels[0]>0)&&(channels[0]<2048))
  {
	  x = channels[0]/2+998;
  }

  if(channels[0]>2047)
  {
	  x = 2000;
  }
  t = x*3/5;
  EPwm3Regs.CMPA.half.CMPA = t;
  EPwm4Regs.CMPA.half.CMPA = t;
  scia_xmit16(x);
  // sbus_data[23]是flags字节

  // DigiChannel 1
  if (sbus_data[23] & (1<<0))
  {
	  channels[16] = 1;
  }
  else
  {
	  channels[16] = 0;
  }
  // DigiChannel 2
  if (sbus_data[23] & (1<<1))
  {
	  channels[17] = 1;
  }
  else
  {
	  channels[17] = 0;
  }
  // Failsafe
  failsafe_status = SBUS_SIGNAL_OK;
  if (sbus_data[23] & (1<<2))
  {
	  failsafe_status = SBUS_SIGNAL_LOST;
  }
  if (sbus_data[23] & (1<<3))
  {
	  failsafe_status = SBUS_SIGNAL_FAILSAFE;
  }

}
void feedLine()
{
  while(1)
  {
	  inData = scib_rx();

    if (inData == 0x0f)
	{
    	bufferIndex = 0;
    	inBuffer[bufferIndex] = inData;
//      inBuffer[24] = 0xff;
    }
    else
	{
    	bufferIndex ++;
    	inBuffer[bufferIndex] = inData;
    }
    if(inBuffer[0]==0x0f && inBuffer[24] == 0x00)
	{

    	memcpy(sbus_data,inBuffer,25);
		toChannels = 1;
		return;
    }
    break;       // if语句成立则跳出while循环
  }
}

//Uint16 channel(Uint16 ch)
//{
//  // Read channel data
//  if ((ch>0)&&(ch<=16))
//  {
//    return channels[ch-1];
//  }
//  else{
//    return 1023;
//  }
//}
//Uint16 digichannel(Uint16 ch)
//{
//  // Read digital channel data
//  if ((ch>0) && (ch<=2))
//  {
//    return channels[15+ch];
//  }
//  else{
//    return 0;
//  }
//}
//void servo(Uint16 ch, Uint16 position)
//{
//  // Set servo position
//  if ((ch>0)&&(ch<=16))
//  {
//    if (position>2048)
//    {
//      position=2048;
//    }
//    servos[ch-1] = position;
//  }
//}
//void digiservo(Uint16 ch, Uint16 position)
//{
//  // Set digital servo position
//  if ((ch>0) && (ch<=2))
//  {
//    if (position>1)
//    {
//      position=1;
//    }
//    servos[15+ch] = position;
//  }
//}
//Uint16 failsafe(void)
//{
//  return failsafe_status;
//}
//
//void passthroughSet(int mode)
//{
//  // Set passtrough mode, if true, received channel data is send to servos
//  sbus_passthrough = mode;
//}
//
//int passthroughRet(void)
//{
//  // Return current passthrough mode
//  return sbus_passthrough;
//}

//void update_servos(void)
//{
//  // Send data to servos
//  // Passtrough mode = false >> send own servo data
//  // Passtrough mode = true >> send received channel data
//  Uint16 i;
//  if (sbus_passthrough==0)
//  {
//    // clear received channel data
//    for (i=1; i<24; i++)
//    {
//      sbus_data[i] = 0;
//    }
//
//    // reset counters
//    ch = 0;
//    bit_in_servo = 0;
//    byte_in_sbus = 1;
//    bit_in_sbus = 0;
//
//    // store servo data
//    for (i=0; i<176; i++)             // 22个字节共176个数据位
//    {
//      if (servos[ch] & (1<<bit_in_servo))
//      {
//        sbus_data[byte_in_sbus] |= (1<<bit_in_sbus);
//      }
//      bit_in_sbus++;
//      bit_in_servo++;
//
//      if (bit_in_sbus == 8)
//      {
//        bit_in_sbus =0;
//        byte_in_sbus++;
//      }
//      if (bit_in_servo == 11)
//      {
//        bit_in_servo =0;
//        ch++;
//      }
//    }
//
//    // DigiChannel 1
//    if (channels[16] == 1)
//    {
//      sbus_data[23] |= (1<<0);
//    }
//    // DigiChannel 2
//    if (channels[17] == 1)
//    {
//      sbus_data[23] |= (1<<1);
//    }
//
//    // Failsafe
//    if (failsafe_status == SBUS_SIGNAL_LOST)
//    {
//      sbus_data[23] |= (1<<2);
//    }
//
//    if (failsafe_status == SBUS_SIGNAL_FAILSAFE)
//    {
//      sbus_data[23] |= (1<<2);
//      sbus_data[23] |= (1<<3);
//    }
//  }
//
//}


//===========================================================================
// End of file.
//===========================================================================
