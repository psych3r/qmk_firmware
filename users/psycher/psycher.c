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


#define _BASE_ROW1 QK_GESC, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC
#define _BASE_ROW2 KC_TAB,  MODS,    HJKL,    KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS
#define _BASE_ROW3 TMUX,    GUIA,    ALTS,    CTLD,   SFTF,   KC_G,   KC_H,   SFTJ,    CTLK,    ALTL,    GUIN,    KC_QUOT, KC_ENT
#define _BASE_ROW4 SCAP,    KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH


#define _BASE_ROW1_65 _BASE_ROW1, KC_DEL
#define _BASE_ROW2_65 _BASE_ROW2, KC_HOME
#define _BASE_ROW3_65 _BASE_ROW3, KC_END

#define _BASE_ROW4_60 _BASE_ROW4, UP__,
#define _BASE_ROW4_65 _BASE_ROW4, KC_RSFT, KC_UP, TT(_hjkl)

// QK_GESC, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
// QK_GESC, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
// QK_GESC, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,

// row 2
// KC_TAB,  MODS,    HJKL,    KC_E,   KC_R,   KC_T,   KC_Y,   KC_U ,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
// KC_TAB,  MODS,    HJKL,    KC_E,   KC_R,   KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
// KC_TAB,  MODS,    HJKL,    KC_E,   KC_R,   KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,

// row 3
// TMUX,    GUIA,    ALTS,    CTLD,   SFTF,   KC_G,   KC_H,   SFTJ ,    CTLK,    ALTL, GUIN   ,    KC_QUOT, KC_ENT,
// TMUX,    GUIA,    ALTS,    CTLD,   SFTF,   KC_G,   KC_H,    SFTJ,    CTLK,    ALTL, GUIN,       KC_QUOT, KC_ENT,  KC_END,
// TMUX,    GUIA,    ALTS,    CTLD,   SFTF,   KC_G,   KC_H,    SFTJ,    CTLK,    ALTL, GUIN   ,    KC_QUOT, KC_ENT,  KC_END,

// row 4
// SCAP,    KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, UP__,
// SCAP,    KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP, TT(_hjkl),
// SCAP,    KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP, TT(_hjkl),

// row 5
// KC_LCTL, KC_LGUI, KC_LALT,              KC_SPC,         TERM,       LEFT     ,  DWNN   , RGHT
// KC_LCTL, KC_LGUI, KC_LALT,              KC_SPC,         TERM,       TT(_vrgb),  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
// KC_LCTL, KC_LGUI, KC_LALT,              KC_SPC,                     TT(_vrgb),  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT




// ============================================================================
// LAYER: _base
// ============================================================================

// Row 1:
// KB1 (60%):
// QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
// QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
// QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,

// Row 2:
// KC_TAB,  MODS,    HJKL,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
// KC_TAB,  MODS,    HJKL,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
// KC_TAB,  MODS,    HJKL,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,

// Row 3:
// TMUX,    GUIA,    ALTS,    CTLD,    SFTF,    KC_G,    KC_H,    SFTJ,    CTLK,    ALTL,    GUIN,    KC_QUOT, KC_ENT,
// TMUX,    GUIA,    ALTS,    CTLD,    SFTF,    KC_G,    KC_H,    SFTJ,    CTLK,    ALTL,    KC_SCLN, KC_QUOT, KC_ENT,  KC_END,
// TMUX,    GUIA,    ALTS,    CTLD,    SFTF,    KC_G,    KC_H,    SFTJ,    CTLK,    ALTL,    GUIN,    KC_QUOT,          KC_ENT,  KC_END,

// Row 4:
// SCAP,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, UP__,
// SCAP,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   TT(_hjkl),
// SCAP,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   TT(_hjkl),

// row 5
// KC_LCTL, KC_LGUI, KC_LALT,              KC_SPC,         TERM,       LEFT     ,  DWNN   , RGHT
// KC_LCTL, KC_LGUI, KC_LALT,              KC_SPC,         TERM,       TT(_vrgb),  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
// KC_LCTL, KC_LGUI, KC_LALT,              KC_SPC,         TT(_vrgb),  KC_RCTL  ,  KC_LEFT, KC_DOWN, KC_RGHT



// ============================================================================
// LAYER: _game
// ============================================================================

// Row 1:
// QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
// QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
// QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,

// Row 2:
// KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
// KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
// KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,

// Row 3:
// KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
// KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_END,
// KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_END,
// KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_END,

// Row 4:
// KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
// KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   DF(_base),
// KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   DF(_base),

// Row 5:
// KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_RALT, TT(_hjkl), KC_RCTL, DF(_base)
// KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_RALT, TT(_vrgb), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
// KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             TT(_vrgb), KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT


// ============================================================================
// LAYER: _vrgb
// ============================================================================

// Row 1:
// KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
// KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  _______,
// KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  _______,

