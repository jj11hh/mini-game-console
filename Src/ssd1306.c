//
// Created by Jiang on 2022/9/18.
//

#include "ssd1306.h"

static const uint8_t ssd1306_init_commands[] = {
		0xAE, // Display Off

		// 0x00, // Set Column Start Address for Page Addressing Mode
		// 0x10,

		// 0x40, // Set Display Start Line

		0x20, // Set Memory Addressing Mode
		0x00, // Horizontal Addressing Mode
		// 0x01, // Vertical Addressing Mode
		// 0x02, // Page Addressing Mode

		// 0xA8, // Select Multiplex Ratio
		// 0x3F, // 1/64 Duty

		0xD5, // Set Display Clock Divide
		0x80, // 105HZ

		// 0xD9, // Set Pre-Charge Period
		// 0x22,

		// 0xDA,
		// 0x12,

		// 0xDB,
		// 0x20,

		0x8D, // Set Charge Pump
		0x14, // Enable Charge Pump

		0xA5, // Entire Display ON
		0xAF, // Display ON
};

void ssd1306_init_device() {
    // Send command
    _SSD1306_SET_DC_LOW();

    // Reset device
    _SSD1306_SET_RST_LOW();
    _SSD1306_DELAY_AT_LEAST_3US();

    _SSD1306_SET_RST_HIGH();

    for (uint8_t i = 0; i < sizeof(ssd1306_init_commands); ++i){
    	//_SSD1306_SPI_WRITE_BYTE(ssd1306_init_commands[i]);
    }
    ssd1306_spi_init_dma();
    ssd1306_spi_set_dma_source((uint8_t*)ssd1306_init_commands, sizeof(ssd1306_init_commands));
}

void ssd1306_commit_command_buffer(ssd1306_command_buffer_t *command_buffer){
    if (command_buffer->dc)
        _SSD1306_SET_DC_HIGH();
    else
        _SSD1306_SET_DC_LOW();
}

