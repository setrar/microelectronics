// Tft320x240Fb:  Frame Buffer version of 320x240 TFT touchscreen display funcions
//          Ted Rossin  5-20-2022
//                      6-17-2022

#include "pico/stdlib.h"
#include "Tft320x240Fb.h"

#define LCD_RDN     8
#define LCD_WRN     9
#define LCD_RSN     10
#define LCD_CSN     11
#define LCD_RSTN    12

#define LCD_DATA_MASK   0xff

static uint16_t FgTextColor,BgTextColor,ClearColor;
static uint8_t gfFontId,FontWidth,FontHeight,ZoomFont2x;

#define FONT_WIDTH0     6
#define FONT_HEIGHT0 	8

const unsigned char Font0[] = {
     0xaa,0x55,0xaa,0x55,0xaa  // 0x00
    ,0x00,0x00,0x00,0x00,0x00  // 0x01
    ,0x00,0x00,0x00,0x00,0x00  // 0x02
    ,0x00,0x00,0x00,0x00,0x00  // 0x03
    ,0x00,0x00,0x00,0x00,0x00  // 0x04
    ,0x00,0x00,0x00,0x00,0x00  // 0x05
    ,0x00,0x00,0x00,0x00,0x00  // 0x06
    ,0x00,0x00,0x00,0x00,0x00  // 0x07
    ,0x00,0x00,0x00,0x00,0x00  // 0x08
    ,0x00,0x00,0x00,0x00,0x00  // 0x09
    ,0x00,0x00,0x00,0x00,0x00  // 0x0A
    ,0x00,0x00,0x00,0x00,0x00  // 0x0B
    ,0x00,0x00,0x00,0x00,0x00  // 0x0C
    ,0x00,0x00,0x00,0x00,0x00  // 0x0D
    ,0x00,0x00,0x00,0x00,0x00  // 0x0E
    ,0x00,0x00,0x00,0x00,0x00  // 0x0F
    ,0x00,0x00,0x00,0x00,0x00  // 0x10
    ,0x00,0x00,0x00,0x00,0x00  // 0x11
    ,0x00,0x00,0x00,0x00,0x00  // 0x12
    ,0x00,0x00,0x00,0x00,0x00  // 0x13
    ,0x00,0x00,0x00,0x00,0x00  // 0x14
    ,0x00,0x00,0x00,0x00,0x00  // 0x15
    ,0x00,0x00,0x00,0x00,0x00  // 0x16
    ,0x00,0x00,0x00,0x00,0x00  // 0x17
    ,0x00,0x00,0x00,0x00,0x00  // 0x18
    ,0x00,0x00,0x00,0x00,0x00  // 0x19
    ,0x00,0x00,0x00,0x00,0x00  // 0x1A
    ,0x00,0x00,0x00,0x00,0x00  // 0x1B
    ,0x00,0x00,0x00,0x00,0x00  // 0x1C
    ,0x00,0x00,0x00,0x00,0x00  // 0x1D
    ,0x00,0x00,0x00,0x00,0x00  // 0x1E
    ,0x00,0x00,0x00,0x00,0x00  // 0x1F
    ,0x00,0x00,0x00,0x00,0x00  // 0x20
    ,0x00,0x00,0x7D,0x00,0x00  // 0x21
    ,0x00,0x30,0x00,0x30,0x00  // 0x22
    ,0x14,0x7F,0x14,0x7F,0x14  // 0x23
    ,0x12,0x2A,0x7F,0x2A,0x24  // 0x24
    ,0x32,0x34,0x08,0x13,0x23  // 0x25
    ,0x36,0x49,0x55,0x22,0x05  // 0x26
    ,0x00,0x00,0x70,0x00,0x00  // 0x27
    ,0x00,0x1C,0x22,0x41,0x00  // 0x28
    ,0x00,0x41,0x22,0x1C,0x00  // 0x29
    ,0x14,0x08,0x3E,0x08,0x14  // 0x2A
    ,0x08,0x08,0x3E,0x08,0x08  // 0x2B
    ,0x00,0x05,0x06,0x00,0x00  // 0x2C
    ,0x08,0x08,0x08,0x08,0x08  // 0x2D
    ,0x00,0x03,0x03,0x00,0x00  // 0x2E
    ,0x02,0x04,0x08,0x10,0x20  // 0x2F
    ,0x3E,0x45,0x49,0x51,0x3E  // 0x30
    ,0x00,0x21,0x7F,0x01,0x00  // 0x31
    ,0x21,0x43,0x45,0x49,0x31  // 0x32
    ,0x42,0x41,0x51,0x69,0x46  // 0x33
    ,0x0C,0x14,0x24,0x7F,0x04  // 0x34
    ,0x72,0x51,0x51,0x51,0x4E  // 0x35
    ,0x1E,0x29,0x49,0x49,0x06  // 0x36
    ,0x60,0x40,0x47,0x48,0x70  // 0x37
    ,0x36,0x49,0x49,0x49,0x36  // 0x38
    ,0x30,0x49,0x49,0x4A,0x3C  // 0x39
    ,0x00,0x36,0x36,0x00,0x00  // 0x3A
    ,0x00,0x35,0x36,0x00,0x00  // 0x3B
    ,0x08,0x14,0x22,0x41,0x00  // 0x3C
    ,0x14,0x14,0x14,0x14,0x14  // 0x3D
    ,0x00,0x41,0x22,0x14,0x08  // 0x3E
    ,0x20,0x40,0x45,0x48,0x30  // 0x3F
    ,0x26,0x49,0x4F,0x41,0x3E  // 0x40
    ,0x3F,0x48,0x48,0x48,0x3F  // 0x41
    ,0x7F,0x49,0x49,0x49,0x36  // 0x42
    ,0x3E,0x41,0x41,0x41,0x22  // 0x43
    ,0x7F,0x41,0x41,0x22,0x1C  // 0x44
    ,0x7F,0x49,0x49,0x49,0x41  // 0x45
    ,0x7F,0x48,0x48,0x48,0x40  // 0x46
    ,0x3E,0x41,0x49,0x49,0x2F  // 0x47
    ,0x7F,0x08,0x08,0x08,0x7F  // 0x48
    ,0x00,0x41,0x7F,0x41,0x00  // 0x49
    ,0x02,0x01,0x41,0x7F,0x40  // 0x4A
    ,0x7F,0x08,0x14,0x22,0x41  // 0x4B
    ,0x7F,0x01,0x01,0x01,0x01  // 0x4C
    ,0x7F,0x20,0x18,0x20,0x7F  // 0x4D
    ,0x7F,0x10,0x08,0x04,0x7F  // 0x4E
    ,0x3E,0x41,0x41,0x41,0x3E  // 0x4F
    ,0x7F,0x48,0x48,0x48,0x30  // 0x50
    ,0x3E,0x41,0x45,0x42,0x3D  // 0x51
    ,0x7F,0x48,0x4C,0x4A,0x31  // 0x52
    ,0x31,0x49,0x49,0x49,0x46  // 0x53
    ,0x40,0x40,0x7F,0x40,0x40  // 0x54
    ,0x7E,0x01,0x01,0x01,0x7E  // 0x55
    ,0x7C,0x02,0x01,0x02,0x7C  // 0x56
    ,0x7E,0x01,0x0E,0x01,0x7E  // 0x57
    ,0x63,0x14,0x08,0x14,0x63  // 0x58
    ,0x70,0x08,0x07,0x08,0x70  // 0x59
    ,0x43,0x45,0x49,0x51,0x61  // 0x5A
    ,0x7F,0x41,0x41,0x00,0x00  // 0x5B
    ,0x20,0x10,0x08,0x04,0x02  // 0x5C
    ,0x00,0x00,0x41,0x41,0x7F  // 0x5D
    ,0x10,0x20,0x40,0x20,0x10  // 0x5E
    ,0x01,0x01,0x01,0x01,0x01  // 0x5F
    ,0x40,0x20,0x10,0x00,0x00  // 0x60
    ,0x02,0x15,0x15,0x15,0x0F  // 0x61
    ,0x7F,0x11,0x11,0x11,0x0E  // 0x62
    ,0x0E,0x11,0x11,0x11,0x00  // 0x63
    ,0x0E,0x11,0x11,0x11,0x7F  // 0x64
    ,0x0E,0x15,0x15,0x15,0x0C  // 0x65
    ,0x00,0x08,0x3F,0x48,0x20  // 0x66
    ,0x18,0x25,0x25,0x29,0x1E  // 0x67
    ,0x7F,0x10,0x10,0x10,0x0F  // 0x68
    ,0x00,0x00,0x2F,0x00,0x00  // 0x69
    ,0x00,0x02,0x01,0x01,0x2E  // 0x6A
    ,0x7F,0x04,0x0A,0x11,0x00  // 0x6B
    ,0x00,0x21,0x3F,0x01,0x00  // 0x6C
    ,0x1F,0x10,0x0F,0x10,0x1F  // 0x6D
    ,0x0F,0x10,0x10,0x10,0x0F  // 0x6E
    ,0x0E,0x11,0x11,0x11,0x0E  // 0x6F
    ,0x1F,0x24,0x24,0x24,0x18  // 0x70
    ,0x18,0x24,0x24,0x1F,0x01  // 0x71
    ,0x1F,0x08,0x10,0x10,0x08  // 0x72
    ,0x08,0x15,0x15,0x15,0x02  // 0x73
    ,0x00,0x10,0x3F,0x11,0x00  // 0x74
    ,0x00,0x1E,0x01,0x01,0x1E  // 0x75
    ,0x1C,0x02,0x01,0x02,0x1C  // 0x76
    ,0x1E,0x01,0x06,0x01,0x1E  // 0x77
    ,0x11,0x0A,0x04,0x0A,0x11  // 0x78
    ,0x00,0x18,0x05,0x06,0x18  // 0x79
    ,0x11,0x13,0x15,0x19,0x11  // 0x7A
    ,0x00,0x08,0x36,0x41,0x00  // 0x7B
    ,0x00,0x00,0x7F,0x00,0x00  // 0x7C
    ,0x00,0x41,0x36,0x08,0x00  // 0x7D
    ,0x08,0x10,0x08,0x04,0x08  // 0x7E
    ,0x00,0x00,0x00,0x00,0x00  // 0x7F
};

