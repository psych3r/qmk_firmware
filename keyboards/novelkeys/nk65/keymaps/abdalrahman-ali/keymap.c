#include QMK_KEYBOARD_H
#include "abdalrahman-ali.h"

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) 
{
    switch (keycode) {
        case GUIA:
            return TAPPING_TERM + 65; break;
        case ALTS:
            return TAPPING_TERM + 85; break;
        case CTLD:
            return TAPPING_TERM + 50; break;
        case SFTF:
            return TAPPING_TERM - 10; break;
        default:
            return TAPPING_TERM;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_base] = LAYOUT_65_ansi( /* Base */
    KC_GESC, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
    KC_TAB,  MODS,    HJKL,    KC_E,   KC_R,   KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
    TMUX,    GUIA,    ALTS,    CTLD,   SFTF,   KC_G,   KC_H,    SFTJ,    CTLK,    ALTL,    KC_SCLN, KC_QUOT, KC_ENT,  KC_END,
    KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   TT(3),
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, TERM,   TT(2),  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_game] = LAYOUT_65_ansi(
    KC_GESC, KC_1,    KC_2,    KC_3,   KC_4,    KC_5,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
    KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
    KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_END,
    KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   DF(0),
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, TT(2),  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_vrgb] = LAYOUT_65_ansi( /* RGB and VOL layer */
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  _______,
    _______, S1_DEC,  S1_INC,  S2_DEC,  S2_INC,  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP,
    KC_CAPS, EF_DEC,  EF_INC,  H1_DEC,  H1_INC,  H2_DEC,  H2_INC,  BR_DEC,  BR_INC,  ES_DEC,  ES_INC,  _______, _______, KC_PGDN,
    _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, KC_MUTE,
    _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
    ),

    [_hjkl] = LAYOUT_65_ansi( /* HJKL layer */
    KC_PWR,  _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSPC, KC_DEL,
    KC_TAB,  _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, KC_PGUP,
    TMUX,    KC_LEFT, KC_RIGHT, KC_UP,   KC_DOWN, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_ENT,  _______, KC_ENT,  KC_PGDN,
    KC_LSFT, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, KC_RSFT, KC_VOLU, _______,
    KC_LCTL, KC_LGUI, KC_LALT,  _______, _______, _______, _______, _______, KC_VOLD, DF(1)
    ),

    [_mods] = LAYOUT_65_ansi( /* MODS layer */
    KC_PWR,  _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSPC, KC_DEL,
    KC_TAB,  _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, KC_PGUP,
    TMUX,    _______, _______,  _______, _______, _______, KC_HOME, KC_BSPC, KC_DEL,  KC_END,  KC_ENT,  _______, KC_ENT,  KC_PGDN,
    KC_LSFT, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, KC_RSFT, KC_VOLU, _______,
    KC_LCTL, KC_LGUI, KC_LALT,  _______, _______, _______, _______, _______, KC_VOLD, _______
    ),

};
