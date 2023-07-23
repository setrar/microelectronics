#ifndef JAVA_SCRIPT_H
#define JAVA_SCRIPT_H

#include "WebServer.h"

#define JS_XFER_INT8   0x0001
#define JS_XFER_UINT8  0x0002
#define JS_XFER_INT16  0x0004
#define JS_XFER_UINT16 0x0008
#define JS_XFER_INT32  0x0010
#define JS_XFER_UINT32 0x0020
#define JS_XFER_STRING 0x0040

class JavaScript{
  public:
    JavaScript();

    void Init(WebServer *Ws);
    void InitCanvas(WebServer *Ws,unsigned int Width,unsigned int Height);
    void CreateTimerCallback(const char *FuncName,int Interval_ms);
    void RequestUpdate(const char *Handler,const char* Message);
    void RequestChangeHeader(const char *FuncName);
    void RequestChangeFooter(void );
    void FillRect(int X,int Y,int Width,int Height);
    void FillStyle(unsigned char R,unsigned char G, unsigned char B);
    void Font(unsigned char Size,const char *Name);
    void FillText(unsigned int X,unsigned int Y,const char *Text);
    void Line(unsigned int X0,unsigned int Y0,unsigned int X1,unsigned int Y1);
    void BeginPath(void);
    void LineWidth(unsigned int Width);
    void LineColor(unsigned char R,unsigned char G,unsigned char B);
    void MoveTo(unsigned int X,unsigned int Y);
    void LineTo(unsigned int X,unsigned int Y);
    void EndPath(void); // stroke
    void EndScript(void);
    void println(const char *s);
    void CreateXferFuncs(int Which);

  private:
    WebServer *pWs;
    int EnableCanvas;
};
#endif
