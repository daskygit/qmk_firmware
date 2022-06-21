# Echo

![echo](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Dasky](https://github.com/daskygit)
* Hardware Supported: N/A
* Hardware Availability: N/A

Make example for this keyboard (after setting up your build environment):

    make echo:default

Flashing example for this keyboard:

    make echo:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key the top left key and plug in the keyboard
* **Physical reset button**: Hold BOOT0 button and either plug-in USB or press NRST button.
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
