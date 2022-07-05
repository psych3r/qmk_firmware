/* Copyright 2022 Abdalrahman Ali @abdalrahman-ali */
#pragma once
#include QMK_KEYBOARD_H

#ifdef TAP_DANCE_ENABLE
#include "tap_dance.h"
#endif

enum my_layers {
    _base = 0,
    _game,
    _vrgb,
    _hjkl,
    _mods
};

// custom KCs enum
enum custom_keycodes {
    MT_TMUXPRE = SAFE_RANGE
};

#define ARRAYSIZE(arr)  sizeof(arr)/sizeof(arr[0])

// Left-hand home row mods
#define GUIA LGUI_T(KC_A)
#define ALTS LALT_T(KC_S)
#define CTLD LCTL_T(KC_D)
#define SFTF LSFT_T(KC_F)

// Right-hand home row mods
#define SFTJ RSFT_T(KC_J)
#define CTLK RCTL_T(KC_K)
#define ALTL LALT_T(KC_L)
#define GUI_SCLN RGUI_T(KC_SCLN)

// Tmux, hjkl and mods
#define TMUX_PRE LCTL_T(MT_TMUXPRE)
#define TMUX LCTL_T(TMUX_PRE)
#define HJKL LT(_hjkl, KC_W)
#define MODS LT(_mods, KC_Q)
#define TERM TD(TD_TERMINATOR)
#define SCAP TD(TD_LSFT_CAPS)
//#define XXX KC_TRNS

#define RGHT LT(_hjkl,KC_RIGHT)
#define UP__ RSFT_T(KC_UP)
#define LEFT LT(_vrgb, KC_LEFT)
#define DWNN RCTL_T(KC_DOWN)


void activate_rgb_nightmode (bool turn_on);
bool get_rgb_nightmode(void);
void set_array_rgb(const uint8_t* led_array, uint8_t arr_size, uint8_t r, uint8_t g, uint8_t b);

// IDLE TIMEOUTS
#ifdef IDLE_TIMEOUT_ENABLE
    #define TIMEOUT_THRESHOLD_DEFAULT   5    // default timeout minutes
    #define TIMEOUT_THRESHOLD_MAX       140  // upper limits (2 hours and 10 minutes -- no rgb indicators above this value)

    //prototype  functions
    uint16_t get_timeout_threshold(void);
    void timeout_reset_timer(void);
    void timeout_update_threshold(bool increase);
    void timeout_tick_timer(void);
#endif  //IDLE_TIMEOUT_ENABLE

