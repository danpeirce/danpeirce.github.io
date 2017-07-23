/* 
 *  Adapted (by Dan Peirce B.Sc.) from example program Encoders 
Program moves the robot forward, stops, spins around 180 degrees, stops
and returns to where it started.
Added checks of gyroscope and accelerometer as checks for robot coming
to a full stop.
Encoders used as measure of distance travelled.
Event loop allows consent checking and updating displayed encoder values at 
100 ms intervals but is non-blocking.
Simple state machine technique used to run sequence of robot manurers. Most states
are non blocking.
 */

#include <Wire.h>
#include <Zumo32U4.h>

void display_encoder_count(void);

// state functions
void stopstate(void);
void runforward1(void);
void coast1(void);
void spin1(void);
void runforward2(void);
void runforward3(void);
void stopstate2(void);

LSM303 compass;
L3G gyro;
Zumo32U4Encoders encoders;
Zumo32U4LCD lcd;
Zumo32U4Buzzer buzzer;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonC buttonC;

const char encoderErrorLeft[] PROGMEM = "!<c2";
const char encoderErrorRight[] PROGMEM = "!<e2";

char report[80];

int basexacc;  // gives acc offset in forward direction.
void (*state)(void) = stopstate;   // note is a function pointer initialized to point
                                   // to stopstate function
								   
void setup()
{
  Wire.begin();

  if (!compass.init())
  {
    // Failed to detect the compass.
    ledRed(1);
    while(1)
    {
      Serial.println(F("Failed to detect the compass."));
      delay(100);
    }
  }

  compass.enableDefault();

  if (!gyro.init())
  {
    // Failed to detect the gyro.
    ledRed(1);
    while(1)
    {
      Serial.println(F("Failed to detect gyro."));
      delay(100);
    }
  }

  gyro.enableDefault();
  compass.read();
  basexacc = compass.a.x; // comes up as non zero so this finds offset
                          // will change if not level
						  // +x is the forward direction
}

void loop()
{
  
  state();    // will call the function this pointer is pointing at
  display_encoder_count(); // display will update if robot pushed

}

void stopstate(void)
// watches for button press of A button
// delay to allow on to move hand clear of robot
// turns on motors after a button pressed. Also 
// assigns new state (runforward1).
{
  static uint8_t lastTime=0, count = 0;
  static bool button_flagged = 0;

  
  if (buttonA.isPressed())
  {
    lastTime = millis();
	button_flagged =1;
  }	  
  
  if (button_flagged && ((uint8_t)(millis() - lastTime) >= 100) )
  {
    count++;
	lastTime = millis();
	if (count > 9)       // should be entered 1 second after button released
    {
	  state = runforward1;
	  motors.setSpeeds(400, 400);
    }
  }

}

void runforward1(void)
// runs forward until left encoder shows robot has moved a count of 2000
// after which moters coast to a stop.
{
    if (encoders.getCountsLeft()> 2000)
    {
      motors.setSpeeds(0, 0);
      state = coast1;
    }
}

void coast1(void)
// as robot slows the accelerometer reads a negative value.
// when accelerometer gets close to base value robot is barely moving
// that is a good time to start spin turn.
{
  compass.read();

  if ( compass.a.x > basexacc -30  ) 
  {
    state = spin1;
    encoders.getCountsAndResetLeft();  // zero the encoders
    encoders.getCountsAndResetRight();
    motors.setSpeeds(400, -400);
  }
}

void spin1(void)
// when robot has spun close to 180 deg the counter is 2000-1500 less a small value
// whiche allows for coasting.
{
  if (encoders.getCountsLeft()> 1585-80)
  {
    motors.setSpeeds(0, -0);
    state = runforward2;
  }
}

void runforward2(void)
// the gyro z zero actually reads about  200 so
// wait until accelerometer value is getting close to 200
// indicating spin turn coast has stopped. Then rn motors forward.
{
  gyro.read();
  if (gyro.g.z > 100)
  {
    encoders.getCountsAndResetLeft();  // zero the encoders
    encoders.getCountsAndResetRight();
    motors.setSpeeds(400, 400);
    state = runforward3;
  }
}

void runforward3()
// stop when left encoder count gets close to 2000
{
  if (encoders.getCountsLeft() > 2000-80)
  {
    motors.setSpeeds(0, 0);
    state = stopstate2;
  }
}

void stopstate2(void)
{
  // so far is a dummy function
}

void display_encoder_count(void) 
{
  static uint8_t lastDisplayTime;
  static uint8_t displayErrorLeftCountdown = 0;
  static uint8_t displayErrorRightCountdown = 0;

  if ((uint8_t)(millis() - lastDisplayTime) >= 100)
  {
    lastDisplayTime = millis();

    int16_t countsLeft = encoders.getCountsLeft();
    int16_t countsRight = encoders.getCountsRight();

    bool errorLeft = encoders.checkErrorLeft();
    bool errorRight = encoders.checkErrorRight();

    if(encoders.checkErrorLeft())
    {
      // An error occurred on the left encoder channel.
      // Display it on the LCD for the next 10 iterations and
      // also beep.
      displayErrorLeftCountdown = 10;
      buzzer.playFromProgramSpace(encoderErrorLeft);
    }

    if(encoders.checkErrorRight())
    {
      // An error occurred on the left encoder channel.
      // Display it on the LCD for the next 10 iterations and
      // also beep.
      displayErrorRightCountdown = 10;
      buzzer.playFromProgramSpace(encoderErrorRight);
    }

    // Update the LCD with encoder counts and error info.
    lcd.clear();
    lcd.print(countsLeft);
    lcd.gotoXY(0, 1);
    lcd.print(countsRight);

    if (displayErrorLeftCountdown)
    {
      // Show an exclamation point on the first line to
      // indicate an error from the left encoder.
      lcd.gotoXY(7, 0);
      lcd.print('!');
      displayErrorLeftCountdown--;
    }

    if (displayErrorRightCountdown)
    {
      // Show an exclamation point on the second line to
      // indicate an error from the left encoder.
      lcd.gotoXY(7, 1);
      lcd.print('!');
      displayErrorRightCountdown--;
    }

    // Send the information to the serial monitor also.
    snprintf_P(report, sizeof(report),
        PSTR("%6d %6d %1d %1d"),
        countsLeft, countsRight, errorLeft, errorRight);
    Serial.println(report);
  }
}


