/*
Copyright 2020 gtips

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xDEAD
#define PRODUCT_ID 0xBEEF
#define DEVICE_VER 0x0001
#define MANUFACTURER royal_kludge
#define PRODUCT rk61
#define DESCRIPTION A 61-key keyboard

/* this will probably turn on the whole row when caps lock is active */
//#define LED_CAPS_LOCK_PIN F4

#define TAPPING_TERM 200
#define COMBO_COUNT 2

/* key combination for command */
#define IS_COMMAND() ( \
    get_mods() == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_LGUI)) \
)
/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { D7, E6, B4, B5, D5 }
// Arduino Pro Micro       6,  7,  8,  9, 22(TXLED)
#define MATRIX_COL_PINS { F5, F6, F7, B1, B3, B2, B6, B0, C6, D4, D0, D1, D2, D3}
// Arduino Pro Micro      20, 19, 18, 15, 14, 16, 10,  8,  5,  4,  3,  2,  0,  1  (RXLED=8=C6)

#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
