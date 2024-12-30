/*
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Publicw License as published by
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

#include "ximi.h"
#include "transactions.h"
#include <string.h>


#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif // CONSOLE_ENABLE

#ifdef POINTING_DEVICE_ENABLE
#    ifndef XIMI_MINIMUM_DEFAULT_DPI
#        define XIMI_MINIMUM_DEFAULT_DPI 400
#    endif // XIMI_MINIMUM_DEFAULT_DPI

#    ifndef XIMI_DEFAULT_DPI_CONFIG_STEP
#        define XIMI_DEFAULT_DPI_CONFIG_STEP 200
#    endif // XIMI_DEFAULT_DPI_CONFIG_STEP

#    ifndef XIMI_MINIMUM_SNIPING_DPI
#        define XIMI_MINIMUM_SNIPING_DPI 200
#    endif // XIMI_MINIMUM_SNIPER_MODE_DPI

#    ifndef XIMI_SNIPING_DPI_CONFIG_STEP
#        define XIMI_SNIPING_DPI_CONFIG_STEP 100
#    endif // XIMI_SNIPING_DPI_CONFIG_STEP

// Fixed DPI for drag-scroll.
#    ifndef XIMI_DRAGSCROLL_DPI
#        define XIMI_DRAGSCROLL_DPI 100
#    endif // XIMI_DRAGSCROLL_DPI

#    ifndef XIMI_DRAGSCROLL_BUFFER_SIZE
#        define XIMI_DRAGSCROLL_BUFFER_SIZE 6
#    endif // !XIMI_DRAGSCROLL_BUFFER_SIZE

typedef union {
    uint8_t raw;
    struct {
        uint8_t pointer_default_dpi : 4; // 16 steps available.
        uint8_t pointer_sniping_dpi : 2; // 4 steps available.
        bool    is_dragscroll_enabled : 1;
        bool    is_sniping_enabled : 1;
    } __attribute__((packed));
} ximi_config_t;

static ximi_config_t g_ximi_config = {0};

/**
 * \brief Set the value of `config` from EEPROM.
 *
 * Note that `is_dragscroll_enabled` and `is_sniping_enabled` are purposefully
 * ignored since we do not want to persist this state to memory.  In practice,
 * this state is always written to maximize write-performances.  Therefore, we
 * explicitly set them to `false` in this function.
 */
static void read_ximi_config_from_eeprom(ximi_config_t* config) {
    config->raw                   = eeconfig_read_kb() & 0xff;
    config->is_dragscroll_enabled = false;
    config->is_sniping_enabled    = false;
}

/**
 * \brief Save the value of `config` to eeprom.
 *
 * Note that all values are written verbatim, including whether drag-scroll
 * and/or sniper mode are enabled.  `read_ximi_config_from_eeprom(…)`
 * resets these 2 values to `false` since it does not make sense to persist
 * these across reboots of the board.
 */
static void write_ximi_config_to_eeprom(ximi_config_t* config) {
    eeconfig_update_kb(config->raw);
}

/** \brief Return the current value of the pointer's default DPI. */
static uint16_t get_pointer_default_dpi(ximi_config_t* config) {
    return (uint16_t)config->pointer_default_dpi * XIMI_DEFAULT_DPI_CONFIG_STEP + XIMI_MINIMUM_DEFAULT_DPI;
}

/** \brief Return the current value of the pointer's sniper-mode DPI. */
static uint16_t get_pointer_sniping_dpi(ximi_config_t* config) {
    return (uint16_t)config->pointer_sniping_dpi * XIMI_SNIPING_DPI_CONFIG_STEP + XIMI_MINIMUM_SNIPING_DPI;
}

