#include "assets.h"

const unsigned char font8x8[] = {
0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,
0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,
0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,
0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,
0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,
0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,
0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,
0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,
0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,
0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,
0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,
0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,
0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,
0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,
0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,
0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0XF4,0X00,0X00,0X00,0X00,0X00,0XC0,0X00,0XC0,0X00,0X00,0X00,
0X00,0X28,0X7C,0X28,0X7C,0X28,0X00,0X00,0X00,0X00,0X24,0X54,0XFE,0X54,0X48,0X00,
0X40,0XA0,0XA8,0X50,0X28,0X54,0X14,0X08,0X00,0X00,0X68,0X94,0X94,0X88,0X08,0X14,
0X00,0X00,0X00,0X00,0XC0,0X00,0X00,0X00,0X00,0X00,0X30,0X48,0X84,0X00,0X00,0X00,
0X00,0X00,0X00,0X84,0X48,0X30,0X00,0X00,0X00,0X00,0XA8,0X70,0XF8,0X70,0XA8,0X00,
0X00,0X00,0X10,0X10,0X7C,0X10,0X10,0X00,0X00,0X00,0X00,0X02,0X04,0X00,0X00,0X00,
0X00,0X00,0X10,0X10,0X10,0X10,0X00,0X00,0X00,0X00,0X00,0X00,0X04,0X00,0X00,0X00,
0X00,0X04,0X08,0X10,0X20,0X40,0X80,0X00,0X00,0X30,0X48,0X84,0X84,0X48,0X30,0X00,
0X00,0X00,0X00,0X44,0XFC,0X04,0X00,0X00,0X00,0X44,0X8C,0X94,0X94,0XA4,0X44,0X00,
0X00,0X48,0X84,0X94,0X94,0XA4,0X48,0X00,0X00,0X18,0X28,0X48,0XFC,0X08,0X00,0X00,
0X00,0XE8,0XA4,0XA4,0XA4,0XA4,0X98,0X00,0X00,0X78,0XA4,0XA4,0XA4,0XA4,0X18,0X00,
0X00,0X84,0X88,0X90,0XA0,0XC0,0X80,0X00,0X00,0X58,0XA4,0XA4,0XA4,0XA4,0X58,0X00,
0X00,0X60,0X94,0X94,0X94,0X94,0X78,0X00,0X00,0X00,0X00,0X00,0X24,0X00,0X00,0X00,
0X00,0X00,0X00,0X02,0X24,0X00,0X00,0X00,0X00,0X10,0X10,0X28,0X28,0X44,0X44,0X00,
0X00,0X28,0X28,0X28,0X28,0X28,0X28,0X00,0X00,0X44,0X44,0X28,0X28,0X10,0X10,0X00,
0X00,0X40,0X80,0X94,0X90,0X60,0X00,0X00,0X18,0X24,0X42,0X5D,0X55,0X7D,0X00,0X00,
0X00,0X0C,0X30,0XD0,0XD0,0X30,0X0C,0X00,0X00,0XFC,0XA4,0XA4,0XA4,0X58,0X00,0X00,
0X30,0X48,0X84,0X84,0X84,0X48,0X00,0X00,0X00,0XFC,0X84,0X84,0X84,0X78,0X00,0X00,
0X00,0XFC,0XA4,0XA4,0XA4,0X84,0X00,0X00,0X00,0XFC,0XA0,0XA0,0XA0,0X80,0X00,0X00,
0X30,0X48,0X84,0X94,0X94,0X58,0X00,0X00,0X00,0XFC,0X20,0X20,0X20,0X20,0XFC,0X00,
0X00,0X00,0X84,0X84,0XFC,0X84,0X84,0X00,0X00,0X08,0X04,0X84,0X84,0XF8,0X00,0X00,
0X00,0XFC,0X10,0X30,0X48,0X84,0X00,0X00,0X00,0XFC,0X04,0X04,0X04,0X04,0X04,0X00,
0X00,0XFC,0X40,0X20,0X10,0X20,0X40,0XFC,0X00,0XFC,0X40,0X20,0X10,0X08,0XFC,0X00,
0X00,0X00,0X78,0X84,0X84,0X84,0X78,0X00,0X00,0XFC,0XA0,0XA0,0XA0,0X40,0X00,0X00,
0X00,0X00,0X78,0X84,0X84,0X84,0X7A,0X00,0X00,0XFC,0XA0,0XB0,0XA8,0X44,0X00,0X00,
0X00,0X00,0X48,0XA4,0X94,0X94,0X48,0X00,0X00,0X80,0X80,0X80,0XFC,0X80,0X80,0X80,
0X00,0XF8,0X04,0X04,0X04,0X04,0XF8,0X00,0X80,0X60,0X18,0X04,0X04,0X18,0X60,0X80,
0X00,0XFC,0X08,0X10,0X20,0X10,0X08,0XFC,0X00,0X84,0X48,0X30,0X30,0X48,0X84,0X00,
0X00,0X80,0X40,0X20,0X1C,0X20,0X40,0X80,0X00,0X84,0X8C,0X94,0XA4,0XC4,0X84,0X00,
0X00,0X00,0XFC,0X84,0X84,0X00,0X00,0X00,0X00,0X80,0X40,0X20,0X10,0X08,0X04,0X00,
0X00,0X00,0X84,0X84,0XFC,0X00,0X00,0X00,0X00,0X00,0X40,0X80,0X40,0X00,0X00,0X00,
0X00,0X04,0X04,0X04,0X04,0X04,0X04,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X80,0X40,0X00,0X00,0X00,0X00,0X08,0X54,0X54,0X54,0X58,0X3C,0X00,
0X00,0XFC,0X28,0X24,0X24,0X24,0X18,0X00,0X00,0X00,0X18,0X24,0X24,0X24,0X00,0X00,
0X00,0X18,0X24,0X24,0X24,0X28,0XFC,0X00,0X00,0X38,0X54,0X54,0X54,0X54,0X30,0X00,
0X00,0X00,0X10,0X7C,0X50,0X00,0X00,0X00,0X00,0X18,0X25,0X25,0X11,0X3E,0X00,0X00,
0X00,0X00,0XFC,0X20,0X20,0X1C,0X00,0X00,0X00,0X00,0X00,0X00,0XBC,0X00,0X00,0X00,
0X00,0X01,0X01,0X21,0XBE,0X00,0X00,0X00,0X00,0X00,0XFC,0X08,0X14,0X24,0X00,0X00,
0X00,0X00,0X00,0XFC,0X04,0X00,0X00,0X00,0X00,0X3C,0X20,0X10,0X10,0X20,0X3C,0X00,
0X00,0X00,0X3C,0X10,0X20,0X20,0X3C,0X00,0X00,0X18,0X24,0X24,0X24,0X24,0X18,0X00,
0X00,0X3F,0X14,0X24,0X24,0X24,0X18,0X00,0X00,0X18,0X24,0X24,0X24,0X14,0X3F,0X00,
0X00,0X00,0X3C,0X10,0X20,0X20,0X10,0X00,0X00,0X00,0X24,0X54,0X54,0X48,0X00,0X00,
0X00,0X00,0X20,0X7C,0X24,0X20,0X00,0X00,0X00,0X00,0X38,0X04,0X04,0X08,0X3C,0X00,
0X00,0X30,0X08,0X04,0X04,0X08,0X30,0X00,0X30,0X0C,0X04,0X08,0X08,0X04,0X0C,0X30,
0X00,0X24,0X14,0X08,0X08,0X14,0X24,0X00,0X00,0X21,0X11,0X0A,0X04,0X08,0X30,0X00,
0X00,0X00,0X24,0X2C,0X34,0X24,0X00,0X00,0X00,0X00,0X30,0XFC,0X84,0X84,0X00,0X00,
0X00,0X00,0X00,0X00,0XFE,0X00,0X00,0X00,0X00,0X00,0X84,0X84,0XFC,0X30,0X00,0X00,
0X00,0X08,0X10,0X10,0X08,0X08,0X10,0X00,0X00,0XFC,0XFC,0XFC,0XFC,0XFC,0XFC,0X00,
};