#define FONT_WIDTH1  	12
#define FONT_HEIGHT1	16

const unsigned int Font1[] = {
/*
     0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x00
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x01
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x02
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x03
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x04
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x05
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x06
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x07
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x08
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x09
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x0A
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x0B
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x0C
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x0D
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x0E
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x0F
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x10
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x11
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x12
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x13
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x14
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x15
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x16
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x17
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x18
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x19
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x1A
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x1B
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x1C
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x1D
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x1E
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x1F
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x20
*/    
     0x0000,0x0000,0x0000,0x0000,0x0000,0x7FF3,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x21
    ,0x0000,0x0000,0x0000,0x7800,0x0000,0x0000,0x0000,0x7800,0x0000,0x0000,0x0000  // 0x22
    ,0x0410,0x0410,0x0410,0x7FFF,0x0410,0x0410,0x0410,0x7FFF,0x0410,0x0410,0x0410  // 0x23
    ,0x0E08,0x1104,0x2082,0x7FFF,0x2082,0x2082,0x2082,0x7FFF,0x2082,0x1044,0x0838  // 0x24
    ,0x1C04,0x2208,0x2210,0x2220,0x1C40,0x0080,0x011C,0x0222,0x0422,0x0822,0x101C  // 0x25
    ,0x1C1C,0x2222,0x4141,0x4081,0x4141,0x2221,0x1C11,0x000A,0x0004,0x000A,0x0001  // 0x26
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x7C00,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x27
    ,0x0000,0x0000,0x0000,0x07F0,0x180C,0x2002,0x4001,0x0000,0x0000,0x0000,0x0000  // 0x28
    ,0x0000,0x0000,0x0000,0x0000,0x4001,0x2002,0x180C,0x07F0,0x0000,0x0000,0x0000  // 0x29
    ,0x0000,0x0000,0x0410,0x0220,0x0140,0x1FFC,0x0140,0x0220,0x0410,0x0000,0x0000  // 0x2A
    ,0x0000,0x0080,0x0080,0x0080,0x0080,0x0FF8,0x0080,0x0080,0x0080,0x0080,0x0000  // 0x2B
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x000D,0x000E,0x0000,0x0000,0x0000,0x0000  // 0x2C
    ,0x0000,0x0000,0x0080,0x0080,0x0080,0x0080,0x0080,0x0080,0x0080,0x0000,0x0000  // 0x2D
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0003,0x0003,0x0000,0x0000,0x0000,0x0000  // 0x2E
    ,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,0x0100,0x0200,0x0400,0x0800,0x1000  // 0x2F
    ,0x0000,0x1FFC,0x2002,0x4001,0x4001,0x41C1,0x4001,0x4001,0x2002,0x1FFC,0x0000  // 0x30
    ,0x0000,0x0000,0x0001,0x1001,0x2001,0x7FFF,0x0001,0x0001,0x0001,0x0000,0x0000  // 0x31
    ,0x1801,0x2003,0x4005,0x4009,0x4011,0x4021,0x4041,0x4081,0x4101,0x2201,0x1C01  // 0x32
    ,0x180C,0x2002,0x4001,0x4001,0x4001,0x4081,0x4081,0x4081,0x4081,0x2142,0x1E3C  // 0x33
    ,0x0080,0x0180,0x0280,0x0480,0x0880,0x1080,0x2080,0x7FFF,0x0080,0x0080,0x0080  // 0x34
    ,0x7F04,0x4102,0x4101,0x4101,0x4101,0x4101,0x4101,0x4101,0x4101,0x4082,0x407C  // 0x35
    ,0x1FFC,0x2082,0x4081,0x4081,0x4081,0x4081,0x4081,0x4081,0x4081,0x2042,0x183C  // 0x36
    ,0x4000,0x4000,0x4000,0x4000,0x4000,0x407F,0x4080,0x4100,0x4200,0x4400,0x7800  // 0x37
    ,0x1E3C,0x2142,0x4081,0x4081,0x4081,0x4081,0x4081,0x4081,0x4081,0x2142,0x1E3C  // 0x38
    ,0x1E0C,0x2102,0x4081,0x4081,0x4081,0x4081,0x4081,0x4081,0x4081,0x2082,0x1FFC  // 0x39
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0630,0x0630,0x0000,0x0000,0x0000,0x0000  // 0x3A
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0634,0x0638,0x0000,0x0000,0x0000,0x0000  // 0x3B
    ,0x0000,0x0000,0x0080,0x0140,0x0220,0x0410,0x0808,0x1004,0x2002,0x0000,0x0000  // 0x3C
    ,0x0000,0x0000,0x0210,0x0210,0x0210,0x0210,0x0210,0x0210,0x0210,0x0000,0x0000  // 0x3D
    ,0x0000,0x0000,0x2002,0x1004,0x0808,0x0410,0x0220,0x0140,0x0080,0x0000,0x0000  // 0x3E
    ,0x1C00,0x2200,0x4000,0x4000,0x4000,0x403B,0x4040,0x4080,0x4100,0x2200,0x1C00  // 0x3F
    ,0x1FFC,0x2002,0x4181,0x4241,0x4421,0x4421,0x4241,0x47F1,0x4011,0x2012,0x1FE4  // 0x40
    ,0x0FFF,0x1080,0x2080,0x4080,0x4080,0x4080,0x4080,0x4080,0x2080,0x1080,0x0FFF  // 0x41
    ,0x7FFF,0x4081,0x4081,0x4081,0x4081,0x4081,0x4081,0x4081,0x4081,0x2142,0x1E3C  // 0x42
    ,0x1FFC,0x2002,0x4001,0x4001,0x4001,0x4001,0x4001,0x4001,0x4001,0x2002,0x180C  // 0x43
    ,0x7FFF,0x4001,0x4001,0x4001,0x4001,0x4001,0x4001,0x4001,0x4001,0x2002,0x1FFC  // 0x44
    ,0x7FFF,0x4081,0x4081,0x4081,0x4081,0x4081,0x4081,0x4001,0x4001,0x4001,0x4001  // 0x45
    ,0x7FFF,0x4080,0x4080,0x4080,0x4080,0x4080,0x4080,0x4000,0x4000,0x4000,0x4000  // 0x46
    ,0x1FFC,0x2002,0x4001,0x4001,0x4001,0x4001,0x4001,0x4041,0x4041,0x2042,0x187C  // 0x47
    ,0x7FFF,0x0080,0x0080,0x0080,0x0080,0x0080,0x0080,0x0080,0x0080,0x0080,0x7FFF  // 0x48
    ,0x0000,0x0000,0x4001,0x4001,0x4001,0x7FFF,0x4001,0x4001,0x4001,0x0000,0x0000  // 0x49
    ,0x0004,0x0002,0x0001,0x0001,0x0001,0x0001,0x4001,0x4001,0x4001,0x4002,0x7FFC  // 0x4A
    ,0x7FFF,0x0080,0x0080,0x0080,0x0140,0x0220,0x0410,0x0808,0x1004,0x2002,0x4001  // 0x4B
    ,0x7FFF,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0003  // 0x4C
    ,0x7FFF,0x2000,0x1000,0x0800,0x0400,0x0200,0x0400,0x0800,0x1000,0x2000,0x7FFF  // 0x4D
    ,0x7FFF,0x0800,0x0400,0x0200,0x0100,0x0080,0x0040,0x0020,0x0010,0x0008,0x7FFF  // 0x4E
    ,0x1FFC,0x2002,0x4001,0x4001,0x4001,0x4001,0x4001,0x4001,0x4001,0x2002,0x1FFC  // 0x4F
    ,0x7FFF,0x4080,0x4080,0x4080,0x4080,0x4080,0x4080,0x4080,0x4080,0x2100,0x1E00  // 0x50
    ,0x1FFC,0x2002,0x4001,0x4001,0x4001,0x4001,0x4001,0x4009,0x4005,0x2002,0x1FFD  // 0x51
    ,0x7FFF,0x4080,0x4080,0x4080,0x40C0,0x40A0,0x4090,0x4088,0x4084,0x2102,0x1E01  // 0x52
    ,0x1E04,0x2102,0x4081,0x4081,0x4081,0x4081,0x4081,0x4081,0x4081,0x2042,0x103C  // 0x53
    ,0x4000,0x4000,0x4000,0x4000,0x4000,0x7FFF,0x4000,0x4000,0x4000,0x4000,0x4000  // 0x54
    ,0x7FFC,0x0002,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,0x7FFC  // 0x55
    ,0x7FE0,0x0010,0x0008,0x0004,0x0002,0x0001,0x0002,0x0004,0x0008,0x0010,0x7FE0  // 0x56
    ,0x7FFF,0x0002,0x0004,0x0008,0x0010,0x0020,0x0010,0x0008,0x0004,0x0002,0x7FFF  // 0x57
    ,0x7007,0x0808,0x0410,0x0220,0x0140,0x0080,0x0140,0x0220,0x0410,0x0808,0x7007  // 0x58
    ,0x7000,0x0800,0x0400,0x0200,0x0100,0x00FF,0x0100,0x0200,0x0400,0x0800,0x7000  // 0x59
    ,0x4007,0x4009,0x4011,0x4021,0x4041,0x4081,0x4101,0x4201,0x4401,0x4801,0x7001  // 0x5A
    ,0x0000,0x0000,0x0000,0x0000,0x7FFF,0x4001,0x4001,0x4001,0x0000,0x0000,0x0000  // 0x5B
    ,0x1000,0x0800,0x0400,0x0200,0x0100,0x0080,0x0040,0x0020,0x0010,0x0008,0x0004  // 0x5C
    ,0x0000,0x0000,0x0000,0x4001,0x4001,0x4001,0x7FFF,0x0000,0x0000,0x0000,0x0000  // 0x5D
    ,0x0000,0x0000,0x0800,0x1000,0x2000,0x4000,0x2000,0x1000,0x0800,0x0000,0x0000  // 0x5E
    ,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001  // 0x5F
    ,0x0000,0x0000,0x0000,0x4000,0x2000,0x1000,0x0800,0x0000,0x0000,0x0000,0x0000  // 0x60
    ,0x0006,0x0009,0x0091,0x0091,0x0091,0x0091,0x0091,0x0091,0x0091,0x0051,0x003F  // 0x61
    ,0x7FFF,0x0081,0x0081,0x0081,0x0081,0x0081,0x0081,0x0081,0x0081,0x0042,0x003C  // 0x62
    ,0x003C,0x0042,0x0081,0x0081,0x0081,0x0081,0x0081,0x0081,0x0081,0x0081,0x0042  // 0x63
    ,0x003C,0x0042,0x0081,0x0081,0x0081,0x0081,0x0081,0x0081,0x0081,0x0081,0x7FFF  // 0x64
    ,0x003C,0x0052,0x0091,0x0091,0x0091,0x0091,0x0091,0x0091,0x0091,0x0051,0x0032  // 0x65
    ,0x0000,0x0000,0x0080,0x0080,0x1FFF,0x2080,0x4080,0x4080,0x2000,0x1800,0x0000  // 0x66
    ,0x00E0,0x0112,0x0209,0x0209,0x0209,0x0209,0x0209,0x0209,0x0209,0x010A,0x00FC  // 0x67
    ,0x7FFF,0x0020,0x0040,0x0080,0x0080,0x0080,0x0080,0x0080,0x0080,0x0040,0x003F  // 0x68
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x02FF,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x69
    ,0x0000,0x0000,0x0002,0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,0x0BFC,0x0000  // 0x6A
    ,0x7FFF,0x0020,0x0020,0x0020,0x0020,0x0020,0x0050,0x0088,0x0104,0x0202,0x0401  // 0x6B
    ,0x0000,0x0000,0x0000,0x0000,0x4001,0x7FFF,0x0001,0x0000,0x0000,0x0000,0x0000  // 0x6C
    ,0x003F,0x0040,0x0080,0x0080,0x0040,0x003F,0x0040,0x0080,0x0080,0x0040,0x003F  // 0x6D
    ,0x0000,0x0000,0x01FF,0x0080,0x0100,0x0100,0x0100,0x0080,0x007F,0x0000,0x0000  // 0x6E
    ,0x003C,0x0042,0x0081,0x0081,0x0081,0x0081,0x0081,0x0081,0x0081,0x0042,0x003C  // 0x6F
    ,0x00FF,0x0108,0x0204,0x0204,0x0204,0x0204,0x0204,0x0204,0x0108,0x00F0,0x0000  // 0x70
    ,0x00F0,0x0108,0x0204,0x0204,0x0204,0x0204,0x0204,0x0204,0x0108,0x03FF,0x0000  // 0x71
    ,0x00FF,0x0020,0x0040,0x0080,0x0080,0x0080,0x0080,0x0080,0x0080,0x0040,0x0020  // 0x72
    ,0x00E2,0x0111,0x0111,0x0111,0x0111,0x0111,0x0111,0x0111,0x0111,0x0111,0x008E  // 0x73
    ,0x0080,0x0080,0x0080,0x0080,0x03FC,0x0082,0x0081,0x0081,0x0081,0x0002,0x0000  // 0x74
    ,0x00FC,0x0002,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0002,0x00FC  // 0x75
    ,0x00E0,0x0010,0x0008,0x0004,0x0002,0x0001,0x0002,0x0004,0x0008,0x0010,0x00E0  // 0x76
    ,0x00F8,0x0004,0x0002,0x0001,0x0002,0x001C,0x0002,0x0001,0x0002,0x0004,0x00F8  // 0x77
    ,0x0000,0x0101,0x0082,0x0044,0x0028,0x0010,0x0028,0x0044,0x0082,0x0101,0x0000  // 0x78
    ,0x0000,0x0000,0x0081,0x0041,0x0022,0x0014,0x0008,0x0010,0x0020,0x0040,0x0080  // 0x79
    ,0x0000,0x0083,0x0085,0x0085,0x0089,0x0089,0x0091,0x0091,0x00A1,0x00A1,0x00C1  // 0x7A
    ,0x0000,0x0000,0x0080,0x0140,0x0E38,0x3006,0x4001,0x0000,0x0000,0x0000,0x0000  // 0x7B
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x7FFF,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x7C
    ,0x0000,0x0000,0x0000,0x0000,0x4001,0x3006,0x0E38,0x0140,0x0080,0x0000,0x0000  // 0x7D
    ,0x0000,0x0000,0x0800,0x1000,0x2000,0x1000,0x0800,0x0400,0x0800,0x1000,0x0000  // 0x7E
    ,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  // 0x7F
};

