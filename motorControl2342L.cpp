/*
motorControl.cpp - Bibliothèque de contrôle de moteur.
_________
Créé par Henri, October 18, 2015.
*/

//#include "WProgram.h"
#include "motorControl2342L.h"

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
// Motor moves clockwise if bForward is true
// Motor runs during iDuration milliseconds
// Motor runs at irpm revolutions per minute
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
  _iExpectedCentiRevolutions = iDuration*irpm*60*1000/100;  
  
  //Serial.print("Motor PWM set to ");
  //Serial.println(255*irpm/_iMotorMaxrpm);
}

// Check whether the motor has turned the expected number of turns or not
// Returns the rotation speed of the motor (motor is running if speed > 0)
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

// Collects the number of turns performed since last start of the motor
int Motor::getCoveredCentiRevolutions()
{
	return _irpm*60*(millis()-_startTime)*1000/100;
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