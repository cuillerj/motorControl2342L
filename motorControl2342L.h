#include <Arduino.h>

#ifndef motorControl_h_included
#define motorControl_h_included

// Enables to instantiate and control Motors
class Motor
{
public:
// Create a Motor knowing the connection pins on arduino and the motor maximum revolutions per minute.
// pinEN corresponds to
// pinIN1 and pinIN2 correspond to
// iMotorMaxrpm is the maximum revolutions per minutes of the motor. This value is used to control the value to send to arduino to reach the expected speed (Arduino sends a value between 0 and 255).
Motor(int pinEN, int pinIN1, int pinIN2, int iMotorMaxrpm);
// Turn the Motor Clockwise if bClockWise is true, counter-clockwise otherwise
// Motor runs during iDuration ms
// Motor runs at irpm revolutions per minute
void TurnMotor(boolean bClockwise, unsigned long iDuration, int irpm);
// Check whether the motor is running and has realised the expected distance
// It returns the speed of the motor (in revolutions per minute), 0 if not running.
int CheckMotor();
// Checks the number of Centi-revolutions (meaning 0.01 revolution) performed since last start of the Motor
int getCoveredCentiRevolutions();
// Stops the motor
void StopMotor();
int _pinEN;
int _pinIN1;
int _pinIN2;
int _iMotorMaxrpm;
int _irpm;
int _iExpectedCentiRevolutions;
unsigned long _startTime;
};
    
#endif
