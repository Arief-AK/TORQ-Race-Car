/******************************************************************************
*                                                                             *
*   Program : FileLogger                                                      *
*                                                                             *
*   FILE : infraredSensor.cpp                                                 *
*                                                                             *
*   Date : 28 / 05 / 2021                                                     *
*                                                                             *
*   Programmers : Team Software "TORQ"                                        *
*                                                                             *
******************************************************************************/

#include "InfraredSensor.h"

InfraredSensor::InfraredSensor(byte m_pin, byte m_led_pin)
{
  pin = m_pin;
  led_pin = m_led_pin;
  state = 0;
}

void InfraredSensor::init()
{
	pinMode(pin, INPUT);
	pinMode(led_pin, OUTPUT);
}

int InfraredSensor::read_pin()
{
  if(digitalRead(pin) == LOW)
	  return HIGH;
  else
    return LOW;
}

void InfraredSensor::display_led()
{
	if (read_pin() == 1)
	{
		digitalWrite(led_pin, HIGH);
		state = 1;
	}
	else
	{
		digitalWrite(led_pin, LOW);
		state = 0;
	}
}

int InfraredSensor::get_state()
{
	return state;
}