#define NUM_FONTS   2

static void LcdWriteCmd(uint8_t Data)  
{    
    gpio_put(LCD_RSN,0);
    gpio_put_masked(LCD_DATA_MASK,Data);
    gpio_put(LCD_WRN,0); 
    gpio_put(LCD_WRN,1); 
    gpio_put(LCD_RSN,1);    
}

static void LcdWriteData(uint8_t Data)
{ 
    gpio_put_masked(LCD_DATA_MASK,Data);
    gpio_put(LCD_WRN,0);
    gpio_put(LCD_WRN,1);
}

static void LcdWriteData16(uint16_t Data)
{     
    gpio_put_masked(LCD_DATA_MASK,Data>>8);
    gpio_put(LCD_WRN,0);
    gpio_put(LCD_WRN,1);
    gpio_put_masked(LCD_DATA_MASK,Data&0xff);
    gpio_put(LCD_WRN,0);
    gpio_put(LCD_WRN,1);
} 

void gfInit(void)
{
    
    FgTextColor = 0xffff;
    BgTextColor = 0x0000;
    gfFontId = 0;
    FontWidth = FONT_WIDTH0;  
    FontHeight= FONT_HEIGHT0;
    ZoomFont2x = 0;
    ClearColor = 0x0000;

    gpio_init(LCD_RDN);  gpio_set_dir(LCD_RDN, GPIO_OUT);
    gpio_init(LCD_WRN);  gpio_set_dir(LCD_WRN, GPIO_OUT);
    gpio_init(LCD_RSN);  gpio_set_dir(LCD_RSN, GPIO_OUT);
    gpio_init(LCD_CSN);  gpio_set_dir(LCD_CSN, GPIO_OUT);
    gpio_init(LCD_RSTN); gpio_set_dir(LCD_RSTN, GPIO_OUT);

    gpio_init_mask(LCD_DATA_MASK);
    gpio_set_dir_masked(LCD_DATA_MASK,LCD_DATA_MASK);
    gpio_put_masked(LCD_DATA_MASK,0x00);

     
    gpio_put(LCD_CSN,1);
    gpio_put(LCD_WRN,1);
    gpio_put(LCD_RDN,1);
  
    gpio_put(LCD_RSTN,1);
    sleep_ms(5); 
    gpio_put(LCD_RSTN,0);
    sleep_ms(15);
    gpio_put(LCD_RSTN,1);
    sleep_ms(15);

    gpio_put(LCD_CSN,1);
    gpio_put(LCD_WRN,1);
    gpio_put(LCD_CSN,0); 
    
    LcdWriteCmd(0xcb);  // Power Control A
    LcdWriteData(0x39); // Required sequence 
    LcdWriteData(0x2c); // Required sequence
    LcdWriteData(0x00); // Required sequence
    LcdWriteData(0x34); // Vcore = 1.6V
    LcdWriteData(0x02); // DDVDH = 5.6V

    LcdWriteCmd(0xcf);  // Power Control B  
    LcdWriteData(0x00); // Required sequence
        // Default is 0x81
    LcdWriteData(0xc1); // PCEQ = 1, DRV_ena=0, Power Control=0 
    LcdWriteData(0X30); // Default settings

    LcdWriteCmd(0xe8);  // Driver Timing Control A  
        // Default is 0x84
    LcdWriteData(0x85); // Non Overlapped timing control = 1 
        // Default is 0x11
    LcdWriteData(0x00); // EQ=0,CR=0 (default is 1,1)
    LcdWriteData(0x78); // Precharge timing = 2 unit

    LcdWriteCmd(0xea);  // Driver Timing Control B 
        // Default is 0x66
    LcdWriteData(0x00); // VG_SW_T(1 to 4) set to 0 instead of 1,2,1,2
    LcdWriteData(0x00); // Required sequence
 
    LcdWriteCmd(0xed);  // Power On Sequence Control 
        // Default is 0x55
    LcdWriteData(0x64); // Soft Start keep 1 frame
        // Default is 0x01
    LcdWriteData(0x03); // 4th frame enable
        // Default is 0x23
    LcdWriteData(0X12); // vgh 1st frame enable, vgl 3rd frame enable 
        // Default is 0x01
    LcdWriteData(0X81); // DDVDH_ENH=1

    LcdWriteCmd(0xf7);  // Pump ratio control
        // Default is 0x10 which is defined as reserved
    LcdWriteData(0x20); //Ratio = 2x VCI
 
    LcdWriteCmd(0xc0);    //Power Control 1
        // Default is 0x21
    LcdWriteData(0x23);   //VRH[5:0] = 4.60V
 
    LcdWriteCmd(0xc1);    //Power Control 2 
    LcdWriteData(0x10);   //VGH = VCIx7, VGL = -VCIx4 

    LcdWriteCmd(0xc5);   //VCOM Control
        // Default is 0x31
    LcdWriteData(0x3e);  //VMH = 5.85V
        // Default is 0x3c
    LcdWriteData(0x28);  //VML = -0.7V
 
    LcdWriteCmd(0xc7);   //VCOM control 2
        // Default is 0xc0
    LcdWriteData(0x86);  // VMF = VMH-58,VML=VML-58 
 
    LcdWriteCmd(0x36);   // Memory Access Control 
        // Default is 0x00
    LcdWriteData(0x08); // BGR=1 so BGR color instead of RGB (was 0x48)

    LcdWriteCmd(0x3a);  // Pixel Format Set (16 or 18 bit mode)    
    LcdWriteData(0x55); // DPI(Display)=16 bits/pixel, DBI(MCU) = 16 bits/pixel

    LcdWriteCmd(0xb1);  //Frame Rate Control  
    LcdWriteData(0x00); // DIVA = fosc 
    LcdWriteData(0x18); // RTNA = 70Hz
 
    LcdWriteCmd(0xb6);  // Display Function Control 
        // Default is 0x0a    
    LcdWriteData(0x08); //PTG=Interval scan, PT=0
    LcdWriteData(0x82); // Magic 0x82
    LcdWriteData(0x27); //PCDIV (Magic)

    LcdWriteCmd(0x11);  //Exit Sleep 
    sleep_ms(120); 
				
    LcdWriteCmd(0x29);  //Display on 
}

