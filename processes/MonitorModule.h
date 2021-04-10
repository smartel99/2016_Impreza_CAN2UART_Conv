/**
 * @addtogroup MonitorModule.h
 * @{
 *******************************************************************************
 * @file	MonitorModule.h
 * @author	Samuel Martel
 * @brief
 * Created on: Apr. 10, 2021
 *******************************************************************************
 */

#ifndef MONITORMODULE_H_
#define MONITORMODULE_H_

/***********************************************/
/* Includes */
#include "shared/defines/module.hpp"



/***********************************************/
/* Defines */
class MonitorModule : public cep::Module
{
public:
    MonitorModule(const std::string& label);
    virtual ~MonitorModule() override = default;

    virtual void               Run() override;
    virtual const std::string& GetLabel() const override { return m_label; }

private:
    std::string m_label = "";
};

/***********************************************/
/* Function declarations */



/**
 * @}
 */
/* END OF FILE */
#endif /* MONITORMODULE_H_ */
