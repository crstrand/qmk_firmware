#include QMK_KEYBOARD_H

enum layer_names {
    _NP,
    _BL
};

/*
    [_NP] = LAYOUT_ortho_4x6(
        KC_I,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_K,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_UP,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
        KC_DOWN, KC_1,    KC_2,    KC_3,    KC_0,    KC_0
    ),
*/
// LAYOUT with USB on left
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NP] = LAYOUT_ortho_4x6(
        KC_0,    KC_0,    KC_3,    KC_2,    KC_1,    KC_DOWN,
        KC_B,    KC_V,    KC_C,    KC_X,    KC_Z,    KC_UP,
        KC_G,    KC_F,    KC_D,    KC_S,    KC_A,    KC_RGHT,
        KC_T,    KC_R,    KC_E,    KC_W,    KC_Q,    KC_ESC
    ),


    [_BL] = LAYOUT_ortho_4x6(
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______
    )
};
