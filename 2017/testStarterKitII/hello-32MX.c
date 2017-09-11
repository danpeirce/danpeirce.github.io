// Example 3.0
// This example was taken from 
// http://www.eevblog.com/forum/microcontrollers/pic32mx-quickstart/msg113629/#msg113629
// it was tested on Microstick II with a PIC32MX150F128B.
// small modifications were made by Dan Peirce B.Sc. June 2016
//   Sep 8, 2017 added loop back to program so anything typed into PuTTY and
//               received by the PIC32 would be sent back to terminal -- thus
//               testing both Rx and Tx on both PIC32 and on USB to serial 
//               converter.
//               Note that program was able to handle pasting long string into
//               PuTTY (to paste right click mouse in PuTTY window)


#pragma config   FNOSC       = FRCPLL
#pragma config   FPLLIDIV    = DIV_2
#pragma config   FPLLMUL    = MUL_20
#pragma config   FPLLODIV    = DIV_2
#pragma config   FPBDIV       = DIV_1
#pragma config   FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING 
#define GetSystemClock()       (40000000ul)
#define GetPeripheralClock()    (GetSystemClock())


#define BaudRate   115200   // Maximim Rate of PICKit2 UART Tool


#include <plib.h>   // results in xc.h being included!
                    // plib.h will include uart.h which
                    //  will include xc.h
#include <stdio.h>

void main(void) 
{
   SYSTEMConfig(GetSystemClock(), SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    mPORTAClearBits(BIT_0);                 //Clear bits to ensure the LED is off.
    mPORTASetBits  (BIT_1);                 //Clear bits to ensure the LED is off.
    mPORTASetPinsDigitalOut(BIT_0|BIT_1);   //Set port as output

   mPORTBClearBits(BIT_10);   
   mPORTBSetPinsDigitalOut(BIT_10);      // Set PB10(Tx) as output
   mPORTBSetPinsDigitalIn (BIT_11);      // Set PB11(Rx) as input

   PPSUnLock;                        // Allow PIN Mapping 
      PPSOutput(4, RPB10, U2TX);        // MAP Tx to PB10  -- pin 21
      PPSInput (2, U2RX, RPB11);        // MAP Rx to PB11  -- pin 22
   PPSLock;                        // Prevent Accidental Mapping

   // Configure UART2
   int j = 500;
   while(j--);   //Kill time -- short delay avoids com glitch after reset 
   UARTConfigure(UART2, UART_ENABLE_PINS_TX_RX_ONLY); 
   UARTSetLineControl(UART2, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1); 
   UARTSetDataRate(UART2, GetPeripheralClock(), BaudRate); 
   UARTEnable(UART2, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));   

   // Serial_print(Message);

   int seconds=0, minutes=0;
   unsigned int rxchar;
   
   printf("\r\n");
   
    while(1)    
    {
        printf("KPU PHYS1600> %4im %2is\r\n", minutes, seconds);
        j = 3200000;
        mPORTAToggleBits(BIT_0);      //Toggle light status. 
        while(j--)   //Kill time and loop back received characters
        {
            if (DataRdyUART2())
            {
                rxchar = getcUART2();
                putcUART2(rxchar);
                if (rxchar == '\r') putcUART2('\n');
            }
        }                       
        seconds++;
        if (seconds>59)
        {
            seconds = 0;
            minutes++;
        }
    }
}
