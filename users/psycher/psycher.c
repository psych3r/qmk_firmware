/* Copyright 2022 Abdalrahman Ali @psycher */

#include "psycher.h"

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
        case PASS_MACRO:
            if (record->event.pressed)
                SEND_STRING("L3tm3inbia55@12\n"/* SS_TAP(X_ENT)*/);
            break;
        default:
            return true; // Process all other keycodes normally
    }
    return true;
}

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

// dz
// QK_GESC, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
// KC_TAB,  MODS,    HJKL,    KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
// TMUX,    GUIA,    ALTS,    CTLD,   SFTF,   KC_G,   KC_H,   SFTJ,    CTLK,    ALTL,    GUIN,    KC_QUOT, KC_ENT ,
// SCAP,    KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, UP__,
// KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, TERM,   LEFT,   DWNN,   RGHT


// nk
// QK_GESC, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
// KC_TAB,  MODS,    HJKL,    KC_E,   KC_R,   KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
// TMUX,    GUIA,    ALTS,    CTLD,   SFTF,   KC_G,   KC_H,    SFTJ,    CTLK,    ALTL,    KC_SCLN, KC_QUOT, KC_ENT,  KC_END,
// KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   TT(_hjkl),
// KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, TERM,   TT(_vrgb),  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT

// 67
// QK_GESC, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
// KC_TAB,  MODS,    HJKL,    KC_E,   KC_R,   KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
// TMUX,    GUIA,    ALTS,    CTLD,   SFTF,   KC_G,   KC_H,    SFTJ,    CTLK,    ALTL,    GUIN,    KC_QUOT,          KC_ENT,  KC_END,
// SCAP,    KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   TT(_hjkl),
// KC_LCTL, KC_LGUI, KC_LALT,                         KC_SPC,                  TT(_vrgb), KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT






