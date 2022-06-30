#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"
#include "abdalrahman-ali.h"

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) 
{
    switch (keycode) {
        case GUIA:
            return TAPPING_TERM + 50; break;
        case ALTS:
            return TAPPING_TERM + 75; break;
        case CTLD:
            return TAPPING_TERM + 50; break;
        default:
            return TAPPING_TERM;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_base] = LAYOUT_60_ansi(
        KC_GESC, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  MODS,    HJKL,    KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        TMUX,    GUIA,    ALTS,    CTLD,   SFTF,   KC_G,   KC_H,   SFTJ,    CTLK,    ALTL,    KC_SCLN, KC_QUOT, KC_ENT ,
        SCAP,    KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, UP__,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, TERM,   LEFT,   DWNN,   RGHT
    ),

    [_game] = LAYOUT_60_ansi(
        KC_GESC, KC_1,    KC_2,    KC_3,   KC_4,    KC_5,   KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,   KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,   KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,   KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, TT(_hjkl),  KC_RCTL, DF(_base)
    ),

    [_vrgb] = LAYOUT_60_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, RGB_TOG, _______, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_MOD, _______, _______, _______, RESET,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, RGB_SPI, RGB_SPD, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, DF(_game)
    ),

    [_hjkl] = LAYOUT_60_ansi(
        KC_PWR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,   KC_DEL,
        _______, _______, KC_UP,   _______, _______, _______, KC_CALC, _______, KC_INS,  _______,  KC_PSCR, KC_SLCK, KC_PAUS,  KC_HOME,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_HOME, KC_PGUP, KC_END,
        KC_MPRV, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, NK_TOGG, _______, _______,  KC_END,  KC_VOLU, KC_MUTE,
        _______, _______, _______, _______, KC_LEFT, KC_VOLD, KC_RIGHT, _______
    ),

    [_mods] = LAYOUT_60_ansi(
        KC_PWR,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSPC,
        KC_TAB,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS,
        TMUX,    _______, _______, _______, _______, _______, KC_HOME, KC_BSPC, KC_DEL,  KC_END,  KC_ENT,  _______, KC_ENT,
        KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, _______, _______, _______, _______, _______
    ),
};

//#ifdef RGB_MATRIX_ENABLE

// Capslock, Scroll lock and Numlock indicator
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)
{
    //if (get_rgb_nightmode()) rgb_matrix_set_color_all(RGB_OFF);

    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK))
    {
        rgb_matrix_set_color(LED_CAPS, RGB_RED);
        rgb_matrix_set_color(LED_Q,    RGB_RED);
        rgb_matrix_set_color(LED_A,    RGB_RED);
    }

    /** if (host_keyboard_led_state().caps_lock) { */
    /**     RGB_MATRIX_INDICATOR_SET_COLOR(LED_CAPS, 255, 255, 255); */
    /** } else { */
    /**     RGB_MATRIX_INDICATOR_SET_COLOR(LED_CAPS, 0, 0, 0); */
    /** } */

    switch(get_highest_layer(default_layer_state))
    {
        case _game:
            set_array_rgb(LED_LIST_LOL, ARRAYSIZE(LED_LIST_LOL), RGB_GOLD);
            break;
        default:
            break;
    }

    switch(get_highest_layer(layer_state))
    {
        case _vrgb:
            rgb_matrix_set_color(LED_FN,   RGB_GOLD);
            break;
        case _hjkl:
            set_array_rgb(LED_LIST_ARROWS, ARRAYSIZE(LED_LIST_ARROWS), RGB_GOLDENROD);
            break;
        case _mods:
            set_array_rgb(LED_LIST_NUMPAD, ARRAYSIZE(LED_LIST_NUMPAD), RGB_CYAN);
            set_array_rgb(LED_LIST_WASD,   ARRAYSIZE(LED_LIST_WASD),   RGB_CHARTREUSE);
            break;
        default:
            break;
    }
}

void suspend_power_down_user(void)
{
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void)
{
    rgb_matrix_set_suspend_state(false);
}
//#endif

void keyboard_post_init_user(void) {
    // start with no rgb, yet enable rgb indication...
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}

/** void keyboard_post_init_keymap(void) { */
/**     // keyboard_post_init_user() moved to userspace */
/**     #ifdef RGB_MATRIX_ENABLE */
/**         rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR); */
/**         activate_rgb_nightmode(false);  // Set to true if you want to startup in nightmode, otherwise use Fn + Z to toggle */
/**     #endif */
/** } */
