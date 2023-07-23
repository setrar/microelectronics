/*
 *  HtmlHelper class: A collection of helper functions to create HTML pages on the fly.
 *        Ted Rossin: 10-23-2018
 *                     6-21-2023
*/

#include <stdlib.h>
#include "pico/stdlib.h"
#include "HtmlHelper.h"
#include "WebServer.h"

HtmlHelper::HtmlHelper(void)
{
    pWs = NULL;
    mNumCallBacks = 0;
    mNumImageCallBacks = 0;
}

void HtmlHelper::Init(WebServer *Ws)
{
    pWs = Ws;
    mNumCallBacks = 0;
    mNumImageCallBacks = 0;
}

void HtmlHelper::SendHeader(void)
{
    pWs->SendText(
        "HTTP/1.1 200 OK\n"
        "Content-Type: text/html\n"
        "\n" //  This is needed (for Chrome, Edge and Safari).  I don't know why.
        "<!DOCTYPE html>\n"
        "<html>\n"
        "<body>\n"
    );
}

void HtmlHelper::SendFooter(void)
{
    pWs->SendText("</body>\n"
        "</html>\n"
    ); 
}

void HtmlHelper::CreateInputField(uint8_t Size,const char *Value,const char *Name,const char *Label)
{ 
  pWs->Printf("<input type=\"text\" size=%d value=\"%s\" name=\"%s\" style=height:50px;width:150px;font-size:45px;><font size=\"+2\"> %s</font><br>\n"
    ,Size,Value,Name,Label);
}

void HtmlHelper::CreateWidthInputField(uint8_t Size,unsigned int Width,const char *Value,const char *Name,const char *Label)
{ 
  pWs->Printf("<input type=\"text\" size=%d value=\"%s\" name=\"%s\" style=height:50px;width:%dpx;font-size:45px;><font size=\"+2\"> %s</font><br>\n"
    ,Size,Value,Name,Width,Label);
}

void HtmlHelper::CreateButton(const char *Message,const char *Text)
{
  pWs->Printf("<a href=\"/%s\"><button style=\"border-radius:15px;height:50px;font-size:40px\">%s</button></a>\n",Message,Text);
}

void HtmlHelper::CreateButton(const char *Message,const char *Text,uint8_t R,uint8_t G,uint8_t B)
{
  pWs->Printf("<a href=\"/%s\"><button style=\"border-radius:15px;height:50px;background-color:#%02x%02x%02x;font-size:40px\">%s</button></a>\n"
    ,Message,R,G,B,Text);
}

void HtmlHelper::CreateSubmitButton(const char *Message,const char *Value,const char *Text)
{             
  pWs->Printf("<button type=\"submit\" name=\"%s\" value=\"%s\" style=height:50px;border-radius:15px;font-size:40px;>%s</button>\n"
    ,Message,Value,Text); 
}

void HtmlHelper::CreateSubmitButton(const char *Message,const char *Value,const char *Text,uint8_t R,uint8_t G,uint8_t B)
{            
  pWs->Printf("<button type=\"submit\" name=\"%s\" value=\"%s\" style=height:50px;border-radius:15px;background-color:#%02x%02x%02x;font-size:40px;>%s</button>\n"
    ,Message,Value,R,G,B,Text); 
}

int HtmlHelper::FetchNumParsePairs(void)
{
    return(mNumStrings);
}

char *HtmlHelper::FetchParsePairName(int Index)
{
    char *ptr;
    int i;
    
    if(Index<mNumStrings){
        ptr = &mStringTemp[mStringIndex[Index]];
        mStringName[0] = 0;
        for(i=0;i<MAX_PARSE_NAME_LEN;i++){
            if(*ptr=='=' || *ptr==0){
                mStringName[i] = 0;
                break;
            }
            else{
                mStringName[i] = *ptr++;
            }
        }
        if(i==MAX_PARSE_NAME_LEN) mStringName[i-1] = 0;
        return(mStringName);
    }
    return(NULL);
}

char *HtmlHelper::FetchParsePairValue(int Index)
{
    char *ptr;
    int i;

    if(Index<mNumStrings){
        ptr = &mStringTemp[mStringIndex[Index]];
        for(i=0;*ptr;i++){
            if(*ptr++=='=') return(ptr);
        }
    }
    return((char *)"Bogus");
}