/** \brief Set the appropriate DPI for the input config. */
static void maybe_update_pointing_device_cpi(ximi_config_t* config) {
    if (config->is_dragscroll_enabled) {
        pointing_device_set_cpi(XIMI_DRAGSCROLL_DPI);
    } else if (config->is_sniping_enabled) {
        pointing_device_set_cpi(get_pointer_sniping_dpi(config));
    } else {
        pointing_device_set_cpi(get_pointer_default_dpi(config));
    }
}

/**
 * \brief Update the pointer's default DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to XIMI_DEFAULT_DPI_CONFIG_STEP.
 */
static void step_pointer_default_dpi(ximi_config_t* config, bool forward) {
    config->pointer_default_dpi += forward ? 1 : -1;
    maybe_update_pointing_device_cpi(config);
}

/**
 * \brief Update the pointer's sniper-mode DPI to the next or previous step.
 *
 * Increases the DPI value if `forward` is `true`, decreases it otherwise.
 * The increment/decrement steps are equal to XIMI_SNIPING_DPI_CONFIG_STEP.
 */
static void step_pointer_sniping_dpi(ximi_config_t* config, bool forward) {
    config->pointer_sniping_dpi += forward ? 1 : -1;
    maybe_update_pointing_device_cpi(config);
}

uint16_t ximi_get_pointer_default_dpi(void) {
    return get_pointer_default_dpi(&g_ximi_config);
}

uint16_t ximi_get_pointer_sniping_dpi(void) {
    return get_pointer_sniping_dpi(&g_ximi_config);
}

void ximi_cycle_pointer_default_dpi_noeeprom(bool forward) {
    step_pointer_default_dpi(&g_ximi_config, forward);
}

void ximi_cycle_pointer_default_dpi(bool forward) {
    step_pointer_default_dpi(&g_ximi_config, forward);
    write_ximi_config_to_eeprom(&g_ximi_config);
}

void ximi_cycle_pointer_sniping_dpi_noeeprom(bool forward) {
    step_pointer_sniping_dpi(&g_ximi_config, forward);
}

void ximi_cycle_pointer_sniping_dpi(bool forward) {
    step_pointer_sniping_dpi(&g_ximi_config, forward);
    write_ximi_config_to_eeprom(&g_ximi_config);
}

bool ximi_get_pointer_sniping_enabled(void) {
    return g_ximi_config.is_sniping_enabled;
}

void ximi_set_pointer_sniping_enabled(bool enable) {
    g_ximi_config.is_sniping_enabled = enable;
    maybe_update_pointing_device_cpi(&g_ximi_config);
}

bool ximi_get_pointer_dragscroll_enabled(void) {
    return g_ximi_config.is_dragscroll_enabled;
}

void ximi_set_pointer_dragscroll_enabled(bool enable) {
    g_ximi_config.is_dragscroll_enabled = enable;
    maybe_update_pointing_device_cpi(&g_ximi_config);
}

/**
 * \brief Augment the pointing device behavior.
 *
 * Implement drag-scroll.
 */
static void pointing_device_task_ximi(report_mouse_t* mouse_report) {
    static int16_t scroll_buffer_x = 0;
    static int16_t scroll_buffer_y = 0;
    if (g_ximi_config.is_dragscroll_enabled) {
#    ifdef XIMI_DRAGSCROLL_REVERSE_X
        scroll_buffer_x -= mouse_report->x;
#    else
        scroll_buffer_x += mouse_report->x;
#    endif // XIMI_DRAGSCROLL_REVERSE_X
#    ifdef XIMI_DRAGSCROLL_REVERSE_Y
        scroll_buffer_y -= mouse_report->y;
#    else
        scroll_buffer_y += mouse_report->y;
#    endif // XIMI_DRAGSCROLL_REVERSE_Y
        mouse_report->x = 0;
        mouse_report->y = 0;
        if (abs(scroll_buffer_x) > XIMI_DRAGSCROLL_BUFFER_SIZE) {
            mouse_report->h = scroll_buffer_x > 0 ? 1 : -1;
            scroll_buffer_x = 0;
        }
        if (abs(scroll_buffer_y) > XIMI_DRAGSCROLL_BUFFER_SIZE) {
            mouse_report->v = scroll_buffer_y > 0 ? 1 : -1;
            scroll_buffer_y = 0;
        }
    }
}



