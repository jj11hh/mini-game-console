#include <string.h>
#include "gfx.h"
#include "ssd1306.h"

#define MAX(x, y) ((x) > (y) ? (x) : y)
#define MIN(x, y) ((x) < (y) ? (x) : y)

static gfx_frame_description_t last_frame_desc;
static gfx_frame_description_t *current_frame_desc;

static uint16_t dirty_mask[SCREEN_HEIGHT / 8];

// To save memory, we draw screen page by pages
static uint8_t back_buffer[SCREEN_WIDTH];
static uint8_t front_buffer[SCREEN_WIDTH];

static uint8_t *draw_page;

// Save sprites to memory and draw them later
static gfx_sprite_info_t sprite_buffer[MAX_SPRITE_ON_SCREEN];
static uint8_t n_sprites;

void gfx_begin_frame(gfx_frame_description_t *frame_desc) {
    current_frame_desc = frame_desc;
    n_sprites = 0;
    draw_page = back_buffer;
}

void gfx_draw_sprite(gfx_sprite_info_t sprite) {
    sprite_buffer[n_sprites++] = sprite;
}

static uint8_t control_cmd[] = {
    0x02, // Column Address: 0x02
    0x10, // Column Address: 0x02
    0xB0, // Page 0
    0xE3, // NOP
};

static ssd1306_command_buffer_t control_buffer;
static ssd1306_command_buffer_t data_buffer;

static inline void draw_upper(uint8_t dst_x_start, uint8_t line_cnt, const uint8_t *sprite_addr,
                       const uint8_t *mask_addr, uint8_t y_offset, uint8_t invert_color){
    for (uint8_t i = 0; i < line_cnt; ++i) {
        uint8_t line_idx = dst_x_start + i;
        uint8_t dst = draw_page[line_idx];
        uint8_t src = sprite_addr[i] >> y_offset;
        if (invert_color) src = ~src;
        uint8_t msk = mask_addr[i] >> y_offset;
        draw_page[line_idx] = (dst & ~msk) | (src & msk);
    }
}

static inline void draw_lower(uint8_t dst_x_start, uint8_t line_cnt, const uint8_t *sprite_addr,
                       const uint8_t *mask_addr, uint8_t y_offset, uint8_t invert_color){
    for (uint8_t i = 0; i < line_cnt; ++i) {
        uint8_t line_idx = dst_x_start + i;
        uint8_t dst = draw_page[line_idx];
        uint8_t src = sprite_addr[i] << (8 - y_offset);
        if (invert_color) src = ~src;
        uint8_t msk = mask_addr[i] << (8 - y_offset);

        draw_page[line_idx] = (dst & ~msk) | (src & msk);
    }
}
static inline void draw_upper_rtl(uint8_t dst_x_start, uint8_t line_cnt, const uint8_t *sprite_addr,
                       const uint8_t *mask_addr, uint8_t y_offset, uint8_t invert_color){
    for (uint8_t i = 0; i < line_cnt; ++i) {
        uint8_t line_idx = dst_x_start + i;
        uint8_t dst = draw_page[line_idx];
        uint8_t src = sprite_addr[-i - 1] >> y_offset;
        if (invert_color) src = ~src;
        uint8_t msk = mask_addr[-i - 1] >> y_offset;
        draw_page[line_idx] = (dst & ~msk) | (src & msk);
    }
}

static inline void draw_lower_rtl(uint8_t dst_x_start, uint8_t line_cnt, const uint8_t *sprite_addr,
                       const uint8_t *mask_addr, uint8_t y_offset, uint8_t invert_color){
    for (uint8_t i = 0; i < line_cnt; ++i) {
        uint8_t line_idx = dst_x_start + i;
        uint8_t dst = draw_page[line_idx];
        uint8_t src = sprite_addr[-i - 1] << (8 - y_offset);
        if (invert_color) src = ~src;
        uint8_t msk = mask_addr[-i - 1] << (8 - y_offset);

        draw_page[line_idx] = (dst & ~msk) | (src & msk);
    }
}

