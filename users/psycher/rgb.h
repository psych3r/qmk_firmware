/* Copyright 2022 Abdalrahman Ali @psycher */

#pragma once
#include "psycher.h"

void activate_rgb_nightmode (bool turn_on);
bool get_rgb_nightmode(void);
void set_array_rgb(const uint8_t* led_array, uint8_t arr_size, uint8_t r, uint8_t g, uint8_t b);

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max);

void suspend_power_down_user(void);

void suspend_wakeup_init_user(void);


// extern const uint8_t LED_LIST_FN[1];
// extern const uint8_t LED_LIST_CAPS[1];
// extern const uint8_t LED_LIST_LOL[6];
// extern const uint8_t LED_LIST_WASD[4];
// extern const uint8_t LED_LIST_ARROWS[4];
// extern const uint8_t LED_LIST_HJKL[4];
// extern const uint8_t LED_LIST_NUMROW[15];
// extern const uint8_t LED_LIST_QWERTYROW[15];
// extern const uint8_t LED_LIST_NUMPAD[12];


// extern const uint8_t *LED_LIST_FN_PTR;
// extern const uint8_t *LED_LIST_CAPS_PTR;
// extern const uint8_t *LED_LIST_LOL_PTR;
// extern const uint8_t *LED_LIST_WASD_PTR;
// extern const uint8_t *LED_LIST_ARROWS_PTR;
// extern const uint8_t *LED_LIST_HJKL_PTR;
// extern const uint8_t *LED_LIST_NUMROW_PTR;
// extern const uint8_t *LED_LIST_QWERTYROW_PTR;
// extern const uint8_t *LED_LIST_NUMPAD_PTR;


// extern const uint8_t LED_LIST_FN_LEN;
// extern const uint8_t LED_LIST_CAPS_LEN;
// extern const uint8_t LED_LIST_LOL_LEN;
// extern const uint8_t LED_LIST_WASD_LEN;
// extern const uint8_t LED_LIST_ARROWS_LEN;
// extern const uint8_t LED_LIST_HJKL_LEN;
// extern const uint8_t LED_LIST_NUMROW_LEN;
// extern const uint8_t LED_LIST_QWERTYROW_LEN;
// extern const uint8_t LED_LIST_NUMPAD_LEN;


extern const uint8_t LED_LIST_FN[LED_LIST_FN_LEN];
extern const uint8_t LED_LIST_CAPS[LED_LIST_CAPS_LEN];
extern const uint8_t LED_LIST_LOL[LED_LIST_LOL_LEN];
extern const uint8_t LED_LIST_WASD[LED_LIST_WASD_LEN];
extern const uint8_t LED_LIST_ARROWS[LED_LIST_ARROWS_LEN];
extern const uint8_t LED_LIST_HJKL[LED_LIST_HJKL_LEN];
extern const uint8_t LED_LIST_NUMROW[LED_LIST_NUMROW_LEN];
extern const uint8_t LED_LIST_QWERTYROW[LED_LIST_QWERTYROW_LEN];
extern const uint8_t LED_LIST_NUMPAD[LED_LIST_NUMPAD_LEN];
