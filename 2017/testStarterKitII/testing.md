% Testing Microstick II with USB to Serial Adaptor
% Dan Peirce B.Sc.

<!---
use pandoc -s -t html5 -c ../../pandocbd.css testing.md -o testing.html
-->

# Microstick II with USB to Serial Adaptor

I'm setting up a class set of Microstick II with a 
[PIC32MX150F128B](http://www.microchip.com/wwwproducts/en/PIC32MX150F128B) installed in the socket. 
A USB to Serial adaptor is also wired to the PIC Tx and Rx lines.

The Microstick II schematic included with the kit as shipped has Tx and Rx marked backwards! I have used the 
following arrangement:

~~~~c
      PPSOutput(4, RPB10, U2TX);        // MAP Tx to PB10 - pin 21
      PPSInput (2, U2RX, RPB11);        // MAP Rx to PB11 - pin 22
~~~~

## Schematic

A portion of the schematic is here (note interchange TxD and RxD):

![](microstickii-schamatic.png)

The pinout can be found on page four of the [datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/60001168J.pdf).

## Test Setup

<img src="test-microstick.jpg" width="800" />


## Test Program

The Test program is here:

* [hello-32MX.c](https://github.com/danpeirce/danpeirce.github.io/blob/master/2017/testStarterKitII/hello-32MX.c)

* Previous notes -- [testing without microstick](https://sites.google.com/site/danpeircenotes/pic32mx/worked-through-guide)