//
// Created by Jiang on 2022/9/18.
//

#ifndef MINIGAMECONSOLE_PIN_DEFS_H
#define MINIGAMECONSOLE_PIN_DEFS_H

#include "main.h"
#include "spi.h"

#define CPU_FREQ 48000000

static inline void ssd1306_set_rst_high() {
    LL_GPIO_SetOutputPin(OLED_RST_GPIO_Port, OLED_RST_Pin);
}

static inline void ssd1306_set_rst_low() {
    LL_GPIO_ResetOutputPin(OLED_RST_GPIO_Port, OLED_RST_Pin);
}

static inline void ssd1306_set_dc_high() {
    LL_GPIO_SetOutputPin(OLED_DC_GPIO_Port, OLED_DC_Pin);
}

static inline void ssd1306_set_dc_low() {
    LL_GPIO_ResetOutputPin(OLED_DC_GPIO_Port, OLED_DC_Pin);
}

static inline void ssd1306_delay_at_least_3us() {
    // wait for 5us
    uint32_t count = CPU_FREQ * 5 / 1000000;
    while (--count);
}

static inline void ssd1306_spi_write_byte(uint8_t data) {
	// Wait for buffer empty
	while(!LL_SPI_IsActiveFlag_TXE(SPI1));
    LL_SPI_TransmitData8(SPI1, data);
	//HAL_SPI_Transmit(&hspi1, &data, 1, 10);
}

static inline void ssd1306_spi_set_dma_source(uint8_t *source_addr, uint32_t length) {
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_3, (uint32_t)source_addr);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, length);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);
}

static inline void ssd1306_spi_init_dma() {
    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_3, (uint32_t)(&SPI1->DR));
    LL_SPI_EnableDMAReq_TX(SPI1);
}

#define _SSD1306_SET_RST_HIGH() ssd1306_set_rst_high()
#define _SSD1306_SET_RST_LOW() ssd1306_set_rst_low()

#define _SSD1306_SET_DC_HIGH() ssd1306_set_dc_high()
#define _SSD1306_SET_DC_LOW() ssd1306_set_dc_low()

#define _SSD1306_DELAY_AT_LEAST_3US() ssd1306_delay_at_least_3us()

#define _SSD1306_SPI_WRITE_BYTE(_Byte) ssd1306_spi_write_byte(_Byte)

#endif //MINIGAMECONSOLE_PIN_DEFS_H