void gfx_end_frame() {
    for (uint8_t current_page = 0; current_page < SCREEN_HEIGHT / 8; ++current_page) {
        int y_min = current_page * 8;
        int y_max = y_min + 8;

        // Clear page before drawing
        for (uint32_t _x = 0; _x < SCREEN_WIDTH / 4; ++_x) *((uint32_t*)draw_page + _x) = 0u;

        for (uint8_t i = 0; i < n_sprites; ++i) {
            gfx_sprite_info_t sprite = sprite_buffer[i];
            int table_width = 64 << current_frame_desc->sprite_table_size;
            int sprite_width = 8 << sprite.sprite_size_x;
            int sprite_height = 8 << sprite.sprite_size_y;
            int sprite_page = sprite.sprite_idx_y;
            int sprite_x_offset = sprite.sprite_idx_x * 8;

            // Position from the left-top
            int x = SP_DECODE_POS(sprite.sprite_pos_x);
            int y = SP_DECODE_POS(sprite.sprite_pos_y);

            // If sprite is out of current page, cull it out
            if (x + sprite_width <= 0 || SCREEN_WIDTH <= x)
                continue;
            if (y + sprite_height <= y_min || y_max <= y)
                continue;

            int dst_x_start = MAX(x, 0);
            int dst_x_end = MIN(x + sprite_width, SCREEN_WIDTH);

            int src_x_start = MAX(-x, 0);
            // int src_x_end = MIN(sprite_width - src_x_start, dst_x_end - dst_x_start);

            uint8_t *sprite_table = current_frame_desc->sprite_table;
            uint8_t *mask_table = current_frame_desc->mask_table;

            int y_offset = y & 7; // mod 8
            int y_page = (y_max - y) >> 3; // div 8

            if (y + sprite_height >= y_max) {
                if (y_offset == 0) y_page -= 1;
                if (!sprite.flip_x) {
                    uint32_t image_offset = (y_page + sprite_page) * table_width + src_x_start + sprite_x_offset;
                    uint8_t *sprite_addr = sprite_table + image_offset;
                    uint8_t *mask_addr = mask_table + image_offset;
                    draw_upper(dst_x_start, dst_x_end - dst_x_start,
                               sprite_addr, mask_addr, y_offset, sprite.invert_color);
                }
                else {
                    uint32_t image_offset = (y_page + sprite_page) * table_width + sprite_x_offset;
                    image_offset += sprite_width - src_x_start;
                    uint8_t *sprite_addr = sprite_table + image_offset;
                    uint8_t *mask_addr = mask_table + image_offset;
                    draw_upper_rtl(dst_x_start, dst_x_end - dst_x_start,
                               sprite_addr, mask_addr,
                               y_offset, sprite.invert_color);
                }
            }

            if (y < y_min) {
                if (!sprite.flip_x) {
                    uint32_t image_offset = (y_page + sprite_page - 1) * table_width + src_x_start + sprite_x_offset;
                    uint8_t *sprite_addr = sprite_table + image_offset;
                    uint8_t *mask_addr = mask_table + image_offset;
                    draw_lower(dst_x_start, dst_x_end - dst_x_start, sprite_addr, mask_addr, y_offset,
                               sprite.invert_color);
                }
                else {
                    uint32_t image_offset = (y_page + sprite_page - 1) * table_width + sprite_x_offset;
                    image_offset += sprite_width - src_x_start;
                    uint8_t *sprite_addr = sprite_table + image_offset;
                    uint8_t *mask_addr = mask_table + image_offset;
                    draw_lower_rtl(dst_x_start, dst_x_end - dst_x_start,
                                   sprite_addr, mask_addr,
                                   y_offset, sprite.invert_color);
                }
            }
        }

        // TODO: Check dirty

        ssd1306_wait_for_complete();

        control_buffer.dc = 0;
        control_buffer.first_command = control_cmd;
        control_buffer.length = sizeof(control_cmd);
        control_buffer.next = &data_buffer;

        data_buffer.dc = 1;
        data_buffer.first_command = draw_page;
        data_buffer.length = SCREEN_WIDTH;
        data_buffer.next = NULL;

        control_cmd[2] = 0xB0 + (7 - current_page);
        ssd1306_submit_command_buffer(&control_buffer);

        // swap buffer
        draw_page = draw_page == back_buffer ? front_buffer : back_buffer;
    }

    last_frame_desc = *current_frame_desc;
}
