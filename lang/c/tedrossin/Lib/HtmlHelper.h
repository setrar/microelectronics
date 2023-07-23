#ifndef HTML_HELPER_H
#define HTML_HELPER_H

#include "WebServer.h"

class HtmlHelper{
  public:
    HtmlHelper();
    void Init(WebServer *Ws);

    void SendHeader(void);
    void SendFooter(void);
    void CreateInputField(uint8_t Size,const char *Value,const char *Name,const char *Label);
    void CreateWidthInputField(uint8_t Size,unsigned int Width,const char *Value,const char *Name,const char *Label);
    void CreateButton(const char *Message,const char *Text);
    void CreateButton(const char *Message,const char *Text,uint8_t R,uint8_t G,uint8_t B);
    void CreateSubmitButton(const char *Message,const char *Value,const char *Text);
    void CreateSubmitButton(const char *Message,const char *Value,const char *Text,uint8_t R,uint8_t G,uint8_t B);
    int Parse(const char *Resp);
    int FetchNumParsePairs(void);
    char *FetchParsePairName(int Index);
    char *FetchParsePairValue(int Index);
    void SetCallBack(const char *Name,void (*Cb)(const char *Value));
    void SetImageCallBack(const char *ImageName,void (*Cb)(void));
    void RemoveCallBacks(void);

  private:
    #define MAX_NAME	50
    #define MAX_CALLBACKS	30
    #define MAX_PARSE_STRINGS 	20
    #define MAX_PARSE_STRING_LEN	300
    #define MAX_PARSE_NAME_LEN	50

    int mNumStrings;
    int mStringIndex[MAX_PARSE_STRINGS];
    char mStringTemp[MAX_PARSE_STRING_LEN];
    char mStringName[MAX_PARSE_NAME_LEN];
    WebServer *pWs;

    struct{
        char Name[MAX_NAME];
        void (*Cb)(const char *);
    }mCallBacks[MAX_CALLBACKS];
    int mNumCallBacks;

    struct{
        char ImageName[MAX_NAME];
        void (*Cb)(void);
    }mImageCallBacks[MAX_CALLBACKS];
    int mNumImageCallBacks;    
};
#endif
