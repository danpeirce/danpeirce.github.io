% Pololu3pi.c Details
% By Dan Peirce B.Sc.

<!---
use 
pandoc -s --toc -t html5 -c ../../pandocbd.css pololu3pi.c-details.pandoc.md -o pololu3pi.c-details.html

pandoc -s --toc -t gfm pololu3pi.c-details.pandoc.md -o pololu3pi.c-details.md
-->

# Pololu3pi.c Details

## menu 

* This function is called after initialization of PIC peripherals regardless of **Roam** or **No Roam** mode.
* This function is also called in No Roam mode when from the menu using the **Esc** key.

~~~~c 
void menu(void)
{
    printf(" \r\n");
    printf("\r\n\n\n\n\n\n\n\n");   
               // this should clear the terminal screen mostly
                       // otherwise may display junk from power cycle
    printf("\tKPU APSC1299 3pi-menu-basic3\n\n\r");
    printf("\t\t  Menu\n\r");
    printf("\t\t--------\r\n");  
    printf("\t\t@. Pololu Signature?\r\n"); 
    printf("\t\t1. Display mV reading\r\n"); // sent to PuTTY only
    printf("\t\t2. Display mV reading in LCD\r\n");  // also send to LCD
    printf("\t\tc. Clear LCD\r\n");
    printf("\t   ctrl+s. Print Sensor Values\r\n");
    printf("\t\t-. Send hyphen to LCD\r\n");
    printf("\t\t~. LCD message APSC1299\r\n");
    printf("\t\treturn. LCD go to start of line two\r\n");
    printf("\t\t<, robot spin left\r\n");
    printf("\t\t>, robot spin right\r\n");
    printf("\t\t|, robot stop\r\n");
    printf("\t     Esc, Print Menu\r\n");
    printf("\t\t--------\r\n\n");
}
~~~~


## print_sensors

* This function only used in **No Roam** mode and is called as a menu item
* ~~Calibrates sensors~~
* Reads sensors and prints normalized values for each to virtual COM port.
* ~~prints timer3 value~~
* possible future changes
	* currently prints new values over old. may change so new values go on new line
	* may change so it prints only one set of values and returns
* calibrate() has been commented out. It was found that calibrate works more consistently when 
  done in Roam mode with no USB cable. The following steps can be used to get sensor readings:
    * Turn robot on in Roam mode
	* Pick the robot up after calibration is complete
	* Move slide switch to No Roam position
	* Attach USB cable
	* Open terminal program
	* Select sensor readings with **Ctrl+s**

~~~~c
void print_sensors(void)
{
    unsigned int * sensorvalues;
    // calibrate();
    while(1)
    {
        sensorvalues = readsensors();
        // __delay_ms(80);
        printf("\rsensor values = %4u, ", *sensorvalues);
        printf("%4u, ", *(sensorvalues+1));
        printf("%4u, ", *(sensorvalues+2));
        printf("%4u, ", *(sensorvalues+3));
        printf("%4u", *(sensorvalues+4));
        //printf(" | Timer Value = %5u",TMR3_ReadTimer());
    }
    
}
~~~~

## forward 

* This function only used in **Roam** mode

~~~~c
void forward(unsigned char speed)
{
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xC1);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(speed);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xC5);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(speed);
}
~~~~

## backward 

* This function only used in **Roam** mode

~~~~c 
void backward(unsigned char speed)
{
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xC2);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(speed);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xC6);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(speed);
}
~~~~

## spinleft

* This function only used in **Roam** mode

~~~~c 
void spinleft(unsigned char speed)
{
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xC2);      // left motor backwards
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(speed);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xC5);     // right motor forward
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(speed);
}
~~~~

## spinright

* This function only used in **Roam** mode

~~~~c 
void spinright(unsigned char speed)
{
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xC1);      // left motor forward
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(speed);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xC6);     // right motor backward
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(speed);
}
~~~~

## readbatteryvoltage

* This function used after menu displayed and as a menu item.
* Sends battery voltage to virtual COM port and returns value

~~~~c
unsigned int readbatteryvoltage(void)
{
    unsigned char lbyte, ubyte;
    
    printf("\r\n\tBattery Voltage = ");
    
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xB1);
    while (!UART1_is_rx_ready()) continue;
    lbyte = UART1_Read();
    while (!UART1_is_rx_ready()) continue;
    ubyte = UART1_Read();
    printf("%d mV\r\n", ubyte*256 + lbyte);
    return (unsigned int)(ubyte*256 + lbyte);
}
~~~~ 

## readsensors 

* Returns pointer to array of sensor values.

