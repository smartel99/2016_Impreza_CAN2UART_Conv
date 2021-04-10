/**
 * @addtogroup MasterApplication.h
 * @{
 *******************************************************************************
 * @file	MasterApplication.h
 * @author	Samuel Martel
 * @brief
 * Created on: Mar 16, 2021
 *******************************************************************************
 */

#ifndef MASTERAPPLICATION_H_
#define MASTERAPPLICATION_H_

/***********************************************/
/* Includes */
#include "shared/processes/application.hpp"

#include "shared/defines/module.hpp"

#include "shared/drivers/canModule.hpp"
#include "shared/drivers/uartModule.hpp"

#include "shared/services/logger.hpp"

#include <map>
#include <string>



/***********************************************/
/* Defines */

#define UART_MODULE static_cast<UartModule*>(MasterApplication::GetModule("uart"))
#define CAN1_MODULE static_cast<CanModule*>(MasterApplication::GetModule("can1"))

/***********************************************/
/* Function declarations */
class MasterApplication : public cep::Application
{
public:
    MasterApplication();
    virtual ~MasterApplication() override = default;

    virtual void Init() override;
    virtual void Run() override;

    void AddModule(cep::Module* newModule) { m_modules[newModule->GetLabel()] = newModule; }

    static cep::Module* GetModule(const std::string& moduleName);

    static MasterApplication* Get() { return s_instance; }

private:
    std::map<std::string, cep::Module*> m_modules;
    Logger*                             m_logger = nullptr;

private:
    static MasterApplication* s_instance;

private:
    void InitializeHAL();
    void InitializeServices();
    void InitializeModules();
};


/**
 * @}
 */
/* END OF FILE */
#endif /* MASTERAPPLICATION_H_ */
