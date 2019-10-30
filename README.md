# Minimal Shitty Add-On with Capture The Flag Challenge

Copyright (C) 2019, Uri Shaked. Released under the MIT license.

[__Learn more in the blog post: Capture The Flag Shitty Add-On__](https://blog.wokwi.com/capture-the-flag-shitty-add-on/?utm_source=github)

## Hardware

The [ctf-shittyaddon board](pcb/) includes the following hardware:

1. ATtiny85 Processor
2. A [ShittyAddon V1](https://twitter.com/MrRobotBadge/status/962043056781324289) connector 
3. Reset button
4. Red LED connected to ATtiny85's pin 6 (PB1)

<img src="https://blog.wokwi.com/content/images/2019/10/image-6.png" alt="Tiny CTF PCB" width="600" />

You can also hack a simplified version on a breadboard:

![Arduino Connection Diagram](https://blog.wokwi.com/content/images/2019/10/image-9.png)

## Firmware

Compile the firmware using the Arduino IDE:

1. Install [ATTiny Core](https://github.com/damellis/attiny)
2. Install the [TinyWire Library](https://github.com/lucullusTheOnly/TinyWire)
3. Configure Arduino IDE as follows:
   - Board: ATtiny25/45/85
   - Processor: ATtiny85
   - Clock: Internal 8 MHz
4. Set the fuses of the chip to enable self programming (`SELFPRGEN=1`). 
   This can be done using `avrdude`:
   ```bash
   avrdude -pattiny85 -cusbtiny -e -Uefuse:w:0xfe:m -Uhfuse:w:0xdf:m -Ulfuse:w:0xe2:m
   ```

When building your own firmware, replace `SECRET` in the string `"$FLAG:SECRET"` 
with your secret value (the flag).

## The Challenge

The [firmware code](ctf-firmware/ctf-firmware.ino) implements an I2C slave listening on address 0x23.

The challenge consists of several milestones of increasing difficulty:

1. Make the red LED light
2. Find the secret flag value (it starts with the string "$FLAG:")
3. Make the red LED blink by executing code directly on the ATTiny85
4. Replace the secret flag with a new value without bricking the board

All the above milestones can be achieved through I2C communication with
the chip.

For more information, [check out the blog post](https://blog.wokwi.com/capture-the-flag-shitty-add-on/?utm_source=github)
