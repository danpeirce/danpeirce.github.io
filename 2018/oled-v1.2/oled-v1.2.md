% IIC OLED V1.2
% Notes by Dan Peirce B.Sc.
%

<!---
use pandoc -s --toc -t html5 -c ../../pandocbd.css oled-v1.2.md -o oled-v1.2.html
-->

# IIC OLED V1.2 Notes

The display was purchased from the Canadian version of the RobotShop website:

* [https://www.robotshop.com/ca/en/iic-128-64-oled-module-blue.html](https://www.robotshop.com/ca/en/iic-128-64-oled-module-blue.html)

Unfortunately they don't provide up to date information for the OLED module. The datasheet is for a previous version.
The Libraries supplied for the display are written by Adafruit. 

## Initial Testing of Display

### Wiring

Initial testing was done with an Ardunino Uno as this was what was shown in the datasheet. Note the silkscreen on the v1.2 board does not match
the v1.1 datasheet with regard to the pinout. I followed the silkscreen.

* Pin Vcc to Arduino Uno 5+
* Pin ground to Arduino Uno ground
* cl to Arduino Uno A5
* data to Arduiono Uno A4

No ext4ernal pull ups were added!

### Arduino IDE Setup

1. Downloaded and installed Arduino IDE for windows 7. (used installer for XP and up)

    * [https://www.arduino.cc/en/Main/Software](https://www.arduino.cc/en/Main/Software)

2. Downloaded libraries from elecfreaks site. 

    * [https://elecfreaks.com/estore/download/EF03155-Paintcode.zip](https://elecfreaks.com/estore/download/EF03155-Paintcode.zip)
    * [https://www.elecfreaks.com/estore/iic-oled.html](https://www.elecfreaks.com/estore/iic-oled.html)
	
    The libraries are actually from Adafruit. One can learn more about them here:

    * [https://learn.adafruit.com/monochrome-oled-breakouts/arduino-library-and-examples](https://learn.adafruit.com/monochrome-oled-breakouts/arduino-library-and-examples)

3. Extracted files/folders from zip file.
4. Two folders containing files were copied to c:\\arduino\\libraries

~~~~
  C:\Users\Student\Downloads\EF03155-Paintcode\Code\Arduino_UNO_DEOM\Hardware I2C\Adafruit_GFX
  C:\Users\Student\Downloads\EF03155-Paintcode\Code\Arduino_UNO_DEOM\Hardware I2C\Adafruit_SSD1306
~~~~
	
5. A new example became available in the IDE

    ![](adafruit_ssd1306_example.png)

    The example was copied and pasted into a new sketch.

6. Initially the sketch would not compile. The compiler error indicated that a variable needed to be a constant to be placed in program memory.
   The following line was changed (line appears just after macro definitions near beginning of file).
   
    * *was        --* static unsigned char PROGMEM logo16_glcd_bmp[] =
	* *changed to --* static const unsigned char PROGMEM logo16_glcd_bmp[] =
	
    Once the **const** reserved word was added the sketch compiled.
   
7. The display still remained blank. An I<sup>2</sup>C scanner Arduino sketch was used to find that the board responded to the address **0x3C**. A line in the example was changed 
   to include this address. Once this was done the display showed the example code.
	
    * display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

8. Other modifications were made as I was interested in concentrating on the display of text rather than graphics.

### Demo Video

This was recorded at the end of the day in a rush. I expect to get a better quality video soon -- it looks better
in person. Also I will do some testing of different text sizes.

<iframe width="560" height="315" src="https://www.youtube.com/embed/nSQjUFMyLBs" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>

### Code Used on First Day	

Code moved to new file to avoid clutter on this page.

* [ssd1306_128x64_i2c.ino.html](ssd1306_128x64_i2c.ino.html)

## Switching to Current Adafruit Libraries (May 20, 2018)

It became apparent that the elecfreaks.com site provided an old version of the libraries and it seemed
expedient to test the current version of the files. 