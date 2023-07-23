/*
 *  JavaScript class: A collection of helper functions to Javascript and HTML 5 
 *                    canvas graphics on the fly.
 *        Ted Rossin: 10-23-2018
 *                     6-29-2023
*/

#include <stdlib.h>
#include "pico/stdlib.h"
#include "JavaScript.h"
#include "WebServer.h"

JavaScript::JavaScript(void)
{
    pWs = NULL;
    EnableCanvas = 0;
}

void JavaScript::Init(WebServer *Ws)
{
    pWs = Ws;
    pWs->SendText("<script>\n");
    pWs->SendText("var gReq;\n");  // Global that is used for RequestUpdate
    EnableCanvas = 0;
}

void JavaScript::InitCanvas(WebServer *Ws,unsigned int Width,unsigned int Height)
{
    pWs = Ws;
    pWs->Printf("<canvas id=\"myCanvas\" width=\"%d\" height=\"%d\"\n",Width,Height);
      // Allow the border color to be set (or just get rid of it
    pWs->SendText("style=\"border:1px solid #c3c3c3;\">\n");
    pWs->SendText("Your browser does not support the canvas element.\n");
    pWs->SendText("</canvas>\n");

    pWs->SendText("<script>\n");
    pWs->SendText("var canvas = document.getElementById(\"myCanvas\");\n");
    pWs->SendText("var ctx = canvas.getContext(\"2d\");\n");
    pWs->SendText("var gReq;\n");  // Global that is used for RequestUpdate
    EnableCanvas = 1;
}

void JavaScript::FillRect(int X,int Y,int Width,int Height)
{
    pWs->Printf("ctx.fillRect(%d,%d,%d,%d);\n",X,Y,Width,Height);
}
  
void JavaScript::FillStyle(unsigned char R,unsigned char G, unsigned char B)
{ 
    pWs->Printf("ctx.fillStyle = \"#%02x%02x%02x\";\n",R,G,B);
}

void JavaScript::Font(unsigned char Size,const char *Name)
{
    pWs->Printf("ctx.font = \"%dpx %s\";\n",Size,Name);
}

void JavaScript::FillText(unsigned int X,unsigned int Y,const char *Text)
{
    pWs->Printf("ctx.fillText(\"%s\",%d,%d)\n",Text,X,Y);
}

void JavaScript::BeginPath(void)
{
    pWs->SendText("ctx.beginPath();\n");
}

void JavaScript::LineWidth(unsigned int Width)
{
    pWs->Printf("ctx.lineWidth = %d;\n",Width);
}

void JavaScript::LineColor(unsigned char R,unsigned char G,unsigned char B)
{
    pWs->Printf("ctx.strokeStyle =\"#%02x%02x%02x\";\n",R,G,B);
}  

void JavaScript::MoveTo(unsigned int X,unsigned int Y)
{
    pWs->Printf("ctx.moveTo(%d,%d);\n",X,Y);
}

void JavaScript::LineTo(unsigned int X,unsigned int Y)
{
    pWs->Printf("ctx.lineTo(%d,%d);\n",X,Y);
}

void  JavaScript::EndPath(void)
{
    pWs->SendText("ctx.stroke();\n");
}

void JavaScript::EndScript(void)
{
    pWs->SendText("</script>\n");
}

void JavaScript::Line(unsigned int X0,unsigned int Y0,unsigned int X1,unsigned int Y1)
{
    BeginPath();
      MoveTo(X0,Y0);
      LineTo(X1,Y1);
    EndPath();
}

void JavaScript::CreateTimerCallback(const char *FuncName,int Interval_ms)
{
    pWs->Printf("setInterval(%s, %d);\n",FuncName,Interval_ms);
}

void JavaScript::RequestUpdate(const char *Handler,const char* Message)
{
    pWs->SendText("{\ngReq = new XMLHttpRequest();\n");
    pWs->Printf("gReq.onreadystatechange = %s;\n",Handler);
    pWs->Printf("gReq.open(\"GET\", \"%s\", true);\n",Message);
    pWs->SendText("gReq.send(null);\n}\n");
}

