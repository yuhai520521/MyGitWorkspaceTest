#include "DSP2833x_Device.h"     // DSP28 Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP28 Examples Include File

/*
**********************************************************************
*　名　　称：DS18B20_init()
*　功　　能：复位DS18B20
*　入口参数：无
*　出口参数：1--存在，0--不存在
*　说　　明：需要配置IO,软件延时要准确
*　范　　例：无
**********************************************************************
*/
void DQ_OUT(void)                           // GPIO85配置为输出口
{
   EALLOW;

   GpioCtrlRegs.GPCMUX2.bit.GPIO85 = 0;     // GPIO85通用的IO
   GpioCtrlRegs.GPCDIR.bit.GPIO85 = 1;      // GPIO85配置为输出口

   EDIS;

}
void DQ_IN(void)                           // GPIO85配置为输入口
{
   EALLOW;

   GpioCtrlRegs.GPCMUX2.bit.GPIO85 = 0;     // GPIO85通用的IO
   GpioCtrlRegs.GPCDIR.bit.GPIO85 = 0;      //配置为输入
   GpioCtrlRegs.GPCPUD.bit.GPIO85 = 0;      //开启上拉

   EDIS;

}

char DS18B20_Reset(void)
{
	    unsigned char e;
        //-------拉低-----------------------------------
        DQ_OUT();
        GpioDataRegs.GPCCLEAR.bit.GPIO85 = 1;    //拉低

        //-------等待480微秒以上----------------------------
        DELAY_US(600);          //只少等待480微秒以上

        //-------拉高-----------------------------------
        DQ_IN();

        //-------等待15微秒---------------------------------
        DELAY_US(40);

        //-------检测存在-------------------------------------------
        e=0;
        while(1)
        {
            if(GpioDataRegs.GPCDAT.bit.GPIO85==0)
            {
                e=1;
                DELAY_US(120);
                break;
            }

        }

        //------------延时480微秒以上---------------------------------
        DELAY_US(600);
        return e;
}

/*
**********************************************************************
*　名　　称：DS18B20_ReadByte()
*　功　　能：读位字
*　入口参数：无
*　出口参数：返回从DS18B20读回的一个字节
*　说　　明：需要配置IO,软件延时要准确
*　范　　例：无
**********************************************************************
*/
unsigned char DS18B20_ReadByte(void)
{
    unsigned char i,retd=0;
    for(i=0;i<8;i++)            //位计数值
    {
        retd>>=1;               //右移，准备接受新的数据位

        //-------拉低总线5微秒--------------------------
        DQ_OUT();
        GpioDataRegs.GPCCLEAR.bit.GPIO85 = 1;    //拉低
        DELAY_US(5);;        //等待5微秒

        //-------释放总线-----------------------------------
        DQ_IN();

        //-------等待15微秒-----------------------------
        DELAY_US(15);       //等待15微秒

        //-------检查该位是否为高-----------------------
        if(GpioDataRegs.GPCDAT.bit.GPIO85)    //该位是否为高

            retd|=0x80;     //是就将此位置高
            else
            retd|=0x00;


        //-------等待42微秒-----------------------------
        DELAY_US(42);       //等待42微秒
    }
    return retd;                //将读到的一个字节返回
}

/*
**********************************************************************
*　名　　称：DS18B20_WriteByte()
*　功　　能：写字节
*　入口参数：无
*　出口参数：无
*　说　　明：需要配置IO,软件延时要准确
*　范　　例：无
**********************************************************************
*/
void DS18B20_WriteByte(unsigned char wrd)
{
    unsigned char i;

    for(i=0;i<8;i++)            //位计数值
    {
        if(wrd&0x01)            //此位数据是否为高
        {
              //-------拉低总线5微秒--------------------------
            DQ_OUT();
            GpioDataRegs.GPCCLEAR.bit.GPIO85 = 1;    //拉低
            DELAY_US(5);

              //-------拉高总线60微秒----------------------------------
            DQ_IN();
            DELAY_US(60);
        }
        else
        {
              //-------拉低总线60微秒----------------------------------
            DQ_OUT();
            GpioDataRegs.GPCCLEAR.bit.GPIO85 = 1;    //拉低
            DELAY_US(60);

              //-------拉高总线5微秒-----------------------------------
            DQ_IN();
            DELAY_US(5);
        }


        //-------等待1微秒以上-------------------------------
        DELAY_US(2);

        //-------右移１位-------------------------------------
        wrd>>=1;                //右移，为写入新的数据位做准备
    }

}

/*
**********************************************************************
*　名　　称：DS18B20_ReadTemp()
*　功　　能：读温度
*　入口参数：无
*　出口参数：返回温度值
*　说　　明：需要配置IO,软件延时要准确
*　范　　例：无
**********************************************************************
*/
char e;
int DS18B20_ReadTemp()
{
	int16 temp = 0;
    unsigned char TH,TL;
    int16 tem;

    e=DS18B20_Reset();          //初始化，每次写命令都从初始化开始
    DS18B20_WriteByte(0xcc);        //跳过ROM
    DS18B20_WriteByte(0x44);        //启动温度转换

    DELAY_US(20000);                  //延时20ms
    e=DS18B20_Reset();              //初始化，每次写命令都从初始化开始
    DS18B20_WriteByte(0xcc);        //跳过ROM

    DS18B20_WriteByte(0xbe);        //送读寄存器命令

    TL = DS18B20_ReadByte();
    TH = DS18B20_ReadByte();

    if(TH > 7)       //通过判读存储器的高五位的0，1来判断温度的正负，
        {
            temp = 0;   //为负
            TH =~TH;
            TL =~TL;
        }
        else
            temp = 1;   //为正
        tem = TH;
        tem =tem<<8;
        tem =tem+TL;
        tem = (double)tem * 0.0625;
        if(temp)
            return tem;
        else
            return -tem;
}

