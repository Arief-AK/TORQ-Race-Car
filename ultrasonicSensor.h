/******************************************************************************
*                                                                             *
*   Program : FileLogger                                                      *
*                                                                             *
*   FILE : ultrasonicSensor.h                                                 *
*                                                                             *
*   Date : 28 / 05 / 2021                                                     *
*                                                                             *
*   Programmers : Team Software "TORQ"                                        *
*                                                                             *
******************************************************************************/

#pragma once

#include <Arduino.h>

class UltrasonicSensor
{
public:
	UltrasonicSensor(byte m_echo_pin, byte m_trig_pin);
	int get_distance();
	

	void init();

	byte echo_pin;
	byte trig_pin;

	long duration;
	int  distance;
};
