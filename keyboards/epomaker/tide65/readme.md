# EPOMAKER TIDE 65

* Keyboard Maintainer: [sdk66](https://github.com/sdk66)
* Hardware Supported: EPOMAKER TIDE 65
* Hardware Availability: [epomaker](https://www.epomaker.com)

Make example for this keyboard (after setting up your build environment):

    make epomaker/tide_65:default
        
Flashing example for this keyboard:

    make epomaker/tide65:default:flash
    
To pair the dongle:

* Unplug dongle
* Disconnect keyboard from USB
* Switch off keyboard
* Switch on keyboard
* Press key mapped to dongle pairing
* Plug in dongle
* Wait a few seconds.

To reset the board into bootloader mode, do one of the following:

* Short the 2 plated through holes of the switch position between the MCU and SPI flash and plug in the keyboard.
* Hold the Escape key while connecting the USB cable (also erases persistent settings)
* Fn+R_Shift+PgUp will reset the board to bootloader mode if you have original firmware

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
