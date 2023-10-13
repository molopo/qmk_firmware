# MCU name
MCU = RP2040
BOOTLOADER = rp2040

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality

# Either do RGBLIGHT_ENABLE or RGB_MATRIX_ENABLE and RGB_MATRIX_DRIVER
RGBLIGHT_ENABLE ?= no
RGB_MATRIX_ENABLE ?= no      # not supported yet, but will add
RGB_MATRIX_DRIVER = WS2812
WS2812_DRIVER = vendor

MIDI_ENABLE = no            # MIDI support
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
ENCODER_ENABLE ?= no
EXTRAFLAGS     += -flto     # macros enable or disable
MOUSEKEY_ENABLE = yes

#HAPTIC FEEDBACK
HAPTIC_ENABLE ?= no
HAPTIC_DRIVER = DRV2605L

AUDIO_ENABLE ?= no
AUDIO_DRIVER = pwm_hardware

VIK_ENABLE = yes

# Choose only one (or none) of the options below
# FP_PER56_CIRQUE_LEDS ?= no
# FP_PER56_PMW3360_LEDS ?= no
# FP_PMW3360 ?= no
# FP_WEACT_ST7735 ?= no

# The rest of the VIK logic is in the keyboards/fingerpunch/src/vik/rules.mk

ifeq ($(strip $(VIK_PER56_CIRQUE_LEDS)), yes)
   RGBLIGHT_ENABLE = yes
endif

ifeq ($(strip $(VIK_PER56_PMW3360_LEDS)), yes)
   RGBLIGHT_ENABLE = yes
endif

ifeq ($(strip $(VIK_WEACT_ST7735)), yes)
   SRC += fonts/urbanist24.qff.c fonts/urbanist36.qff.c 
   SRC += fonts/roboto12.qff.c fonts/roboto18.qff.c fonts/roboto14.qff.c
   SRC += display.c
   WPM_ENABLE 					= yes
endif

ifeq ($(strip $(CIRQUE_ENABLE)), yes)
   POINTING_DEVICE_ENABLE := yes
   POINTING_DEVICE_DRIVER := cirque_pinnacle_spi
   OPT_DEFS += -DCIRQUE_ENABLE
endif

include keyboards/fingerpunch/src/rules.mk

DEFERRED_EXEC_ENABLE = yes
SRC +=  keyboards/fingerpunch/src/fp.c \
        keyboards/fingerpunch/src/fp_haptic.c \
        keyboards/fingerpunch/src/fp_audio.c \
        keyboards/fingerpunch/src/fp_keyhandler.c \
        keyboards/fingerpunch/src/fp_encoder.c \
        keyboards/fingerpunch/src/fp_pointing.c \
        keyboards/fingerpunch/src/fp_rgb_common.c \
        keyboards/fingerpunch/src/fp_rgblight.c \
        keyboards/fingerpunch/src/fp_rgb_matrix.c
