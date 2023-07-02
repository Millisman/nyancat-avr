# nyancat-avr
Nyancat rendered in your terminal from AVR ATMega64/ATMega128. Not Arduino - only a pure C-code on a bare hardware.
The port was created for loved ones McU AVR Mega 64/128. I used AVR atmega1284P - but the cat can fit into the ATMeGA64 processor
You can configure this target processor in the MakeFile.inc file

[![Nyancats-avr](https://raw.githubusercontent.com/Millisman/nyancat-avr/main/NyanCat.png)](https://raw.githubusercontent.com/Millisman/nyancat-avr/main/NyanCat.png)

The port is made from this project https://github.com/klange/nyancat

# Nyancat CLI

Nyancat rendered in your terminal.

[![Nyancats](http://nyancat.dakko.us/nyancat.png)](http://nyancat.dakko.us/nyancat.png)

## Setup

You will need AVR Atmega 64/128 MCU, or even 256

I used the programmer on IC FT232H, but you can use any other programmer. Detailed in the MakeFile.inc file.

The clock frequency by default 20 MHz and UART0 Port speed 115200bps - this affects speed for drawing of the picture.

For build, use the command 'make all'

For programming - command 'make flash'

If you have collected your first fee based on ATMGA1284 with external crystal, then go Fuse using 'make fuse'

Use avr-gcc and Unix make.

* Made for entertainment and educational purposes. May contain errors

## Licenses, References, etc.

The original source of the Nyancat animation is
[prguitarman](http://www.prguitarman.com/index.php?id=348).

The code provided here is provided under the terms of the
[NCSA license](http://en.wikipedia.org/wiki/University_of_Illinois/NCSA_Open_Source_License).
