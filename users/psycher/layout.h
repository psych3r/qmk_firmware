/* TODO
   [] remove all DF(_base) and DF(_game) and replace with TG(_game)
   [] HJKL layer as FN2 is not ideal, should be a typing auxilary layer on kc_w only!
   [] Numpad layer?
*/

// wrapper to force macro expansion inside layout macros. usage:
// [_base] = LAYOUT_wrapper(  LAYOUT_60_ansi, _BASE_ROW1, ...
#define LAYOUT_wrapper(layout, ...) layout(__VA_ARGS__)

// ============================================================================
// LAYER: _base
// ============================================================================

#define _BASE_ROW1 QK_GESC, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC
#define _BASE_ROW2 KC_TAB,  MODS,    HJKL,    KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS
#define _BASE_ROW3 TMUX,    GUIA,    ALTS,    CTLD,   SFTF,   KC_G,   KC_H,   SFTJ,    CTLK,    ALTL,    GUIN,    KC_QUOT, KC_ENT
#define _BASE_ROW4 SCAP,    KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH
#define _BASE_ROW5 KC_LCTL, KC_LGUI, KC_LALT,                         KC_SPC,                            TERM

#define _BASE_ROW1_65      _BASE_ROW1, KC_DEL
#define _BASE_ROW2_65      _BASE_ROW2, KC_HOME
#define _BASE_ROW3_65      _BASE_ROW3, KC_END
#define _BASE_ROW4_65      _BASE_ROW4, KC_RSFT,   KC_UP,   TT(_hjkl)
#define _BASE_ROW5_65_3mod _BASE_ROW5, TT(_vrgb), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
#define _BASE_ROW5_65_2mod _BASE_ROW5, TT(_vrgb),          KC_LEFT, KC_DOWN, KC_RGHT

#define _BASE_ROW4_60             _BASE_ROW4, UP__
#define _BASE_ROW4_60_split_rshft _BASE_ROW4, UP__, TT(_hjkl)
#define _BASE_ROW5_60             _BASE_ROW5, LEFT, DWNN, RGHT

// ============================================================================
// LAYER: _game
// ============================================================================

#define _GAME_ROW1 _BASE_ROW1
#define _GAME_ROW2 KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS
#define _GAME_ROW3 KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT
#define _GAME_ROW4 KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT
#define _GAME_ROW5 KC_LCTL, KC_LGUI, KC_LALT,                              KC_SPC,                             KC_RALT, TT(_vrgb)

#define _GAME_ROW1_65      _GAME_ROW1, KC_DEL
#define _GAME_ROW2_65      _GAME_ROW2, KC_HOME
#define _GAME_ROW3_65      _GAME_ROW3, KC_END
#define _GAME_ROW4_65      _GAME_ROW4, KC_UP,   DF(_base)
#define _GAME_ROW5_65_3mod _GAME_ROW5, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
#define _GAME_ROW5_65_2mod _GAME_ROW5,          KC_LEFT, KC_DOWN, KC_RGHT

#define _GAME_ROW4_60_split_rshft _GAME_ROW4, DF(_base)
#define _GAME_ROW5_60             _GAME_ROW5, KC_RCTL, DF(_base)

// ============================================================================
// LAYER: _vrgb
// ============================================================================

/* potential rename layer -> FN1: F-keys, media & RGB
    Access    -> Second button after SPACE.
                 60: On-Hold                      (LT(_vrgb, KC_LEFT) where LT is like MO)
                 65: On-Hold + double-tap toggle  (TT)
    ESC       -> Power OFF
    TAB       -> Toggle RGB matrix
    WASD      -> WS: Saturation, AD: Hue
    [,]       -> Prev, Next RGB animation
    HJKL      -> JK: RGB Brightness, HL: RGB Speed
    backslash -> QK_BOOT
    ARROWS    -> up/down: volume control, left/right: monitor brightness control
    P         -> play/pause media
    <,>       -> next/prev media track
    M         -> Volume mute
    /         -> Game mode TG(_game)
*/

