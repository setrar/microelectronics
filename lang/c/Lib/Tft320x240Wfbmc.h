#ifndef TFT320x240Wfb_H

#define TFT320x240Wfb_H 1

int wgfInit(uint16_t x,uint16_t y,uint16_t w,uint16_t h);
void wgfFree(int Id);
void wgfUpdateDisplay(uint8_t ClearBuffer);
void wgfClearDisplay(void);
void wgfSetClearColor(uint16_t Color);
void wgfSetActiveWindow(int Id);

void wgfLine(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t Color);
void wgfDrawPixel(uint16_t X,uint16_t Y, uint16_t Color);

#endif
