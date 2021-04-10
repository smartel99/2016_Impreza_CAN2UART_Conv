/**
 * @addtogroup  main
 * @{
 * @file        main.cpp
 * @author      Pascal-Emmanuel Lachance
 */
/*************************************************************************************************/
/* File includes ------------------------------------------------------------------------------- */

#include "processes/MasterApplication.h"
#include "Core/Inc/main.h"

/*************************************************************************************************/
/* Private functions declarations -------------------------------------------------------------- */
void SystemClock_Config();

/*************************************************************************************************/
/* Global variables ---------------------------------------------------------------------------- */

/*************************************************************************************************/
/* main ---------------------------------------------------------------------------------------- */
int main()
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();
    // Make sure that SYSCLK isn't set to PLL before configuring it.
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_SW);

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize program */
    MasterApplication app;

    app.Init();

    app.Run();
    /* We should never get here as control is now taken by the scheduler */
    /* Infinite loop */
    while (true)
    {
    }
}

/**
 * @brief System Clock Configuration
 * @retval None
 */

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct   = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct   = {0, 0, 0, 0, 0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState            = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM            = 1;
    RCC_OscInitStruct.PLL.PLLN            = 10;
    RCC_OscInitStruct.PLL.PLLP            = RCC_PLLP_DIV7;
    RCC_OscInitStruct.PLL.PLLQ            = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR            = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType =
      RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection    = RCC_PERIPHCLK_USART3 | RCC_PERIPHCLK_ADC;
    PeriphClkInit.Usart3ClockSelection    = RCC_USART3CLKSOURCE_PCLK1;
    PeriphClkInit.AdcClockSelection       = RCC_ADCCLKSOURCE_PLLSAI1;
    PeriphClkInit.PLLSAI1.PLLSAI1Source   = RCC_PLLSOURCE_HSI;
    PeriphClkInit.PLLSAI1.PLLSAI1M        = 1;
    PeriphClkInit.PLLSAI1.PLLSAI1N        = 8;
    PeriphClkInit.PLLSAI1.PLLSAI1P        = RCC_PLLP_DIV7;
    PeriphClkInit.PLLSAI1.PLLSAI1Q        = RCC_PLLQ_DIV2;
    PeriphClkInit.PLLSAI1.PLLSAI1R        = RCC_PLLR_DIV2;
    PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_ADC1CLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
    /** Configure the main internal regulator output voltage
     */
    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
    {
        Error_Handler();
    }
}


/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler()
{
    while (true)
    {
    }
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
    UNUSED(file);
    UNUSED(line);
    while (true)
    {
    }
}
#endif /* USE_FULL_ASSERT */

/*************************************************************************************************/
/**
 * @}
 */
/* ----- END OF FILE ----- */