#define _VRGB_ROW1  KC_PWR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL
#define _VRGB_ROW2  RM_TOGG, _______, RM_SATU, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, RM_PREV, RM_NEXT, QK_BOOT
#define _VRGB_ROW3  KC_CAPS, RM_HUED, RM_SATD, RM_HUEU, _______, _______, RM_SPDD, RM_VALD, RM_VALU, RM_SPDU, _______, _______, _______
#define _VRGB_ROW4  _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_MPRV, KC_MNXT, TG(_game)
#define _VRGB_ROW5  _______, _______, _______,                            _______,                            _______

#define _VRGB_LDR  KC_BRID, KC_VOLD, KC_BRIU

#define _VRGB_ROW1_65      _VRGB_ROW1, _______
#define _VRGB_ROW2_65      _VRGB_ROW2, KC_PGUP
#define _VRGB_ROW3_65      _VRGB_ROW3, KC_PGDN
#define _VRGB_ROW4_65      _VRGB_ROW4, _______, KC_VOLU, KC_MUTE
#define _VRGB_ROW5_65_2mod _VRGB_ROW5, _______, _VRGB_LDR
#define _VRGB_ROW5_65_3mod _VRGB_ROW5, _______, _______, _VRGB_LDR

#define _VRGB_ROW4_60              _VRGB_ROW4, KC_VOLU
#define _VRGB_ROW4_60_split_rshft  _VRGB_ROW4, KC_VOLU, KC_MUTE
#define _VRGB_ROW5_60              _VRGB_ROW5, _VRGB_LDR

// ============================================================================
// LAYER: _hjkl
// ============================================================================

/* for some reason FN2 button goes here, I don't like that!
   Access -> Hold KC_W
   ASDF   -> L,R,U,D
   HJKL   -> Arrow keys L,D,U,R
   ;      -> Macros PASS_MACRO)
*/

#define _HJKL_ROW1  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
#define _HJKL_ROW2  _HJKL_ROW1
#define _HJKL_ROW3  _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RIGHT, PASS_MACRO, _______, _______
#define _HJKL_ROW4  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
#define _HJKL_ROW5  _______, _______, _______,                            _______,                             _______, _______, _______, _______

#define _HJKL_ROW1_65      _HJKL_ROW1, _______
#define _HJKL_ROW2_65      _HJKL_ROW2, _______
#define _HJKL_ROW3_65      _HJKL_ROW3, _______
#define _HJKL_ROW4_65      _HJKL_ROW1
#define _HJKL_ROW5_65_2mod _HJKL_ROW5, _______
#define _HJKL_ROW5_65_3mod _HJKL_ROW5, _______, _______

#define _HJKL_ROW4_60_split_rshft _HJKL_ROW4, _______

// ============================================================================
// LAYER: _mods
// ============================================================================

/* Access -> Hold KC_Q
   HJKL   -> Backspace, End, Home, Delete
   ;      -> Enter
*/

#define _MODS_ROW1  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
#define _MODS_ROW2  _MODS_ROW1
#define _MODS_ROW3  _______, _______, _______, _______, _______, _______, KC_BSPC,  KC_END, KC_HOME, KC_DEL,  KC_ENT,  _______, _______
#define _MODS_ROW4  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
#define _MODS_ROW5  _______, _______, _______,                            _______,                            _______, _______, _______, _______

#define _MODS_ROW1_65      _MODS_ROW1, _______
#define _MODS_ROW2_65      _MODS_ROW2, _______
#define _MODS_ROW3_65      _MODS_ROW3, _______
#define _MODS_ROW4_65      _MODS_ROW1
#define _MODS_ROW5_65_2mod _MODS_ROW5, _______
#define _MODS_ROW5_65_3mod _MODS_ROW5, _______, _______

#define _MODS_ROW4_60_split_rshft _MODS_ROW4, _______