static void SetRegion(uint16_t x1, uint16_t y1, uint16_t x2,uint16_t y2)
{
    uint16_t swap;
        // X1 must be less than or equal to x2
        // Y1 must be less than or equal to y2
    if(x2<x1){ swap = x1;  x1=x2;  x2=swap; }
    if(y2<y1){ swap = y1;  y1=y2;  y2=swap; }
        // X: 0 to 319,  Y: 0 to 239
    LcdWriteCmd(0x2a); // Column Address Set
    LcdWriteData(0);
	LcdWriteData((uint8_t)y1);	// Start Column
    LcdWriteData(0);
	LcdWriteData((uint8_t)y2); // End Column
    LcdWriteCmd(0x2b);	// Page Address Set (Row)
	LcdWriteData(x1>>8);
	LcdWriteData((uint8_t)x1);	// Start Row
	LcdWriteData(x2>>8);
	LcdWriteData((uint8_t)x2);	// End Row
	LcdWriteCmd(0x2c);	// Memory Write: Send (EndC-StartC+1)*(EndR-StartR+1) pixels
}

static uint16_t Fb[DISP_WIDTH*DISP_HEIGHT];

// REVISIT: Optimize for clear color of 0x0000
void gfUpdateDisplay(uint8_t ClearBuffer)
{
    uint16_t Data,*Ptr=Fb;
    uint16_t *EndPtr = &Fb[DISP_WIDTH*DISP_HEIGHT];
    
    SetRegion(0,0,DISP_WIDTH-1,DISP_HEIGHT-1);

    if(ClearBuffer){        
        while(Ptr!=EndPtr){
            //LcdWriteData16(*Ptr);
                // Unwind loop for performance    
            Data = *Ptr;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
            *Ptr++=ClearColor;

            Data = *Ptr;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
            *Ptr++=ClearColor;

            Data = *Ptr;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
            *Ptr++=ClearColor;

            Data = *Ptr;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
            *Ptr++=ClearColor;            

            Data = *Ptr;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
            *Ptr++=ClearColor;

            Data = *Ptr;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
            *Ptr++=ClearColor;

            Data = *Ptr;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
            *Ptr++=ClearColor;

            Data = *Ptr;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1); 
            *Ptr++=ClearColor; 
        }
    }
    else{
        while(Ptr!=EndPtr){
            //LcdWriteData16(*Ptr++);
                // Unwind loop for performance 
            Data = *Ptr++;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);

            Data = *Ptr++;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);

            Data = *Ptr++;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);

            Data = *Ptr++;
            gpio_put_masked(LCD_DATA_MASK,Data>>8);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);
            gpio_put_masked(LCD_DATA_MASK,Data);
            gpio_put(LCD_WRN,0);
            gpio_put(LCD_WRN,1);           
        }
    }        
}

