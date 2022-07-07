/* Copyright 2022 Abdalrahman Ali @abdalrahman-ali */

#include "abdalrahman-ali.h"

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
    switch (keycode)
    {
        // sends tmux prefix on tap, that is lctl(kc_spc)
        // tap_code16 sends advanced keycodes. the 16 bit version of the `tap_code` function is used here.
        case TMUX_PRE:
            if (record->tap.count > 0)
            {
                if (record->event.pressed)
                    tap_code16(LCTL(KC_SPC));

                // do not continue with default tap action
                // if the MT was pressed or released, but not held
                return false;
            }
            break;
        default:
            return true; // Process all other keycodes normally
    }
    return true;
}

#ifdef RGB_MATRIX_ENABLE

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

#endif

// TIMEOUTS
#ifdef IDLE_TIMEOUT_ENABLE

static uint16_t timeout_timer = 0;
static uint16_t timeout_counter = 0;  //in minute intervals
static uint16_t timeout_threshold = TIMEOUT_THRESHOLD_DEFAULT;

uint16_t get_timeout_threshold(void) { return timeout_threshold; }

void timeout_reset_timer(void)
{
    timeout_timer = timer_read();
    timeout_counter = 0;
};

void timeout_update_threshold(bool increase)
{
    if (increase && timeout_threshold < TIMEOUT_THRESHOLD_MAX) timeout_threshold++;
    if (!increase && timeout_threshold > 0) timeout_threshold--;
};

void timeout_tick_timer(void)
{
    if (timeout_threshold > 0)
    {
        if (timer_elapsed(timeout_timer) >= 60000)   // 1 minute tick
        {
            timeout_counter++;
            timeout_timer = timer_read();
        }
        #ifdef RGB_MATRIX_ENABLE
        if (timeout_threshold > 0 && timeout_counter >= timeout_threshold)
            rgb_matrix_disable_noeeprom();
        #endif
    } // timeout_threshold = 0 will disable timeout
}
#endif // IDLE_TIMEOUT_ENABLE

__attribute__ ((weak)) void keyboard_post_init_keymap(void) {}
void keyboard_post_init_user(void)
{
    keyboard_post_init_keymap();
    #ifdef STARTUP_NUMLOCK_ON
        activate_numlock(true); // turn on Num lock by default so that the numpad layer always has predictable results
    #endif // STARTUP_NUMLOC_ON
    #ifdef IDLE_TIMEOUT_ENABLE
        timeout_timer = timer_read(); // set inital time for ide timeout
    #endif
}
