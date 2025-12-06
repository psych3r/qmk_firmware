#include QMK_KEYBOARD_H
#include "debounce.h"
#include "psycher.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_base] = LAYOUT_wrapper(LAYOUT_60_ansi_split_rshift, _BASE_ROW1, _BASE_ROW2, _BASE_ROW3, _BASE_ROW4_60_split_rshft, _BASE_ROW5_60),
    [_game] = LAYOUT_wrapper(LAYOUT_60_ansi_split_rshift, _GAME_ROW1, _GAME_ROW2, _GAME_ROW3, _GAME_ROW4_60_split_rshft, _GAME_ROW5_60),
    [_vrgb] = LAYOUT_wrapper(LAYOUT_60_ansi_split_rshift, _VRGB_ROW1, _VRGB_ROW2, _VRGB_ROW3, _VRGB_ROW4_60_split_rshft, _VRGB_ROW5_60),
    [_hjkl] = LAYOUT_wrapper(LAYOUT_60_ansi_split_rshift, _HJKL_ROW1, _HJKL_ROW2, _HJKL_ROW3, _HJKL_ROW4_60_split_rshft, _HJKL_ROW5),
    [_mods] = LAYOUT_wrapper(LAYOUT_60_ansi_split_rshift, _MODS_ROW1, _MODS_ROW2, _MODS_ROW3, _MODS_ROW4_60_split_rshft, _MODS_ROW5),

    // [0] = LAYOUT_wired(
    //     KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,     KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSLS, KC_BSPC,
    //     KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,     KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS,
    //     KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,     KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, KC_NUHS, KC_ENT,
    //     KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, KC_RSFT, MO(1),
    //     KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT,  KC_RGUI, MO(1),   KC_RCTL
    // ),
    //
    // [1] = LAYOUT_wired(
    //     KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,   KC_F12,  KC_TRNS, KC_TRNS,
    //     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
    //     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, NK_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
    //     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_KB_11, QK_KB_12,KC_TRNS,  KC_TRNS, KC_TRNS,
    //     KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                                      KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS
    // ),
    //
    // [2] = LAYOUT_60_ansi_split_rshift(
    //     KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,     KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC,
    //     KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,     KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS,
    //     KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,     KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,      KC_ENT,
    //     KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, KC_RSFT, MO(1),
    //     KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT,  KC_RGUI, MO(1),   KC_RCTL
    //     ),

};

// Add this function to your keymap.c file
// This will control the Caps Lock LED based on layer state
layer_state_t layer_state_set_user(layer_state_t state) {
    // Turn on Caps Lock LED when layer 1 is active, off otherwise
    writePin(LED_CAPS_LOCK_PIN, layer_state_cmp(state, _game));
    // writePin(LED_CAPS_LOCK_PIN, !layer_state_cmp(state, 1));
    return state;
}

// [] There should be smarter ways to do this in QMK
bool led_update_user(led_t led_state) {
    // Disable the default Caps Lock LED behavior
    // Return false to prevent QMK from controlling the LED
    return false;
}

// Alternative method if LED_CAPS_LOCK_PIN is not defined:
// Use this if the above doesn't work
// layer_state_t layer_state_set_user(layer_state_t state) {
//     // Check if layer 1 is active
//     if (layer_state_cmp(state, 1)) {
//         // Turn on Caps Lock LED
//         gpio_set_pin_output(LED_CAPS_LOCK_PIN);
//         gpio_write_pin_low(LED_CAPS_LOCK_PIN);  // or gpio_write_pin_high depending on your LED
//     } else {
//         // Turn off Caps Lock LED
//         gpio_write_pin_high(LED_CAPS_LOCK_PIN);  // or gpio_write_pin_low depending on your LED
//     }
//     return state;
// }
