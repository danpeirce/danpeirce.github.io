#include <stdio.h>
#include "sumovore.h"
#include "motor_control.h"
#include "sensor.h"
#include "process_command.h"
#include "menu.h"


// main acts as a cyclical task sequencer
void main(void)
{
    enum commands command = 0;
    
    initialization(); // function from sumovore.c
                      // it sets up pwm (using timer2),
                      // IO pins, the ADC, the 
                      // USART and the default
                      // threshold 

    
    printf("\a\f"); // audible bell on the terminal
                    // and form feed
    menu_top();

    while(1)
    {
        check_sensors();   // from sumovore.c
        set_leds();
	    command = process_command();  // from process_command.c
	    if (command == null); // if null skip the rest
	    else if(command < boundary_top_motor) motor_control(command); // function from motor_control.c
	    else if (command < boundary_top_sensor) sensor_reading(command);  //function from sensor.c
	    else printf("\r\c command not valid -- bug main.c \r\c");
    }
}
 