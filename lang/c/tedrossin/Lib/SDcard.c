/*
   SDcard.c:  Interface to MMC/SD cards
	Ted Rossin:	11-30-2011 original code written for a PIC
				 8-04-2022   
				
      Interface to SD card.
	     MISO GPIO 16
		 CSn  GPIO 17
		 Sclk GPIO 18
		 MOSI GPIO 19
  
  Notes:
     check out http://elm-chan.org/docs/mmc/mmc_e.html
		
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#include "SDcard.h"

#define CSn	17


#define SD_CMD_GO_IDLE_STATE		( 0 | 0x40)
#define SD_CMD_SEND_OP_COND			( 1 | 0x40)
#define SD_CMD_GO_IDLE_STATE_CRC		  0x95
#define SD_CMD_SEND_IF_COND			( 8 | 0x40)
#define SD_CMD_APP_CMD				(55 | 0x40)
#define SD_APP_SEND_OP_COND			(41 | 0x40)  // HCS is bit 30
#define SD_CMD_READ_OCR				(58 | 0x40)
#define SD_CMD_SET_BLOCKLEN			(16 | 0x40)
#define SD_CMD_READ_SINGLE_BLOCK 	(17 | 0x40)
#define SD_CMD_WRITE_BLOCK 			(24 | 0x40)


#define SD_R1_NO_ERROR			0x00
#define SD_R1_IN_IDLE_STATE		0x01
#define SD_R1_ERASE_RESET		0x02
#define SD_R1_ILLEGAL_COMMAND	0x04
#define SD_R1_COM_CRC_ERROR		0x08
#define SD_R1_ERASE_SEQ_ERROR	0x10
#define SD_R1_ADDRESS_ERROR		0x20
#define SD_R1_PARAMETER_ERROR	0x40
#define SD_R1_NO_RESPONSE		0x80

#define SD_READ_ERROR			0x01
#define SD_READ_CC_ERROR		0x02
#define SD_READ_ECC_ERROR		0x04
#define SD_READ_OUT_OF_RANGE	0x08

static int HighDensity = 0;

#define SPI_SPEED_10MHz	1
#define SPI_SPEED_20MHz	2

static void SpiSetSpeed(uint8_t Speed)
{
	switch(Speed){
		case SPI_SPEED_10MHz:
			spi_set_baudrate (spi0,10000*1000); 
			break;
		case SPI_SPEED_20MHz:
			spi_set_baudrate (spi0,20000*1000);
			break;
	}   
}

static uint8_t SpiRead(void)
{
     uint8_t Buf[2];

    spi_read_blocking(spi0,0xff,Buf,1);
    return(Buf[0]);
}

static uint8_t SpiWrite(uint8_t Val)
{
    uint8_t Buf[2];

    Buf[0] = Val;
    spi_write_blocking(spi0,Buf,1);
    return(0);
}

void SDCmd(unsigned char Command,unsigned long Argument)
{
    union{
		uint32_t In;
		uint8_t Out[4];
	} It;
	It.In = Argument;

	while(SpiRead() != 0xff);
	
	SpiWrite(Command | 0x40);
	SpiWrite(It.Out[3]);
	SpiWrite(It.Out[2]);
	SpiWrite(It.Out[1]);
	SpiWrite(It.Out[0]);
	SpiWrite(0xff);
}

uint8_t SDInit(void)
{
    uint8_t Command,Resp2;
    uint8_t Loop,Loop2,Retry;
    uint8_t Type;
    uint16_t Val[8];    
    
    HighDensity = 0;
    spi_init(spi0,500*1000);  // 500 KHz spi on GPIO 16,17,18,19
    spi_set_format(spi0,8,SPI_CPOL_1,SPI_CPHA_1,SPI_MSB_FIRST);  //Mode 3 gives better command setup time
    gpio_set_function(16,GPIO_FUNC_SPI);    // MISO
    gpio_set_function(17,GPIO_FUNC_SIO);    // CSn
    gpio_set_dir(17,true);  // Output
    gpio_put(17,1);  // CSn=1
    gpio_set_function(18,GPIO_FUNC_SPI);    // Sclk
    gpio_set_function(19,GPIO_FUNC_SPI);    // MOSI


		// Wiggle the clock to help initialize the card without nCS asserted
	gpio_put(CSn,1);
	for(Loop=0;Loop<10;Loop++){  // From Spec.  Need 72 clocks.
		SpiRead();  
	}
	sleep_ms(100);

    Retry = 1;
	Command = SD_R1_NO_RESPONSE;  
	for(Retry=0;(Command & SD_R1_NO_RESPONSE) && Retry<200;Retry++){
		gpio_put(CSn,0);  // Enable SD card
		sleep_ms(20);
		SpiWrite(SD_CMD_GO_IDLE_STATE);  // CMD0 (R1 format return)
		SpiWrite(0);  SpiWrite(0); SpiWrite(0); SpiWrite(0);
		SpiWrite(SD_CMD_GO_IDLE_STATE_CRC);
		
		Command = SD_R1_NO_RESPONSE; 
		for(Loop=0;Command & SD_R1_NO_RESPONSE && Loop<100;Loop++){	
			Command = SpiRead();
		}
	}
	if(Command & SD_R1_NO_RESPONSE) return(SD_INVALID_CARD);
//printf("Made it to IDLE state\r\n");

	sleep_ms(20);
	
	while(SpiRead() != 0xff);
	SpiWrite(SD_CMD_SEND_IF_COND);  // CMD8 (R7 format return)
	SpiWrite(0);
	SpiWrite(0);
	SpiWrite(0x01);  // Voltage range 2.7 to 3.6
	SpiWrite(0xaa);  // Check pattern 0xaa
	SpiWrite(0x87);  // Need correct CRC (can't use 0xff)
	
	Command=SD_R1_NO_RESPONSE;
	for(Loop=0;Command & SD_R1_NO_RESPONSE;Loop++){
		if(Loop==255){ 
//printf("Timeout on IF_COND command\r\n");            
			return(SD_INVALID_CARD);
		}
		Command = SpiRead();
	}
	Val[0] = Loop;
	Val[1] = Command;  // R1 portion of response
	Val[2] = SpiRead();
	Val[3] = SpiRead();
	Val[4] = SpiRead();
	Val[5] = SpiRead();	
//printf("SEND_IF_COND: Loop=%d R1=0x%02x 0x%02x_%02x_%02x_%02x\r\n",Loop,Command,Val[2],Val[3],Val[4],Val[5]);

	if(Command & SD_R1_ILLEGAL_COMMAND){  // Illegal command so Ver1.x SD or MMC card
		Type = SD_VER1_CARD;
	}
	else{  // Ver 2.00 or later SD card
		Type = SD_VER2_CARD;
	}
	Command = SD_R1_IN_IDLE_STATE;
	for(Loop=0;Command & SD_R1_IN_IDLE_STATE && Loop<200;Loop++){
		sleep_ms(20);
		Resp2 = SD_R1_NO_RESPONSE;
		SDCmd(SD_CMD_APP_CMD,0);  // CMD55 (R1 response)
		for(Loop2=0;Resp2 & SD_R1_NO_RESPONSE;Loop2++){
			Resp2 = SpiRead();            
			if(Loop2==255){
//printf("Timeout waiting on response to APP_CMD\r\n");
                return(SD_INVALID_CARD);
            }
		}	
		if(Type==SD_VER2_CARD)  // Request high capacity mode
			SDCmd(SD_APP_SEND_OP_COND,0x40000000);  // ACMD41 (R1 response)
		else
			SDCmd(SD_APP_SEND_OP_COND,0);  // ACMD41 (R1 response)			
		Command = SD_R1_NO_RESPONSE;
		for(Loop2=0;Command & SD_R1_NO_RESPONSE;Loop2++){
			Command = SpiRead();
			if(Loop2==255){ 
//printf("Timeout waiting on response to OP_COND\r\n");                
                return(SD_INVALID_CARD);
            }
		}	
		
		if(Type == SD_VER2_CARD){
			if(Command & SD_R1_ILLEGAL_COMMAND){
			}
		}
		else{
			if(Loop==0 && (Command & SD_R1_ILLEGAL_COMMAND)) Loop=254;
		}				
	}

	if(Command & SD_R1_ILLEGAL_COMMAND){ // MMC card (Need to use CMD1 to initialize)
		Type=SD_MMC_CARD;
		Command = SD_R1_IN_IDLE_STATE;
		for(Loop=0;Command & SD_R1_IN_IDLE_STATE && Loop<200;Loop++){
			sleep_ms(10);

			SDCmd(SD_CMD_SEND_OP_COND,0);  // CMD1 (R1 response)
			Command = SD_R1_NO_RESPONSE;
			for(Loop2=0; Command & SD_R1_NO_RESPONSE; Loop2++){
				sleep_ms(10);
				Command = SpiRead();
				if(Loop2==20){
//printf("Timeout waiting on response to OP_COND\r\n");                    
                    return(SD_INVALID_CARD);
                }
			}	
		}
	}
//printf("Debug point 2\r\n");
	if(Command & SD_R1_IN_IDLE_STATE){
//puts("R1_IN_IDLE_STATE\r\n");        
		return(SD_INVALID_CARD);
	}
//puts("Debug point 3\r\n");	
	if(Type==SD_VER2_CARD){
		SDCmd(SD_CMD_READ_OCR,0);  // CMD58( R3 response)
		Command = SD_R1_NO_RESPONSE;  // Bug fix for quick response to read ocr
		for(Loop2=0; Command & SD_R1_NO_RESPONSE; Loop2++){
			Command = SpiRead();
			if(Loop2==200){ 
//puts("Timeout waiting for response to READ_OCR\r\n");                
                return(SD_INVALID_CARD);
            }
		}
		Val[0] = Command;	// R1
		Val[1] = SpiRead(); // OCR[31:24]
		Val[2] = SpiRead(); // 
		Val[3] = SpiRead(); // 
		Val[4] = SpiRead(); // OCR[31:24]

//sprintfx(Buf,"%02x %02x %02x %02x %02x\r\n",Val);  puts(Buf);		
		if(Val[1] & 0x40){ // CCS bit		
			HighDensity = 1;
			Type = SD_VER2_HD_CARD;			
		}
	}
    SpiSetSpeed(SPI_SPEED_20MHz);
	Command = SD_R1_NO_RESPONSE;
	SDCmd(SD_CMD_SET_BLOCKLEN,512);
	for(Loop=0;Command & SD_R1_NO_RESPONSE && Loop<250;Loop++){
		Command = SpiRead();
	}
//sprintf1(Buf,"Type=0x%02x\r\n",Type);  puts(Buf);
	return(Type);
}

uint8_t SDWriteSector(unsigned long Addr,uint8_t *Buf)
{
    uint8_t Resp,Loop;
    uint16_t DataLoop;
   
    if(!HighDensity) Addr = Addr<<9;  // Convert sector to add 
	SDCmd(SD_CMD_WRITE_BLOCK,Addr); 
	Resp = SD_R1_NO_RESPONSE;
	for(DataLoop=0;Resp & SD_R1_NO_RESPONSE && DataLoop<30000;Loop++){
		Resp = SpiRead();
	}
	if(Resp != SD_R1_NO_ERROR){
		//sprintf1(Buf,"Data write command error 0x%02x recieved\r\n",Resp); puts(Buf);
//puts("Data write command error\r\n");
		return(0xff);
	}
	SpiWrite(0xfe);  // Start data token
		// Send 512 bytes
	for(DataLoop=0;DataLoop<512;DataLoop++){
		SpiWrite(*Buf++);
	}
		// Dummy CRC.
	SpiWrite(0xff);
	SpiWrite(0xff);
	
		// Wait for response.
	
	Resp = 0xff;	
	for(Loop=0;Resp & 0x10 && Loop<250;Loop++){
		Resp = SpiRead(); 
	}
	if((Resp&0x1f) != 0x05){  // Make sure data was accepted
//		sprintf1(Buf,"Data write response error 0x%02x recieved\r\n",Resp); puts(Buf);
//puts("Data write response error\r\n");
		return(0xff);
	}
		// Wait for Write to complete
	Resp = 0;
	
	for(DataLoop=0;Resp != 0xff && DataLoop<30000;DataLoop++){
		Resp = SpiRead(); // Looking for 0xff
	}

	if(Resp != 0xff){
		for(DataLoop=0;DataLoop<1000;DataLoop++){
				// Maybe wait a bit longer
			//Wait50us(10); // 0.5ms
			sleep_ms(1);
			Resp = SpiRead(); // Looking for 0xff
			if(Resp==0xff){ 
				return(0);
			}
		}
		return(0xff);		
	}
//	sprintf1(Buf,"Data write busy finished on loop %d\r\n",DataLoop); puts(Buf);
	return(0);
}

uint8_t SDReadSector(unsigned long Addr,uint8_t *Buf)
{
    uint8_t Resp,Loop;
    uint16_t DataLoop;

    if(!HighDensity) Addr = Addr<<9;  // Convert sector to add    
	SDCmd(SD_CMD_READ_SINGLE_BLOCK,Addr);  
	Resp = SD_R1_NO_RESPONSE;
	for(Loop=0;Resp & SD_R1_NO_RESPONSE && Loop<250;Loop++){
		Resp = SpiRead();
	}
	if(Resp & SD_R1_NO_RESPONSE){
//puts("SDReadSector: Timeout on response to READ_SINGLE_BLOCK\r\n");        
		return(0xff);
	}
	else{
			// Get Start block token
		Resp=0xff;
		for(DataLoop=0;Resp!=0xfe && DataLoop<20000;DataLoop++){
			Resp = SpiRead(); // Looking for 0xfe
			if((Resp & 0xf0) == 0x00){
				*Buf = Resp;
//puts("SDReadSector: Timeout on start block token\r\n");                  
				return(0xff);
			}
		}
		if(Resp != 0xfe){
//puts("SDReadSector: Invalid start block token\r\n");             
			return(0xff);
		}
			// Now get 512 bytes

		for(Loop=0;Loop<4;Loop++){
			for(Resp=0;Resp<128;Resp++){
				*Buf++ = SpiRead();
			}
		}
			// Now get two byte CRC.
		SpiRead(); 
		SpiRead();
	}
	return(0);
}