// don't worry about these #pragma directives but include them in every future project
// except those which include sumovore.c
// These are not C statements but directives to the C18 compiler. They result in configuration
// bits in the PIC18F4525 being set in the flash memory. This configuration is set when the 
// PIC is programmed by the PICkit2 programmer and before any program starts to run in the PIC.


#pragma config WDT = OFF
#pragma config OSC = INTIO7      // puts osc/4 on pin 14 to check freq
#pragma config MCLRE = OFF
#pragma config LVP = OFF
#pragma config PBADEN = OFF      // PORTB<4:0> are digital IO 