void gfSetClearColor(uint16_t Color)
{
    ClearColor = Color;
}

void gfClearDisplay(void)
{
    uint16_t *Ptr=Fb;
    uint16_t *EndPtr = &Fb[DISP_WIDTH*DISP_HEIGHT];

    while(Ptr!=EndPtr){
        *Ptr++=ClearColor;
    }
}

void gfRectFill(uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint16_t Color)
{
    uint16_t LoopX,LoopY,Amount;
    uint32_t Offset = x*DISP_HEIGHT+y;  // Display is rotated

    Amount = DISP_HEIGHT-h;
    for(LoopX=0;LoopX<w;LoopX++){
        for(LoopY=0;LoopY<h;LoopY++){
            Fb[Offset++] = Color;
        }
        Offset += Amount;
    }
}

void gfDrawPixel(uint16_t X,uint16_t Y,uint16_t Color)
{
    uint32_t Offset = X*DISP_HEIGHT+Y;  // Display is rotated
    Fb[Offset] = Color;
}

// Some help from Bresenham
void gfLine(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t Color)
{
    int16_t dx, sx = x0<x1 ? 1 : -1;
    int16_t dy, sy = y0<y1 ? 1 : -1; 
    int16_t err, e2; 

    dx = x1-x0;  if(dx<0) dx = -dx;
    dy = y1-y0;  if(dy<0) dy = -dy;
    err = dx>dy ? dx : -dy;
		// -1/2 = 0 but -1 >> 1 is -1 so clean up the math
    if(err == -1) err = 0; else err = err>>1;

    while(1){
        gfDrawPixel(x0,y0,Color);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }   
    }
}

