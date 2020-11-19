# MCU name
MCU = atmega32u4
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
MOUSEKEY_ENABLE = no        # Mouse keys
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
BLUETOOTH_ENABLE = no       # Enable Bluetooth
AUDIO_ENABLE = no           # Audio output
TAP_DANCE_ENABLE = no
COMBO_ENABLE = no

EXTRAKEY_ENABLE = yes       # Audio control and System control (for KC_CALC to work)
BOOTMAGIC_ENABLE = lite     # Fn key while powering on will enter bootloader
COMMAND_ENABLE = yes        # Commands for debug and configuration
CONSOLE_ENABLE = no        # Console for debug

LAYOUTS = 60_ansi
