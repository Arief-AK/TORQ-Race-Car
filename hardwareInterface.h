/******************************************************************************
*                                                                             *
*   Program : FileLogger                                                      *
*                                                                             *
*   FILE : hardwareInterfac.cpp                                               *
*                                                                             *
*   Date : 28 / 05 / 2021                                                     *
*                                                                             *
*   Programmers : Team Software "TORQ"                                        *
*                                                                             *
******************************************************************************/

#pragma once

#include "driveshaft.h"
#include "sensorPanel.h"

class HardwareInterface
{
public:
    HardwareInterface(
        byte h_LUS_epin, byte h_LUS_tpin,   // Sensor Panel init args
        byte h_RUS_epin, byte h_RUS_tpin,
        byte h_LIF_pin, byte h_LIF_lpin,
        byte h_RIF_pin, byte h_RIF_lpin,
        byte h_FIF_pin, byte h_FIF_lpin,

        byte h_m_epin, byte h_m_inapin,     // Driveshaft init args
        byte h_m_inbpin, byte h_m_s_pin);

    SensorPanel sensorPanel;
    DriveShaft driveShaft;
};