void HtmlHelper::RemoveCallBacks(void)
{
    mNumCallBacks = 0;
    mNumImageCallBacks = 0;
}

void HtmlHelper::SetCallBack(const char *Name,void (*Cb)(const char *Value))
{
    if(mNumCallBacks>MAX_CALLBACKS) return;

    strncpy(mCallBacks[mNumCallBacks].Name,Name,MAX_NAME);
    mCallBacks[mNumCallBacks].Name[MAX_NAME-1] = 0;
    mCallBacks[mNumCallBacks].Cb = Cb;

    mNumCallBacks++;
}

void HtmlHelper::SetImageCallBack(const char *ImageName,void (*Cb)(void))
{
    if(mNumImageCallBacks>MAX_CALLBACKS) return;

    strncpy(mImageCallBacks[mNumImageCallBacks].ImageName,ImageName,MAX_NAME);
    mImageCallBacks[mNumImageCallBacks].ImageName[MAX_NAME-1] = 0;    
    mImageCallBacks[mNumImageCallBacks].Cb = Cb;

    mNumImageCallBacks++;
}

int HtmlHelper::Parse(const char *Response)
{
    int Start,i,Index,Value,OutIndex,FoundImageCallBack;
    char *Ptr,HexString[3];
    char Resp[1000];

    if(mNumImageCallBacks){
            // See if this is an image request
        if(strstr(Response,"Accept: image/")){
            Resp[0] = 0;
            sscanf(Response,"GET /%s HTTP",Resp);
            FoundImageCallBack = 0;
            for(i=0;!FoundImageCallBack && i<mNumImageCallBacks;i++){           
                if(strstr(Resp,mImageCallBacks[i].ImageName)){
                    (*mImageCallBacks[i].Cb)();
                    FoundImageCallBack = 1;
                }
            }
            if(!FoundImageCallBack){          
                pWs->SendText("HTTP/1.1 404 Not Found\nConnection: close\n\n");
            }   
            return(1);
        }
    }

    HexString[2] = 0;  OutIndex = 0;
    mNumStrings = 0;
    mStringIndex[0] = 0;

        // Just deal with the first line of request
    strncpy(Resp,Response,1000);  Resp[999] = 0;
    Ptr = strstr(Resp,"\n");
    if(Ptr) *Ptr = 0;

    Start = 0;
    if(!strncmp(Resp,"GET",3)) Start = 4;
    for(i=Start;Resp[i];i++){
        if(Resp[i]=='?'){
            OutIndex = 0;
            mNumStrings = 0;
        }
        else if(Resp[i]=='&' || Resp[i]==' '){
            mStringTemp[OutIndex++] = 0;
            mNumStrings++;
	          if(mNumStrings>=MAX_PARSE_STRINGS) mNumStrings--;
            mStringIndex[mNumStrings] = OutIndex;
        }
        else{
            if(Resp[i]=='%'){
                i++;
                HexString[0] = Resp[i++];
                HexString[1] = Resp[i];
                sscanf(HexString,"%x",&Value);
                mStringTemp[OutIndex++]=(char)Value;
            }
            else{
                if(Resp[i]=='+')
                    mStringTemp[OutIndex++] = ' ';
                else{
                    if(Resp[i]!='/') mStringTemp[OutIndex++] = Resp[i];
                }
            }
        }
        if(OutIndex>=MAX_PARSE_STRING_LEN){ 
            OutIndex--;
            mStringTemp[OutIndex] = 0;
        }
    }
    if(mNumStrings==1){ // Bad algorithm so do a clean up check
	    if(!strstr(mStringTemp,"=")) mNumStrings=0;  // No Name=Value pair
    }

    if(mNumCallBacks){
        for(Index=0;Index<mNumStrings;Index++){
            Ptr = FetchParsePairName(Index);
            if(Ptr){
                for(i=0;i<mNumCallBacks;i++){
                    if(!strcmp(mCallBacks[i].Name,Ptr)){
                        (*mCallBacks[i].Cb)(FetchParsePairValue(Index));
                    }
                }
            }
        }
    }
    return(0);
}