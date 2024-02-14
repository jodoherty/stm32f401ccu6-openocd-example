# STM32F401CCU6 Arduino demo

This is an example PlatformIO project for a WeAct Studio Black Pill
STM32F401CCU6 board:

https://stm32-base.org/boards/STM32F401CCU6-WeAct-Black-Pill-V1.2.html

I put it on a breadboard with a little 128x32 OLED screen and a GY-511
accelerometer/compass module:

https://www.adafruit.com/product/931

https://www.pololu.com/product/2124

I use OpenOCD with an FT2232HL mini module compatible clone:

https://ftdichip.com/products/ft2232h-mini-module/

http://dangerousprototypes.com/docs/index.php?title=FT2232_breakout_board&oldid=16252

Pins A9 and A10 on the STM32 board are connected to the BDBUS0 and BDBUS1 pins
on the FT2232H module to provide UART (note, some cheaper clones label these
pins CDBUS0 and CDBUS1 -- you can follow the traces off of the chip to identify
what's what). This is so you can run `screen /dev/ttyUSB1 9600` to see the
serial out of the microcontroller.

Connect SWSCK to ADBUS0 on the FT2232H module. Then connect SWDIO to a 470 Ohm
resistor shorting ADBUS1 and ADBUS2 together. These connections are for OpenOCD
to program and debug the STM32.

Finally, connect ground to ground between the STM32 dev board and the FT2232H
module.

Pin B6 is the I2C SCK line. The internal pullup resistor is used, so just
connect the OLED SCK and the GY-511 SCK to it.

Pin B7 is the I2C SDA line. Connect it to both devices as well.

On Debian, make sure you have OpenOCD installed:

```
sudo apt install openocd
```

You can build and run the project with platformio:

```
pio run -t upload
```

You can also debug the project with gdb:

```
pio debug --interface=gdb -- -x .pioinit
```

## Why the system installed OpenOCD?

The purpose of this project is partially to play around with using custom tool
commands for upload and debug.

Note the use of `${PROG_PATH}` to reference the `firmware.elf` file instead of
`program.bin`. This seems to be the file OpenOCD needs to program the board.

