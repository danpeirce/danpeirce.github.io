-   [Pololu3pi.c Details](#pololu3pi.c-details)
    -   [print\_sensors](#print_sensors)
    -   [foreward](#foreward)
    -   [backward](#backward)
    -   [spinleft](#spinleft)
    -   [spinright](#spinright)
    -   [readbatteryvoltage](#readbatteryvoltage)
    -   [readsensors](#readsensors)
    -   [sendbatteryvoltage](#sendbatteryvoltage)
    -   [sendchar](#sendchar)
    -   [clearLCD](#clearlcd)
    -   [LCD\_print](#lcd_print)
    -   [LCD\_line2](#lcd_line2)
    -   [display\_signature](#display_signature)
    -   [send\_hyphen](#send_hyphen)
    -   [send\_APSC1299](#send_apsc1299)
    -   [calibrate](#calibrate)
    -   [go\_pd](#go_pd)
    -   [stop\_pd](#stop_pd)

<!---
use 
pandoc -s --toc -t html5 -c ../../pandocbd.css pololu3pi.c-details.pandoc.md -o pololu3pi.c-details.html

pandoc -s --toc -t gfm pololu3pi.c-details.pandoc.md -o pololu3pi.c-details.md
-->

Pololu3pi.c Details
===================

print\_sensors
--------------

-   This function only used in No Roam mode and is called as a menu item
-   Calibrates sensors
-   Reads sensors and prints values to virtual COM port.
-   prints timer3 value
-   possible future changes
    -   Move calibrate into a different function.
    -   currently prints new values over old. may change so new values
        go on new line
    -   may change so it prints only one set of values and returns

<!-- -->

    void print_sensors(void)
    {
        unsigned int * sensorvalues;
        calibrate();
        while(1)
        {
            sensorvalues = readsensors();
            // __delay_ms(80);
            printf("\rsensor values = %4u, ", *sensorvalues);
            printf("%4u, ", *(sensorvalues+1));
            printf("%4u, ", *(sensorvalues+2));
            printf("%4u, ", *(sensorvalues+3));
            printf("%4u", *(sensorvalues+4));
            printf(" | Timer Value = %5u",TMR3_ReadTimer());
        }
        
    }

foreward
--------

-   This function only used in Roam mode

<!-- -->

    void foreward(unsigned char speed)
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

backward
--------

-   This function only used in Roam mode

<!-- -->

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

spinleft
--------

-   This function only used in Roam mode

<!-- -->

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

spinright
---------

-   This function only used in Roam mode

<!-- -->

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

readbatteryvoltage
------------------

-   This function used after menu displayed and as a menu item.
-   Sends battery voltage to virtual COM port and returns value

<!-- -->

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

readsensors
-----------

-   Returns pointer to array of sensor values.

<!-- -->

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

sendbatteryvoltage
------------------

-   Calls readbatteryvoltage, prints returned values to LCD.

<!-- -->

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

sendchar
--------

-   Sends a single character to the LCD.

<!-- -->

    void sendchar(char a_char)
    {
        while(!UART1_is_tx_ready()) continue;
        UART1_Write(0xB8);   // print LCD command to slave
        while(!UART1_is_tx_ready()) continue;
        UART1_Write(1);     // send one character
        while(!UART1_is_tx_ready()) continue;
        UART1_Write(a_char);     // send one character
    }

clearLCD
--------

    void clearLCD(void)
    {
        while(!UART1_is_tx_ready()) continue;
        UART1_Write(0xB7);   // clear LCD
    }

LCD\_print
----------

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

LCD\_line2
----------

    void LCD_line2(void)
    {
        while(!UART1_is_tx_ready()) continue;
        UART1_Write(0xB9);   // goto LCD position
        while(!UART1_is_tx_ready()) continue;
        UART1_Write(0x00);   // column 0
        while(!UART1_is_tx_ready()) continue;
        UART1_Write(0x01);   // row 1
    }

display\_signature
------------------

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

send\_hyphen
------------

    // just to test that printing to the LCD is working
    void send_hyphen(void)
    {
        // see https://www.pololu.com/docs/0J21/10.a 
        while(!UART1_is_tx_ready()) continue;
        UART1_Write(0xB8);   // print LCD command to slave
        while(!UART1_is_tx_ready()) continue;
        UART1_Write(1);     // send one character
        while(!UART1_is_tx_ready()) continue;
        UART1_Write('-');   // send a hyphen
    }

send\_APSC1299
--------------

    void send_APSC1299(void)
    {
        char  msg_length=8; // to send 8 characters
        char msg[] = "APSC1299";
        LCD_print(msg, msg_length); 
    }

calibrate
---------

    void calibrate(void)
    {
        while(!UART1_is_tx_ready()) continue;
        UART1_Write(0xBA);   // autocalibration command to slave
        while(!UART1_is_rx_ready()) continue;
        while(UART1_Read() != 'c')
        {
            while(!UART1_is_rx_ready()) continue;
        }
        while(!UART1_is_tx_ready()) continue;
        UART1_Write(0xB7);   // clear LCD
        LCD_print("Cal Done", 8); // LCD msg
    }

go\_pd
------

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
        UART1_Write(0xBA);   // set d = 2
    }

stop\_pd
--------

    void stop_pd(void)
    {
        while(!UART1_is_tx_ready()) continue;
        UART1_Write(0xBC);   // stop PD control
    }
