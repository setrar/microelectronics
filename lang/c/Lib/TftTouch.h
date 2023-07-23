typedef struct{
    uint8_t Down;
    uint16_t X;
    uint16_t Y;
    uint8_t Pressure;
} TfTouch_t;

TfTouch_t TfFetchTouch(void);
void TfCalibrate(void);
void TfEnableHyst(void);
void TfDisableHyst(void);