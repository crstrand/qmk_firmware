/*
Copyright 2020 Cam Strandlund

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
/* NOTE: Despite what may be shown at
   https://beta.docs.qmk.fm/using-qmk/hardware-features/custom_matrix
   about CUSTOM_MATRIX = lite, you need to include ALL the functions
   from quantum/matrix.c in your custom matrix.c to get CUSTOM_MATRIX = lite to work
*/
#include <stdint.h>
#include <stdbool.h>
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

/* matrix state(1:on, 0:off) */
extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values

// matrix code

static void select_row(uint8_t row) {
    setPinOutput(row_pins[row]);
    writePinLow(row_pins[row]);
}

static void unselect_row(uint8_t row) { setPinInputHigh(row_pins[row]); }

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh(row_pins[x]);
    }
}

static void init_pins(void) {
    unselect_rows();
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputHigh(col_pins[x]);
    }
    setPinOutput(RK61_BACKLIGHT);
    writePinLow(RK61_BACKLIGHT);
}

static void select_col(uint8_t col) {
    setPinOutput(col_pins[col]);
    writePinLow(col_pins[col]);
}

static void unselect_col(uint8_t col) { setPinInputHigh(col_pins[col]); }

void led_update(int col_index, uint8_t current_row)
{
    int min_col;
    bool caps_lock  = IS_HOST_LED_ON(USB_LED_CAPS_LOCK);
    int is_bl = is_backlight_enabled();
    if(current_row==2)
    {
        if(is_bl)
        { // backlight is on so make sure all columns are lit (except CAPS lock)
            writePinHigh(RK61_BACKLIGHT); // output for LED row 2
            if(caps_lock)
                min_col = 0;
            else
                min_col = 1;
            // set LED column low (on) for one loop
            if(col_index>=min_col) select_col(col_index); // set column to output low to turn on LED if ROWLED line is low
        }
        else // backlight off so only turn on CAPS lock if needed
        {
            if(caps_lock && col_index==0)
            {
                writePinHigh(RK61_BACKLIGHT); // output for LED row 2
                select_col(col_index); // set column to output low to turn on CAPS LED if ROWLED line is low
            }
        }
    }
    else writePinLow(RK61_BACKLIGHT); // Turn off LED row

    unselect_col((col_index>0?col_index-1:MATRIX_COLS-1)); // set previous column back to input pullup.

    // After the column loop, something else happens that causes the last column to remain lit for longer than the rest
    //   this causes it to look brighter than the other keys.
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;
    // Select row and wait for row selecton to stabilize
    select_row(current_row);
    matrix_io_delay();

    // For each col...
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        // Select the col pin to read (active low)
        uint8_t pin_state = readPin(col_pins[col_index]);
        led_update(col_index,current_row);
        // Populate the matrix row with the state of the col pin
        current_row_value |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    // Unselect row
    unselect_row(current_row);

    // If the row has changed, store the row and return the changed flag.
    if (current_matrix[current_row] != current_row_value) {
        current_matrix[current_row] = current_row_value;
        return true;
    }
    return false;
}

void matrix_init_custom(void) {
    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(MATRIX_ROWS);

    matrix_init_quantum();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(current_matrix, current_row);
    }
    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    matrix_scan_quantum();
    return (uint8_t)changed;
}
