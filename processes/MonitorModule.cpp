/**
 * @addtogroup MonitorModule.cpp
 * @{
 *******************************************************************************
 * @file	MonitorModule.cpp
 * @author	Samuel Martel
 * @brief
 * Created on: Apr. 10, 2021
 *******************************************************************************
 */


#include "MonitorModule.h"

#include "processes/MasterApplication.h"

#include "defines/macros.hpp"
#include "defines/misc.hpp"

#include <cstdio>

MonitorModule::MonitorModule(const std::string& label) : m_label(label)
{
    LOG_INFO("[MON]: Initialized.");
}


void MonitorModule::Run()
{
    static CanModule* can = CAN1_MODULE;

    while (can->GetNumberOfAvailableFrames() != 0)
    {
        static char pkt[128] = {0};

        CEP_CAN::Frame frame = can->ReceiveFrame();

        size_t pos = 0;

        for (size_t i = 0; i < frame.frame.DLC; i++)
        {
            pos += sprintf(&pkt[pos], "0x%02X ", frame.data[i]);
        }

        LOG_INFO("[MON]: ID (%s): 0x%04X\tData: %s",
                 (frame.frame.IDE ? "EXT" : "STD"),
                 (frame.frame.IDE ? frame.frame.ExtId : frame.frame.StdId),
                 pkt);
    }
}
