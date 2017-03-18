#include <stdio.h>
#include "sumovore.h"
#include "motor_control.h"



unsigned long count=0;
 
void motor_control(enum commands command)
{
    if( command != null)
    {
        switch(command)
        {
            case motor_left_fast:
              set_motor_speed(left, fast, 0);
              break;
            case motor_left_medium:
              set_motor_speed(left, medium, 0);
              break;
            case motor_left_slow:
              set_motor_speed(left, slow, 0);
              break;
            case motor_left_coast:
              set_motor_speed(left, stop, 0);
              break;          
            case motor_right_fast:
              set_motor_speed(right, fast, 0);
              break;
            case motor_right_medium:
              set_motor_speed(right, medium, 0);
              break;
            case motor_right_slow:
              set_motor_speed(right, slow, 0);
              break;
            case motor_right_coast:
              set_motor_speed(right, stop, 0);
              break;
            case motor_left_rev_fast:
              set_motor_speed(left, rev_fast, 0);
              break;
            case motor_left_rev_medium:
              set_motor_speed(left, rev_medium, 0);
              break;
            case motor_left_rev_slow:
              set_motor_speed(left, rev_slow, 0);
              break;
            case motor_left_rev_coast:
              set_motor_speed(left, stop, 0);
              break;          
            case motor_right_rev_fast:
              set_motor_speed(right, rev_fast, 0);
              break;
            case motor_right_rev_medium:
              set_motor_speed(right, rev_medium, 0);
              break;
            case motor_right_rev_slow:
              set_motor_speed(right, rev_slow, 0);
              break;
            case motor_right_rev_coast:
              set_motor_speed(right, stop, 0);
              break;
            case motor_brake_all:
              motors_brake_all();
              break;
            default:
              printf("unknown command -- bug in program\r\n"); 
              break;
        }
    }    
}

void brake_all(void)
{
	motors_brake_all();
}

void coast(void)
{
  set_motor_speed(left, stop, 0); 
  set_motor_speed(right, stop, 0); 
}

void spin_left(void)
{
  set_motor_speed(left, rev_medium, 0); 
  set_motor_speed(right, medium, 0); 
}

void turn_left(void)
{
  set_motor_speed(left, stop, 0); 
  set_motor_speed(right, fast, 0); 
}
void straight_fwd(void)
{
  set_motor_speed(left, fast, 0); 
  set_motor_speed(right, fast, 0); 
}
void spin_right(void)
{
  set_motor_speed(left, medium , 0); 
  set_motor_speed(right, rev_medium, 0); 
}
void turn_right(void)
{
  set_motor_speed(left, fast, 0); 
  set_motor_speed(right, stop, 0); 
}