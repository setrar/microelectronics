#ifndef TFT320x240Fb_H

#define TFT320x240Fb_H 1

#define DISP_HEIGHT 240
#define DISP_WIDTH  320

#define COLOR565(R,G,B) (((R&0x1f)<<11) | ((G&0x3f)<<5) | (B&0x1f))

void gfInit(void);
void gfClearDisplay(void);

void gfLine(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t Color);
void gfHLine(uint16_t x, uint16_t y, uint16_t l, uint16_t Color);                  
void gfVLine(uint16_t x, uint16_t y, uint16_t l, uint16_t Color);                   
void gfRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t Color);
void gfRectFill(uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint16_t Color);
void gfDrawPixel(uint16_t X,uint16_t Y, uint16_t Color);
void gfCircle(uint16_t xc,uint16_t yc,uint16_t r,uint16_t Color);
void gfCircleFill(uint16_t xc,uint16_t yc,uint16_t r,uint16_t Color);
void gfLine(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t Color);

void gfSetTextColor(uint16_t Color);
void gfSetTextBackgroundColor(uint16_t Color);
void gfSetClearColor(uint16_t Color);
void gfSelectFont(uint8_t Id);
uint8_t gfGetFontWidth(void);
uint8_t gfGetFontHeight(void);
void gfSetFontZoom(uint8_t Factor);
void gfPutc(uint16_t X,uint16_t Y,char c);
void gfPuts(uint16_t X,uint16_t Y,char s[]);

void gfDrawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h,uint16_t Data[]);
void gfDrawRect8(uint16_t x, uint16_t y, uint16_t w, uint16_t h,uint8_t Data[]);

#endif
