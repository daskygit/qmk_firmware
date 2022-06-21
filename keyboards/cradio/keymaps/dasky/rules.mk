# MCU name
MCU = STM32G474

# Bootloader selection
BOOTLOADER = stm32-dfu
USBPD_ENABLE = yes
NKRO_ENABLE = yes

SERIAL_DRIVER = usart
#EEPROM_DRIVER = i2c

EXTRAFLAGS += -O2
