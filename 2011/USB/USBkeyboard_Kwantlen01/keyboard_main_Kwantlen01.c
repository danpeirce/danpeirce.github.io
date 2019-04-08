/* 
file: keyboard_main_Kwantlen01.c

to be used with USB_Keyboard01.c and Keyboard.h
which can be found in this same folder.
USB_Keyboard01.c is adapted from Microchip's Keyboard.c
More details can be seen at the top of the USB_Keyboard.c file.

This file was created on April 29, 2011 by Dan Peirce B.Sc.

*/

#include "keyboard01.h"

void process_next_character(void);

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

static char message[] = "Kwantlen Polytechnic University\n   USB Keyboard emulation\n   by Dan Peirce B.Sc.\n   April 29, 2011\n\n";
static unsigned int msg_position = 0;
static union modifier_keys_union modifier_keys = 0;
static unsigned char keycode = 0;

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
	
//State machine
                switch (state)
                {			 
                case 0: 
                    delaycounter++;  
                    if(delaycounter>90000u) //delay allows USB enumeration to complete
                    {
                        delaycounter = 0;
                        state = 3;
                                                // set defaults for Keyboard Input Report
                        MODIFIER_KEYS_ENT = 0;  // used for shift control and alt. ...
                        RESERVED_ENT = 0;          
                        KEYCODE1_ENT = 0;  // Used for most keys
                        KEYCODE2_ENT = 0;  // only used for keys that send mult codes...
                        KEYCODE3_ENT = 0;
                        KEYCODE4_ENT = 0;
                        KEYCODE5_ENT = 0;
                        KEYCODE6_ENT = 0;
                    }
                    break; 
                case 3: 
               
                    if(SIE_TX_READY() )  //Can the SIE transmit?
                    {
                        process_next_character();  // converts ASCII character from message[] to keyboard codes
                                                  //Load the HID buffer  
                        MODIFIER_KEYS_ENT = modifier_keys.byte;  // used for shift control and alt. ...                                  
                        KEYCODE1_ENT = keycode;  // keycode 1 set & others left at default              
                        SEND_HID_REPORT();        //Send the 8 byte packet over USB to the host.
                        
                        if (keycode == 0) state = 5;   // if null then done so go to end state
                        else 
                        {
                            if (message[msg_position] == message[msg_position+1] ) state = 4; // send key-up
                            msg_position++;             // else go to next character
                        }
                    }
                    
                    break;
                case 4:                                          // case 4 sends a key-up message
                    if( SIE_TX_READY() )  //Can the SIE transmit?
                    {
                                                //Load the HID buffer  
                        MODIFIER_KEYS_ENT = 0;  // used for shift control and alt. ...
                        RESERVED_ENT = 0;          
                        KEYCODE1_ENT = 0;  // keycode 1
                        KEYCODE2_ENT = 0;          // keycode 2...
                        KEYCODE3_ENT = 0;
                        KEYCODE4_ENT = 0;
                        KEYCODE5_ENT = 0;
                        KEYCODE6_ENT = 0;
                        SEND_HID_REPORT();  //Send the 8 byte packet over USB to the host.
                        
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

void process_next_character(void)
{
    modifier_keys.left_shift = 0;
            // send a lower case letter
    if ( (message[msg_position] >= 'a') && (message[msg_position] <= 'z') ) keycode = message[msg_position] - 'a' + 4;
            // send an upper case letter
    else if ( (message[msg_position] >= 'A') && (message[msg_position] <= 'Z') )
    {
        keycode = message[msg_position] - 'A' + 4;
        modifier_keys.left_shift = 1;                // is a capital letter so use shift
    }
            // send a digit between 1 and 9
    if ( (message[msg_position] >= '1') && (message[msg_position] <= '9') ) keycode = message[msg_position] - '1' + 30;
    else if (message[msg_position]== '0')  keycode = 39; // send a zero
    else if (message[msg_position]== 0x20) keycode = 44; // a space results in the keyboard spacebar
    else if (message[msg_position]== ',')  keycode = 54; // a "," results in a keyboard comma
    else if (message[msg_position]== '.')  keycode = 55; // a "." results in a keyboard period
    else if (message[msg_position]== 0x0A) keycode = 40; // Enter on keyboard if \n newline
    else if (message[msg_position]== 0x00) keycode = 0;  // if null character message done and key-up
}
