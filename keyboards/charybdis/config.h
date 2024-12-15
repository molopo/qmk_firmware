/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#pragma once

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 10

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
//#define MATRIX_ROW_PINS_RIGHT { D4, C6, D7, E6 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1 }
#define MATRIX_COL_PINS_RIGHT { B4, B5, F6, F4, F5 }

#define MATRIX_ROW_PINS { D4, C6, D7, E6 }
#define MATRIX_ROW_PINS_RIGHT { D4, C6, D7, E6 }


#define UNUSED_PINS

// /* COL2ROW, ROW2COL*/
// #define DIODE_DIRECTION ROW2COL

// /*
//  * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
//  */
// #define SOFT_SERIAL_PIN D2  // or D1, D2, D3, E6

#define MASTER_LEFT
#define SPLIT_USB_DETECT
/* Pointing device configuration. */


// Enable use of pointing device on slave split.
#define SPLIT_POINTING_ENABLE

// Pointing device is on the right split.
#define POINTING_DEVICE_RIGHT

// Limits the frequency that the sensor is polled for motion.
#define POINTING_DEVICE_TASK_THROTTLE_MS 1

// Invert X axis on mouse reports.
#define POINTING_DEVICE_INVERT_X

#define PMW33XX_CS_PIN F7
# define PMW3360_CPI 400
// /* RGB matrix support. */
// #ifdef RGB_MATRIX_ENABLE
// #    ifndef __arm__
// // Disable control of RGB matrix by keycodes (must use firmware implementation
// // to control the feature).
// #        define RGB_MATRIX_DISABLE_KEYCODES
// #    else // __arm__
// // Enable all animations on ARM boards since they have plenty of memory
// // available for it.
// #        define ENABLE_RGB_MATRIX_ALPHAS_MODS
// #        define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
// #        define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
// #        define ENABLE_RGB_MATRIX_BREATHING
// #        define ENABLE_RGB_MATRIX_BAND_SAT
// #        define ENABLE_RGB_MATRIX_BAND_VAL
// #        define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
// #        define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
// #        define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
// #        define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
// #        define ENABLE_RGB_MATRIX_CYCLE_ALL
// #        define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
// #        define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
// #        define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
// #        define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
// #        define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
// #        define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
// #        define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
// #        define ENABLE_RGB_MATRIX_DUAL_BEACON
// #        define ENABLE_RGB_MATRIX_RAINBOW_BEACON
// #        define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
// #        define ENABLE_RGB_MATRIX_RAINDROPS
// #        define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
// #        define ENABLE_RGB_MATRIX_HUE_BREATHING
// #        define ENABLE_RGB_MATRIX_HUE_PENDULUM
// #        define ENABLE_RGB_MATRIX_HUE_WAVE
// #        define ENABLE_RGB_MATRIX_TYPING_HEATMAP
// #        define ENABLE_RGB_MATRIX_DIGITAL_RAIN
// #        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
// #        define ENABLE_RGB_MATRIX_SOLID_REACTIVE
// #        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
// #        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
// #        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
// #        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
// #        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
// #        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
// #        define ENABLE_RGB_MATRIX_SPLASH
// #        define ENABLE_RGB_MATRIX_MULTISPLASH
// #        define ENABLE_RGB_MATRIX_SOLID_SPLASH
// #        define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
// #    endif // !__arm__
// #endif

#ifdef VIA_ENABLE
/* VIA configuration. */
#    define DYNAMIC_KEYMAP_LAYER_COUNT 7
#endif // VIA_ENABLE

/* Disable unused features. */
#define NO_ACTION_ONESHOT

/* Charybdis-specific features. */

#ifdef POINTING_DEVICE_ENABLE
// Automatically enable the pointer layer when moving the trackball.  See also:
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS`
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD`
// #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif // POINTING_DEVICE_ENABLE