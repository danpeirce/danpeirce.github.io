//***************************************************************************************
// 
// APSC1299 first project. Note SparkFun LCD must be connected to power and the 
// signal lead connected to pin 25 TX on the breadboard.  
// adapted from helloWorld.c Nov. 30, 2010 by Dan Peirce
// helloWorld.c was by
// Mike Coombes, 25 May 2007 
//
//***************************************************************************************
 
#include <stdio.h>          // library containing printf() function
#include <delays.h>
#include "osc.h"            // library for set_osc_32MHz()
#include "configureUSART.h" // library for configureUSART(baud)

void main(void)  // a C project can only have one main() function
{
	
	set_osc_32MHz(); // set MCU to run at 32 MHz
					 // fOSC = 32 000 000 Hz
                     // TOSC = 1/32 000 000 s = 31.25 ns
                     // TCY = 4*TOSC = 125 ns 	
	configureUSART(9600); // configure MCU serial communication module to run at 9600 baud 
                          // defined in configureUSART.c
                          // 9600 is default
                          // other choices 2 400, 4 800, 19 200, 38 400, 57 600, 115 200, 500 000, and 1 000 000  

    //wait for splash screen to finish just over 1 second

    Delay10KTCYx(200); // wait 10 000 * 200 * TCY = 0.250 seconds 
//    printf("%c",0x12); // reset to 9600 bps
    
    Delay10KTCYx(200); // Delay10KTCYx(num), num can only range from 1 to 255 
    Delay10KTCYx(200); 
    Delay10KTCYx(200);     
    Delay10KTCYx(190);  
    Delay10KTCYx(190);  

//    printf("%c%c",0x7C,0x04); // 16 character (w) display  
//    printf("%c%c",0x7C,0x06); // 2 line display  


     printf("%c%c",0xFE,0x01); //Command - clear and zero display                                  
    Delay10KTCYx(200); 
//    printf("%c%c",0x7C,128); // dim backlight to min to save power  
//    printf("%c%c",0x7C,157); // new white on black requires some backlight       
    Delay10KTCYx(190);  
//    Delay10KTCYx(190);                                
 //   printf("%c%c",0xFE,0x09);    // toggle splash screen
 //   printf("%c%c",0xFE,0x0E);    // turn on underline cursor
//   printf("%c%c",0xFE   ,0x0C);    // turn cursor off
                              
    printf("LCD     Kwantlen"); // 16 chars wide to fill top line of LCD
    printf("test    APSC1299");
//    printf("test    APSC129");
 
//    printf("  Sparkfun.com  "); // 16 chars wide to fill top line of LCD
//   printf("  SerLCD v2     "); 
//    printf("%c%c",0x7C,0x0A);
  
       
	while(1)
	   {
		  // MCUs run continuouslly so an endless loop is required.
	   }
}	

