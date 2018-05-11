# Change the following to point to your install locations
ARDUINO  = $(HOME)/Programming/keyboards/Arduino_1.8.3.app
NRF52    = $(HOME)/Documents/Arduino/hardware/Adafruit/Adafruit_nRF52_Arduino
TOOLS    = $(HOME)/Library/Arduino15/packages/adafruit/tools

# Control whether commands are shown
# use "make QUIET=" to enable display of commands
QUIET = @

BINUTILS = $(TOOLS)/gcc-arm-none-eabi/5_2-2015q4/
CXX      = $(BINUTILS)/bin/arm-none-eabi-g++
CC       = $(BINUTILS)/bin/arm-none-eabi-gcc
AR       = $(BINUTILS)/bin/arm-none-eabi-ar
OBJCOPY  = $(BINUTILS)/bin/arm-none-eabi-objcopy
LIBGCC   = $(BINUTILS)/lib/gcc/arm-none-eabi/5.2.1/libgcc.a

NRFUTIL  = /usr/local/bin/nrfutil

ARCHFLAGS += -mcpu=cortex-m4
ARCHFLAGS += -mthumb
ARCHFLAGS += -mfloat-abi=hard
ARCHFLAGS += -mfpu=fpv4-sp-d16

LINKFLAGS += -u _printf_float
LINKFLAGS += -Wl,--gc-sections
LINKFLAGS += -L$(NRF52)/cores/nRF5/linker

# choice of which bootloader we work with
LINKFLAGS += -Tbluefruit52_s132_2.0.1.ld
# LINKFLAGS += -Tbluefruit52_s132_5.1.0.ld

# LINKFLAGS += -Wl,--cref
LINKFLAGS += -Wl,-Map,main.map
LINKFLAGS += -Wl,--check-sections
LINKFLAGS += -Wl,--gc-sections
LINKFLAGS += -Wl,--unresolved-symbols=report-all
LINKFLAGS += -Wl,--warn-common
LINKFLAGS += -Wl,--warn-section-align
LINKFLAGS += --specs=nano.specs
LINKFLAGS += --specs=nosys.specs

# LINKFLAGS += -save-temps

OPTFLAGS += -g
OPTFLAGS += --param max-inline-insns-single=500
OPTFLAGS += -Os

OPTFLAGS += -ffunction-sections
OPTFLAGS += -fdata-sections
OPTFLAGS += -nostdlib

CXXLANGFLAGS += -std=gnu++11
CXXLANGFLAGS += -fno-rtti
CXXLANGFLAGS += -fno-exceptions
CXXLANGFLAGS += -x c++
CXXLANGFLAGS += -fno-threadsafe-statics

CLANGFLAGS   += -x c
CLANGFLAGS   += -std=gnu11

ASMLANGFLAGS += -x assembler-with-cpp

DEFINES += -DF_CPU=64000000
DEFINES += -DARDUINO=10805
DEFINES += -DARDUINO_NRF52_FEATHER
DEFINES += -DARDUINO_ARCH_ADAFRUIT_NRF52_ARDUINO
DEFINES += -DARDUINO_BSP_VERSION=\"0.8.3\"
DEFINES += -DARDUINO_FEATHER52
DEFINES += -DARDUINO_NRF52_ADAFRUIT
DEFINES += -DNRF5
DEFINES += -DNRF52
DEFINES += -DNRF52832_XXAA
DEFINES += -DSOFTDEVICE_PRESENT
DEFINES += -DUSE_LFXO
DEFINES += -DS132
DEFINES += -DSD_VER=201
DEFINES += -DCFG_DEBUG=0

CORES     = $(NRF52)/cores

