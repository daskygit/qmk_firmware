# stinky

![stinky](imgur.com image replace me!)

_A short description of the keyboard/project_

-   Keyboard Maintainer: [Dasky](https://github.com/Dasky)
-   Hardware Supported: _The PCBs, controllers supported_
-   Hardware Availability: _Links to where you can find this hardware_

Make example for this keyboard (after setting up your build environment):

    make stinky:default

Flashing example for this keyboard:

    make stinky:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
-   **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
