//############################################################################
//
// FILE:   SD_SPI_Transmission.c
//
// TITLE:  SD/MMC SPI Transmission and Error Functions
//
//############################################################################
#include "SD.h"
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "sdio_sd.h"
#include "ff.h"
#include <stdio.h>

//############################# SPI_XMIT_BYTE ################################
Uint16 spi_xmit_byte(Uint16 byte)
{
	while( McbspaRegs.SPCR2.bit.XRDY == 0 ) {}         // Master waits until TX data is ready
	McbspaRegs.DXR1.all = byte;
   	while( McbspaRegs.SPCR1.bit.RRDY == 0 ) {}         // Master waits until RX data is ready
	 McbspaRegs.DRR1.all = (McbspaRegs.DRR1.all);        // 清除接收标志位
  	return (McbspaRegs.DRR1.all);			//Read Byte from RXBUF and return
}
//############################# SPI_XMIT_BYTE ################################


//############################ SPI_XMIT_COMMAND ##############################
void spi_xmit_command(Uint16 command, Uint32 data, Uint16 crc)
{
	Uint16 i, full_command[6];			
	
	//If data manipulation is requested from standard capacity card,
	//multiply data by 512 to receive full address to transmit
	if((data_manipulation == TRUE) && (high_capacity == FALSE))
		data *= BLOCK_LENGTH;					 
	
	//Set first element of full_command to the command to be transmitted
	full_command[0] = command;		

	//This loop breaks the data/address into 4 bytes to be transmitted. Since 
	//the data is brought into function as a long, it must be typecast to an unsigned
	//integer to transmit properly. The data is anded with 0xFF to get what data is located
	//in the last two bytes of data. Data is then right shifted by eight to test the next 
	//byte.  
	for(i=4;i>0;i--)
	{
		full_command[i] = (Uint16)(Uint32)(data & 0x000000FF);
		data = data >> 8;
	}
    
	//Set last element of full_command to the crc value to be transmitted
	if(crc_enabled == TRUE)
    	full_command[5] = sd_crc7(full_command);
	else
		full_command[5] = crc;
    
    for(i=0;i<6;i++)						//Transmit full command 
    	spi_xmit_byte(full_command[i]);			
} 
//############################ SPI_XMIT_COMMAND ##############################


//################################ SD_CRC7 ###################################
Uint16 sd_crc7(Uint16 full_command[6])
{
	Uint16 i,j,command,crc = 0x00;
   	                                           
    for (i=0;i<5;i++)
    {
		command = full_command[i];		
       	for (j=0;j<8;j++)
      	{
         	crc = crc << 1;					//Shift crc left by 1			
         	if ((command ^ crc) & 0x80)	//Test command XOR with crc and masked with 0x8000
         		crc = crc ^ 0x09;  		//XOR crc with 0x0900
         	command = command << 1;			//Shift command left by 1
      	}

       	crc = crc & 0x7F;					//Mask CRC with 0x7F00
   	}
   
   	crc = crc << 1;							//Shift crc left by 1
   	crc |= 0x01;							//CRC ORed with 0x0100
   
  	return(crc);							//Return CRC
}
//################################ SD_CRC7 ###################################


//########################## SD_COMMAND_RESPONSE #############################
void sd_command_response()
{
	Uint16 i;

	RESET_RESPONSE;							//Reset Response
		
	//This loop continously transmits 0xFF in order to receive response from card. 
	//The card is expected to return 00 or 01 stating that it is in idle state or 
	//it has finished it's initialization(SUCCESS). If anything is received besides
	//0x00, 0x01, or 0xFF then an error has occured. 
	for(i=0;i<8;i++)
	{
		response = spi_xmit_byte(DUMMY_DATA);
		//If response is 0x00 or 0x01 break from loop		
		if ((response == IN_IDLE_STATE) || (response == SUCCESS))
			break;
		//If response is not 0x00, 0x01, or 0xFF branch to sd_error
		else if (response != DUMMY_DATA)
			sd_error();
	}
}
//########################## SD_COMMAND_RESPONSE #############################


//############################### SD_ERROR ###################################
void sd_error()
{	
	//For this example all errors are sent to this trap function. Specific application 
	//will have to be written to handle errors.
	 
	CS_HIGH;								//Pull CS high			
   	//After receiving response clock must be active for 8 clock cycles
	EIGHT_CLOCK_CYCLE_DELAY;

	asm(" ESTOP0");							//Emulation stop
   	for(;;){};								//Loop forever
}
//############################### SD_ERROR ###################################

//############################### sd_writedata ###################################
FATFS fs;         /* Work area (file system object) for logical drive */
FIL fsrc;         /* file objects */
FRESULT res=FR_OK;
UINT br;

//char path[512]="0:";
Uint8 textFileBuffer[] = "感谢您使用研旭28335开发版 ！^_^ \r\n";
FRESULT h;
FRESULT t;
char m[]="0:/data.txt";

void sd_writedata(void)
{

   	sd_card_insertion();			// SD卡插入检测

	sd_initialization();			// SD卡初始化

//	sd_read_register(SEND_CSD);		// 读 CSD register
//	sd_read_register(READ_OCR);		// 读 OCR register
//	sd_read_register(SEND_CID);		// 读 CID register

//	res = f_unlink(m);    // 删除SD卡内同名文件
	h=f_mount(0,&fs);      // 在磁盘注册一个工作缓冲区
	if(h!=FR_OK)          // 文件注册失败，程序暂停
	asm(" ESTOP0");

//	f_mkfs(0,0,1024);     // 格式化SD卡
//	if(t!=FR_OK)          // 文件注册失败，程序暂停
//	asm(" ESTOP0");
//	h=f_mount(0,&fs);      // 在磁盘注册一个工作缓冲区
//	if(h!=FR_OK)          // 文件注册失败，程序暂停
//	asm(" ESTOP0");
	res = f_open( &fsrc , m , FA_CREATE_ALWAYS | FA_WRITE);    // 新建一个文件 如果文件已存在则覆盖

	if ( res == FR_OK )
	{
	    /* Write buffer to file */
		res = f_write(&fsrc, textFileBuffer, sizeof(textFileBuffer), &br);
		/*close file */
		f_close(&fsrc); //如果此句屏蔽则文件内容不会被写入SD卡
	}
	//	res = f_unlink(m);
	//	res=f_read(&fsrc,read,sizeof(textFileBuffer), &br);

	asm(" ESTOP0");				//Emulation stop


}
//############################### sd_writedata ###################################
