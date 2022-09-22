//
// SSD1306 driver for 4-wire SPI interface
// Created by Jiang on 2022/9/18.
//

#ifndef MINIGAMECONSOLE_SSD1306_H
#define MINIGAMECONSOLE_SSD1306_H

#include "pin_defs.h"
#include "stdlib.h"

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

typedef struct ssd1306_command_buffer_s {
    uint8_t *first_command;
    struct ssd1306_command_buffer_s *next;
    uint32_t dc : 1; // Data or Command, HIGH for Data, LOW for Command
    uint32_t length : 31;
} ssd1306_command_buffer_t;

typedef struct ssd1306_command_buffer_list_s {
    ssd1306_command_buffer_t *head;
    ssd1306_command_buffer_t *tail;
} ssd1306_command_buffer_list_t;

static inline void ssd1306_init_command_buffer(ssd1306_command_buffer_t *command_buffer) {
    command_buffer->first_command = NULL;
    command_buffer->length = 0u;
    command_buffer->next = NULL;
}

static inline void ssd1306_init_command_buffer_list(ssd1306_command_buffer_list_t *list) {
    list->head = NULL;
    list->tail = NULL;
}

static inline void ssd1306_command_buffer_list_push(ssd1306_command_buffer_list_t *list, ssd1306_command_buffer_t *command_buffer) {
    if (list->head == NULL) {
        list->head = command_buffer;
        list->tail = command_buffer;
    }
    else {
        list->tail->next = command_buffer;
        list->tail = command_buffer;
    }
}

static inline void ssd1306_command_buffer_list_popleft(ssd1306_command_buffer_list_t *list, const ssd1306_command_buffer_t *command_buffer) {
    command_buffer = list->head;
    if (list->head != NULL) {
        list->head = list->head->next;
    }
    if (list->head == NULL) {
        list->tail = NULL;
    }
}

ssd1306_command_buffer_t *ssd1306_alloc_command_buffer();
void ssd1306_release_command_buffer(ssd1306_command_buffer_t *);

// Execute a single command buffer. User manages its memory
void ssd1306_submit_command_buffer(ssd1306_command_buffer_t *command_buffer);
void ssd1306_spi_dma_handle_irq();
void ssd1306_init_device();

#endif //MINIGAMECONSOLE_SSD1306_H
