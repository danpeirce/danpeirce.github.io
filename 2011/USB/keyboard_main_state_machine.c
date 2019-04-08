/* 
file: keyboard_main_state_machine.c
to be used with USB_Keyboard.c and Keyboard.h
which can be found in this same folder.
USB_Keyboard.c is adapted from Microchip's Keyboard.c
More details can be seen at the top of the USB_Keyboard.c file
which is located in this same folder.

The state machine in this file as been substantially changed from 
the original example written by Microchip can be found on page 26 of 
the Low Pin Count USB Development Kit User's Guide. 
see http://ww1.microchip.com/downloads/en/DeviceDoc/41356B.pdf

This file was created on April 27, 2011 by Dan Peirce
Last modified            April 28, 2011
*/

#include "keyboard.h"

void main(void)
{
    InitializeSystem();

    while(1)           // simple cooperative multitasking task loop
    {
        USBDeviceTasks(); 
        ProcessIO();  // defined in USB_keyboard.c -- calls some USB functions and Keyboard()      
    }
}

void Keyboard(void)
{
	static unsigned char state = 0;	
	static unsigned long delaycounter = 0;	
	static unsigned char HIDoutput;	
	static unsigned char HIDoutputLast=5; // added april 25, 2011
	
//State machine
                switch (state)
                {			 
                case 0: 
                    delaycounter++;  
                    if(delaycounter>90u)
                    {
                        delaycounter = 0;
                        state = 1;
                    }
                    break;
                case 1: 
                    ADCON0bits.GO_DONE = 1; //Start an ADC conversion
                    state = 2;
                    break;
                case 2: 
                    if(ADCON0bits.GO_DONE == 0) //Check if conversion is completed
                    {
                        state = 3;
                    }
                    break; 
                case 3: 
                    HIDoutput = ADRESH>>3;      //shift the result in ADRESH
                    //left by three
                    if(HIDoutput<=4u) HIDoutput = 4;    // scan code 4 (dec) on a USB keyboard is an "a" or "A"
                    if(HIDoutput>=29u) HIDoutput = 29;  // scan code 24 (dec) on a USB keyboard is an "z" or "Z"
                    
                    //Can the SIE transmit?
                    if((HIDTxHandleBusy(lastTransmission) == 0) )
                    {
                        if( HIDoutput != HIDoutputLast )  // only send character if different from last time!
                        {
                            //Load the HID buffer  may put this into a function in next version
                            hid_report_in[0] = 0;
                            hid_report_in[1] = 0;          // used for shift control and alt. ...
                            hid_report_in[2] = HIDoutput;  // first other key
                            hid_report_in[3] = 0;          // second other key...
                            hid_report_in[4] = 0;
                            hid_report_in[5] = 0;
                            hid_report_in[6] = 0;
                            hid_report_in[7] = 0;
                            //Send the 8 byte packet over USB to the host.
                            lastTransmission = HIDTxPacket(HID_EP,(BYTE*)hid_report_in, 0x08);
                            HIDoutputLast = HIDoutput;
                        }
                        state = 4;
                    }
                    
                    break;
                case 4:
                    if((HIDTxHandleBusy(lastTransmission) == 0) )
                    {
                        
                        {
                            HIDoutput = 0;
                            //Load the HID buffer
                            hid_report_in[0] = 0;
                            hid_report_in[1] = 0;
                            hid_report_in[2] = HIDoutput; // since HIDoutput was set to zero
                            hid_report_in[3] = 0;         //  this gives an indication of 
                            hid_report_in[4] = 0;         //  key up. This avoids
                            hid_report_in[5] = 0;         //  possible repeate key function
                            hid_report_in[6] = 0;         //  in the PC connected to USB
                            hid_report_in[7] = 0;
                            //Send the 8 byte packet over USB to the host.
                            lastTransmission = HIDTxPacket(HID_EP,(BYTE*)hid_report_in, 0x08);
                        }
                        state = 0;
                    }
                    break;
                 default: 
                    state = 0;
                    break;
                 }	
	
}

