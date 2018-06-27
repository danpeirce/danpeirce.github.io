/* file diagnostic_timer_box.c

Program written by Dan Peirce B.Sc.
for Kwantlen Polytechnic University

___________________________________________________________

October 3, 2006
  project addapted from echo.c

___________________________________________________________
*/


/* Compile options:  -ml (Large code model) */
/* enabled compiler errors, warnings and messages */
/* also enabled all optimizations except procedural abstraction
If procedural abstraction is enabled the following warning is made during build
WARNING:  The procedural abstraction optimization will not be supported when the demo becomes feature limited.*/ 

#include <p18F4525.h>
#include <usart.h>
#include <stdio.h>

#pragma config WDT = OFF
#pragma config OSC = INTIO7  // puts osc/4 on pin 14 to check freq
#pragma config MCLRE = OFF
#pragma config LVP = OFF

void reopen_osc(void);
void openPORTC(void);
void openPORTD(void);
void show_welcome_msg(void);
unsigned char echo(void);
void red_on(void);
void green_on(void);
void led_off(void);

void main (void)
{
  unsigned char rec_char;
  char flag1=1, flag2=1;

  reopen_osc();  // to change the internal oscillator frequency
  openPORTC();  
  openPORTD();

  OpenUSART( USART_TX_INT_OFF  &
             USART_RX_INT_OFF  &
             USART_ASYNCH_MODE &
             USART_EIGHT_BIT   &
             USART_CONT_RX     &
             USART_BRGH_HIGH,
             103 );                 // for 19200 bit per second
// (32000000/19200/16)-1 = 103.17
// actual buad rate is 32000000/(16*(103+1)) = 19230.8 baud

  show_welcome_msg();

  while(1)
  {
    if(DataRdyUSART()) 
    {
       rec_char = echo();    // task #1
       if(rec_char == 'r' || rec_char == 'R' ) red_on();
       if(rec_char == 'g' || rec_char == 'G' ) green_on();
       if(rec_char == 'f' || rec_char == 'F' ) led_off(); 
    }
    if( flag1 && !PORTCbits.RC2 ) 
    {
       printf("PHOTO GATE 1 blocked\n\r>");
       flag1 = 0;
    }
    if( !flag1 && PORTCbits.RC2 ) 
    {
       printf("PHOTO GATE 1 unblocked\n\r>");
       flag1 = 1;
    }
    if( flag2 && !PORTCbits.RC1 ) 
    {
       printf("PHOTO GATE 2 blocked\n\r>");
       flag2 = 0;
    }
    if( !flag2 && PORTCbits.RC1 ) 
    {
       printf("PHOTO GATE 2 unblocked\n\r>");
       flag2 = 1;
    }
  }
  
}

void red_on(void)
{
  PORTDbits.RD1 = 1;       // leds attached to RD1 and RD2
  PORTDbits.RD2 = 0;
  printf("\r\n>");
}


void green_on(void)
{
  PORTDbits.RD1 = 0;       // leds attached to RD1 and RD2
  PORTDbits.RD2 = 1;
  printf("\r\n>");
}


void led_off(void)
{
  PORTDbits.RD1 = 0;       // leds attached to RD1 and RD2
  PORTDbits.RD2 = 0;
  printf("\r\n>");
}

void reopen_osc(void)
{
  unsigned int i;

  OSCCONbits.IRCF1 = 1;     // setting the OSCILLATOR Control Register
  OSCCONbits.IRCF0 = 1;     //  will reset the interal oscillaror to run
                            //  at 8 MHz rather than at the 1 MHz default
  OSCTUNEbits.PLLEN = 1;     //  Once the internal oscillator is set to 8 MHz
                            //  the PLL can be enabled; this results in an 
                            //  internal oscillator freq 4*8MHz = 32 MHz
// that means the instruction cycle rate and internal timer rate will be at 8 MHz.
  for(i=0;i<500;i++);    // delay to allow clock PLL to lock (stabilize)
                           // (May 30; delay length just arbitrary)
                           // (i<100 is too short)                          
}

void openPORTC(void)
{
  TRISCbits.TRISC2 = 1;    // set CCP1 as an input
  TRISCbits.TRISC1 = 1;    // set CCP2 as an input
  TRISCbits.TRISC6 = 0;    // set TX (RC6) as output 
  TRISCbits.TRISC7 = 1;    // and RX (RC7) as input
}

void openPORTD(void)
{
  PORTDbits.RD1 = 0;       // leds attached to RD1 and RD2
  PORTDbits.RD2 = 0;
  TRISDbits.TRISD2 = 0;
  TRISDbits.TRISD1 = 0;
}

void show_welcome_msg(void)
{
  putrsUSART( "\n\r\n\r**************************************\n\r\n\r" );

  printf("Program:     diagnostic_timer_box.c\n\r");
  printf("By Dan Peirce B.Sc.\n\r");
  printf("For Kwantlen Polytechnic University\n\r");
  printf("date October 3, 2006\n\r\n\r");
  printf("\"r\" to turn on Red LED\n\r");
  printf("\"g\" to turn on Green LED\n\r");
  printf("\"f\" to turn both LED's off\n\r\n\r");
  putrsUSART( "**************************************\n\r\n\r" );
  printf("\r\n>");

}

unsigned char echo(void)
{
    unsigned char result;

    result = getcUSART();
    putcUSART(result);
    if (result == '\r') putcUSART('\n'); // this expands an "enter" to a return + newline
    return result;
}
