
// File sumovore.c by Dan Peirce B.Sc.
 
// Kwantlen University College
// apsc1299

// rev. April 30, 2010 to add reliability features (wdt,bor,lvd and stack overflow)
// rev. Nov. 17 2009 to make use of new LED macro's,
//        to incorparate #pragma lines and
//        to point to osc.h in Functions folder
// rev. june 2009 for dynamic braking
// rev. May 22, 2009 to refect changes for BB2
// rev. March 13, 2007
// rev. March 2, 2007
#pragma config WDT = ON      // rev. April 30, 2010 for reliability
                            // reset if the watchdog timer times out
#pragma config WDTPS = 8     // rev. April 30, 2010
#pragma config BOREN = ON // hardware enable BOR 
                            // rev. April 30, 2010
#pragma config BORV = 0   // BOR voltage set between
                          // 4.36 and 4.82
                          // rev. April 30, 2010
#pragma config STVREN = ON  // reset on a stack overflow
                            // rev. April 30, 2010

#pragma config OSC = INTIO67  // allows osc1 (pin 13) and osc2 (pin 14) to be used as inputs
                              // note there is a crystal attached to these pins on the 
                              // brainboard
#pragma config MCLRE = OFF
#pragma config LVP = OFF
// #pragma config lines must come before #include "sumovore.h" as sumovore.h redefines OFF!!!

#include <p18F4525.h>
#include <usart.h>
#include <stdio.h>
#include <adc.h>
#include <pwm.h>
#include <timers.h>
#include <reset.h>
#include "..\Functions\osc.h"
#include "sumovore.h"


void openPORTCforPWM(void);
void openPORTCforUSART(void); 
void openPORTA(void);
void openPORTB(void);
void openPORTD(void);
void openPORTE(void);

void PORtask(void);
void BORtask(void);
void RESETtask(void);
void WDTtask(void);
void STKFULtask(void);
void openLVD(void);

union sensor_union SeeLine = 0;
unsigned int threshold;    // value compared to adc result


void initialization(void)
{
    RCONbits.IPEN = 1;      // rev. April 30, 2010
    INTCONbits.GIEH = 0;    // rev. April 30, 2010
    INTCONbits.GIEL = 0;    // rev. April 30, 2010
    
    set_osc_32MHz();  // to change the internal oscillator frequency (see osc.h osc.c)
    openPORTCforUSART();

    OpenUSART( USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_HIGH,
             16 );            // for 19200 bit per second
                               // (32000000/19200/16)-1 = 103.17
                  // actual buad rate is 32000000/(16*(103+1)) = 19230.8 baud

    openPORTCforPWM();

    openPORTA();
    openPORTB();
    openPORTD(); 
    openPORTE();
    PORTD = 0;  // TURN ALL LED'S OFF
    
    if( isPOR() ) PORtask();        // rev. April 30, 2010
    else if (isBOR() ) BORtask();
    else if(isWDTTO() ) WDTtask();
    else if(STKPTRbits.STKFUL) STKFULtask(); 
    else RESETtask();
     
    openLVD(); 
    
    

    OpenADC(ADC_FOSC_32 & ADC_RIGHT_JUST & ADC_6_TAD , ADC_CH1 & ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS, AN0_AN4);
// AN0-AN4 is defined in sumovore.h the others are defined in adc.h (C18 library) 

    RmotorGoFwd = NO;  // NO is defined as 0b0 in sumovore.h
    RmotorGoFwdCmp = NO;
    LmotorGoFwd = NO;
    LmotorGoFwdCmp = NO;
//  PWMperiod = [(period)+1]x 4 x Tosc x TMR2
//  period	Tosc    	TMR2Pre		pwm_period		freq
//  255	    3.13E-08	16  		5.12E-04		1.95E+03

    OpenTimer2(TIMER_INT_OFF & T2_PS_1_16 & T2_POST_1_1);  // TMR2 prescale is 16
    OpenPWM1(199);           // TPWM = (199+1)*4*(31.25 ns)*16
                             //      = 0.400 ms   or 2500 Hz
    OpenPWM2(199);
    SetDCPWM1(0);            // TDC  = 64*(31.25 ns)*16
                             //      = 0.032 ms
                             //      = 0% * TPWM  (800 will give 100%)
    SetDCPWM2(0);
    threshold = THRESHOLD_DEFAULT; 

}

//***********************************************************************************
//                          openPORTCforUSART()
//***********************************************************************************
void openPORTCforUSART(void)
{
  TRISCbits.TRISC6 = 0;  // set TX (RC6) as output 
  TRISCbits.TRISC7 = 1;  // and RX (RC7) as input
}

//***********************************************************************************
//                          openPORTCforPWM()
//***********************************************************************************
void openPORTCforPWM(void)
{
    TRISCbits.TRISC0 = 0; // Direction Left M
    TRISCbits.TRISC1 = 0; // Enable Left M
    TRISCbits.TRISC2 = 0; // Enable Right M 
    TRISCbits.TRISC3 = 0; // I2C SCL
    TRISCbits.TRISC4 = 0; // I2C SDA
    TRISCbits.TRISC5 = 0; // Direction Right M
    // TRISC6 and TRISC 7 initialized in openPORTCforUSART()
}

//***********************************************************************************
//                          openPORTA()
//***********************************************************************************
void openPORTA(void)
{
    TRISA = 0B11101111; // RA0/AN0, RA1/AN1, RA2/AN2, RA3/AN3, RA5/AN4 SET AS INPUTS
                        // RA4 not used set as output
                        // bits RA6 and RA7 are left as inputs (crystal still attached 
                        //  on sumovore)
}

