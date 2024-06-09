UART_DRIVER_REQUIRED = yes

WS2812_DRIVER = spi

VPATH += keyboards/epomaker/tide65/wireless
SRC += rf_driver.c
SRC += rf_reports.c
SRC += rf_packets.c

DEBOUNCE_TYPE = asym_eager_defer_pk