report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    if (is_keyboard_master()) {
        pointing_device_task_ximi(&mouse_report);
        mouse_report = pointing_device_task_user(mouse_report);
    }
    return mouse_report;
}

#    if defined(POINTING_DEVICE_ENABLE) && !defined(NO_XIMI_KEYCODES)
/** \brief Whether SHIFT mod is enabled. */
static bool has_shift_mod(void) {
#        ifdef NO_ACTION_ONESHOT
    return mod_config(get_mods()) & MOD_MASK_SHIFT;
#        else
    return mod_config(get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;
#        endif // NO_ACTION_ONESHOT
}
#    endif // POINTING_DEVICE_ENABLE && !NO_XIMI_KEYCODES

/**
 * \brief Outputs the Ximi configuration to console.
 *
 * Prints the in-memory configuration structure to console, for debugging.
 * Includes:
 *   - raw value
 *   - drag-scroll: on/off
 *   - sniping: on/off
 *   - default DPI: internal table index/actual DPI
 *   - sniping DPI: internal table index/actual DPI
 */
static void debug_ximi_config_to_console(ximi_config_t* config) {
#    ifdef CONSOLE_ENABLE
    dprintf("(ximi) process_record_kb: config = {\n"
            "\traw = 0x%X,\n"
            "\t{\n"
            "\t\tis_dragscroll_enabled=%u\n"
            "\t\tis_sniping_enabled=%u\n"
            "\t\tdefault_dpi=0x%X (%u)\n"
            "\t\tsniping_dpi=0x%X (%u)\n"
            "\t}\n"
            "}\n",
            config->raw, config->is_dragscroll_enabled, config->is_sniping_enabled, config->pointer_default_dpi, get_pointer_default_dpi(config), config->pointer_sniping_dpi, get_pointer_sniping_dpi(config));
#    endif // CONSOLE_ENABLE
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) {
        debug_ximi_config_to_console(&g_ximi_config);
        return false;
    }
#    ifdef POINTING_DEVICE_ENABLE
#        ifndef NO_XIMI_KEYCODES
    switch (keycode) {
        case POINTER_DEFAULT_DPI_FORWARD:
            if (record->event.pressed) {
                // Step backward if shifted, forward otherwise.
                ximi_cycle_pointer_default_dpi(/* forward= */ !has_shift_mod());
            }
            break;
        case POINTER_DEFAULT_DPI_REVERSE:
            if (record->event.pressed) {
                // Step forward if shifted, backward otherwise.
                ximi_cycle_pointer_default_dpi(/* forward= */ has_shift_mod());
            }
            break;
        case POINTER_SNIPING_DPI_FORWARD:
            if (record->event.pressed) {
                // Step backward if shifted, forward otherwise.
                ximi_cycle_pointer_sniping_dpi(/* forward= */ !has_shift_mod());
            }
            break;
        case POINTER_SNIPING_DPI_REVERSE:
            if (record->event.pressed) {
                // Step forward if shifted, backward otherwise.
                ximi_cycle_pointer_sniping_dpi(/* forward= */ has_shift_mod());
            }
            break;
        case SNIPING_MODE:
            ximi_set_pointer_sniping_enabled(record->event.pressed);
            break;
        case SNIPING_MODE_TOGGLE:
            if (record->event.pressed) {
                ximi_set_pointer_sniping_enabled(!ximi_get_pointer_sniping_enabled());
            }
            break;
        case DRAGSCROLL_MODE:
            ximi_set_pointer_dragscroll_enabled(record->event.pressed);
            break;
        case DRAGSCROLL_MODE_TOGGLE:
            if (record->event.pressed) {
                ximi_set_pointer_dragscroll_enabled(!ximi_get_pointer_dragscroll_enabled());
            }
            break;
    }
#        endif // !NO_XIMI_KEYCODES
#    endif     // POINTING_DEVICE_ENABLE
    if (IS_QK_KB(keycode) || IS_MOUSEKEY(keycode)) {
        debug_ximi_config_to_console(&g_ximi_config);
    }
    return true;
}

