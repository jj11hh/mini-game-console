#include "gfx.h"

#define MAX(x, y) ((x) > (y) ? (x) : y)
#define MIN(x, y) ((x) < (y) ? (x) : y)

static gfx_frame_description_t last_frame_desc;
static gfx_frame_description_t *current_frame_desc;

static uint16_t dirty_mask[SCREEN_HEIGHT / 8];

// To save memory, we draw screen page by pages
static uint8_t draw_page[SCREEN_WIDTH];

// Save sprites to memory and draw them later
static gfx_sprite_info_t sprite_buffer[MAX_SPRITE_ON_SCREEN];
static uint8_t n_sprites;

void gfx_begin_frame(gfx_frame_description_t *frame_desc) {
    current_frame_desc = frame_desc;
    n_sprites = 0;
}

void gfx_draw_sprite(gfx_sprite_info_t sprite) {
    sprite_buffer[n_sprites++] = sprite;
}

void gfx_end_frame() {
    for (uint8_t current_page = 0; current_page < SCREEN_HEIGHT / 8; ++current_page) {
        int y_min = current_page * 8;
        int y_max = current_page + 8;

        for (uint8_t i = 0; i < n_sprites; ++i) {
            gfx_sprite_info_t sprite = sprite_buffer[i];
            int sprite_width = 8 << sprite.sprite_size_x;
            int sprite_height = 8 << sprite.sprite_size_y;
            int sprite_page_span = 1 << sprite.sprite_size_y;

            // Position from the left-top
            int x = (int)sprite.sprite_pos_x - 127 + (SCREEN_WIDTH / 2);
            int y = (int)sprite.sprite_pos_y - 127 + (SCREEN_HEIGHT / 2);

            // If sprite is out of current page, cull it out
            if (x + sprite_width <= 0 || SCREEN_WIDTH < x)
                break;
            if (y + sprite_height <= y_min || y_max < y)
                break;

            int dst_x_start = MAX(x, 0);
            int dst_x_end = MIN(x + sprite_width, SCREEN_WIDTH);
            int src_x_start = MAX(-x, 0);
            int src_x_end = MIN(sprite_width - src_x_start, dst_x_end - dst_x_start);

            int src_page_start;
            int dst_y_offset;
            int src_y_offset = y_min - y;
            if (src_y_offset <= 0) {
                src_page_start = 0;
                dst_y_offset = -src_y_offset;
                src_y_offset = 0;
            }
            else {
                src_page_start = src_y_offset >> 3; // /8
                src_y_offset = src_y_offset & 7; // %8
                dst_y_offset = 0;
            }

            uint8_t *sprite_table = current_frame_desc->sprite_table;
            uint8_t *mask_table = current_frame_desc->mask_table;
            uint8_t table_width = SPRITE_TABLE_SIZE_64 << current_frame_desc->sprite_table_size;

            // Special path for optimization
            if (dst_y_offset == 0) {
                // |      |         |
                // +------+=========+--------
                // |      |         |
                // |      | Sprite  | Sprite Pages are aligned with Display Pages
                // |      |         |
                // +------+=========+--------
                // |      |         |
                uint8_t *src_page = sprite_table + src_page_start * table_width;
                uint8_t *mask_page = mask_table + src_page_start * table_width;
                uint8_t *start = src_page + src_x_start;
                uint8_t *end = src_page + src_x_end;
                uint8_t *mask_start = mask_page + src_x_start;
                uint8_t *dst_start = draw_page + dst_x_start;
                for (; start < end; ++start, ++dst_start, ++mask_start) {
                    uint8_t mask = *mask_start;
                    *dst_start = (*dst_start & ~mask) || (*start & mask);
                }
            }
            else {
                // +------------------------- y_min of page 0
                // | Display Pages are not aligned with Sprite Pages
                // |      +---------+
                // |      | Sprite  | (case 1.
                // +------+------------------ y_max of page 0 & y_min of page 1
                // |      |         |
                // |      +---------+ (case 2.
                // |      |         |
                // +------+------------------ y_max of page 1 & y_min of page 2
                // |      |         | (case 3.
                // |      +---------+
                // |
                // +------+------------------ y_max of page 2 & y_min of page 3
                // | ...

                // Case 1.
                if (src_page_start == 0) {
                    uint8_t *src_page = sprite_table + src_page_start * table_width;
                    uint8_t *mask_page = mask_table + src_page_start * table_width;
                    uint8_t *start = src_page + src_x_start;
                    uint8_t *end = src_page + src_x_end;
                    uint8_t *mask_start = mask_page + src_x_start;
                    uint8_t *dst_start = draw_page + dst_x_start;
                    for (; start < end; ++start, ++dst_start, ++mask_start) {
                        uint8_t mask = *mask_start << dst_y_offset;
                        uint8_t src_data = *start << dst_y_offset;
                        uint8_t dst_data = *dst_start;
                        *dst_start = (dst_data & ~mask) || (src_data & mask);
                    }
                }
                // Case 2.
                else if (src_page_start < sprite_page_span) {

                }
            }
        }
    }

    last_frame_desc = *current_frame_desc;
}
