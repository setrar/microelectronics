void SerialInit(void);
void SerialPutBytes(uint8_t Data[],uint16_t Count);
void SerialPutByte(uint8_t Data);
uint8_t SerialPeekByte(void);
uint8_t SerialGetByte(void);
char *SerialGets(char *s,int Num);