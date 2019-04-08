/* 
file: keyboard_main_Kwantlen.c

to be used with USB_Keyboard.c and Keyboard.h
which can be found in this same folder.
USB_Keyboard.c is adapted from Microchip's Keyboard.c
More details can be seen at the top of the USB_Keyboard.c file.

This file was created on April 28, 2011 by Dan Peirce B.Sc.

*/

#include "keyboard.h"

union modifier_keys_union
{
    struct
    {
        unsigned left_ctrl:1;
        unsigned left_shift:1;
        unsigned left_alt:1;
        unsigned left_gui:1;
        unsigned right_ctrl:1;
        unsigned right_shift:1;
        unsigned right_alt:1;
        unsigned right_gui:1; 
    };
    unsigned char byte;
};

char message[] = "Kwantlen Polytechnic University\n   USB Keyboard emulation\n   by Dan Peirce B.Sc.\n   April 28, 2011\n\n";

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
	static unsigned char HIDoutput= 0;	
	static union modifier_keys_union modifier_keys = 0; 
	static unsigned int msg_position = 0;

	
//State machine
                switch (state)
                {			 
                case 0: 
                    delaycounter++;  
                    if(delaycounter>90000u) //delay allows USB enumeration to complete
                    {
                        delaycounter = 0;
                        state = 3;
                    }
                    break; 
                case 3: 
                          
                    modifier_keys.left_shift = 0;
                            // send a lower case letter
                    if ( (message[msg_position] >= 'a') && (message[msg_position] <= 'z') ) HIDoutput = message[msg_position] - 'a' + 4;
                            // send an upper case letter
                    else if ( (message[msg_position] >= 'A') && (message[msg_position] <= 'Z') )
                    {
                        HIDoutput = message[msg_position] - 'A' + 4;
                        modifier_keys.left_shift = 1;
                    }
                            // send a digit between 1 and 9
                    if ( (message[msg_position] >= '1') && (message[msg_position] <= '9') ) HIDoutput = message[msg_position] - '1' + 30;
                    else if (message[msg_position]== '0') HIDoutput = 39; // send a zero
                    else if (message[msg_position]== 0x20) HIDoutput = 44; // a space results in the keyboard spacebar
                    else if (message[msg_position]== ',') HIDoutput = 54; // a "," results in a keyboard comma
                    else if (message[msg_position]== '.') HIDoutput = 55; // a "." results in a keyboard period
                    else if (message[msg_position]== 0x0A) HIDoutput = 40; // Enter on keyboard if \n newline
                    else if (message[msg_position]== 0x00) HIDoutput = 0;  // if null character message done and key-up
                                      
                    if((HIDTxHandleBusy(lastTransmission) == 0) )  //Can the SIE transmit?
                    {
                        //Load the HID buffer  may put this into a function in next version
                        hid_report_in[0] = modifier_keys.byte;  // used for shift control and alt. ...
                        hid_report_in[1] = 0;          
                        hid_report_in[2] = HIDoutput;  // keycode 1
                        hid_report_in[3] = 0;          // keycode 2...
                        hid_report_in[4] = 0;
                        hid_report_in[5] = 0;
                        hid_report_in[6] = 0;
                        hid_report_in[7] = 0;
                        //Send the 8 byte packet over USB to the host.
                        lastTransmission = HIDTxPacket(HID_EP,(BYTE*)hid_report_in, 0x08);
                        
                        if (HIDoutput == 0) state = 5;   // if null then done so go to end state
                        else 
                        {
                            if (message[msg_position] == message[msg_position+1] ) state = 4; // send key-up
                            msg_position++;             // else go to next character
                        }
                    }
                    
                    break;
                case 4:                                          // case 4 sends a key-up message
                    if((HIDTxHandleBusy(lastTransmission) == 0) )  //Can the SIE transmit?
                    {
                        //Load the HID buffer  may put this into a function in next version
                        hid_report_in[0] = 0;    // used for shift control and alt. ...
                        hid_report_in[1] = 0;          
                        hid_report_in[2] = 0;  // keycode is key-up
                        hid_report_in[3] = 0;          
                        hid_report_in[4] = 0;
                        hid_report_in[5] = 0;
                        hid_report_in[6] = 0;
                        hid_report_in[7] = 0;
                        //Send the 8 byte packet over USB to the host.
                        lastTransmission = HIDTxPacket(HID_EP,(BYTE*)hid_report_in, 0x08);
                        
                        state = 3;
                    }
                    
                    break;                    
                case 5:
                               // does nothing at all (all done!)
                    break;

                 default: 
                    state = 0;
                    break;
                 }	
	
}

