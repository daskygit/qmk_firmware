# Build Options
#   change yes to no to disable
#
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
DEBOUNCE_TYPE= asym_eager_defer_pk
LTO_ENABLE = yes
EXTRAFLAGS += -Ofast
REGISTER_MULTIPLE_KEYEVENTS_ENABLE = yes
CONSOLE_ENABLE = no
MOUSEKEY_ENABLE = yes
CUSTOM_MATRIX = yes
SRC = matrix.c matrix_common.c
TAP_DANCE_ENABLE = yes

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
   SRC += tapdances.c
endif
