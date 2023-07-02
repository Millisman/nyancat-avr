BUILD_MCU = atmega1284p
BUILD_CLK = 20000000UL
UPLOADER = ft232h-clone
# UPLOADER = usbtiny
DUDEPORT =
FUSES = -U lfuse:w:0xdf:m -U hfuse:w:0xd1:m -U efuse:w:0xff:m

###################################################
# Tools & flags
###################################################

CC 	= avr-gcc
AR 	= avr-ar
SIZE 	= avr-size
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

DUDEFLAGS = -V -p $(BUILD_MCU) $(DUDEPORT) -c $(UPLOADER)

SIZEFLAGS =

PRJCFLAGS = -Os -g -mmcu=$(BUILD_MCU) -DF_CPU=$(BUILD_CLK) \
	-ffunction-sections -fdata-sections -fmerge-all-constants \
	-fno-inline-small-functions -fshort-enums \
	-fno-exceptions \
	-W -Wall -pedantic

LDFLAGS := $(LDFLAGS) -Wl,--gc-sections -Wl,--relax

FORMAT = ihex


# programmer
# id = "ft232h-clone";
# desc = "FT232H based generic programmer";
# type = "avrftdi";
# prog_modes = PM_TPI | PM_ISP;
# connection_type = usb;
# usbvid = 0x0403;
# usbpid = 0x6014;
# usbdev = "A";
# # ISP-signals
# reset = 7; # AD3 (TMS)
# sck = 6; # AD0 (TCK)
# sdo = 4; # AD1 (TDI)
# sdi = 5; # AD2 (TDO)
# ;
