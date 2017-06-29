#include <Arduino.h>

#ifndef motorControl_h_included
#define motorControl_h_included
// Enables to instantiate and control Motors
class Motor
{
public:
// Create a Motor knowing the connection pins on arduino and the motor maximum revolutions per minute.
// pinEN corresponds to the arduino PWM pin used to set the rotation speed of the motor. The value sent by arduino should be comprised between 0 and 255.
// pinIN1 and pinIN2 correspond to the arduino pins used to define the rotation sense of the motor. 10 makes the motor run clockwise (TBC) and 01 makes the motor run counter-clockwise (TBC).
// iMotorMaxrpm is the maximum revolutions per minutes of the motor. This value is used to control the value to send to arduino to reach the expected speed.
Motor(int pinEN, int pinIN1, int pinIN2, int iMotorMaxrpm, int iSlowPMW);
// Moves motor according to defined direction, number of centi-revolutions and speed
// Motor moves clockwise if bClockWise is true, counter-clockwise otherwise
// Speed is supposed to be linear with PWM 
// iSlowPMW used to slowdown the rotation before stopping

// Motor runs during iCentiRevolutions centi-revolutions (meaning 0.01 revolution)
// Motor runs at irpm revolutions per minute. This value is limited to _iMotorMaxrpm (if a greater value is sent, this value is reduced to _iMotorMaxrpm)
void TurnMotor(boolean bClockwise, unsigned long iRequestedCentiRevolutions, int irpm);

// Check whether the motor is running and has realised the expected distance
// It returns the speed of the motor (in revolutions per minute), 0 if not running.
int CheckMotor(unsigned int currentMotorpeed, unsigned long lDoneCentiRevolutions);

// Checks the number of Centi-revolutions (meaning 0.01 revolution) performed since last start of the Motor.
unsigned long getCoveredCentiRevolutions();

// Just start motor at the requested PWM value - Stop and speed has to been managed by the main code
void RunMotor(boolean bClockwise, unsigned int iPWM);  

// Stops the motor
void StopMotor();

void AdjustMotorPWM( unsigned int iPWM );

boolean RunningMotor();

int _pinEN;
int _pinIN1;
int _pinIN2;
int _iMotorMaxrpm;
int _irpm; // Stores the current speed of the motor. Once appropriate hardware is integrated, this constant should be replaced by the result of a function computing dynamically the speed of the motor.
int _iSlowPMW;
boolean _running;
unsigned long _expectedCentiRevolutions; // At each start of the motor, this value stores the number of centi-revolutions asked to the motor (computed from iDuration and irpm)
unsigned long _startTime; // At each start of the motor, this value stores the start time of the motor. Once appropriate hardware is integrated, this constant should no more be necessary as the distance covered since last start of the motor will be collected from sensors (and no more computed as done today).
};
    
#endif