//***********************************************************************************
//                          openPORTB()
//***********************************************************************************
void openPORTB(void)
{
    TRISB = 0B11000000; // PORTB mostly not used
                        // reserve pins 39 (RB6/PGC) and 40 (RB7/PGD)
                        // as inputs to avoid conflict if ISP and PICkit2
}

//***********************************************************************************
//                          openPORTD()
//***********************************************************************************
void openPORTD(void)
{
    TRISD = 0b01100000; // RD7 not connected
    // RD6 is IR Right, RD5 is IR Left, RD4 is LED5, RD3 is LED4
    // RD2 is LED3, RD1 is LED2 and RD0 is LED1
}

//***********************************************************************************
//                          openPORTE()
//***********************************************************************************
void openPORTE(void)
{
    TRISE = 0b000; // all outputs 
                   // E0 and E1 are now used for motor direction and
                   // dynamic braking
                   // E2 is not used    
}



void set_motor_speed(enum motor_selection the_motor, enum motor_speed_setting motor_speed, int speed_modifier)
{
    const static int motor_speeds[] = { -800, -600, -400, 0, 400, 600, 800};
    int duty_cycle;
    enum e_direction {reverse,forward} dir_modifier= forward;

    duty_cycle = motor_speeds[ motor_speed ] + speed_modifier;
    if ( duty_cycle < 0 ) 
    {
        dir_modifier = reverse;
        duty_cycle = -1 * duty_cycle;
    }
    if ( duty_cycle > 800 ) duty_cycle = 800;

    if (the_motor == left)
    {
        SetDCPWM2((unsigned int) duty_cycle );
        if ( dir_modifier == reverse ) LmotorGoFwd = NO;
        else LmotorGoFwd = YES;
        LmotorGoFwdCmp = !LmotorGoFwd;
    }
    else
    {
        SetDCPWM1((unsigned int) duty_cycle );
        if ( dir_modifier == reverse ) RmotorGoFwd = NO;
        else RmotorGoFwd = YES;
        RmotorGoFwdCmp = !RmotorGoFwd;   
    }
}

void motors_brake_all( void )  // created june 26, 2009
{
    SetDCPWM1(800u ); // enable motors 100% for braking 
    SetDCPWM2(800u ); //
    LmotorGoFwdCmp = NO; // ground all direction lines
    LmotorGoFwd = NO;  // motor terminals will have dead short
    RmotorGoFwdCmp = NO;
    RmotorGoFwd = NO;
 
}

unsigned int adc(unsigned char channel)
{
    SetChanADC( channel );
    ConvertADC();
    while( BusyADC() );

    return ReadADC();    
}

// ****************************************************************
//                          check_sensors
// ****************************************************************
void check_sensors(void)
{
        SeeLine.b.Left = ( adc(RLS_LeftCH0) > threshold );      // adc() prototye in sumovore.h
        SeeLine.b.CntLeft = ( adc(RLS_CntLeftCH1) > threshold );   // adc() code in sumovore.c
        SeeLine.b.Center = ( adc(RLS_CenterCH2) > threshold );    //  ledx turns on when corresponding 
        SeeLine.b.CntRight = ( adc(RLS_CntRightCH3) > threshold );  //    reflective sensore sees a line
        SeeLine.b.Right = ( adc(RLS_RightCH4) > threshold );
}
// ******************************************************************


// ****************************************************************
//                          set_leds
// ****************************************************************
void set_leds(void)
{
        setLED1(SeeLine.b.Left);
        setLED2(SeeLine.b.CntLeft);
        setLED3(SeeLine.b.Center);
        setLED4 (SeeLine.b.CntRight);
        setLED5(SeeLine.b.Right);
}
// ****************************************************************

void PORtask(void)  // rev. April 30, 2010
{
    StatusReset();       // Zero's flags that indicate POR or BOR
                         //  has occured.
    printf("<POR>"); // may modify this to count # of POR    
}    

void BORtask(void)  // rev. April 30, 2010
{
    StatusReset();       // Zero's flags that indicate POR or BOR
                         //  has occured.
    printf("<BOR>"); // may modify this to count # of POR
    while(1) ClrWdt(); //trap here    
}

void WDTtask(void)  // rev. April 30, 2010
{
    printf("<WDT TO>");
    while(1)             // trap code here until POR
    {                    //  may want to change this
                        // to print message and continue
        ClrWdt();  
    }
}

void STKFULtask(void)    // rev. April 30, 2010
{
                           // An error on the hardware stack
    STKPTRbits.STKFUL = 0; //  caused a reset!
    printf("<STKFUL>");    //  continue 
    while(1) ClrWdt();  // trap here     
}    

void RESETtask(void)    // rev. April 30, 2010
{

    printf(" <reset> "); // may modify this to count # of POR    
    while(1) ClrWdt();  // trap here
}   

// this function sets up the low voltage
//  detect feature of the PIC18F4525 
//   sets HLVDIP to a high priority interupt
void openLVD(void)
{
    RCONbits.IPEN = 1;
    HLVDCONbits.HLVDEN = 1; // HLVDEN enabled

    IPR2bits.HLVDIP = 1; // sets HLVD to high priority
    HLVDCONbits.VDIRMAG = 0; // interupt occures if voltage below
                             //  trip point
    HLVDCONbits.HLVDL3 = 1; // set to about 4.59 volts
    HLVDCONbits.HLVDL2 = 1; 
    HLVDCONbits.HLVDL1 = 1;
    HLVDCONbits.HLVDL0 = 0;                                
    PIR2bits.HLVDIF = 0; // ensure interupt is clear                           
    PIE2bits.HLVDIE = 1; // enables HLVD interupt
    INTCONbits.GIEH = 1; // globle enable of interupts
}    

void LVtrap(void)
{
      printf("\\<LVD>");
      while(1)
      {
        ClrWdt(); 
      }  
}
