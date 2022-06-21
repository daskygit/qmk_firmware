BOOTMAGIC_ENABLE = yes
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
RAW_ENABLE = yes
CONSOLE_ENABLE = yes
DEBOUNCE_TYPE = asym_eager_defer_pk
LTO_ENABLE = yes
CUSTOM_TAP_CODE_ENABLE = yes
COMBO_ENABLE = yes

SPACE_CADET_ENABLE    = no
GRAVE_ESC_ENABLE      = no

SRC += dasky.c autoshift.c

ifeq ($(strip $(USER_MINIMAL)), yes)
	OPT_DEFS += -DUSER_MINIMAL
	CONSOLE_ENABLE = no
endif
ifeq ($(strip $(CUSTOM_TAP_CODE_ENABLE)), yes)
	OPT_DEFS += -DCUSTOM_TAP_CODE_ENABLE
    SRC += tap_codes.c
endif
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tap_dances.c
endif
ifeq ($(strip $(USBPD_ENABLE)), yes)
    SRC += usbpd_bits.c
endif
ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += oled.c
endif
ifeq ($(strip $(RAW_ENABLE)), yes)
    SRC += raw_hid.c
endif
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    SRC += rgb_indicators.c
	SRC += rgb_bits.c
endif
ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    SRC += rgb_indicators.c
endif
ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
    SRC += user_sync.c
endif
ifeq ($(strip $(ENCODER_ENABLE)), yes)
    SRC += encoder.c
endif
ifeq ($(strip $(COMBO_ENABLE)), yes)
    SRC += combos.c
endif
