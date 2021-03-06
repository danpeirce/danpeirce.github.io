# Zumo 32U4 from Pololu Notes

Notes by Dan Peirce B.Sc.

<!---
use 
     pandoc -s -t html5 -T "Zumo 32U4 from Pololu" -c pandocbd.css zumo-robot.md -o zumo-robot.html
-->

## Demo Video from Pololu

<iframe width="560" height="315" src="https://www.youtube.com/embed/Jtwu7-T1a9o" frameborder="0" allowfullscreen></iframe>

* [Example code including code used in above demos](https://github.com/pololu/zumo-32u4-arduino-library/tree/master/examples)
* [Blog post regarding demo video](https://www.pololu.com/blog/482/video-zumo-32u4-robot-example-projects)
* [http://pololu.github.io/zumo-32u4-arduino-library/](http://pololu.github.io/zumo-32u4-arduino-library/)

-------------

* [zumo-robots-and-accessories](https://www.pololu.com/category/129/zumo-robots-and-accessories)
    * The 32u4 models have encoders [Zumo 32u4 Robot](https://www.pololu.com/category/170/zumo-32u4-robot)
    * [need 4 AA - can use NiMH](https://www.digikey.ca/product-detail/en/panasonic-bsg/BK-200AAB9B/P688-ND/5067197)
    * [zumo-32u4-schematic-diagram.pdf](https://www.pololu.com/file/download/zumo-32u4-schematic-diagram.pdf?file_id=0J862)
        * note expansion ports - looks like it should be possible to piggy back a MCU board. 
           
## Using Microstick II With Zumo (still speculative)

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

![Zumo Right Side Expansion Area](zumo/expansion-area-right.png)

See [https://www.pololu.com/docs/0J63/all#3.9](https://www.pololu.com/docs/0J63/all#3.9)

## Reflective Line Sensors

### Work Differently than on Sumovore

The Zumo has five reflective line sensors like the Solarbotics Sumovore. The method of reading the sensors is 
different on the Zumo. Rather than using a pull up resistor the Zumo uses a capacitor. The photo transistor pulls a current
proportional to the reflected IR. The higher the current the faster the capacitor charges. The ATmega32U4 measures 
the time it takes for the capacitor to charge. Note the line voltage approaches ground as the capacitor charges because the other 
side of the capacitor is at V~dd~.

* [https://www.pololu.com/docs/0J63/3.5](https://www.pololu.com/docs/0J63/3.5)
* [ Sharp GP2S60 compact reflective photointerrupter](https://www.pololu.com/file/download/GP2S60_DS.pdf?file_id=0J683)

![](zumo/reflective.png)

### More Sensors than Pins

The assembled Zumo ships with five line sensors and three proximity sensors. Only three of the line sensors ship 
connected to the ATmega32U4 MCU. That configuration works for sumo events and other purposes. For line following
one would want to change the configuration to use all five reflective line sensors. The change would involve moving
jumpers that are soldered in place.

~~~~
The signals from the sensors can be remapped by soldering in a wire from 
the signal output to the desired I/O pin. You would also want to disconnect 
the sensor output from the standard I/O pin so that pin can be used for 
other purposes. For line sensor 1, line sensor 3, line sensor 5, and the 
front proximity sensor, disconnecting the sensor involves cutting a trace 
between the signal output and the standard I/O pin, which is labeled on 
the board. For the line sensor 2, line sensor 4, the left proximity sensor, 
and the right proximity sensor, you can simply move or remove the 
corresponding jumper.
~~~~

Quoted from [https://www.pololu.com/docs/0J63/3.5](https://www.pololu.com/docs/0J63/3.5)

The jumpers that need to be moved are not visible on an assembled Zumo. The front sensor array board is easily 
removed by gently pulling the board away from the main board. Once removed the jumpers become visible. 
See [https://www.pololu.com/docs/0J63/4](https://www.pololu.com/docs/0J63/4) and page down to the Heading 
*Front sensor array* or click here [https://a.pololu-files.com/picture/0J6707.600.jpg](https://a.pololu-files.com/picture/0J6707.600.jpg)

## The Quadrature Encoders

* [Quadrature encoders](https://www.pololu.com/docs/0J63/3.4) -- Zumo 32U4 manual
* Historical perspective on [development of the encoders from 2014](https://www.pololu.com/blog/414/new-products-magnetic-quadrature-encoders-for-micro-metal-gearmotors)

![](zumo/encoders.png)

![Pololu magnetic encoder concept drawing -- https://a.pololu-files.com/picture/0J5839.450.jpg?574b555f52778f79260127402ca1b130](https://a.pololu-files.com/picture/0J5839.450.jpg?574b555f52778f79260127402ca1b130)

## Inertial Measurement Unit (IMU)

* [https://www.pololu.com/docs/0J63/3.7](https://www.pololu.com/docs/0J63/3.7)

    * ST [LSM303D](https://www.pololu.com/product/2127) compass module, combines a 3-axis accelerometer and 3-axis magnetometer into a single package
	* ST [L3GD20H](https://www.pololu.com/product/2129) 3-axis gyroscope

![Inertial Sensors](zumo/inertial-sensors.png)
