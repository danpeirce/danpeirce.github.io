title: Low Voltage PIC18 Devices Vs Standard Devices

# PIC18LF Devices

    by Dan Peirce 

translated from [dokuwiki](danpeirce.net46.net/dokuwiki/doku.php?id=pic18lf) format July 20, 2013

[TOC]

## Low Voltage PIC18 Devices VS Standard Devices

  
from [ PIC18F2525/2620/4525/4620 Data
Sheet](http://ww1.microchip.com/downloads/en/devicedoc/39626b.pdf) page 8

    
    
        Like all Microchip PIC18 devices, members of the
        PIC18F2525/2620/4525/4620 family are available as
        both standard and low-voltage devices. Standard
        devices with Enhanced Flash memory, designated with
        an "F" in the part number (such as PIC18F2620),
        accommodate an operating VDD range of 4.2V to 5.5V.
        Low-voltage parts, designated by "LF" (such as
        PIC18LF2620), function over an extended VDD range
        of 2.0V to 5.5V.

Have tested [ PIC18**LF**4525](testing_usb_powered_pic.html).

## 28 Pin Skinny Package


Have tested PIC18LF2620 at 3.3 volts. It comes in a 28 pin package which
should have enough IO for us. Note that we have been using the PIC18F4525 40
pin IC for apsc1299 but this package style is needed in that case because it
fits on the brainboard of our robots.

from [ PIC18F2525/2620/4525/4620 Data
Sheet](http://ww1.microchip.com/downloads/en/devicedoc/39626b.pdf) page 365.
![](28pin_skinny.png)

## hello world for PIC18LF2620 at 3.3 Volts

  * see [hello33](hello33.html)