void JavaScript::RequestChangeHeader(const char *FuncName)
{
    pWs->Printf("function %s()\n{\n",FuncName);
    pWs->SendText("if(gReq.readyState==4 && gReq.status==200){\n");
}
    
void JavaScript::RequestChangeFooter(void )
{
    pWs->SendText("}\n}\n");
}

void JavaScript::CreateXferFuncs(int Which)
{
    if(Which & JS_XFER_INT32){
        pWs->SendText("function FetchArray_int32(Input,Count,Result)\n{\n");
        pWs->SendText("var Loop;\n");

        pWs->SendText("for(Loop=0;Loop<Count;Loop++){\n");
            pWs->SendText("Result[Loop] = Number('0x'+Input.slice(8*Loop,8*Loop+8));\n");
            pWs->SendText("if(Result[Loop] & 0x80000000) Result[Loop] = -((~Result[Loop]&0xffffffff)+1);\n");
        pWs->SendText("}\n");
        pWs->SendText("return(8*Count);\n}\n");
    }
    if(Which & JS_XFER_UINT32){
        pWs->SendText("function FetchArray_uint32(Input,Count,Result)\n{\n");
        pWs->SendText("var Loop;\n");

        pWs->SendText("for(Loop=0;Loop<Count;Loop++){\n");
            pWs->SendText("Result[Loop] = Number('0x'+Input.slice(8*Loop,8*Loop+8));\n");
        pWs->SendText("}\n");
        pWs->SendText("return(8*Count);\n}\n");
    }

    if(Which & JS_XFER_INT16){
        pWs->SendText("function FetchArray_int16(Input,Count,Result)\n{\n");
        pWs->SendText("var Loop;\n");

        pWs->SendText("for(Loop=0;Loop<Count;Loop++){\n");
    	    pWs->SendText("Result[Loop] = Number('0x'+Input.slice(4*Loop,4*Loop+4));\n");
    	    pWs->SendText("if(Result[Loop] & 0x8000) Result[Loop] = -((~Result[Loop]&0xffff)+1);\n");
        pWs->SendText("}\n");
        pWs->SendText("return(4*Count);\n}\n");
    }

    if(Which & JS_XFER_UINT16){
        pWs->SendText("function FetchArray_uint16(Input,Count,Result)\n{\n");
        pWs->SendText("var Loop;\n");

        pWs->SendText("for(Loop=0;Loop<Count;Loop++){\n");
    	    pWs->SendText("Result[Loop] = Number('0x'+Input.slice(4*Loop,4*Loop+4));\n");
        pWs->SendText("}\n");
        pWs->SendText("return(4*Count);\n}\n");
    }

    if(Which & JS_XFER_INT8){
        pWs->SendText("function FetchArray_int8(Input,Count,Result)\n{\n");
        pWs->SendText("var Loop;\n");

        pWs->SendText("for(Loop=0;Loop<Count;Loop++){\n");
    	    pWs->SendText("Result[Loop] = Number('0x'+Input.slice(2*Loop,2*Loop+2));\n");
    	    pWs->SendText("if(Result[Loop] & 0x80) Result[Loop] = -((~Result[Loop]&0xff)+1);\n");
        pWs->SendText("}\n");
        pWs->SendText("return(2*Count);\n}\n");
    } 

    if(Which & JS_XFER_UINT8){
        pWs->SendText("function FetchArray_int8(Input,Count,Result)\n{\n");
        pWs->SendText("var Loop;\n");

        pWs->SendText("for(Loop=0;Loop<Count;Loop++){\n");
    	    pWs->SendText("Result[Loop] = Number('0x'+Input.slice(2*Loop,2*Loop+2));\n");
        pWs->SendText("}\n");
        pWs->SendText("return(2*Count);\n}\n");
    }

    if(Which & JS_XFER_STRING){
        pWs->SendText("function FetchArray_string(Input,Count,Size,Result)\n{\n");
        pWs->SendText("var Loop;\n");

        pWs->SendText("for(Loop=0;Loop<Count;Loop++){\n");
    	    pWs->SendText("Result[Loop] = Input.slice(Size*Loop,Size*Loop+Size);\n");
        pWs->SendText("}\n");
        pWs->SendText("return(Size*Count);\n}\n");
    }
}
