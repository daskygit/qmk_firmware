# MCU name
MCU = STM32G474

# Bootloader selection
BOOTLOADER = stm32-dfu
USBPD_ENABLE = yes
NKRO_ENABLE = yes

SERIAL_DRIVER = usart
EEPROM_DRIVER = i2c
WS2812_DRIVER = pwm

EXTRAFLAGS += -O2

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pimoroni_trackball