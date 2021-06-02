/******************************************************************************
*                                                                             *
*   Program : FileLogger                                                      *
*                                                                             *
*   FILE : driveshaft.cpp                                                     *
*                                                                             *
*   Date : 28 / 05 / 2021                                                     *
*                                                                             *
*   Programmers : Team Software "TORQ"                                        *
*                                                                             *
******************************************************************************/

#include "driveShaft.h"

DriveShaft::DriveShaft(byte m_epin, byte m_inapin, byte m_inbpin, byte m_s_pin) : p_mainMotor(m_epin, m_inapin, m_inbpin), p_servoMotor(m_s_pin)
{
}

void DriveShaft::moveForward(int m_speed)
{
  p_servoMotor.reset();
	p_mainMotor.set_rpm(m_speed);
	p_mainMotor.rotate_clockwise();
}

void DriveShaft::turnLeft(int m_speed, int m_angle)
{
  p_servoMotor.reset();
  p_servoMotor.rotate_left(m_angle);
	p_mainMotor.set_rpm(m_speed);
	p_mainMotor.rotate_clockwise();
}

void DriveShaft::turnRight(int m_speed, int m_angle)
{
  p_servoMotor.reset();
  p_servoMotor.rotate_right(m_angle);
	p_mainMotor.set_rpm(m_speed);
	p_mainMotor.rotate_clockwise();
}

void DriveShaft::powerStart()
{
  p_servoMotor.reset();
  p_mainMotor.set_rpm(500);
  p_mainMotor.rotate_clockwise();
  delay(200);
}

void DriveShaft::stopMovement()
{
	p_servoMotor.reset();
	p_mainMotor.rotate_stop();
}
