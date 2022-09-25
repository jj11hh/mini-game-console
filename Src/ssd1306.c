//
// Created by Jiang on 2022/9/18.
//

#include "ssd1306.h"

static const uint8_t ssd1306_init_commands[] = {
		0xAE, // Display Off

		// 0x00, // Set Column Start Address for Page Addressing Mode
		// 0x10,

		0x40, // Set Display Start Line

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

		0xDA,
		0x12,

        0xA1,

		// 0xDB,
		// 0x20,

        0xD3, // Set Display Offset
        0x00, // 0

		0x8D, // Set Charge Pump
		0x14, // Enable Charge Pump

		0xA4, // Entire Display ON
		0xAF, // Display ON
};

static volatile ssd1306_command_buffer_t current_commands;

// 0 for complete
static volatile uint8_t transmit_complete;

void ssd1306_init_device() {
    // Clear complete flag
    transmit_complete = 0u;

    // Reset device
    _SSD1306_SET_RST_LOW();
    _SSD1306_DELAY_AT_LEAST_3US();

    _SSD1306_SET_RST_HIGH();

    ssd1306_spi_init_dma();

    ssd1306_command_buffer_t init_commands;

    init_commands.first_command = (uint8_t*)ssd1306_init_commands;
    init_commands.length = sizeof(ssd1306_init_commands);
    init_commands.next = NULL;
    init_commands.dc = 0u; // 0 for command

    ssd1306_submit_command_buffer(&init_commands);
}

void ssd1306_wait_for_complete(){
    while (transmit_complete);
}

void ssd1306_submit_command_buffer(ssd1306_command_buffer_t *command_buffer){
    // Wait for last command buffer list to complete
    while (transmit_complete);
    current_commands = *command_buffer;

    ssd1306_wait_for_spi_complete();
    if (current_commands.dc)
        _SSD1306_SET_DC_HIGH();
    else
        _SSD1306_SET_DC_LOW();

    ssd1306_spi_set_dma_source((uint8_t*)current_commands.first_command, current_commands.length);
    ssd1306_spi_dma_start_transmit();
    transmit_complete = 1u;
}

void ssd1306_spi_dma_handle_irq() {
    // Your need clear your flags before this function call manually
    if (current_commands.next != NULL) {
        uint8_t dc = current_commands.dc;
        current_commands = *current_commands.next;

        if (dc != current_commands.dc) {
            ssd1306_wait_for_spi_complete();
            if (current_commands.dc)
                _SSD1306_SET_DC_HIGH();
            else
                _SSD1306_SET_DC_LOW();
        }

        ssd1306_spi_set_dma_source((uint8_t*)current_commands.first_command, current_commands.length);
        ssd1306_spi_dma_start_transmit();
    }
    else {
        // Clear flag
        transmit_complete = 0u;
    }
}

