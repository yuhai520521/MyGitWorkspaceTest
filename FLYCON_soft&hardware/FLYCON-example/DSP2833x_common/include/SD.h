//############################################################################
//
// FILE:   SD.h
//
// TITLE:  Command, Data Token, Global Prototypes, and Global Variables
//
#include "DSP2833x_Device.h"     // DSP280x Headerfile Spi Include File

//SD Standard Commands  结构：01xxxxxx,后面是6位命令号;0x40+CMD0
#define GO_IDLE_STATE          		0x40
#define SEND_OP_COND  				0x41
#define SWITCH_FUNC					0x46
#define SEND_IF_COND				0x48
#define SEND_CSD	  				0x49
#define SEND_CID	  				0x4A
#define	STOP_TRANSMISSION			0x4C
#define SEND_STATUS 				0x4D
#define	SET_BLOCKLEN				0x50
#define READ_SINGLE_BLOCK 			0x51
#define READ_MULTIPLE_BLOCK			0x52
#define WRITE_BLOCK 				0x58
#define	WRITE_MULTIPLE_BLOCK		0x59
#define PROGRAM_CSD					0x5B
#define SET_WRITE_PROT				0x5C
#define CLR_WRITE_PROT				0x5D
#define SEND_WRITE_PROT				0x5E
#define ERASE_WR_BLK_START_ADDR 	0x60
#define ERASE_WR_BLK_END_ADDR 		0x61
#define ERASE 						0x66
#define	LOCK_UNLOCK					0x6A
#define APP_CMD						0x77
#define GEN_CMD						0x78
#define READ_OCR	 				0x7A
#define CRC_ON_OFF					0x7B

//SD Application Specific Commands
#define	SD_STATUS					0x4D
#define SEND_NUM_WR_BLOCKS			0x56
#define SET_WR_BLK_ERASE_COUNT		0x57
#define SD_SEND_OP_COND				0x69
#define SET_CLR_CARD_DETECT			0x6A
#define SEND_SCR					0x73

//Data Tokens
#define INITIAL_CRC 				0x95
#define DUMMY_CRC 					0xFF
#define DUMMY_DATA 					0xFF
#define START_BLOCK					0xFE
#define MULTIPLE_START_BLOCK 		0xFC
#define MULTIPLE_STOP_TRANSMISSION	0xFD
    #define SECTOR_ZERO 		    	128//0x0000
#define STUFF_BITS 					0x00
#define BUSY						0x00
#define SINGLE_SECTOR				0x01
#define MULTIPLE_WRITE				0x01
#define CRC_ON						0x01
#define CRC_OFF						0x00
#define BLOCK_LENGTH				0x02
#define TRUE  						0x01
#define FALSE 						0x00
#define CHECK_PATTERN				0xAA
#define SUPPLY_VOLTAGE				0x01
#define HIGH_CAPACITY				0x40
#define SUPPORTED_VOLTAGE			0xFF
#define INTERFACE_COND				0x1AA    // 426
#define VER2_OP_COND				1073741824

//Status and Error Codes
#define IN_IDLE_STATE 				0x01
#define SUCCESS 					0x00
#define DATA_ACCEPTED 				0x05
#define CRC_ERROR 					0x0B
#define WRITE_ERROR 				0x0D
#define ERROR						0x01
#define CC_ERROR					0x02
#define CARD_ECC_FAILED				0x04
#define OUT_OF_RANGE				0x08
#define ILLEGAL_COMMAND_IDLE_STATE  0x05

//Continuous Commands
#define CS_HIGH GpioDataRegs.GPASET.bit.GPIO23 = 1;
#define	CS_LOW GpioDataRegs.GPACLEAR.bit.GPIO23 = 1;
#define RESET_RESPONSE response = 0xFF;
#define EIGHT_CLOCK_CYCLE_DELAY spi_xmit_byte(DUMMY_DATA);

//Global Prototypes

//Functions located in SD_SPI_Erase.c
extern void sd_erase_block(Uint16 starting_sector, Uint16 total_sectors);

//Functions located in SD_SPI_Initialization.c
extern void spi_initialization();
extern void led_initialization();
  void sd_card_insertion();
extern void sd_initialization();
extern void sd_version1_initialization();
extern void sd_version2_initialization();

//Functions located in SD_SPI_Read.c
extern void sd_read_block(Uint16 sector, Uint8 *pBuffer);
extern void sd_read_multiple_block(Uint16 sector, Uint8 *pBuffer, Uint16 total_sectors);
extern void sd_data_response(Uint8 *pBuffer, Uint16 total_sectors);

//Functions located in SD_SPI_Registers.c
extern void sd_read_register(Uint16 command);
extern void sd_ocr_response();
extern void sd_cid_csd_response(Uint16 command);
extern void sd_send_status();
extern void sd_switch_function(Uint16 *pBuffer);

//Functions located in SD_SPI_Transmission.c
extern Uint16 spi_xmit_byte(Uint16 byte);
extern void spi_xmit_command(Uint16 command, Uint32 data, Uint16 crc);
extern Uint16 sd_crc7(Uint16 full_command[6]);
extern void sd_command_response();
extern void sd_error();

//Functions located in SD_SPI_Write.c
extern void sd_write_block(Uint16 sector, Uint8 *pBuffer);
extern void sd_write_multiple_block(Uint16 sector, Uint8 *pBuffer, Uint16 total_sectors);
extern void sd_write_data(Uint8 *pBuffer, Uint16 total_sectors, Uint16 multiple_write);
void sd_writedata(void);

//Global Variables
extern Uint16 response, ocr_contents[5], csd_contents[16], cid_contents[16];
extern Uint16 card_status[2], data_manipulation, high_capacity, crc_enabled;


