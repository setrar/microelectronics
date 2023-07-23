#define SD_INVALID_CARD	0xff
#define SD_INVALID_FS	0xfe
#define SD_MMC_CARD		0x00
#define SD_VER1_CARD	0x01
#define SD_VER2_CARD	0x02
#define SD_VER2_HD_CARD	0x03

uint8_t SDInit(void);
void SDCmd(unsigned char Command,unsigned long Argument);
uint8_t SDReadSector(unsigned long Addr,uint8_t *Buf);
uint8_t SDWriteSector(unsigned long Addr,uint8_t *Buf);