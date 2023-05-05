
<!---
use 
pandoc --metadata pagetitle="PHYS1600 Parts"  -s --toc -t html5 -c ../pandocbd.css phys1600_parts.md -o phys1600_parts.html

-->

# PHYS1600 Parts Main Box

## LEDs, mom Switches, Resistors (shelf)

Note that this shelf is moved to the APSC1299 box for the spring semester.

### RGB LEDs

* [datasheet](http://cdn.sparkfun.com/datasheets/Components/General/YSL-R1047CR4G3BW-F8.pdf)
* [digikey.ca](https://www.digikey.ca/en/products/detail/sparkfun-electronics/COM-11120/5673801)

I have tested the RGB LED and it works nicely.

I used 200 ohm resistors so had about 10 mA for the green and blue and about 15 ma for the red. 
The intensity of this LED is much less than some of the hi efficiency ones we have. It is physically 
arger and frosted white in appearance and the colors are well combined.

One possible issue is the only distinction between the different leads is the lead length and that 
indication would disappear if/when the leads are trimed. One solution might be to mark the underside 
with a blue sharpie and a red sharpie.  At the moment I have a blue sharpie and it appears that the 
white plastic takes the blue quite well. The order of the leads is 

red---common Cathode---green--- blue

Note there is an anode lead for each color.

## Ultrasonic Sensors, Acclelerometers... (shelf)

### IR Sensor - 23

* [datasheet](https://www.onsemi.com/pdf/datasheet/qse159-d.pdf)
* [digikey.ca](https://www.digikey.ca/en/products/detail/onsemi/QSE159/187485?s=N4IgTCBcDaIIoGUCiBGArATgLQDkAiIAugL5A)
* [mouser.ca](https://www.mouser.ca/ProductDetail/onsemi-Fairchild/QSE159?qs=PzUwjIhihRtaYi%252B1q6Eqeg%3D%3D&gclid=Cj0KCQjwr82iBhCuARIsAO0EAZzeTVX80WdByrLldwyaHA-ZI1hhMHG4lRAH-acrE2eZ1GeSL52osf0aAsxnEALw_wcB)

### ADXL335 - Accelerometer, 3 Axis Sensor

* [datasheet Analog Devices](https://www.analog.com/media/en/technical-documentation/data-sheets/ADXL335.pdf)
* [digikey.ca](https://www.digikey.ca/en/products/detail/sparkfun-electronics/SEN-09269/5140809?utm_adgroup=Evaluation%20Boards%20-%20Sensors&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Product_Development%20Boards%2C%20Kits%2C%20Programmers_NEW&utm_term=&productid=5140809&gclid=Cj0KCQjwr82iBhCuARIsAO0EAZzBkcJxeCtOusvQLKyJGVo_n0F11KZxi8es8bdkXn1FImPJarY9HfEaAqLKEALw_wcB)
* this sensor has three analog output. There are newer sensors with more features but Mike was using this as an example of an analog device.

## 12 Button Keypad (shelf)

### twelve button keypads - 11 

* [adafruit site](https://www.adafruit.com/product/419)
* [mouser.ca site](https://www.mouser.ca/ProductDetail/Adafruit/419?qs=GURawfaeGuC%252BBrOA%252BZwq8A%3D%3D)
* [digikey.ca site](https://www.digikey.ca/en/products/detail/adafruit-industries-llc/419/5353596)
	
### Water Pumps with USB A plug

* [https://ca.robotshop.com](https://ca.robotshop.com/products/5v-brushless-portable-submersible-pump)
* used with USB breakout for switching.
	