void gfHLine(uint16_t x, uint16_t y, uint16_t l, uint16_t Color)                   
{	
    uint16_t i;
    uint32_t Offset = x*DISP_HEIGHT+y;  // Display is rotated

    for(i=0;i<l;i++){ 
        Fb[Offset] = Color;
        Offset+=DISP_HEIGHT;
    }
}

void gfVLine(uint16_t x, uint16_t y, uint16_t l, uint16_t Color)                   
{	
    uint16_t i;
    uint32_t Offset = x*DISP_HEIGHT+y;  // Display is rotated

    for(i=0;i<l;i++){ 
        Fb[Offset++] = Color;
    }
}

void gfRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t Color)
{
  gfHLine(x  , y  , w, Color);
  gfHLine(x  , y+h-1, w, Color);
  gfVLine(x  , y  , h, Color);
  gfVLine(x+w-1, y  , h, Color);
}

void gfDrawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h,uint16_t Data[])
{
    uint16_t IndexX,IndexY,Amount;
    uint32_t SrcOffset,Offset = x*DISP_HEIGHT+y;  // Display is rotated 

    Amount = DISP_HEIGHT-h;
   
    for(IndexX=0;IndexX<w;IndexX++){
         SrcOffset = IndexX;
        for(IndexY=0;IndexY<h;IndexY++){
            Fb[Offset++] = Data[SrcOffset];
            SrcOffset += w;
        }
        Offset+=Amount;
    }  
}

