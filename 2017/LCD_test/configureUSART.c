//****************************************************************************************
//
// configureUSART.c
//
// Configures the PIC18F4525 serial communication (USART) module for operation
// and set the baud rate (communication speed).
//
// Note. These value are correct only if MCU is operating at 32 MHz. 
//
// Mike Coombes, 25 May 2007
//
//****************************************************************************************
#include <xc.h>
#include <usart.h>       // library containing serial communtication functions
#include <delays.h>      // library containing delays - i.e. wait for time t

void configureUSART(unsigned int baudrate)
{
  unsigned int spbrg;
	
  TRISCbits.TRISC6 = 0;     // set TX (RC6) as output 
  TRISCbits.TRISC7 = 1;     // and RX (RC7) as input

  switch(baudrate)
       {
        case 2400u:     spbrg = 832;
                       break;
        case 4800:     spbrg = 415;
                       break;
        case 19200:    spbrg = 103;
                       break;
        case 38400:    spbrg = 51;
                       break;
        case 57600:    spbrg = 33;
                       break;
        case 115200:   spbrg = 16;
                       break;
        case 500000:   spbrg = 3;
                       break;
        case 1000000:  spbrg = 1;
                       break;
        default:       // 9600 baud
                      spbrg = 207;
                      break;                                
       }

  OpenUSART( USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & 
             USART_CONT_RX & USART_BRGH_HIGH, spbrg );   
  if (baudrate == 2400u) 
  {
      BAUDCONbits.BRG16 = 1;
      TXSTAbits.BRGH = 0;
  }    
  // OpenUSART is part of the C18 usart.h library        
  Delay10KTCYx(1); // small 0.0125 s delay to allow communication speed to stabilize
  // part of the C18 delays.h library
}          
          
