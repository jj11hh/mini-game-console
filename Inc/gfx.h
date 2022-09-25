#ifndef __GFX_H__
#define __GFX_H__

#include <stdlib.h>
#include <stdint.h>

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

#define MAX_SPRITE_ON_SCREEN 64

#define SPRITE_TABLE_SIZE_64  0
#define SPRITE_TABLE_SIZE_128 1

// A sprite table is consist of an image for its texture and an image with same size for mask (like "alpha").
typedef struct gfx_frame_description_s {
    uint8_t *sprite_table;
    uint8_t *mask_table;
    uint8_t *tile_map;
    uint32_t tile_map_x_offset :16;
    uint32_t tile_map_y_offset :16;
    uint32_t tile_map_width :8;
    uint32_t tile_map_height :8;
    uint32_t sprite_table_size :1;
    uint32_t full_clear :1;
    uint32_t invert_color :1;
} gfx_frame_description_t;

#define SPRITE_SIZE_8 0
#define SPRITE_SIZE_16 1
#define SPRITE_SIZE_32 2
#define SPRITE_SIZE_64 3

typedef struct gfx_sprite_info_s {
    uint32_t sprite_pos_x :8; // map [-128, 127] to [0, 255], 0 for the center of screen
    uint32_t sprite_pos_y :8; // map [-128, 127] to [0, 255], 0 for the center of screen
    uint32_t sprite_idx_x :4;
    uint32_t sprite_idx_y :4;
    uint32_t sprite_size_x :2;
    uint32_t sprite_size_y :2;
} gfx_sprite_info_t;

void gfx_begin_frame(gfx_frame_description_t *frame_desc);
void gfx_draw_sprite(gfx_sprite_info_t sprite);
void gfx_end_frame();

#endif // __GFX_H__