static void _circlePixel(uint16_t xc,uint16_t yc,uint16_t x,uint16_t y,uint16_t Color)
{
    gfDrawPixel(xc+x,yc+y,Color);
    gfDrawPixel(xc+x,yc-y,Color);
    gfDrawPixel(xc-x,yc+y,Color);
    gfDrawPixel(xc-x,yc-y,Color);
    gfDrawPixel(xc+y,yc+x,Color);
    gfDrawPixel(xc+y,yc-x,Color);
    gfDrawPixel(xc-y,yc+x,Color);
    gfDrawPixel(xc-y,yc-x,Color);      
}

void gfCircle(uint16_t xc,uint16_t yc,uint16_t r,uint16_t Color)
{
    int16_t x,y;
    int16_t p;

    x = 0;
    y = (int16_t)r;
    p = (int16_t)(3 - (r<<1));
    _circlePixel(xc,yc,0,y,Color);
  
    while(x<y){
        if(p<0){
            x++;
            p += ((x<<2)+6);
        }
        else{
            x++;
            y--;
            p += (((x-y)<<2)+10);
        }
        _circlePixel(xc,yc,x,y,Color);
    }
}

static void _circleFill(uint16_t xc,uint16_t yc,uint16_t x,uint16_t y,uint16_t Color)
{
    gfHLine(xc-x  , yc+y  , x+x, Color);    // Bottom of circle
    gfHLine(xc-x  , yc-y  , x+x, Color);    // Top of circle
    
    gfHLine(xc-y  , yc+x  , y+y, Color);    // Bottom middle of circle
    gfHLine(xc-y  , yc-x  , y+y, Color);    // Top middle of circle      
}

