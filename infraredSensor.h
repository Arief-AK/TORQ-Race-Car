/******************************************************************************
*                                                                             *
*   Program : FileLogger                                                      *
*                                                                             *
*   FILE : infraredSensor.h                                                   *
*                                                                             *
*   Date : 28 / 05 / 2021                                                     *
*                                                                             *
*   Programmers : Team Software "TORQ"                                        *
*                                                                             *
******************************************************************************/

#pragma once

#include <Arduino.h>

class InfraredSensor
{
public:
	InfraredSensor(byte m_pin, byte m_led_pin);

	void display_led();
	int get_state();
  int read_pin();
	
	void init();
  
	byte pin;
	byte led_pin;
	int state;
};