INCLUDES += -I$(CORES)/nRF5/SDK/components/toolchain/
INCLUDES += -I$(CORES)/nRF5/SDK/components/toolchain/cmsis/include
INCLUDES += -I$(CORES)/nRF5/SDK/components/toolchain/gcc/
INCLUDES += -I$(CORES)/nRF5/SDK/components/device/
INCLUDES += -I$(CORES)/nRF5/SDK/components/drivers_nrf/delay/
INCLUDES += -I$(CORES)/nRF5/SDK/components/drivers_nrf/hal/
INCLUDES += -I$(CORES)/nRF5/SDK/components/libraries/util/
INCLUDES += -I$(CORES)/nRF5/softdevice/s132/2.0.1/headers/
INCLUDES += -I$(CORES)/nRF5/freertos/source/include
INCLUDES += -I$(CORES)/nRF5/freertos/config
INCLUDES += -I$(CORES)/nRF5/freertos/portable/GCC/nrf52
INCLUDES += -I$(CORES)/nRF5/freertos/portable/CMSIS/nrf52
INCLUDES += -I$(CORES)/nRF5/sysview/SEGGER
INCLUDES += -I$(CORES)/nRF5/sysview/Config
INCLUDES += -I$(CORES)/nRF5
INCLUDES += -I$(NRF52)/libraries/nffs/src
INCLUDES += -I$(NRF52)/libraries/nffs/src/fs/nffs/include
INCLUDES += -I$(NRF52)/libraries/nffs/src/fs/fs/include
INCLUDES += -I$(NRF52)/libraries/nffs/src/fs/disk/include
INCLUDES += -I$(NRF52)/libraries/nffs/src/util/crc/include
INCLUDES += -I$(NRF52)/libraries/nffs/src/kernel/os/include
INCLUDES += -I$(NRF52)/libraries/nffs/src/kernel/os/include/os/arch/cortex_m4
INCLUDES += -I$(NRF52)/libraries/nffs/src/hw/hal/include
INCLUDES += -I$(NRF52)/libraries/nffs/src/sys/flash_map/include
INCLUDES += -I$(NRF52)/libraries/nffs/src/sys/defs/include
INCLUDES += -I$(NRF52)/libraries/SPI
INCLUDES += -I$(NRF52)/libraries/Bluefruit52Lib/src
INCLUDES += -I$(NRF52)/libraries/BLEHomekit/src
INCLUDES += -I$(NRF52)/variants/feather52
INCLUDES += -I$(ARDUINO)/Contents/Java/libraries/Keyboard/src
INCLUDES += -I$(NRF52)/libraries/SoftwareSerial

ERRFLAGS += -Wall
ERRFLAGS += -Wextra
ERRFLAGS += -Wno-unused-parameter
ERRFLAGS += -Wno-missing-field-initializers
ERRFLAGS += -Wno-pointer-arith

CXXFLAGS = $(ARCHFLAGS) $(ERRFLAGS) $(OPTFLAGS) $(CXXLANGFLAGS) $(DEFINES) $(INCLUDES)
CFLAGS   = $(ARCHFLAGS) $(ERRFLAGS) $(OPTFLAGS) $(CLANGFLAGS)   $(DEFINES) $(INCLUDES)
ASMFLAGS = $(ARCHFLAGS) $(ERRFLAGS) $(OPTFLAGS) $(ASMLANGFLAGS) $(DEFINES) $(INCLUDES)

%.o: %.cpp
	@ echo Building $@
	$(QUIET) $(CXX) $(CXXFLAGS) $^ -c -o $@

%.o: %.c
	@ echo Building $@
	$(QUIET) $(CC) $(CFLAGS)    $^ -c -o $@

%.o: %.S
	@ echo Building $@
	$(QUIET) $(CC) $(ASMFLAGS)  $^ -c -o $@

NRF52_DIRS += $(NRF52)/cores
NRF52_DIRS += $(NRF52)/libraries

NRF52_OBJS += $(patsubst %.cpp, %.o, $(shell find $(NRF52_DIRS) -name '*.cpp'))
NRF52_OBJS += $(patsubst %.c,   %.o, $(shell find $(NRF52_DIRS) -name '*.c'))
NRF52_OBJS += $(patsubst %.S,   %.o, $(shell find $(NRF52_DIRS) -name '*.S'))


nrf52_cores.a : $(NRF52_OBJS)
	@ echo Building $@
	$(QUIET) $(RM) -f $@
	$(QUIET) $(AR) cr $@ $^
	$(QUIET) $(AR) s $@

LIBS += nrf52_cores.a
LIBS += $(LIBGCC)

variant.o: $(NRF52)/variants/feather52/variant.cpp
	@ echo Building $@
	$(QUIET) $(CXX) $(CXXFLAGS) $^ -c -o $@

main.elf: main.o variant.o $(LIBS)
	@ echo Building $@
	$(QUIET) $(CC) $(ARCHFLAGS) $(LINKFLAGS) main.o variant.o -Wl,--start-group -lm $(LIBS) -Wl,--end-group -o $@

%.hex: %.elf
	@ echo Building $@
	$(QUIET) $(OBJCOPY) -O ihex $^ $@

%.zip: %.hex
	@ echo Building $@
	$(QUIET) $(NRFUTIL) dfu genpkg --dev-type 0x0052 --sd-req 0x0088 --application $^ $@

upload: main.zip
	@ echo Uploading
	$(QUIET) $(NRFUTIL) --verbose dfu serial -pkg $^ -p /dev/cu.SLAB_USBtoUART -b 115200

clean::
	$(RM) *.o *.a
	$(RM) main
	$(RM) $(NRF52_OBJS)

# End of Makefile
