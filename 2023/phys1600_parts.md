
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

### Bi-Color LEDs

* [datasheet](https://www.sunledusa.com/products/spec/XLUGR58M.pdf)
* [digikey.ca](https://www.digikey.ca/en/products/detail/sunled/XLUGR58M/4745841)

Newer stock from digikey. The advantage is availabilty and quick delivery. Also previous vendor did not provide datasheet.

### Ceramic Capacitor 10 nF

General Purpose, 20%, multilayer, Radial
Here generally used for decoupling
(AKA 10,000 pf, 0.01 μF and 103)

* [Datasheet](https://www.vishay.com/docs/45171/kseries.pdf)
* [digikey.ca](https://www.digikey.ca/en/products/detail/vishay-beyschlag-draloric-bc-components/K103M15X7RF53H6/2824341)

### Tacktile Switch (mom)

A breadboard friendly, two lead, momentary, normally open tacktile switch.

* [datasheet](https://sten-eswitch-13110800-production.s3.amazonaws.com/system/asset/product_line/data_sheet/184/TL59-TL58.pdf)
* [digikey.ca](https://www.digikey.ca/en/products/detail/e-switch/TL59FF160Q/1767493)

### Amber LED

[datasheet](https://media.digikey.com/pdf/Data%20Sheets/CREE%20Power/C556D-RFx,GFx,BFx,AFx.pdf)
[digikey.ca](https://www.digikey.ca/en/products/detail/creeled-inc/C566D-AFE-CV0X0251/4793716)

With these oval LEDs the part ordered in the past may not have always been the same.

### Red LED

* [datasheet](https://assets.cree-led.com/a/ds/h/HB-C5SMF-RJF-RJE-GJF-GJE-BJF-BJE.pdf)
* [digikey.ca](https://www.digikey.ca/en/products/detail/creeled-inc/C5SMF-RJF-CT0W0BB2/4794052)

### Green LED

* [datasheet](https://media.digikey.com/pdf/Data%20Sheets/CREE%20Power/C5SME-RJx,C5SMF-RJx,GJx,BJx.pdf)
* [digikey.ca](https://www.digikey.ca/en/products/detail/creeled-inc/C5SMF-GJS-CV0Y0792/1987463?s=N4IgTCBcDaIMIFYDKBZAYgcQFJILQAI4A1ABgE0SB2ATjDgBVcA5AERAF0BfIA)


### Blue LED

* [datasheet](https://media.digikey.com/PDF/Data%20Sheets/Everlight%20PDFs/5484BN_BADC_AGJA_X_MS.pdf)
* [digikey.ca](https://www.digikey.ca/en/products/detail/everlight-electronics-co-ltd/5484BN-BADC-AGJA-PR-MS/4950440?s=N4IgTCBcDaIIwAYAcCC0i4FZ2oHIBEQBdAXyA)

### 470 Ω Resistors

1/4 watt, 5% and through hole.

### 10 KΩ Resistors

1/4 watt, 5% and through hole.

### 200 Ω Resistors

1/4 watt, 5% and through hole.

## Ultrasonic Sensors, Acclelerometers... (shelf)

### IR Sensor - 23

* [datasheet](https://www.onsemi.com/pdf/datasheet/qse159-d.pdf)
* [digikey.ca](https://www.digikey.ca/en/products/detail/onsemi/QSE159/187485?s=N4IgTCBcDaIIoGUCiBGArATgLQDkAiIAugL5A)
* [mouser.ca](https://www.mouser.ca/ProductDetail/onsemi-Fairchild/QSE159?qs=PzUwjIhihRtaYi%252B1q6Eqeg%3D%3D&gclid=Cj0KCQjwr82iBhCuARIsAO0EAZzeTVX80WdByrLldwyaHA-ZI1hhMHG4lRAH-acrE2eZ1GeSL52osf0aAsxnEALw_wcB)

### ADXL335 - Accelerometer, 3 Axis Sensor

* [datasheet Analog Devices](https://www.analog.com/media/en/technical-documentation/data-sheets/ADXL335.pdf)
* [digikey.ca](https://www.digikey.ca/en/products/detail/sparkfun-electronics/SEN-09269/5140809?utm_adgroup=Evaluation%20Boards%20-%20Sensors&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Product_Development%20Boards%2C%20Kits%2C%20Programmers_NEW&utm_term=&productid=5140809&gclid=Cj0KCQjwr82iBhCuARIsAO0EAZzBkcJxeCtOusvQLKyJGVo_n0F11KZxi8es8bdkXn1FImPJarY9HfEaAqLKEALw_wcB)
* this sensor has three analog output. There are newer sensors with more features but Mike was using this as an example of an analog device.

### Grove Ultrasonic Distance Sensor

* [Seeed 101020010 ](https://www.seeedstudio.com/Grove-Ultrasonic-Distance-Sensor.html)
* [digikey.ca 1597-1122-ND](https://www.digikey.ca/en/products/detail/seeed-technology-co-ltd/101020010/5482600)
* [mouser 713-101020010](https://www.mouser.ca/ProductDetail/Seeed-Studio/101020010?qs=1%252B9yuXKSi8D6aN06jq6dCQ%3D%3D)

* [custom braket designed to be used with sensor](https://github.com/danpeirce/us-sensor)

## 12 Button Keypad (shelf)

### twelve button keypads - 11 

* [adafruit site](https://www.adafruit.com/product/419)
* [mouser.ca site](https://www.mouser.ca/ProductDetail/Adafruit/419?qs=GURawfaeGuC%252BBrOA%252BZwq8A%3D%3D)
* [digikey.ca site](https://www.digikey.ca/en/products/detail/adafruit-industries-llc/419/5353596)
	
### Water Pumps with USB A plug

* [https://ca.robotshop.com](https://ca.robotshop.com/products/5v-brushless-portable-submersible-pump)
* used with USB breakout for switching.
	