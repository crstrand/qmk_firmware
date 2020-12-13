#include QMK_KEYBOARD_H
enum layer_names {
    _NP,
    _BL
};

void matrix_init_user() {
  backlight_level(BACKLIGHT_LEVELS);
  backlight_enable();
}
bool fn1_on = false;
bool fn2_on = false;

// Try the command key thing to change layers first
bool process_record_user (uint16_t keycode, keyrecord_t *record) {
    // return true to send the keycode to the Keyboard/Revision (_kb) level
    // return false and the keycode stops here
    // NOTICE: make sure you DO NOT use keys k00 and k30 in the _BL layer
    if(record->event.key.row==0 && record->event.key.col==0)
    {
        fn1_on = record->event.pressed;
    }
    if(record->event.key.row==3 && record->event.key.col==0)
    {
        fn2_on = record->event.pressed;
    }
    // toggle function row or arrows layers
    if (fn1_on && fn2_on)
    {
        layer_on(_BL);
        return (record->event.key.col>0); // continue to process keys that are not in column 0, else stop it here
    }
    else
    {
        layer_off(_BL);
    }
    return true;
}

// LAYOUT with USB on left
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NP] = LAYOUT_ortho_4x6L(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
        KC_LCTL, KC_1,    KC_2,    KC_3,    KC_SPC,  KC_SPC
    ),
    [_BL] = LAYOUT_ortho_4x6L(
        _______, _______, _______, _______, BL_ON  , BL_INC,
        _______, _______, _______, _______, BL_OFF , BL_DEC,
        _______, _______, _______, _______, _______, BL_BRTG,
        _______, _______, _______, _______, BL_TOGG, BL_TOGG
    )
};
