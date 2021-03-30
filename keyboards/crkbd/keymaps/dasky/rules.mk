MCU = STM32G474
BOOTLOADER = stm32-dfu
USBPD_ENABLE = yes

BOOTMAGIC_ENABLE = lite
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
NKRO_ENABLE = yes
RGB_MATRIX_ENABLE = yes
OLED_DRIVER_ENABLE = yes
RAW_ENABLE = yes
CONSOLE_ENABLE = yes
CUSTOM_MATRIX = yes

DEBOUNCE_TYPE = asym_eager_defer_pk

REGISTER_MULTIPLE_KEYEVENTS_ENABLE = yes

SERIAL_DRIVER = usart
WS2812_DRIVER = pwm

ifeq ($(strip $(CUSTOM_MATRIX)), yes)
   SRC += matrix.c matrix_common.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
   SRC += tapdances.c
endif

LTO_ENABLE = yes
EXTRAFLAGS += -Ofast
