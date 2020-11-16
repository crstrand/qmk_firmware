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
  _FN,
  _FN_ARROW,
  _FN_ALL
};

// custom keycode section
enum rk61_keycodes {
    // Function codes
    RK61_FN = SAFE_RANGE
};

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
    if (keycode == RK61_FN) {
        if (record->event.pressed)
            // set layer _FN_ALL
            layer_on(_FN_ALL);
        else
            layer_off(_FN_ALL);
    }
    return true;
}

// Tap Dance declarations
enum {
    TD_GUI_ON,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Left GUI, twice for GUI key ON (in case you turned it off on any of the other layers)
    [TD_GUI_ON] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, GUI_ON),
};

enum combos {
  RS_L1,
  LC_L2
};

// Combo section
const uint16_t PROGMEM rs_combo[] = {KC_RSFT, RK61_FN, COMBO_END};
const uint16_t PROGMEM lc_combo[] = {KC_LCTL, RK61_FN, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  //[RS_L1] = COMBO(rs_combo, MAGIC_KEY_LAYER1),
  //[LC_L2] = COMBO(lc_combo, MAGIC_KEY_LAYER2)
  [RS_L1] = COMBO_ACTION(rs_combo),
  [LC_L2] = COMBO_ACTION(lc_combo)
};
void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case RS_L1:
      if (pressed) {
        layer_invert(_ARROWS);
      }
      break;
    case LC_L2:
      if (pressed) {
        layer_invert(_FN);
      }
      break;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base */
  [_BASE] = LAYOUT_60_ansi(
    KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
    KC_LCTL, TD(TD_GUI_ON), KC_LALT,                            KC_SPC,                             KC_RALT, KC_MENU, KC_RCTL, RK61_FN //TG(_FN)
  ),
  [_ARROWS] = LAYOUT_60_ansi(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP  ,          _______,
    _______, _______, _______,                            _______,                            KC_LEFT, KC_DOWN, KC_RGHT, _______
  ),
  [_FN] = LAYOUT_60_ansi(
    KC_GRV , KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______,                            _______,                            _______, _______, _______, _______
  ),
  [_FN_ARROW] = LAYOUT_60_ansi(
    KC_GRV , KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP  ,          _______,
    _______, _______, _______,                            _______,                            KC_LEFT, KC_DOWN, KC_RGHT, _______
  ),
  [_FN_ALL] = LAYOUT_60_ansi(
    KC_GRV , KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,KC_DEL,
    _______, KC_P1   ,KC_P2   ,KC_P3   ,_______ ,_______ ,KC_PSCR ,KC_SLCK ,KC_PAUS ,_______ ,_______ ,_______ ,_______ ,_______,
    _______, KC_P4   ,KC_P5   ,KC_P6   ,_______ ,_______ ,KC_INS  ,KC_HOME ,KC_PGUP ,_______ ,_______ ,_______ ,         _______ ,
    _______,          KC_P7   ,KC_P8   ,KC_P9   ,_______ ,_______ ,KC_DEL  ,KC_END  ,KC_PGDN ,_______ ,KC_UP   ,         _______ ,
    _______, GUI_OFF ,KC_P0                              ,_______                            ,KC_LEFT ,KC_DOWN ,KC_RGHT ,_______
  )

};

