/* Copyright 2022 Abdalrahman Ali @psycher */

#pragma once
#include "psycher.h"

// tap dance enum
enum tap_dance_keys {
    TD_CLN = 1,
    TD_TERMINATOR,
    TD_LSFT_CAPS,
    TD_COUNT // tap_dance_actions array size
};

// Declare with explicit size
#ifdef TAP_DANCE_ENABLE
    extern tap_dance_action_t tap_dance_actions[TD_COUNT];
#endif

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;


// https://docs.qmk.fm/#/feature_tap_dance
td_state_t cur_dance(tap_dance_state_t *state);

// void terminator_exec(tap_dance_state_t *state, void *user_data);

void terminator_finished(tap_dance_state_t *state, void *user_data);
void terminator_reset(tap_dance_state_t *state, void *user_data);

// void dance_cln_finished(tap_dance_state_t *state, void *user_data);
// void dance_cln_reset(tap_dance_state_t *state, void *user_data);
// void dance_LSFT_finished(tap_dance_state_t *state, void *user_data);
// void dance_LSFT_reset(tap_dance_state_t *state, void *user_data);
