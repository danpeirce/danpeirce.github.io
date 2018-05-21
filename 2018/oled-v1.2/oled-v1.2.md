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

![](explore_text.png)

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

It worked with a minor adjustment for the electfreak display.

### Adjustments for 3rd Party Display.

1. As before the address of the display had to be adjusted.

    *  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // was 0x3D
	
2. Had to make a change to Adafruit_SSD1306.had

    At line 73 changed which line was commented out.
	
~~~~c
   #define SSD1306_128_64
//   #define SSD1306_128_32
//   #define SSD1306_96_16
~~~~

### Forked on Github

I forked the project on Github and made a new branch called 3rdparty.

* [https://github.com/danpeirce/Adafruit_SSD1306/tree/3rdparty](https://github.com/danpeirce/Adafruit_SSD1306/tree/3rdparty)
* [https://github.com/adafruit/Adafruit_SSD1306/compare/master...danpeirce:3rdparty](https://github.com/adafruit/Adafruit_SSD1306/compare/master...danpeirce:3rdparty)

### Explore Text Branch

Added a new branch to fork of Adafruit_SSD1306 repository Called exploring_text.

* [https://github.com/danpeirce/Adafruit_SSD1306/blob/explore_text/examples/explore_text/explore_text.ino](https://github.com/danpeirce/Adafruit_SSD1306/blob/explore_text/examples/explore_text/explore_text.ino)

![](explore_text.png)