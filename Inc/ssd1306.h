//
// SSD1306 driver for 4-wire SPI interface
// Created by Jiang on 2022/9/18.
//

#ifndef MINIGAMECONSOLE_SSD1306_H
#define MINIGAMECONSOLE_SSD1306_H

#include "pin_defs.h"

#ifndef _SSD1306_SET_RST_HIGH
#define _SSD1306_SET_RST_HIGH()
#endif

#ifndef _SSD1306_SET_RST_LOW
#define _SSD1306_SET_RST_LOW()
#endif

#ifndef _SSD1306_SET_DC_HIGH
#define _SSD1306_SET_DC_HIGH()
#endif

#ifndef _SSD1306_SET_DC_LOW
#define _SSD1306_SET_DC_LOW()
#endif

#ifndef _SSD1306_DELAY_AT_LEAST_3US
#define _SSD1306_DELAY_AT_LEAST_3US()
#endif

#ifndef _SSD1306_SPI_WRITE_BYTE
#define _SSD1306_SPI_WRITE_BYTE(_Byte)
#endif

void ssd1306_init_device();

#endif //MINIGAMECONSOLE_SSD1306_H
