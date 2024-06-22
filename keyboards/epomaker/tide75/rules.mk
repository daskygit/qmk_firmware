UART_DRIVER_REQUIRED = yes

WS2812_DRIVER = spi

VPATH += keyboards/epomaker/common
SRC += rf8003a/rf_driver.c
SRC += rf8003a/rf_reports.c
SRC += rf8003a/rf_packets.c
SRC += lpm/lpm_wb32fq95.c
SRC += tide/tide.c

DEBOUNCE_TYPE = asym_eager_defer_pk