// Row 2:
// _______, RM_TOGG, _______, RM_HUEU, RM_HUED, RM_SATU, RM_SATD, RM_VALU, RM_VALD, RM_NEXT, _______, _______, _______, QK_BOOT,
// _______, RM_SPDD, RM_SPDU, RM_SPDD, RM_SPDU, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP,
// _______, RM_TOGG, RM_NEXT, RM_HUEU, RM_HUED, RM_SATU, RM_SATD, RM_VALU, RM_VALD, _______, KC_PSCR, KC_SCRL, KC_PAUS, QK_BOOT, KC_PGUP,

// Row 3:
// KC_CAPS, _______, _______, _______, _______, _______, _______, _______, RM_SPDU, RM_SPDD, _______, _______, _______,
// KC_CAPS, RM_PREV, RM_NEXT, RM_HUED, RM_HUEU, RM_HUED, RM_HUEU, RM_VALD, RM_VALU, RM_SATD, RM_SATU, _______, _______, KC_PGDN,
// _______, RM_SPDU, RM_SPDD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          EE_CLR,  KC_PGDN,

// Row 4:
// _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
// _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, KC_MUTE,
// _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, _______, _______, _______, _______, _______,       TT(_numpad), KC_VOLU, KC_MUTE,

// Row 5:
// _______, _______, _______, _______, _______, _______, _______, DF(_game)
// _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
// _______, _______, _______,                            _______,                            _______,   TERM,             KC_MPRV, KC_VOLD, KC_MNXT
// _______, _______, _______,                            _______,                            _______,   TERM,             KC_MPRV, KC_VOLD, KC_MNXT


// ============================================================================
// LAYER: _hjkl
// ============================================================================

// Row 1:
// KC_PWR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
// KC_PWR,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSPC, KC_DEL,
// KC_PWR,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

// Row 2:
// _______, _______, KC_UP,   _______, _______, _______, KC_CALC, _______, KC_INS,  _______, KC_PSCR, KC_SCRL, KC_PAUS, KC_HOME,
// KC_TAB,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, KC_PGUP,
// _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

// Row 3:
// _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_HOME, KC_PGUP, KC_END,
// TMUX,    KC_LEFT, KC_RIGHT, KC_UP,  KC_DOWN, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_ENT,  _______, KC_ENT,  KC_PGDN,
// _______, KC_LEFT, KC_RIGHT, KC_UP,  KC_DOWN, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, PASS_MACRO, _______,       _______, _______,

// Row 4:
// KC_MPRV, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, NK_TOGG, _______, _______, KC_END,  KC_VOLU, KC_MUTE,
// KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RSFT, KC_VOLU, _______,
// _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU, _______,

// Row 5:
// _______, _______, _______, _______, KC_LEFT, KC_VOLD, KC_RIGHT, _______
// KC_LCTL, KC_LGUI, KC_LALT, _______, _______, _______, _______, _______, KC_VOLD, DF(_game)
// _______, _______, _______,                            _______,                            TERM,      _______,          _______, KC_VOLD, DF(_game)


// ============================================================================
// LAYER: _mods
// ============================================================================

// Row 1:
// KC_PWR,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSPC,
// KC_PWR,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSPC, KC_DEL,
// KC_PWR,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

// Row 2:
// KC_TAB,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS,
// KC_TAB,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, KC_PGUP,
// _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

// Row 3:
// TMUX,    _______, _______, _______, _______, _______, KC_HOME, KC_BSPC, KC_DEL,  KC_END,  KC_ENT,  _______, KC_ENT,
// TMUX,    _______, _______, _______, _______, _______, KC_HOME, KC_BSPC, KC_DEL,  KC_END,  KC_ENT,  _______, KC_ENT,  KC_PGDN,
// _______, _______, _______, _______, _______, _______, KC_BSPC, KC_END,  KC_HOME, KC_DEL,  KC_ENT,  _______,          _______, _______,

// Row 4:
// KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RSFT,
// KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RSFT, KC_VOLU, _______,
// _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_RSFT, KC_VOLU, _______,

// Row 5:
// KC_LCTL, KC_LGUI, KC_LALT, _______, _______, _______, _______, _______
// KC_LCTL, KC_LGUI, KC_LALT, _______, _______, _______, _______, _______, KC_VOLD, _______
// _______, _______, _______,                            _______,                            TERM,      _______,          _______, KC_VOLD, _______


// ============================================================================
// LAYER: _numpad (KB3 & KB4 only)
// ============================================================================

// Row 1:
_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

// Row 2:
_______, _______, _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    _______, _______, _______, _______,

// Row 3:
_______, _______, _______, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    _______,          _______, _______,

// Row 4:
_______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_BSPC,      TT(_numpad), _______, _______,

// Row 5:
_______, _______, _______,                            KC_0,                               KC_DOT,    KC_ENT,           _______, _______, _______

