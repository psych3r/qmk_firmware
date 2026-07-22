#include QMK_KEYBOARD_H
#include "debounce.h"
#include "psycher.h"

/* ============================================================================
 * LAYER SWITCHING CHEATSHEET
 * ============================================================================
 * Layers:  _base (0) -> everyday typing, home-row mods
 *          _game (1) -> plain QWERTY, no home-row mods
 *          _vrgb (2) -> FN1: F-keys, media, RGB
 *          _hjkl (3) -> FN2: arrow cluster on hold
 *          _mods (4) -> FN:  editing cluster (BSPC/HOME/END/DEL/ENT) on hold
 *
 * Four DIFFERENT switching mechanisms are used below — the confusing part is
 * that they behave differently, so here's what each one actually does:
 *
 *   HOLD keys (momentary, like a normal Fn key)
 *   -------------------------------------------
 *   - MODS  (row2, sits where "Q" is)  -> hold  => _mods active while held
 *   - HJKL  (row2, sits where "W" is)  -> hold  => _hjkl active while held
 *     These are custom dual-role keys from psycher.h: tap = normal Q/W,
 *     hold = the layer. Release and you're back to whatever layer you held
 *     it from (_base or _game).
 *
 *   TT() keys (Tap-Toggle: tap once = nothing/passthrough, HOLD = momentary,
 *              but tap TWICE quickly = layer LOCKS ON until you tap it again)
 *   ------------------------------------------------------------------------
 *   - TT(_hjkl) -> split-rshift key on _base's bottom row.
 *   - TT(_vrgb) -> the key right after Spacebar on _game's bottom row
 *                  (in the RAlt spot).
 *   NOTE: lining up _base's row5 against _game's row5 key-by-key, the key in
 *   _base that sits in the SAME physical spot as _game's TT(_vrgb) is
 *   actually LEFT (a plain left-arrow, no layer function). And _base's TERM
 *   key lines up with _game's KC_RALT spot instead — a single ordinary key,
 *   not a merged RAlt+TT(_vrgb) combo like I said earlier (that was wrong).
 *   So as far as I can tell from this file alone, _base has NO key that
 *   reaches _vrgb directly, and _base also has no DF(_game)/TG(_game)
 *   anywhere. Either TERM is a custom psycher.h key that secretly handles
 *   entry into _game/_vrgb (tap-dance, hold, etc.), or there's another path
 *   I'm not seeing — worth checking psycher.h for what TERM actually does.
 *
 *   TG() key (Toggle: single tap flips the layer fully on/off, no holding)
 *   ------------------------------------------------------------------------
 *   - TG(_game) -> sits on _vrgb's bottom-ish row (right side).
 *     Tap once from _vrgb to jump straight into _game (fully on, not just
 *     while held). Tap again while in _game (if you find this same key on
 *     that layer) to flip back off.
 *
 *   DF() keys (Default Layer: changes your BASE layer, not just active one —
 *              this is the "permanent until changed again" switch)
 *   ------------------------------------------------------------------------
 *   - DF(_base) -> appears TWICE on _game: the split-rshift key (row4) and
 *     the bottom-right key (row5). Tap either one to make _base your
 *     default layer again (this is how you escape _game layer entirely).
 *
 * TL;DR — quick recovery paths:
 *   Stuck in _game?  -> tap DF(_base) (bottom row, either the split-rshift
 *                       key or the bottom-right corner key).
 *   Stuck in _vrgb?  -> if you got there by holding/double-tapping TERM or
 *                       TT(_vrgb), release or tap the same key again to
 *                       unlock. From _vrgb you can also tap TG(_game) to hop
 *                       into _game (which then has its own DF(_base) exits).
 *   Stuck in _hjkl/_mods? -> these are hold-only from MODS/HJKL keys (Q/W),
 *                       so just release the key and you're back to normal.
 *                       (TT(_hjkl) on _base's split-rshift key is the
 *                       exception — double-tap it again to unlock.)
 *   How do you even get to _game/_vrgb from _base in the first place? ->
 *                       unclear from this file; likely handled by the
 *                       custom TERM key in psycher.h. Worth confirming.
 * ============================================================================
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* [_base] ---------------------------------------------------------------
     * ,-----------------------------------------------------------------------.
     * |GESC|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|MINS| EQL|   BSPC          |
     * |-----------------------------------------------------------------------|
     * |TAB   |MODS|HJKL|  E|  R|  T|  Y|  U|  I|  O|  P|LBRC|RBRC|    BSLS     |
     * |-----------------------------------------------------------------------|
     * |TMUX   |GUIA|ALTS|CTLD|SFTF|  G|  H|SFTJ|CTLK|ALTL|GUIN|QUOT|    ENT    |
     * |-----------------------------------------------------------------------|
     * |SCAP    |  Z|  X|  C|  V|  B|  N|  M|COMM| DOT|SLSH| UP_|  TT(_hjkl)   |
     * |-----------------------------------------------------------------------|
     * |LCTL|LGUI|LALT|          SPC          |TERM|VRGB(TT)|LEFT|DWNN|RGHT    |
     * `-----------------------------------------------------------------------'
     * Notes: MODS/HJKL/TMUX/GUIA/ALTS/CTLD/SFTF/SFTJ/CTLK/ALTL/GUIN/SCAP/TERM/
     *        UP_/DWNN are custom keycodes defined in psycher.h (home-row mods,
     *        tap-dance, tmux leader, etc). TT(_hjkl) on split-rshift key.
     */
    [_base] = LAYOUT_wrapper(LAYOUT_60_ansi_split_rshift, _BASE_ROW1, _BASE_ROW2, _BASE_ROW3, _BASE_ROW4_60_split_rshft, _BASE_ROW5_60),

    /* [_game] ---------------------------------------------------------------
     * ,-----------------------------------------------------------------------.
     * |GESC|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|MINS| EQL|   BSPC          |
     * |-----------------------------------------------------------------------|
     * |TAB   |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|LBRC|RBRC|    BSLS      |
     * |-----------------------------------------------------------------------|
     * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|SCLN|QUOT|    ENT          |
     * |-----------------------------------------------------------------------|
     * |LSFT    |  Z|  X|  C|  V|  B|  N|  M|COMM| DOT|SLSH|RSFT|  DF(_base)   |
     * |-----------------------------------------------------------------------|
     * |LCTL|LGUI|LALT|          SPC          |RALT|TT(_vrgb)|RCTL| DF(_base)  |
     * `-----------------------------------------------------------------------'
     * Notes: plain QWERTY (no home-row mods) for gaming. DF(_base) on both the
     *        split-rshift key and bottom-right key lets you bail back to _base
     *        from either spot. TT(_vrgb) still reachable bottom-right area.
     */
    [_game] = LAYOUT_wrapper(LAYOUT_60_ansi_split_rshift, _GAME_ROW1, _GAME_ROW2, _GAME_ROW3, _GAME_ROW4_60_split_rshft, _GAME_ROW5_60),

    /* [_vrgb] (FN1: F-keys, media & RGB) --------------------------------------
     * ,-----------------------------------------------------------------------.
     * |PWR | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11 | F12|   DEL           |
     * |-----------------------------------------------------------------------|
     * |RGBTOG|xxx|SATU|xxx|xxx|xxx|xxx|xxx|xxx|xxx|MPLY|PREV|NEXT|   QK_BOOT   |
     * |-----------------------------------------------------------------------|
     * |CAPS   |HUED|SATD|HUEU|xxx|xxx|SPDD|VALD|VALU|SPDU|xxx|xxx|   xxx       |
     * |-----------------------------------------------------------------------|
     * |xxx     |xxx|xxx|xxx|xxx|xxx|xxx|MUTE|MPRV|MNXT|TG(_game)|VOLU|MUTE    |
     * |-----------------------------------------------------------------------|
     * |xxx |xxx |xxx |          xxx          |xxx |xxx     |BRID|VOLD|BRIU   |
     * `-----------------------------------------------------------------------'
     * Notes: xxx = _______ (transparent, falls through to _base/_game).
     *        WASD/hjkl area not remapped here — only the labeled RGB/media keys
     *        listed above are active on this layer. Access via TT(_vrgb) held
     *        or double-tapped from _base/_game.
     */
    [_vrgb] = LAYOUT_wrapper(LAYOUT_60_ansi_split_rshift, _VRGB_ROW1, _VRGB_ROW2, _VRGB_ROW3, _VRGB_ROW4_60_split_rshft, _VRGB_ROW5_60),

    /* [_hjkl] (FN2: arrow-cluster on hold-W) -----------------------------------
     * ,-----------------------------------------------------------------------.
     * |xxx |xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx |xxx |   xxx           |
     * |-----------------------------------------------------------------------|
     * |xxx   |xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|    xxx         |
     * |-----------------------------------------------------------------------|
     * |xxx    |xxx|xxx|xxx|xxx|xxx|LEFT|DOWN|UP|RIGHT|PASS_MACRO|xxx|  xxx    |
     * |-----------------------------------------------------------------------|
     * |xxx     |xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|      xxx        |
     * |-----------------------------------------------------------------------|
     * |xxx |xxx |xxx |          xxx          |xxx |xxx     |xxx |xxx |xxx    |
     * `-----------------------------------------------------------------------'
     * Notes: xxx = _______. Only the home-row-ish HJKL cluster (mapped to
     *        LEFT/DOWN/UP/RIGHT) and ; (PASS_MACRO) are live. TODO in file
     *        flags this as not ideal — meant to be a typing aux layer on
     *        holding W only, currently reached via FN2 more broadly.
     */
    [_hjkl] = LAYOUT_wrapper(LAYOUT_60_ansi_split_rshift, _HJKL_ROW1, _HJKL_ROW2, _HJKL_ROW3, _HJKL_ROW4_60_split_rshft, _HJKL_ROW5),

    /* [_mods] (FN: hold-Q editing keys) ----------------------------------------
     * ,-----------------------------------------------------------------------.
     * |xxx |xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx |xxx |   xxx           |
     * |-----------------------------------------------------------------------|
     * |xxx   |xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|    xxx         |
     * |-----------------------------------------------------------------------|
     * |xxx    |xxx|xxx|xxx|xxx|xxx|BSPC|END|HOME|DEL|ENT|xxx|  xxx            |
     * |-----------------------------------------------------------------------|
     * |xxx     |xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|xxx|      xxx        |
     * |-----------------------------------------------------------------------|
     * |xxx |xxx |xxx |          xxx          |xxx |xxx     |xxx |xxx |xxx    |
     * `-----------------------------------------------------------------------'
     * Notes: xxx = _______. Only HJKL; row remapped to BSPC/END/HOME/DEL/ENT —
     *        an editing cluster accessed by holding Q.
     */
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
