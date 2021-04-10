/**
 ******************************************************************************
 * @addtogroup MasterApplication
 * @{
 * @file    MasterApplication
 * @author  Samuel Martel
 * @brief   Source for the MasterApplication module.
 *
 * @date 2021/03/16
 *
 ******************************************************************************
 */
#include "MasterApplication.h"

#include "Core/Inc/can.h"
#include "Core/Inc/gpio.h"
#include "Core/Inc/usart.h"


MasterApplication* MasterApplication::s_instance = nullptr;

MasterApplication::MasterApplication()
{
    CEP_ASSERT(s_instance == nullptr, "Cannot have multiple instances of Application!");
    s_instance = this;
}

void MasterApplication::Init()
{
    InitializeHAL();
    InitializeServices();
    InitializeModules();
}

void MasterApplication::Run()
{
    while (true)
    {
        for (auto& module : s_instance->m_modules)
        {
            module.second->Run();
        }
    }
}

cep::Module* MasterApplication::GetModule(const std::string& moduleName)
{
    return s_instance->m_modules.at(moduleName);
}

/*****************************************************************************/
/* Private Method Definitions                                                */
/*****************************************************************************/
void MasterApplication::InitializeHAL()
{
    // HAL devices initialization
    MX_GPIO_Init();
    MX_CAN1_Init();
    MX_USART3_UART_Init();
}

void MasterApplication::InitializeServices()
{
}

void MasterApplication::InitializeModules()
{
    // Uart module for debug purposes.
    UartModule* uart3 = new UartModule(&huart3, "uart");
    // Enable UART interrupts, low-ish priority.
    HAL_NVIC_SetPriority(USART3_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
    AddModule(uart3);

    m_logger = new Logger(uart3);
    Logger::Get()->Log("\n\n\r");
    Logger::Get()->Log(
      "===============================================================================\n\r");
    Logger::Get()->Log(
      "|                      2016 Subaru Impreza CAN bus monitor                    |\n\r");
    Logger::Get()->Log(
      "|                          (c) 2021 - Samuel Martel                           |\n\r");
#if defined(DEBUG)
    Logger::Get()->Log(
      "|                            !!! DEBUG VERSION !!!                            |\n\r");
#endif
    Logger::Get()->Log(
      "===============================================================================\n\r");

    auto can = new CanModule(&hcan1, "can1");
    AddModule(can);

    // CAN filter configuration
    // Default filter, FIFO0, bank0, mask = 0, id = 0, enabled.
    CEP_CAN::FilterConfiguration filter;
    can->ConfigureFilter(filter);

    can->EnableInterrupts({CEP_CAN::Irq::TxMailboxEmpty,
                           CEP_CAN::Irq::Fifo0MessagePending,
                           CEP_CAN::Irq::Fifo0Full,
                           CEP_CAN::Irq::Fifo0Overrun,
                           CEP_CAN::Irq::Fifo1MessagePending,
                           CEP_CAN::Irq::Fifo1Full,
                           CEP_CAN::Irq::Fifo1Overrun,
                           CEP_CAN::Irq::Wakeup,
                           CEP_CAN::Irq::SleepAck,
                           CEP_CAN::Irq::ErrorWarning,
                           CEP_CAN::Irq::ErrorPassive,
                           CEP_CAN::Irq::BusOffError,
                           CEP_CAN::Irq::LastErrorCode,
                           CEP_CAN::Irq::ErrorStatus});


    // IRQ enable after everything is initialized to prevent calling interrupts without handlers
    // ready.
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
    HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
}
