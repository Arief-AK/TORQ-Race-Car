/******************************************************************************
*                                                                             *
*   Program : FileLogger                                                      *
*                                                                             *
*   FILE : hardwareInterface.h                                                *
*                                                                             *
*   Date : 28 / 05 / 2021                                                     *
*                                                                             *
*   Programmers : Team Software "TORQ"                                        *
*                                                                             *
******************************************************************************/

#include "hardwareInterface.h"

HardwareInterface::HardwareInterface(
    byte h_LUS_epin, byte h_LUS_tpin,   
    byte h_RUS_epin, byte h_RUS_tpin,
    byte h_LIF_pin, byte h_LIF_lpin,
    byte h_RIF_pin, byte h_RIF_lpin,
    byte h_FIF_pin, byte h_FIF_lpin,

    byte h_m_epin, byte h_m_inapin,     
    byte h_m_inbpin, byte h_m_s_pin
): sensorPanel(
        h_LUS_epin, h_LUS_tpin,   
        h_RUS_epin, h_RUS_tpin,
        h_LIF_pin, h_LIF_lpin,
        h_RIF_pin, h_RIF_lpin,
        h_FIF_pin, h_FIF_lpin ) , 
   driveShaft(h_m_epin, h_m_inapin, h_m_inbpin, h_m_s_pin)
{}