void gfCircleFill(uint16_t xc,uint16_t yc,uint16_t r,uint16_t Color)
{
    int16_t x,y;
    int16_t p;

    x = 0;
    y = r;
    p = (int16_t)(3 - (r<<1));
    _circleFill(xc,yc,0,y,Color);
  
    while(x<y){
        if(p<0){
            x++;
            p += ((x<<2)+6);
        }
        else{
            x++;
            y--;
            p += (((x-y)<<2)+10);
        }
        _circleFill(xc,yc,x,y,Color);
    }
}

void gfSetTextColor(uint16_t Color)
{
    FgTextColor = Color;
}

void gfSetTextBackgroundColor(uint16_t Color)
{
    BgTextColor = Color;
}

void gfSelectFont(uint8_t Id)
{
    if(Id>=NUM_FONTS) return;
     
     gfFontId = Id;
     switch(gfFontId){
           case 0: FontWidth = FONT_WIDTH0;  FontHeight=FONT_HEIGHT0;  break;
           case 1: FontWidth = FONT_WIDTH1;  FontHeight=FONT_HEIGHT1;  break;
     }    
}

uint8_t gfGetFontWidth(void)
{
    return(ZoomFont2x ? FontWidth+FontWidth : FontWidth);
}

uint8_t gfGetFontHeight(void)
{
    return(ZoomFont2x ? FontHeight+FontHeight : FontHeight);
}

void gfSetFontZoom(uint8_t Factor)
{
    ZoomFont2x = (Factor==2) ? 1 : 0;
}

void gfPutc(uint16_t X,uint16_t Y,char c)
{
    uint16_t FontIndex,LimitX,LimitY,Value16,SenseMask,Amount;
    uint8_t Bit,ZoomLoop,Limit;
    uint8_t Index;
    uint32_t Offset = X*DISP_HEIGHT+Y;  // Display is rotated 

    if(c>0x80) return;
    
    FontIndex = 0;
    if(gfFontId>0 && c>0x20){
        FontIndex = (FontWidth-1)*(c-0x21);
    }
    else{
        FontIndex = (FontWidth-1)*c;
    }
    
        // Skip character if it will exceed display area
    LimitX = X+((ZoomFont2x) ? 2*FontWidth : FontWidth)-1;
    if(LimitX>=DISP_WIDTH) return; //LimitX = DISP_WIDTH;
    LimitY = Y+((ZoomFont2x) ? 2*FontHeight : FontHeight)-1;
    if(LimitY>=DISP_HEIGHT) return; //LimitY = DISP_HEIGHT; 

    Amount = DISP_HEIGHT-((ZoomFont2x) ? 2*FontHeight : FontHeight);  
        // Fill from top left (step Y) to bottom right (0,319 is bottom left)
    SenseMask = 1<<(FontHeight-2);  // Was FontHeight-1
    for(Index=0;Index<FontWidth-1;Index++){
        Limit = ZoomFont2x ? 2 : 1;
        for(ZoomLoop=0;ZoomLoop<Limit;ZoomLoop++){
            if(gfFontId>0 && c<=0x20){
                Value16 = 0;  // Make space after character
            }
            else{
                switch(gfFontId){
                    case 0: Value16 = Font0[FontIndex+Index];   break;
                    case 1: Value16 = Font1[FontIndex+Index];   break;
                    default: Value16 = 0;
                }
            }            
            for(Bit=0;Bit<FontHeight;Bit++){              
                Fb[Offset++] = (Value16 & SenseMask) ? FgTextColor : BgTextColor;
                //if(ZoomFont2x) LcdWriteData16((Value16 & SenseMask) ? FgTextColor : BgTextColor);
                if(ZoomFont2x) Fb[Offset++] = (Value16 & SenseMask) ? FgTextColor : BgTextColor;
                Value16 = Value16<<1;
            }
            Offset+=Amount;
        }
    }
        // Blank line to the right

    Limit = (ZoomFont2x) ? 2*FontHeight : FontHeight;
    for(Bit=0;Bit<Limit;Bit++) Fb[Offset++] = BgTextColor;
    if(ZoomFont2x){
        Offset+=Amount;
        for(Bit=0;Bit<Limit;Bit++) Fb[Offset++] = BgTextColor;
    }
}

void gfPuts(uint16_t X,uint16_t Y,char s[])
{
    uint8_t i;
    
    if(Y>=DISP_HEIGHT) return;
    for(i=0;s[i];i++){ 
		gfPutc(X,Y,s[i]);
		X+=FontWidth;
        if(ZoomFont2x) X+=FontWidth;
		if(X>=DISP_WIDTH) return;
	}    
}