
// File sumovore.c by Dan Peirce B.Sc.
 
// Kwantlen University College
// apsc1299

// rev. May 22, 2009 to refect changes for BB2
// rev. March 13, 2007
// rev. March 2, 2007

#include <p18F4525.h>
#include <usart.h>
#include <stdio.h>
#include <adc.h>
#include <pwm.h>
#include <timers.h>
#include "osc.h"
#include "sumovore.h"


void openPORTCforPWM(void);
void openPORTCforUSART(void); 
void openPORTA(void);
void openPORTB(void);
void openPORTD(void);
void openPORTE(void);

union sensor_union SeeLine;
unsigned char SeeLine_filtered[] = {0,0,0,0,0};

void initialization(void)
{
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
    

    OpenADC(ADC_FOSC_32 & ADC_RIGHT_JUST & ADC_6_TAD , ADC_CH1 & ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS, AN0_AN4);
// AN0-AN4 is defined in sumovore_a.h the others are defined in adc.h (C18 library) 

// note that there are four wires from the PIC to the motor driver IC
//    RmotorGoFwd and LmotorGoFwd control the direction of each of the two motors
//    The enables have in the past been used to turn the motors on and off
//    the intent is to start using the PWM module in which case the speed will
//    be set by writing to a register.
    EnableRmotor = NO; // NO is defined as 0b0 in sumovore.h
    EnableLmotor = NO;
    RmotorGoFwd = YES;  // YES is defined as 0b1 in sumovore.h
    LmotorGoFwd = YES;

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
    TRISE = 0b000; // all output and unused
    PORTD =0;
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
