/* Copyright 2020 gtips
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _BASE,
  _ARROWS,
  _FN_ROW,
  _SPECIAL
};

// custom keycode section
enum rk61_keycodes {
    // Function codes
    RK61_FN = SAFE_RANGE
};

bool fn_on = false;
bool fn_row;
bool ar_row;

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
    // return true to send the keycode to the Keyboard/Revision (_kb) level
    // return false and the keycode stops here
    // If console is enabled, it will print the matrix position and status of each key pressed
    #ifdef CONSOLE_ENABLE
        uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    #endif
    if (keycode == RK61_FN) {
        if (record->event.pressed)
        {
            fn_on = true;
            // record current state of function row and arrows layers
            fn_row = layer_state_is(_FN_ROW);
            ar_row = layer_state_is(_ARROWS);
            if (fn_row)
                layer_off(_FN_ROW);
            else
                layer_on(_FN_ROW);

            if (ar_row)
                layer_off(_ARROWS);
            else
                layer_on(_ARROWS);
            layer_on(_SPECIAL);
        }
        else // Fn key is released. Restore the states recorded on key down
        {
            fn_on = false;
            if (fn_row)
                layer_on(_FN_ROW);
            else
                layer_off(_FN_ROW);

            if (ar_row)
                layer_on(_ARROWS);
            else
                layer_off(_ARROWS);
            layer_off(_SPECIAL);
        }
        return false;
    }
    // toggle function row or arrows layers
    if (record->event.pressed)
    {
        if(fn_on && keycode == KC_LCTL)
        {
            // invert the state that existed when we started pressing the Fn key
            if (fn_row)
                layer_off(_FN_ROW);
            else
                layer_on(_FN_ROW);
            // update the state so releasing the Fn key doesn't undo our change
            fn_row = layer_state_is(_FN_ROW);
            return false;
        }
        if(fn_on && keycode == KC_RSFT)
        {
            // invert the state that existed when we started pressing the Fn key
            if (ar_row)
                layer_off(_ARROWS);
            else
                layer_on(_ARROWS);
            // update the state so releasing the Fn key doesn't undo our change
            ar_row = layer_state_is(_ARROWS);
            return false;
        }
        if(fn_on && keycode == KC_LGUI)
        {
            keymap_config.no_gui = !keymap_config.no_gui;
            return false;
        }
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base */
  [_BASE] = LAYOUT_60_ansi(
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_CALC, KC_RCTL, RK61_FN
  ),
  [_ARROWS] = LAYOUT_60_ansi(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP  ,          _______,
    _______, _______, _______,                            _______,                            KC_LEFT, KC_DOWN, KC_RGHT, _______
  ),
  [_FN_ROW] = LAYOUT_60_ansi(
    _______ , KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12 ,_______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______,                            _______,                            _______, _______, _______, _______
  ),
  [_SPECIAL] = LAYOUT_60_ansi(
    KC_GRV , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
    _______, KC_P1   ,KC_P2   ,KC_P3   ,_______ ,_______ ,KC_PSCR ,KC_SLCK ,KC_PAUS ,_______ ,_______ ,_______ ,_______ ,BL_TOGG,
    _______, KC_P4   ,KC_P5   ,KC_P6   ,_______ ,_______ ,KC_INS  ,KC_HOME ,KC_PGUP ,_______ ,_______ ,_______ ,         _______ ,
    _______,          KC_P7   ,KC_P8   ,KC_P9   ,_______ ,_______ ,KC_DEL  ,KC_END  ,KC_PGDN ,_______ ,_______ ,         _______ ,
    _______, _______ ,KC_P0                              ,_______                            ,_______ ,_______ ,_______ ,_______
  )

};

