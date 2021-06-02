/******************************************************************************
*                                                                             *
*   Program : FileLogger                                                      *
*                                                                             *
*   FILE : mainMotor.cpp                                                      *
*                                                                             *
*   Date : 28 / 05 / 2021                                                     *
*                                                                             *
*   Programmers : Team Software "TORQ"                                        *
*                                                                             *
******************************************************************************/

#include "mainMotor.h"

MainMotor::MainMotor(byte m_enable_pin, byte m_input_a, byte m_input_b)
{
  enable_pin = m_enable_pin;
  input_a = m_input_a; 
  input_b = m_input_b; 
  rpm = 100;
}

void MainMotor::init()
{
	pinMode(enable_pin, OUTPUT);
	pinMode(input_a, OUTPUT);
	pinMode(input_b, OUTPUT);
}

void MainMotor::set_rpm(int m_rpm)
{
	rpm = m_rpm;
}

void MainMotor::rotate_clockwise()
{
	digitalWrite(input_a, LOW);
	digitalWrite(input_b, HIGH);
	analogWrite(enable_pin, rpm);
}

void MainMotor::rotate_anti_clockwise()
{
	digitalWrite(input_a, HIGH);
	digitalWrite(input_b, LOW);
	analogWrite(enable_pin, 500);
}

void MainMotor::rotate_stop()
{
	digitalWrite(input_a, LOW);
	digitalWrite(input_b, LOW);
	analogWrite(enable_pin, 0);
}
