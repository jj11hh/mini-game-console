//
// Created by Jiang on 2022/10/22.
//

#ifndef MINIGAMECONSOLE_KEYPAD_H
#define MINIGAMECONSOLE_KEYPAD_H

#include "main.h"

extern uint8_t key_pressed;
extern uint8_t prev_key_pressed;

static inline uint8_t get_raw_key_data() {
    uint8_t result = 0u;
    uint32_t data = LL_GPIO_ReadInputPort(GPIOA);

    // Extract PA0 - PA4 bits
    result = data & 0x1F;

    data = LL_GPIO_ReadInputPort(GPIOB);

    // Store PB1 to 6th bit
    result |= ((data & 0x2u) >> 1u) << 5u;

    // Pins are configured as pull-up, if a key is pressed, a low value is read
    // Turn it to high for pressed
    return ~result;
}

static inline void update_key_state() {
    prev_key_pressed = key_pressed;
    key_pressed = get_raw_key_data();
}

static inline uint8_t get_key_pressed(){
    return key_pressed & 0x3F;
}

static inline uint8_t get_key_down() {
    return (key_pressed ^ prev_key_pressed) & key_pressed & 0x3F;
}

static inline uint8_t get_key_up() {
    return (key_pressed ^ prev_key_pressed) & (~key_pressed) & 0x3F;
}



#endif //MINIGAMECONSOLE_KEYPAD_H
