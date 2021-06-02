/******************************************************************************
*                                                                             *
*   Program : FileLogger                                                      *
*                                                                             *
*   FILE : sensorPanel.cpp                                                    *
*                                                                             *
*   Date : 28 / 05 / 2021                                                     *
*                                                                             *
*   Programmers : Team Software "TORQ"                                        *
*                                                                             *
******************************************************************************/

#include "sensorPanel.h"

SensorPanel::SensorPanel(byte LUS_epin, byte LUS_tpin, byte RUS_epin, byte RUS_tpin, byte LIF_pin, byte LIF_lpin, byte RIF_pin, byte RIF_lpin, byte FIF_pin, byte FIF_lpin) : Ultrasonic_LEFT(LUS_epin, LUS_tpin), Ultrasonic_RIGHT(RUS_epin, RUS_tpin), Infrared_LEFT(LIF_pin, LIF_lpin), Infrared_RIGHT(RIF_pin, RIF_lpin), Infrared_FRONT(FIF_pin, FIF_lpin)
{
   
}

void SensorPanel::updateOutputSequence()
{
    for (int i = 0; i < 5; ++i)
    {
        if (i < FRONT)
            outputSequence[i] = readUS(i);
        else
            outputSequence[i] = readIF(i - 2);
    }
}

int SensorPanel::readUS(int m_direction)
{
    if (m_direction >= LEFT && m_direction <= RIGHT)
    {
        if(m_direction == LEFT)
          Ultrasonic_LEFT.get_distance();

        if(m_direction == RIGHT)
          Ultrasonic_RIGHT.get_distance();
    }
    else
        return -1;
}

int SensorPanel::readIF(int m_direction)
{
    if (m_direction >= LEFT && m_direction <= FRONT)
    {
        if(m_direction == LEFT)
          Infrared_LEFT.read_pin();

        if(m_direction == RIGHT)
          Infrared_RIGHT.read_pin();

        if(m_direction == FRONT)
          Infrared_FRONT.read_pin();
    }
    else
        return -1;
}
