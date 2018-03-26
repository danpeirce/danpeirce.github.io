% Motor MOSFET and Trinket M0
% by Dan Peirce B.Sc.

<!---
use pandoc -s --toc -t html5 -c ../../pandocbd.css motor-mosfet.md -o motor-mosfet.html
-->

# Motor MOSFET and Trinket M0

Simple example of Trinket M0 controlling a motor with a power MOSFET. The trinket M0 digital output can only source 7 mA. The motot in this example has a stall current of 500 mA so the trinket M0 can not drive the motor directly.

## Power MOSFET

* [http://www.vishay.com/docs/91308/sihld24.pdf](http://www.vishay.com/docs/91308/sihld24.pdf)
* [https://www.digikey.ca/product-detail/en/IRLD024PBF/IRLD024PBF-ND/812492](https://www.digikey.ca/product-detail/en/IRLD024PBF/IRLD024PBF-ND/812492)

The MOSFET is used in much the same way as in [https://danpeirce.github.io/remote-actuator.html#schematic-of-circuit](https://danpeirce.github.io/remote-actuator.html#schematic-of-circuit)
exceot the gate circuit is replaced with a Trinket M0 and D2 is not required.

![](mosfet-pins.png)

## Trinket M0

see [https://danpeirce.github.io/2017/testTrinketM0/testing.html](https://danpeirce.github.io/2017/testTrinketM0/testing.html)


