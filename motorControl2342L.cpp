/*
motorControl.cpp - Bibliothèque de contrôle de moteur.
_________
Créé par Henri, October 18, 2015.
*/

//#include "WProgram.h"
#include "motorControl2342L.h"

// Create a Motor knowing the connection pins on arduino and the motor maximum revolutions per minute.
// pinEN corresponds to the arduino PWM pin used to set the rotation speed of the motor. The value sent by arduino should be comprised between 0 and 255.
// pinIN1 and pinIN2 correspond to the arduino pins used to define the rotation sense of the motor. 10 makes the motor run clockwise (TBC) and 01 makes the motor run counter-clockwise (TBC).
// iMotorMaxrpm is the maximum revolutions per minutes of the motor. This value is used to control the value to send to arduino to reach the expected speed.
Motor::Motor(int pinEN, int pinIN1, int pinIN2, int iMotorMaxrpm)
{
  pinMode(pinEN, OUTPUT);
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  _pinEN = pinEN;
  _pinIN1 = pinIN1;
  _pinIN2 = pinIN2;
  _iMotorMaxrpm = iMotorMaxrpm;
  _irpm = 0;
  _iExpectedCentiRevolutions = 0;
}

// Moves motor according to defined direction, duration and speed
// Motor moves clockwise if bClockWise is true, counter-clockwise otherwise
// Motor runs during iDuration milliseconds
// Motor runs at irpm revolutions per minute. This value is limited to _iMotorMaxrpm (if a greater value is sent, this value is reduced to _iMotorMaxrpm)
void Motor::TurnMotor(boolean bClockwise, unsigned long iDuration, int irpm)
{
  // Direction du Moteur
  digitalWrite(_pinIN1,bClockwise);
  digitalWrite(_pinIN2,!bClockwise);

  if (irpm>_iMotorMaxrpm)
  { // Limit requested speed to known motor limit
    _irpm = _iMotorMaxrpm;
  }
  else
  {
	  _irpm = irpm;
  }
  analogWrite(_pinEN,255*_irpm/_iMotorMaxrpm);
  _startTime = millis();
  Serial.print("Expected duration: ");
  Serial.println(iDuration);
  Serial.print("Expected rpm: ");
  Serial.println(irpm);
  _iExpectedCentiRevolutions = iDuration*irpm*60*1000/100;
  Serial.print("Number of expected centi-revolutions: ");
  Serial.println(_iExpectedCentiRevolutions);
  
  //Serial.print("Motor PWM set to ");
  //Serial.println(255*irpm/_iMotorMaxrpm);
}

// Check whether the motor is running and has realised the expected distance
// It returns the speed of the motor (in revolutions per minute), 0 if not running.
int Motor::CheckMotor()
{
	if (_irpm > 0)
	{
		if (!(getCoveredCentiRevolutions() > _iExpectedCentiRevolutions))
		{
			return _irpm;
		}
		else
		{
			StopMotor();
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

// Checks the number of Centi-revolutions (meaning 0.01 revolution) performed since last start of the Motor.
int Motor::getCoveredCentiRevolutions()
{
	int iCoveredCentiRevolutions = _irpm*60*(millis()-_startTime)*1000/100;
	Serial.print("Number of performed centi-revolutions: ");
    Serial.println(iCoveredCentiRevolutions);
	return iCoveredCentiRevolutions;
}

// Stops the motor
void Motor::StopMotor()
{
	digitalWrite(_pinEN, LOW);
	_irpm = 0;
	_startTime = 0;
	_iExpectedCentiRevolutions = 0;
	// Serial.println("Motor stopped");
}