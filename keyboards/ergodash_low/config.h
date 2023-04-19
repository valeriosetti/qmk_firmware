/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

#define MATRIX_ROW_PINS { B5, B4, E6, D7, D4 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2 }

#define DIODE_DIRECTION COL2ROW

#define TAPPING_TERM 120
#define DEBOUNCE 5

#define USE_I2C

#define MASTER_LEFT

#define SPLIT_USB_DETECT

// Enable kinetic mode for mouse emulation (instead of accelerated mode)
#define MOUSEKEY_MAX_SPEED 5

// save some code size
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT
