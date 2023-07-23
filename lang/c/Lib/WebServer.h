#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "pico/cyw43_arch.h"

#include "lwip/pbuf.h"
#include "lwip/tcp.h"

#define MSG_EMPTY       0
#define MSG_REQUEST     1
#define MSG_CLOSED      2
#define MSG_CANCELED    3

#define INIT_RETRY_FOREVER  1
#define INIT_SINGLE_TIMEOUT 0

typedef struct{
    unsigned int Id;
    int Type;
    const char *Data;
} WebMsg_t;

typedef struct{
  struct tcp_pcb *client_pcb;
  unsigned int BytesPending;
  char *RBuf;
  unsigned int Id;
  uint8_t Hidden;
  uint8_t ClientClosed;
  uint8_t Canceled;
} WebServer_t;

typedef struct{
    unsigned int Id;
    int Type;
    char *Data;
    WebServer_t *State;
}PrivateWebMsg_t;

class WebServer{
  public:
    WebServer();

    WebMsg_t ReadMessage(void);
    int Printf(const char *Format, ...);
    int SendText(const char *Data);
    int SendImage(const char *Type,int Size,const char *Data);
    int Write(const char *Data,int Size);
    char *FetchAddr(void);
    int Init(const char *WifiSsid,const char *WifiPassword,int RetryForever=1);
    void ProcessMessages(unsigned int IdleSleepTime_ms,void (*Cb)(const char *Request));
    void ResetWifi(void);   

  private:
    int InitBase(const char *WifiSsid,const char *WifiPassword);
    WebServer_t *StateInit(void);
    int SendTheData(const char *Data,int Len);
    err_t SendNotFound(void *arg, struct tcp_pcb *tpcb);
    int SendMsg(PrivateWebMsg_t Msg);
    
    void CloseConnection(struct tcp_pcb *tpcb);
    void CloseClientAndServer(void);
      // Note that call back functions have to be static
    static err_t TcpServerAccept(void *arg, struct tcp_pcb *client_pcb, err_t err);
    static void TcpServerError(void *arg, err_t err);
    static err_t TcpServerReceive(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
    static err_t TcpServerSent(void *arg, struct tcp_pcb *tpcb, u16_t len); 

    struct tcp_pcb *mServerPcb;
    struct {
      uint8_t Rd, Wr, Size;
    }mMqInfo;
    char mSsid[100],mPswd[100];
    #define MSG_QUEUE_SIZE  20
    PrivateWebMsg_t mMsgQueue[MSG_QUEUE_SIZE];


    void AddConnectionToTracker(WebServer_t *State);     
    void RemoveConnectionFromTracker(WebServer_t *State); 
        // Stupid array to deal with pending requests when WiFi is lost or the connection is reset.  
        // This allows client_pcbs to be freed up that might never be acked or sent.
    #define MAX_PENDING 50
    WebServer_t *mPending[MAX_PENDING];
    int mNumPending;    
};
#endif