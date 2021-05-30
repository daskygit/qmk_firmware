VIA_ENABLE = yes
BOOTMAGIC_ENABLE = lite 	#ideally should be enabled if running nanoboot
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
NKRO_ENABLE = yes
RGB_MATRIX_ENABLE = yes
OLED_DRIVER_ENABLE = yes
RAW_ENABLE = yes
LTO_ENABLE = yes
BOOTLOADER = nanoboot 		#hid bootloader not supported by qmk
CONSOLE_ENABLE = no
CUSTOM_MATRIX = yes

DEBOUNCE_TYPE = asym_eager_defer_pk

REGISTER_MULTIPLE_KEYEVENTS_ENABLE = yes


ifeq ($(strip $(CUSTOM_MATRIX)), yes)
   SRC += matrix.c matrix_common.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
   SRC += tapdances.c
endif

ifeq ($(strip $(BOOTLOADER)), nanoboot)
   SRC += nanoboot.c
   BOOTLOADER_SIZE = 512
endif
