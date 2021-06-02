/******************************************************************************
*                                                                             *
*   Program : FileLogger                                                      *
*                                                                             *
*   FILE : mainMotor.h                                                        *
*                                                                             *
*   Date : 28 / 05 / 2021                                                     *
*                                                                             *
*   Programmers : Team Software "TORQ"                                        *
*                                                                             *
******************************************************************************/

#pragma once

#include <Arduino.h>

class MainMotor
{
public:
	MainMotor(byte m_enable_pin, byte m_input_a, byte m_input_b);

	void set_rpm(int rpm);
	void rotate_clockwise();
	void rotate_anti_clockwise();
	void rotate_stop();
 
  void init();

	byte input_a;
	byte input_b;
	byte enable_pin;
	int rpm;
};
