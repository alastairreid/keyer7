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

    pushd Adafruit_nRF52_Arduino/tools/nrfutil-0.5.2
    # to install the packages, you might need to disable virtualenv
    # (or you might want to select an appropriate virtualenv)
    export PIP_REQUIRE_VIRTUALENV=false

    pip install --user -r requirements.txt
    python setup.py install
    popd

    # download and install driver for CP2104 USB-to-Serial (the chip on the NRF52 board)
    wget https://www.silabs.com/documents/public/software/Mac_OSX_VCP_Driver.zip
    unzip Mac_OSX_VCP_Driver.zip
    open SiLabsUSBDriverDisk.dmg
    # install the driver
    # confirm install (if NRF board is connected over USB at the moment)
    ls /dev/*USB*
    # Should show: /dev/cu.SLAB_USBtoUART /dev/tty.SLAB_USBtoUART

Build the Adafruit library as follows.
This will generate a lot of warning messages --- hold your nose and ignore them.

    make nrf52_cores.a

Build as follows

    make main.elf

Upload as follows

    make upload

In the build_system branch, you should see the blue LED pulsing on and off.
