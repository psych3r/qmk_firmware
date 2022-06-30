/* Copyright 2022 Abdalrahman Ali @abdalrahman-ali */

#pragma once
#include "abdalrahman-ali.h"

// tap dance enum
enum tap_dance_keys {
    TD_CLN = 1,
    TD_TERMINATOR,
    TD_LSFT_CAPS
};

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
};


// https://docs.qmk.fm/#/feature_tap_dance 
uint8_t cur_dance(qk_tap_dance_state_t *state);

void terminator_finished(qk_tap_dance_state_t *state, void *user_data);
void terminator_reset(qk_tap_dance_state_t *state, void *user_data);
void dance_cln_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_cln_reset(qk_tap_dance_state_t *state, void *user_data);
void dance_LSFT_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_LSFT_reset(qk_tap_dance_state_t *state, void *user_data);

