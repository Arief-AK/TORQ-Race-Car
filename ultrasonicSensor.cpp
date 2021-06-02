/******************************************************************************
*                                                                             *
*   Program : FileLogger                                                      *
*                                                                             *
*   FILE : ultrasonicSensor.cpp                                               *
*                                                                             *
*   Date : 28 / 05 / 2021                                                     *
*                                                                             *
*   Programmers : Team Software "TORQ"                                        *
*                                                                             *
******************************************************************************/

#include "ultrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(byte m_echo_pin, byte m_trig_pin)
{
  echo_pin = m_echo_pin;
  trig_pin = m_trig_pin;
  duration = 0.0;
  distance = 0;
}

void UltrasonicSensor::init()
{
	pinMode(trig_pin, OUTPUT);
	pinMode(echo_pin, INPUT);
}

int UltrasonicSensor::get_distance()
{
	// Clears the trig_pin condition
	digitalWrite(trig_pin, LOW);
	delayMicroseconds(2);
  
	// Sets the trig_pin HIGH (ACTIVE) for 10 microseconds
	digitalWrite(trig_pin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trig_pin, LOW);
  
	// Reads the echo_pin, returns the sound wave travel time in microseconds
	duration = pulseIn(echo_pin, HIGH);
  
	// Calculating the distance
	distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

	return distance;
}
