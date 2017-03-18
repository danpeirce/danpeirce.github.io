// ********************************************************************
// this file sumovore.h is for use with the solarbotics sumovore
//   and the PIC18F4525 and microchip 18C compiler 


//  By Dan Peirce B.Sc.
//  For Kwantlen University College
//  rev. May 22, 2009 for brainboard 2
//  some comments revised March 5, 2007
//  rev. March 13, 2007
//  rev. March 2, 2007

// *******************************************************************

#define    LEDs    PORTD
#define    LED1    PORTDbits.RD0    // RD0 is pin 19
#define    LED2    PORTDbits.RD1    // RD1 is pin 20
#define    LED3    PORTDbits.RD2    // RD2 is pin 21
#define    LED4    PORTDbits.RD3    // RD3 is pin 22
#define    LED5    PORTDbits.RD4    // RD4 is pin 27
#define    LeftIR  !PORTDbits.RD5   // RD5 is pin 28 
#define    RightIR !PORTDbits.RD6   // RD6 is pin 29
            // Note that the IR detectors output low when an object
            //     is detected so the not "!" of the pin is used
            //  in the define to maintain positive logic

#define    EnableRmotor  PORTCbits.RC2    // pin_c2  -- Enable Right motor  
#define    EnableLmotor  PORTCbits.RC1    // pin_c1  -- Enable Left motor   
#define    RmotorGoFwd   PORTCbits.RC5    // rev for bb2  -- Right motor forward 
#define    RmotorGoFwdCmp PORTEbits.RE0   // rev for bb2  -- Right motor forward complement
#define    LmotorGoFwd   PORTCbits.RC0    // rev for bb2  -- Left motor forward  
#define    LmotorGoFwdCmp PORTEbits.RE1   // rev for bb2  -- Left motor forward complement

#define    RLS_LeftCH0      ADC_CH0    // AN0  (left reflective line sensor)
#define    RLS_CntLeftCH1   ADC_CH1    // AN1  (center left reflective line sensor)
#define    RLS_CenterCH2    ADC_CH2    // AN2  (center reflective line sensor)
#define    RLS_CntRightCH3  ADC_CH3    // AN3  (center right reflective line sensor)
                    // Pin RA4 No connection 
#define    RLS_RightCH4     ADC_CH4    // AN4  (right reflective line sensor)
                                       // note PortA is only 6 bits!

#define YES       0b1        // used to turn on an individual bit        
#define NO        0b0        // used to turn off an individual bit
#define ON        0b1
#define OFF       0b0

#define AN0_AN4    0B1010  // used for configuration of PCFG3:PCFG0
                           // A/D port Configuration Control Bits
                           // these determine which pins are analog inputs
                           // see page 224 of PIC18F4525 datasheet

struct sensors
{
    unsigned     Left:1;
    unsigned  CntLeft:1;
    unsigned   Center:1;
    unsigned CntRight:1;
    unsigned    Right:1;
    unsigned :3;
};

union sensor_union
{
    unsigned char B;
    struct sensors b;
};

void initialization(void);  // defined in sumovore.c

unsigned int adc(unsigned char channel);  // defined in sumovore.c

enum motor_speed_setting { rev_fast, rev_medium, rev_slow, stop, slow, medium, fast };

enum motor_selection { left, right };

void set_motor_speed(enum motor_selection the_motor, enum motor_speed_setting motor_speed, int speed_modifier);
                 // defined in sumovore.c
void motors_brake_all( void );

extern union sensor_union SeeLine;

