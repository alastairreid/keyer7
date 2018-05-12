# Keyer7

Ever since I first saw the
[microwriter](https://en.wikipedia.org/wiki/Microwriter), I have been
fascinated by chorded keyboards: single handed keyboards with a handful
(literally) of keys where instead of pressing one key at a time, you press
a "chord" (several keys) to select each letter.

Now that low cost Bluetooth LE devices like the [Adafruit
NRF52](https://www.adafruit.com/product/3406) are cheap and
easy to program, there really was no excuse not to build one.

## Building

Install the tool and Adafruit library as follows

    wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2017q4/gcc-arm-none-eabi-7-2017-q4-major-mac.tar.bz2
    tar jxf gcc-arm-none-eabi-7-2017-q4-major-mac.tar.bz2

    git submodule init
    git submodule update

Build the Adafruit library as follows.
This will generate a lot of warning messages --- hold your nose and ignore them.

    make nrf52_cores.a

Build as follows

    make main.elf

Upload as follows

    make upload

In the build_system branch, you should see the blue LED pulsing on and off.
