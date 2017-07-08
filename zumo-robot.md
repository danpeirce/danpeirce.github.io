# Zumo 32U4 from Pololu Notes

Notes by Dan Peirce B.Sc.

<!---
use 
     pandoc -s -t html5 -T "Zumo 32U4 from Pololu" -c pandocbd.css zumo-robot.md -o zumo-robot.html
-->

## Demo Video from Pololu

<iframe width="560" height="315" src="https://www.youtube.com/embed/Jtwu7-T1a9o" frameborder="0" allowfullscreen></iframe>


* [zumo-robots-and-accessories](https://www.pololu.com/category/129/zumo-robots-and-accessories)
    * The 32u4 models have encoders [Zumo 32u4 Robot](https://www.pololu.com/category/170/zumo-32u4-robot)
    * [need 4 AA - can use NiMH](https://www.digikey.ca/product-detail/en/panasonic-bsg/BK-200AAB9B/P688-ND/5067197)
    * [zumo-32u4-schematic-diagram.pdf](https://www.pololu.com/file/download/zumo-32u4-schematic-diagram.pdf?file_id=0J862)
        * note expansion ports - looks like it should be possible to piggy back a MCU board. 
           
## Using Microstick II With Zumo

The ATmega32U4 MCU has limitations so I am considering methods to use a Microstick II with a 
PIC32MX150F128B piggybacked on the Zumo. This perhaps will be simplified through the use of the I^2^C 
interface bus on the Zumo. Some of the sensors on the Zumo are accessed via I^2^C. As designed the ATmega32U4 would 
be the master of the bus. For use with the Microstick II the ATmega32U4 would be reprogrammed as an I^2^C slave 
and the added PIC32MX150F128B would become the new master. The ATmega32U4 could continue to be used to read
the line sensors. The condition of the line sensors could be read from ATmega32U4 via I^2^C and sensors like 
the accelerometer could be read directly using the I^2^C.

Although the PIC32MX150F128B runs at 3.3 volts some pins are 5 volt tolerant. Pins 17 and 18 used for I^2^C are 
5 volt tolerant.

![](zumo/pic32mx150f128b-pins.png)

One big advantage of I^2^C is it requires just two wires on an open drain bus. Custom wiring would be minimal. 

One could also continue to use the existing ATmega32U4 to run the motors. The PIC could send commands to the ATmega 
via the I^2^C bus that would set the duty cycle and direction of the motors. The high level student program
would go into the PIC and the lowest level code would be preprogrammed into the ATmega (saving us some development 
time).

I have not yet tested this but I believe we can connect to the I^2^C bus via an expansion header on the Zumo. 
Note the SCL and SDA lines:

![](zumo/expansion-area-right.png)

See [https://www.pololu.com/docs/0J63/all#3.9](https://www.pololu.com/docs/0J63/all#3.9)

## The Quadrature Encoders

* [Quadrature encoders](https://www.pololu.com/docs/0J63/3.4) -- Zumo 32U4 manual
* Historical perspective on [development of the encoders from 2014](https://www.pololu.com/blog/414/new-products-magnetic-quadrature-encoders-for-micro-metal-gearmotors)

![](zumo/encoders.png)
