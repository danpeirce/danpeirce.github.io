% IIC OLED V1.2
% Notes by Dan Peirce B.Sc.
%


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

No external pull ups were added!

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

### Documentation of Adafruit Graphics Library

* [https://learn.adafruit.com/adafruit-gfx-graphics-library?view=all](https://learn.adafruit.com/adafruit-gfx-graphics-library?view=all)

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

### Terminal Branch

Added a new branch to fork of Adafruit_SSD1306 called terminal. The intent is to be able to send serial strings to
the Arduino that will act as a controller for the display. The stream of characters could come from any MCU which 
would not need the graphics library ported. Current testing is being done with Arduino serial monitor but will follow up with project MCU.

1. Runs Adafruit splash screen followed by Hello World KPU PHYS1600. It then waits for input and blanks the screen 
   when input received, then shows text in top left of screen. 
2. Display wraps to start of next line if it runs out of room on current line. In addition a newline character will 
   also send the cursor to beginning of next line.
3. If too many rows of text are received new text is not visible.
4. Intercepts a number of ASCII control codes and calls a corresponding library function. The number of codes may 
   be expanded.
5. To facilitate testing a Processing sketch has been written that is capable of both sending regular text and 
   generating the control characters when select non-alphanumeric characters are used.

![](test-oled.png)

~~~~cpp
 display.setRotation(1); // results in a portrait orientation for text on the screen
~~~~
 
* [https://github.com/danpeirce/Adafruit_SSD1306/blob/terminal/examples/explore_text/explore_text.ino](https://github.com/danpeirce/Adafruit_SSD1306/blob/terminal/examples/explore_text/explore_text.ino)

![](rotate-display.png)

### Terminal Branch with SO

Added a new branch with SO (shift out) support. To facilitate multiple SO commands the sketch/program was converted to a state machine structure. This permits the 
ability to add parameters to a command. The set text position command for example requires X and Y coordinates as parameters for setting the cursor position.

![test-oled-so.png](test-oled-so.png)

#### Code for this branch:

* [https://github.com/danpeirce/Adafruit_SSD1306/blob/terminal_so/examples/explore_text/explore_text.ino](https://github.com/danpeirce/Adafruit_SSD1306/blob/terminal_so/examples/explore_text/explore_text.ino)
* [https://github.com/danpeirce/Adafruit_SSD1306/blob/terminal_so/examples/explore_text/sketch_180522a_test_oled/sketch_180522a_test_oled.pde](https://github.com/danpeirce/Adafruit_SSD1306/blob/terminal_so/examples/explore_text/sketch_180522a_test_oled/sketch_180522a_test_oled.pde)

As of the time of this entry (June 6, 2018) The font has been changed to the 9 point Serif font. This font is 
easier to read than the built in font.

* *an image of display with serif font will be added when time permits*.

##### Moving String Literals to Flash

To save RAM space the F() macro is being used with string literals. This conserves RAM. (June 17, 2018)

### Timer Branch

A new branch was added which differs from terminal_so primarily in the look of the start screen.

![](photogateTimer.jpg)

* [https://github.com/danpeirce/Adafruit_SSD1306/blob/timer/examples/explore_text/explore_text.ino](https://github.com/danpeirce/Adafruit_SSD1306/blob/timer/examples/explore_text/explore_text.ino)

The code in the **setup()** function was simplified by breaking out lines responsible for the 
start screen into a separate function. A SO command was added so that this function can be called 
again after the screen is cleared. This refactoring will be merged back into the timer_so branch.

![](test-oled-timer.png) 

### Tic Tac Toe Branch

Tic tac toe branch allows easy setup of Tic Tac Toe screens for play.

![](tictactoe.jpg)

The next image shows the numbered positions corresponding to the nine positions that an X or and O can be placed. 
The numbers are added with the sequence: **"&ts"**

![](tictactoepos.jpg)

The next image shows an example. An X is put in position "1" with the sequence: **"&t1X" enter**
The O is placed with the sequence: **"&t9O"**

![](tictactoeXO.jpg)

Menu items for Tic Tac Toe have been added for testing.

![](test-oled-tictactoe.png) 

#### Code for this branch

* [https://github.com/danpeirce/Adafruit_SSD1306/blob/tictactoe/examples/explore_text/explore_text.ino](https://github.com/danpeirce/Adafruit_SSD1306/blob/tictactoe/examples/explore_text/explore_text.ino)
* [https://github.com/danpeirce/Adafruit_SSD1306/blob/tictactoe/examples/explore_text/sketch_180522a_test_oled/sketch_180522a_test_oled.pde](https://github.com/danpeirce/Adafruit_SSD1306/blob/tictactoe/examples/explore_text/sketch_180522a_test_oled/sketch_180522a_test_oled.pde)

## New Target Pro Trinket 5v

On May 28, 2018 moved testing from Arduino Uno to Adafruit Pro Trinket 5 volts. This board is much like the Uno when combined with a USB to serial adaptor board.
The Arduino IDE sees the combination as the same as a Arduino Uno. The Pro Trinket will shrink the size of the project and reduce cost. The final project will not
need the USB to serial adaptor board attached which will further reduce cost when we make a class set. I will continue to use the USB to serial baord for programming 
and testing only.

* [https://www.digikey.ca/product-detail/en/adafruit-industries-llc/2000/1528-1039-ND/4990788](https://www.digikey.ca/product-detail/en/adafruit-industries-llc/2000/1528-1039-ND/4990788)

![](proTrinket5-oled.jpg)

<!---
use 
  pandoc -s --toc -t html5 -c ../../pandocbd.css oled-v1.2.md -o oled-v1.2.html
  pandoc -t markdown_github -s --toc -o readme.md oled-v1.2.md
-->