~~~~c 
unsigned int* readsensors(void)
{
    unsigned char lbyte[5], ubyte[5], i;
    static unsigned int values[5];
    
    // printf("\r\n\tSensor Readings =  ");
    
    while(!UART1_is_tx_ready()) continue;
    test2_PORT = 1;
    UART1_Write(0x87);
    for (i=0;i<5;i++)
    {
        while (!UART1_is_rx_ready()) continue;
        lbyte[i] = UART1_Read();
        while (!UART1_is_rx_ready()) continue;
        ubyte[i] = UART1_Read();
        values[i] = ubyte[i]*256 + lbyte[i];
    }
    test2_PORT = 0;

    return values;
}
~~~~ 

## sendbatteryvoltage 

* Calls readbatteryvoltage, prints returned values to LCD.

~~~~c
// sends battery voltage to LCD
void sendbatteryvoltage(void)
{
    unsigned int voltage;
    char bat_volt[9];
    unsigned char msg_length, i=0;
    
    voltage = readbatteryvoltage();
    msg_length = sprintf(bat_volt, "%u mV", voltage);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xB8);   // print LCD command to slave
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(msg_length);     // send eight characters
    while (i<msg_length)
    {
        if(UART1_is_tx_ready())
        {
            UART1_Write(bat_volt[i]);
            i++;
        }
    }
    
}
~~~~

## sendchar 

* Sends a single character to the LCD.

~~~~c 
void sendchar(char a_char)
{
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xB8);   // print LCD command to slave
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(1);     // send one character
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(a_char);     // send one character
}
~~~~

## clearLCD 

* Clears the LCD and moves cursor to row zero column zero

~~~~c 
void clearLCD(void)
{
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xB7);   // clear LCD
}
~~~~

## LCD_print

* Prints a string to the LCD.

~~~~c
void LCD_print(char *str, char length)
{
    char i=0;
    
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xB8);   // print LCD command to slave
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(length);     // send eight characters
    while (i<length)
    {
        if(UART1_is_tx_ready())
        {
            UART1_Write(str[i]);
            i++;
        }
    }
}
~~~~

## LCD_line2

* Moves the LCD cursor to the beginning of the second row (row 1).

~~~~c 
void LCD_line2(void)
{
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xB9);   // goto LCD position
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0x00);   // column 0
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0x01);   // row 1
}
~~~~

## display_signature

* Obtains a version signature form the slave program and prints it in the LCD.

~~~~c
void display_signature(void)
{
    char signature[7], i = 0;
    int sig_length = 6;
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0x81);
    while (i < sig_length)
    {
        if (UART1_is_rx_ready())
        {
            signature[i] = UART1_Read();
            i++;
        }
    }
    signature[sig_length] = '\0';  // terminate string
    printf("\r\n\tThe Signature from 3Pi is: %s\r\n", signature);
    LCD_print(signature, sig_length);
}
~~~~

## send_APSC1299

~~~~c 
void send_APSC1299(void)
{
    char  msg_length=8; // to send 8 characters
    char msg[] = "APSC1299";
    LCD_print(msg, msg_length); 
}
~~~~

## calibrate

* It is assumed that the robot is sitting over a black line.
* the robot spins to the left and right moving the five sensors over the line.
* the slave program calculates constants to normalize the readings from the sensors.

~~~~c 
void calibrate(void)
{
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xBA);   // auto calibration command to slave
    while(!UART1_is_rx_ready()) continue;
    while(UART1_Read() != 'c')
    {
        while(!UART1_is_rx_ready()) continue;
    }
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xB7);   // clear LCD
    LCD_print("Cal Done", 8); // LCD msg
}
~~~~

## go_pd

* The slave program uses a proportional - derivative algorithm to follow a simple line. 
* The position of the line relative to the sensors is given by a number from 0 to 4000.
    * 0 is on the far left
	* 2000 in the centre
	* 4000 on the far right
* difference in the motor speeds will be set to **(L-2000)×a/b + D×c/d**, where 
    * L is the position of the line as described above, 
	* D is the derivative of L.
	* a, b, c and d are constants
* If the line disappears the algorithm will see a position of zero and the robot will turn to the right.  
  Students will want the PIC program to override this behaviour when programming for gaps.  Essentially they need to
  read the sensors watching for all white stop pd and set the direction of the robot in the PIC program.
* In a similar way the student program needs to watch for acute turns, sharp turns and end of line and have the
  PIC program take control.
  
~~~~c 
void go_pd(unsigned char speed)
{
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xBB);   // start PD control
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(speed);   // set speed 
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(1);   // set a = 1
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(20);   // set b = 20
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(3);   // set c = 3
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xBA);   // This value is arbitrarily large and essentially removes the derivative feedback
	                     // It must be made smaller if the robot is set to faster speeds or the robot 
						 // will overshoot the line. When seed set to 100 I set this value to d = 2
}
~~~~

## stop_pd

* Stop using PD so the PIC can control the robot.

~~~~c 
void stop_pd(void)
{
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xBC);   // stop PD control
}
~~~~
