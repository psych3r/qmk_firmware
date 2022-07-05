#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"
#include "abdalrahman-ali.h"

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record)
{
    switch (keycode)
    {
        case GUIA:
            return TAPPING_TERM + 50; break;
        case ALTS:
            return TAPPING_TERM + 75; break;
        case CTLD:
            return TAPPING_TERM + 50; break;
        case SFTF:
            return TAPPING_TERM - 10; break;
        default:
            return TAPPING_TERM;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
    [_base] = LAYOUT_65_ansi_blocker(
        KC_GESC, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  MODS,    HJKL,    KC_E,   KC_R,   KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        TMUX,    GUIA,    ALTS,    CTLD,   SFTF,   KC_G,   KC_H,    SFTJ,    CTLK,    ALTL,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_END,
        SCAP,    KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   TT(_hjkl),
        KC_LCTL, KC_LGUI, KC_LALT,                         KC_SPC,                  TT(_vrgb), KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_game] = LAYOUT_65_ansi_blocker(
        KC_GESC, KC_1,    KC_2,    KC_3,   KC_4,    KC_5,   KC_6,    KC_7,    KC_8,      KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,   KC_Y,    KC_U,    KC_I,      KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,   KC_H,    KC_J,    KC_K,      KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_END,
        KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,   KC_N,    KC_M,    KC_COMM,   KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP, DF(_base),
        KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,           TT(_vrgb), KC_RCTL,                   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_vrgb] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_DEL,  _______,
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, KC_PSCR, KC_SLCK,  KC_PAUS, QK_BOOT, KC_PGUP,
        _______, RGB_SPI, RGB_SPD, _______, _______, _______, _______, _______, _______, _______, _______, _______,           EEP_RST, KC_PGDN,
        _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, _______, _______, _______, _______, _______,       TT(_numpad), KC_VOLU, KC_MUTE,
        _______, _______, _______,                            _______,                   _______, TERM,              KC_MPRV, KC_VOLD, KC_MNXT
    ),

    [_hjkl] = LAYOUT_65_ansi_blocker(
        KC_PWR,  _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_LEFT, KC_RIGHT, KC_UP,   KC_DOWN, _______, KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, KC_ENT, _______,          _______,  _______,
        _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU, _______,
        _______, _______, _______,  _______, _______, _______,                                                       _______, KC_VOLD, DF(_game)
    ),

    [_mods] = LAYOUT_65_ansi_blocker(
        KC_PWR,  _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,  _______, _______, _______, KC_BSPC, KC_END,  KC_HOME,  KC_DEL,  KC_ENT, _______,          _______, _______,
        _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______,          KC_RSFT, KC_VOLU, _______,
        _______, _______, _______,  _______, _______, _______,                                                       _______, KC_VOLD, _______
    ),

    [_numpad] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_BSPC,      TT(_numpad), _______, _______,
        _______, _______, _______,                            KC_0,             KC_DOT,  KC_ENT,                    _______, _______, _______
    ),
};

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)
{
    if (get_rgb_nightmode()) rgb_matrix_set_color_all(RGB_OFF);

    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) rgb_matrix_set_color(LED_CAPS, RGB_WHITE);

    /** if (host_keyboard_led_state().caps_lock) { */
    /**     RGB_MATRIX_INDICATOR_SET_COLOR(LED_CAPS, 255, 255, 255); */
    /** } else { */
    /**     RGB_MATRIX_INDICATOR_SET_COLOR(LED_CAPS, 0, 0, 0); */
    /** } */

    /** static uint16_t key_timer; */
    /** switch(get_highest_layer(default_layer_state)) */
    /** { */
    /**     case _game: */
    /**         [> key_timer = timer_read(); <] */
    /**         [> if (timer_elapsed(key_timer) < 1000) <] */
    /**         [> { <] */
    /**         [>     // do something if less than 100ms have passed <] */
    /**         [>     set_array_rgb(LED_LIST_LOL, ARRAYSIZE(LED_LIST_LOL), RGB_GOLD); <] */
    /**         [> } <] */
    /**         [> else <] */
    /**         [> { <] */
    /**         [>     // do something if 100ms or more have passed <] */
    /**         [>     set_array_rgb(LED_LIST_LOL, ARRAYSIZE(LED_LIST_LOL), RGB_OFF); <] */
    /**         [>     //rgb_matrix_set_color_all(RGB_OFF); <] */
    /**         [> } <] */
    /**         set_array_rgb(LED_LIST_LOL, ARRAYSIZE(LED_LIST_LOL), RGB_GOLD); */
    /**         break; */
    /**     default: */
    /**         break; */
    /** } */

    switch(get_highest_layer(layer_state | default_layer_state))
    {
        case _game:
            set_array_rgb(LED_LIST_LOL, ARRAYSIZE(LED_LIST_LOL), RGB_GOLD);
            break;
        case _vrgb:
            rgb_matrix_set_color(LED_FN,   RGB_GOLD);
            break;
        case _hjkl:
            set_array_rgb(LED_LIST_HJKL, ARRAYSIZE(LED_LIST_HJKL), RGB_GOLDENROD);
            break;
        case _mods:
            //set_array_rgb(LED_LIST_WASD,   ARRAYSIZE(LED_LIST_WASD),   RGB_CHARTREUSE);
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
            set_array_rgb(LED_LIST_NUMPAD, ARRAYSIZE(LED_LIST_NUMPAD), RGB_CYAN);
            break;
        default:
            break;
    }
}

void suspend_power_down_user(void) { rgb_matrix_set_suspend_state(true); }
void suspend_wakeup_init_user(void) { rgb_matrix_set_suspend_state(false); }


void keyboard_post_init_kb(void)
{
    // start with no rgb, yet enable rgb indication...
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CYCLE_ALL);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}

void keyboard_post_init_keymap(void)
{
    // keyboard_post_init_user() moved to userspace
    #ifdef RGB_MATRIX_ENABLE
    //rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    activate_rgb_nightmode(true);  // Set to true if you want to startup in nightmode, otherwise use Fn + Z to toggle
    #endif
}
