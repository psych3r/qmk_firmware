/* Copyright 2022 Abdalrahman Ali @psycher */

#include "rgb.h"

static bool rgb_nightmode = false;

// Turn on/off NUM LOCK if current state is different
void activate_rgb_nightmode (bool turn_on)
{
    if (rgb_nightmode != turn_on)
        rgb_nightmode = !rgb_nightmode;
}

bool get_rgb_nightmode(void) { return rgb_nightmode; }

void set_array_rgb(const uint8_t* led_array, uint8_t arr_size, uint8_t r, uint8_t g, uint8_t b)
{
    for (uint8_t i = 0; i < arr_size; i++) rgb_matrix_set_color(led_array[i], r, g, b);
}

// Capslock, Scroll lock and Numlock indicator
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)
{
    if (get_rgb_nightmode()) rgb_matrix_set_color_all(RGB_OFF);

    if ( host_keyboard_led_state().caps_lock )
        rgb_matrix_set_color(LED_LIST_CAPS[0], RGB_WHITE);

    switch(get_highest_layer(layer_state | default_layer_state))
    {
        case _game:
            set_array_rgb(LED_LIST_LOL, LED_LIST_LOL_LEN, RGB_GOLD);
            break;
        case _vrgb:
            rgb_matrix_set_color(LED_LIST_FN[0],   RGB_GOLD);
            break;
        case _hjkl:
            set_array_rgb(LED_LIST_HJKL, LED_LIST_HJKL_LEN, RGB_GOLDENROD);
            break;
        case _mods:
            //set_array_rgb(LED_LIST_WASD,   LED_LIST_WASD_LEN,   RGB_CHARTREUSE);
            for (uint8_t row = 0; row < MATRIX_ROWS; ++row)
            {
                for (uint8_t col = 0; col < MATRIX_COLS; ++col)
                {
                    uint8_t index = g_led_config.matrix_co[row][col];
                    if (index >= led_min && index <= led_max
                            && index != NO_LED && keymap_key_to_keycode(_mods, (keypos_t) {col, row}) > KC_TRNS)
                    {
                        rgb_matrix_set_color(index, RGB_CHARTREUSE);
                    }
                }
            }
            break;
        case _numpad:
            set_array_rgb(LED_LIST_NUMPAD, LED_LIST_NUMPAD_LEN, RGB_CYAN);
            break;
        default:
            break;
    }
    return true;
}

void suspend_power_down_user(void)
{
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void)
{
    rgb_matrix_set_suspend_state(false);
}

//////////////////////////////

void keyboard_post_init_kb(void) {
    // start with no rgb, yet enable rgb indication...
    // rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_ALL);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}

void keyboard_post_init_keymap(void) {
    // keyboard_post_init_user() moved to userspace
#ifdef RGB_MATRIX_ENABLE
    // rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    // activate_rgb_nightmode(false);  // Set to true if you want to startup in nightmode, otherwise use Fn + Z to toggle
    activate_rgb_nightmode(true);
#endif
}

