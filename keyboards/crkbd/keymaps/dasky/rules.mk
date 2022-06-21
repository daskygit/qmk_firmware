# MCU name
MCU = STM32G474

# Bootloader selection
BOOTLOADER = stm32-dfu

RGB_MATRIX_ENABLE = yes
USBPD_ENABLE = yes
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
NKRO_ENABLE = yes

SERIAL_DRIVER = usart
WS2812_DRIVER = pwm
EEPROM_DRIVER = i2c

EXTRAFLAGS += -O2

