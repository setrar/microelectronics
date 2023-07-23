#define DISP_WIDTH                  128
#define DISP_HEIGHT                 64

void I2cInit(void);

void gfSwapDisplayBuffer(uint8_t Color);
uint8_t SendCmd(uint8_t Val);
void gfDisplayOLEDInitMC(void);
void gfClearDisplay(void);
void gfSetPixel(uint8_t X,uint8_t Y);
void gfClearPixel(uint8_t X,uint8_t Y);
void gfSetColor(uint8_t c);
void gfSetFill(uint8_t Solid);
void gfHLine(uint8_t X,uint8_t Y,uint8_t Width);
void gfVLine(uint8_t X,uint8_t Y,uint8_t Height);
void gfRect(uint8_t X,uint8_t Y,uint8_t Width,uint8_t Height);
void gfSelectFont(uint8_t Id);
void gfFontZoom(unsigned char Factor);
void gfPutc(uint8_t X,uint8_t Y,uint8_t c);
void gfPuts(uint8_t X,uint8_t Y,char s[]);
void gfLine(int x0,int y0,int x1,int y1);
void gfCircle(uint16_t xc,uint16_t yc,uint16_t r);
void gfCopyRect(uint8_t SrcX,uint8_t SrcY,uint8_t Width,uint8_t Height,uint8_t DstX,uint8_t DstY);
uint8_t gfGetFontWidth(void);
uint8_t gfGetFontHeight(void);

void TerminalInit();
void TerminalScroll();
void TerminalSetCursor(uint8_t X, uint8_t Y);
void TerminalPuts(char s[]);
