
<!---
use 
pandoc --metadata pagetitle="PHYS1600 Parts"  -s --toc -t html5 -c ../pandocbd.css phys1600_parts.md -o phys1600_parts.html
   to create HTML5 page.
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
(AKA 10,000 pf, 0.01 μF and 103)  -- also [located on a different shelf](#ceramic-capacitor-0.01-μf)

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

Has been used for optical 9600 bps serial data link. Has also been used in photogate like applications.

Used with the [IR emitter](#ir-emitter) listed as the next item.

* [datasheet](https://www.onsemi.com/pdf/datasheet/qse159-d.pdf)
    * Open collector output! 
	* Use with external pullup resistor!
    * Binary logic output
	* Schmitt trigger built in
* [digikey.ca](https://www.digikey.ca/en/products/detail/onsemi/QSE159/187485?s=N4IgTCBcDaIIoGUCiBGArATgLQDkAiIAugL5A)
* [mouser.ca](https://www.mouser.ca/ProductDetail/onsemi-Fairchild/QSE159?qs=PzUwjIhihRtaYi%252B1q6Eqeg%3D%3D&gclid=Cj0KCQjwr82iBhCuARIsAO0EAZzeTVX80WdByrLldwyaHA-ZI1hhMHG4lRAH-acrE2eZ1GeSL52osf0aAsxnEALw_wcB)

### IR Emitter

Has been used for optical 9600 bps serial data link. Has also been used in photogate like applications.
This part has a side facing lens like the sensor. It is easy to set up to work with the sensor as both have the same dimensions and side facing lenses.

Used with the [IR sensor](#ir-sensor---23) listed as the previous item

* [datasheet](https://media.digikey.com/pdf/Data%20Sheets/ON%20Semiconductor%20PDFs/QEE122_123.pdf)
* [digikey.ca](https://www.digikey.ca/en/products/detail/onsemi/QEE123/187428)

### IR Emitter - higher intensity

This IR emitter has a smaller emission angle than the one listed above. It also has a higher maximum current rating. 
We use this one to make a custom photogate.

* [datasheet](https://www.onsemi.com/pdf/datasheet/qed123-d.pdf)
* [mouser](https://www.mouser.ca/ProductDetail/onsemi-Fairchild/QED123)

### ADXL335 - Accelerometer, 3 Axis Sensor

* [sparkfun breakout board](https://www.sparkfun.com/products/9269)
* [datasheet Analog Devices](https://www.analog.com/media/en/technical-documentation/data-sheets/ADXL335.pdf)
* [digikey.ca](https://www.digikey.ca/en/products/detail/sparkfun-electronics/SEN-09269/5140809?utm_adgroup=Evaluation%20Boards%20-%20Sensors&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Product_Development%20Boards%2C%20Kits%2C%20Programmers_NEW&utm_term=&productid=5140809&gclid=Cj0KCQjwr82iBhCuARIsAO0EAZzBkcJxeCtOusvQLKyJGVo_n0F11KZxi8es8bdkXn1FImPJarY9HfEaAqLKEALw_wcB)
* this sensor has three analog output. There are newer sensors with more features but Mike was using this as an example of an analog device.

### Grove Ultrasonic Distance Sensor

* [Seeed 101020010 ](https://www.seeedstudio.com/Grove-Ultrasonic-Distance-Sensor.html)
* [digikey.ca 1597-1122-ND](https://www.digikey.ca/en/products/detail/seeed-technology-co-ltd/101020010/5482600)
* [mouser 713-101020010](https://www.mouser.ca/ProductDetail/Seeed-Studio/101020010?qs=1%252B9yuXKSi8D6aN06jq6dCQ%3D%3D)

* [custom braket designed to be used with sensor](https://github.com/danpeirce/us-sensor)

### LV-MaxSonar-EZ1

These are expensive. In recent years we have generally used the [Grove Ultrasonic Distance Sensor](#grove-ultrasonic-distance-sensor) instead!

* [datasheet](https://maxbotix.com/pages/lv-maxsonar-ez-datasheet)
* [abra-electronics.com](https://abra-electronics.com/sensors/sensors-maxbotix/mb1010-ultrasonic-range-finder-lv-maxsonar-ez1-mb1010.html)

### Bright Yellow 50mA LED

This part was used in PHYS1220 take home kits for an IV curve lab during the pandemic. I have put the extras here in case they are useful at some point.

* static sensitive according to datasheet!

* [datasheet](https://www.ttelectronics.com/TTElectronics/media/ProductFiles/Datasheet/OVLL.pdf)
* [digikey.ca](https://www.digikey.ca/en/products/detail/tt-electronics-optek-technology/OVLLY8C7/827140)

### 8MHz crystal Oscillator 5v

With the PIC MCU we generally used the internal oscillator (with phase locked loop multiplier) most of the time. The students also used an 
external oscillator for particular projects when the added stability was wanted. This is not likely to be used with the Arduino Nano as that board 
has an on board crystal and does not offer other clock options.

* [datasheet MXO45HS-3C-8M000000](https://www.ctscorp.com/wp-content/uploads/MXO45_MXO45HS.pdf)
    * Note that it is recommended to put a 0.01 µF capacitor as close as possible to the Vcc and gnd pins.
* [digikey.ca](https://www.digikey.ca/en/products/detail/cts-frequency-controls/MXO45HS-3C-8M000000/1801858)

### 8MHz crystal Oscillator 3.3v

With the PIC MCU we generally used the internal oscillator (with phase locked loop multiplier) most of the time. The students also used an 
external oscillator for particular projects when the added stability was wanted. This is not likely to be used with the Arduino Nano as that board 
has an on board crystal and does not offer other clock options.

There were a number of years where we used a 3.3 volt PIC board rather than a 5 volt board. That is why we have a small old stock of 3.3 volt oscillators.

* [datasheet ACHL-8.000MHZ-EK](https://abracon.com/Oscillators/ACHL.pdf)
* [digikey.ca](https://www.digikey.ca/en/products/detail/abracon-llc/ACHL-8-000MHZ-EK/675397)

### Ceramic Capacitor 0.01 μF

General Purpose, 20%, multilayer, Radial
Here generally used for decoupling
(AKA 10,000 pf, 10 nF and 103)

Historically located by the oscilators for convenience. I also have [these on another tray](#ceramic-capacitor-10-nf).

* [Datasheet](https://www.vishay.com/docs/45171/kseries.pdf)
* [digikey.ca](https://www.digikey.ca/en/products/detail/vishay-beyschlag-draloric-bc-components/K103M15X7RF53H6/2824341)

### TTLy FTDI USB to serial

A USB to serial addaptor that can be set to work at either 3.3 or 5 volts. 

* the default is 5 volts. To change to 3.3 one must cut a small trace and add a solder bump. 

**Warning** -- there is at least one of these boards set to 3.3 volts.

* [solarbotics.com](https://www.solarbotics.com/product/39240/)
* [ca.robotshop.com](https://ca.robotshop.com/products/ttlyftdi-usb-to-ttl-cable-adapter)

### Grove 4PIN MALE Jumpers to connector 5PACK

Breaks out the Grove 4 pin connector to pins suitable for a breadboard.
Total length is about 20 cm. 

We use as a replacment cable for items that come with a grove cable having a grove connector on both ends.

Examples:

* Grove I²C LCD
* MSTACK devices like the Mini Keyboard

* [digikey.ca](https://www.digikey.ca/en/products/detail/seeed-technology-co.,-ltd/110990210/5482570)

### M5Stack CardKB Mini Keyboard

*[ca.robotshop.com](https://ca.robotshop.com/products/m5stack-cardkb-mini-keyboard-programmable-unit-v11-mega8a)

## 12 Button Keypad (shelf)

### twelve button keypads - 11 

* [adafruit site](https://www.adafruit.com/product/419)
* [mouser.ca site](https://www.mouser.ca/ProductDetail/Adafruit/419?qs=GURawfaeGuC%252BBrOA%252BZwq8A%3D%3D)
* [digikey.ca site](https://www.digikey.ca/en/products/detail/adafruit-industries-llc/419/5353596)
	
### Water Pumps with USB A plug

Since this item has a USB A plug but one will want to switch it on and off with the MCU board it is suggested that the student also use 
[USB breakout socket](#usb-a-socket-breakout) with this device.

* [https://ca.robotshop.com](https://ca.robotshop.com/products/5v-brushless-portable-submersible-pump)
* used with USB breakout for switching.
	
## USB-C to USB-A Socket (side bin)

### USB-C to USB-A Socket Adaptor

Some **laptops** lack USB-A sockets and have only USB-C sockets. These adaptors will allow one to plug a USB-A plug 
into one of these computers and is USB 3.1 conpatable.

The following is simular if not exactly the same as the ones in the bin.

* [datasheet](https://www.digikey.ca/en/products/detail/tripp-lite/U428-000-F/7243253)
* [digikey.ca](https://assets.tripplite.com/product-pdfs/en/u428000f.pdf)

### USB MicroB socket to USB-C plug Adaptor

Some devices arrive with a USB-C socket but we have far more USB microB cables than USB-C cables. 
This adaptor allows one to use a USB MicroB cable with a USB-C device. In many cases this works fine as the device often actually only supports USB 2 anyway.

Note that USB-C cables are more versitile but also more expensive.

* [datasheet](https://media.digikey.com/pdf/Data%20Sheets/CNC%20Tech%20PDFs/1005-1092-WH.pdf)
* [digikey.ca](https://www.digikey.ca/en/products/detail/cnc-tech/1005-1092-WH/8747889)

### USB A socket breakout

For possible use with [water pump](#water-pumps-with-usb-a-plug) that uses a USB A plug. In that case a project would be done in which the MCU would need to
be able to switch the water pump on and off.

There are a number of other USB breakout boards in the bin. I am moving on to other parts for now.

### USB hub

Some students have laptops that don't have enough USB ports.

### USB to SD card reader

Not frequently used in PHYS1600 but on ocasion someone has needed a card reader to transfer files from a laptop to a desktop.	