void eeconfig_init_kb(void) {
    g_ximi_config.raw = 0;
    write_ximi_config_to_eeprom(&g_ximi_config);
    maybe_update_pointing_device_cpi(&g_ximi_config);
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    read_ximi_config_from_eeprom(&g_ximi_config);
    matrix_init_user();
}

#    ifdef XIMI_CONFIG_SYNC
void ximi_config_sync_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(g_ximi_config)) {
        memcpy(&g_ximi_config, initiator2target_buffer, sizeof(g_ximi_config));
    }
}
#    endif

void keyboard_post_init_kb(void) {
    maybe_update_pointing_device_cpi(&g_ximi_config);
#    ifdef XIMI_CONFIG_SYNC
    transaction_register_rpc(RPC_ID_KB_CONFIG_SYNC, ximi_config_sync_handler);
#    endif
    keyboard_post_init_user();
}

#    ifdef XIMI_CONFIG_SYNC
void housekeeping_task_kb(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave.
        static ximi_config_t last_ximi_config = {0};
        static uint32_t           last_sync             = 0;
        bool                      needs_sync            = false;

        // Check if the state values are different.
        if (memcmp(&g_ximi_config, &last_ximi_config, sizeof(g_ximi_config))) {
            needs_sync = true;
            memcpy(&last_ximi_config, &g_ximi_config, sizeof(g_ximi_config));
        }
        // Send to slave every 500ms regardless of state change.
        if (timer_elapsed32(last_sync) > 500) {
            needs_sync = true;
        }

        // Perform the sync if requested.
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_KB_CONFIG_SYNC, sizeof(g_ximi_config), &g_ximi_config)) {
                last_sync = timer_read32();
            }
        }
    }
    // No need to invoke the user-specific callback, as it's been called
    // already.
}
#    endif // XIMI_CONFIG_SYNC
#endif     // POINTING_DEVICE_ENABLE

#if defined(KEYBOARD_bastardkb_ximi_3x5_blackpill) || defined(KEYBOARD_bastardkb_ximi_4x6_blackpill)
void keyboard_pre_init_kb(void) {
    setPinInputHigh(A0);
    keyboard_pre_init_user();
}

void matrix_scan_kb(void) {
    if (!readPin(A0)) {
        reset_keyboard();
    }
    matrix_scan_user();
}
#endif // KEYBOARD_bastardkb_ximi_3x5_blackpill || KEYBOARD_bastardkb_ximi_4x6_blackpill

bool shutdown_kb(bool jump_to_bootloader) {
    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_setrgb(RGB_RED);
#endif // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    void rgb_matrix_update_pwm_buffers(void);
    rgb_matrix_set_color_all(RGB_RED);
    rgb_matrix_update_pwm_buffers();
#endif // RGB_MATRIX_ENABLE
    return true;
}

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

void keyboard_post_init_user(void) {
    pointing_device_set_cpi_on_side(true, 0.1); //Set cpi on left side to a low value for slower scrolling.
    pointing_device_set_cpi_on_side(false, 800); //Set cpi on right side to a reasonable value for mousing.
}

#define SCROLL_DIVISOR_H 6.0
#define SCROLL_DIVISOR_V 6.0

report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
     scroll_accumulated_h += (float)left_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)left_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        left_report.h = (int8_t)scroll_accumulated_h;
        left_report.v = (int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;
    left_report.x = 0;
    left_report.y = 0;
    return pointing_device_combine_reports(left_report, right_report);
}

