/**
 * @file main.c
 * @author Grant Wilk
 * @created 2/09/2020
 * @modified 2/11/2020
 * @brief a music player application
 */

# include "main.h"
# include "music_player.h"

/**
 * Private variables
 */
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;

/**
 * Function prototypes
 */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM5_Init(void);

/**
 * The application entry point
 * @return execution status
 */
int main(void) {
    // reset peripherals, initialize flash interface, and initialize systick
    HAL_Init();

    // configure system clock
    SystemClock_Config();

    // initialize peripherals
    MX_GPIO_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_TIM5_Init();

    // configure user button as input
    GPIOC->MODER |= (GPIO_MODE_INPUT << GPIO_MODER_MODER13_Pos);
    GPIOC->PUPDR |= (GPIO_PULLUP << GPIO_PUPDR_PUPD13_Pos);

    while (1) {

        // wait for the button to be pressed
        while (GPIOC->IDR & GPIO_IDR_ID13);

        // initialize music player
        mp_init();

        // the notes of the song
        mp_note notes[] = {
                {MP_INSTR_REST, MP_NOTE_QUARTER, 0,   MP_INSTR_KICK},
                {MP_INSTR_REST, MP_NOTE_EIGTH,   0,   MP_INSTR_HAT},

                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   440, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 494, MP_INSTR_NONE},
                {MP_INSTR_REST, MP_NOTE_EIGTH,   0,   MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   440, MP_INSTR_KICK},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   440, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   392, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 370, MP_INSTR_KICK},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 370, MP_INSTR_NONE},

                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 740, MP_INSTR_HAT},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER + MP_NOTE_EIGTH, 370, MP_INSTR_KICK},
                {MP_INSTR_REST, MP_NOTE_EIGTH,   0,   MP_INSTR_NONE},

                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   370, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   330, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   294, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   330, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 370, MP_INSTR_KICK},

                {MP_INSTR_KICK, MP_NOTE_QUARTER, 0,   MP_INSTR_NONE},
                {MP_INSTR_KICK, MP_NOTE_QUARTER, 0,   MP_INSTR_NONE},
                {MP_INSTR_KICK, MP_NOTE_QUARTER, 0,   MP_INSTR_NONE},

                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 494, MP_INSTR_NONE},
                {MP_INSTR_REST, MP_NOTE_QUARTER, 0,   MP_INSTR_NONE},

                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 494, MP_INSTR_NONE},
                {MP_INSTR_REST, MP_NOTE_EIGTH,   0,   MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   370, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   440, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   392, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 370, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 370, MP_INSTR_NONE},

                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   370, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   440, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 370, MP_INSTR_NONE},
                {MP_INSTR_REST, MP_NOTE_QUARTER, 0,   MP_INSTR_NONE},

                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   370, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   330, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   294, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   330, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER + MP_NOTE_EIGTH, 370, MP_INSTR_NONE},

                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   588, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   588, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   588, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   588, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   659, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 740, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 659, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 588, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 494, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 440, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 588, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 494, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 392, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_WHOLE,   370, MP_INSTR_NONE},

                {MP_INSTR_KICK, MP_NOTE_QUARTER, 0,   MP_INSTR_NONE},
                {MP_INSTR_REST, MP_NOTE_QUARTER, 0,   MP_INSTR_NONE},
                {MP_INSTR_KICK, MP_NOTE_EIGTH,   0,   MP_INSTR_NONE},
                {MP_INSTR_KICK, MP_NOTE_EIGTH,   0,   MP_INSTR_NONE},
                {MP_INSTR_REST, MP_NOTE_EIGTH,   0,   MP_INSTR_NONE},

                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   659, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 740, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 659, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 588, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 494, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 440, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 588, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 494, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 392, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER + MP_NOTE_EIGTH, 740, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   880, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_HALF,    740, MP_INSTR_NONE},

                {MP_INSTR_KICK, MP_NOTE_EIGTH,   0,   MP_INSTR_NONE},
                {MP_INSTR_KICK, MP_NOTE_EIGTH,   0,   MP_INSTR_NONE},
                {MP_INSTR_REST, MP_NOTE_EIGTH,   0,   MP_INSTR_NONE},
                {MP_INSTR_KICK, MP_NOTE_EIGTH,   0,   MP_INSTR_NONE},
                {MP_INSTR_KICK, MP_NOTE_EIGTH,   0,   MP_INSTR_NONE},
                {MP_INSTR_REST, MP_NOTE_QUARTER, 0,   MP_INSTR_NONE},

                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   659, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 740, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 659, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 588, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 494, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 440, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 588, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 494, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_QUARTER, 392, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_WHOLE,   370, MP_INSTR_NONE},

                {MP_INSTR_KICK, MP_NOTE_EIGTH,   0,   MP_INSTR_NONE},
                {MP_INSTR_REST, MP_NOTE_QUARTER + MP_NOTE_EIGTH, 0,   MP_INSTR_NONE},

                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   370, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   330, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   294, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   330, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_WHOLE,   370, MP_INSTR_NONE},

                {MP_INSTR_KICK, MP_NOTE_EIGTH,   0,   MP_INSTR_NONE},
                {MP_INSTR_KICK, MP_NOTE_EIGTH,   0,   MP_INSTR_NONE},
                {MP_INSTR_REST, MP_NOTE_QUARTER, 0,   MP_INSTR_NONE},

                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   370, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   330, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   294, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_EIGTH,   330, MP_INSTR_NONE},
                {MP_INSTR_KEYS, MP_NOTE_WHOLE,   294, MP_INSTR_NONE},
                {MP_INSTR_KICK, MP_NOTE_EIGTH,   0,   MP_INSTR_NONE},

                {MP_INSTR_END}

        };

        mp_song song = {notes};

        mp_add_song(&song);

        mp_play();

    }

}

/**
 * Configures the system clock with CubeMX settings
 */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
        Error_Handler();
    }
}

/**
 * Configures TIM2 with CubeMX settings
 */
static void MX_TIM2_Init(void) {

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 16000;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 0;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }

    // enable output compare on TIM2 channel 1
    TIM2->CCER |= TIM_CCER_CC1E;

}

/**
 * Configures TIM3 with CubeMX settings
 */
static void MX_TIM3_Init(void) {

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 400;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 91;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim3) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_TIM_OC_Init(&htim3) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_OC_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) {
        Error_Handler();
    }

    HAL_TIM_MspPostInit(&htim3);

    // enable output compare on TIM3 channel 1
    TIM3->CCER |= TIM_CCER_CC1E;

}

/**
 * Configures TIM4 with CubeMX settings
 */
static void MX_TIM4_Init(void) {

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    htim4.Instance = TIM4;
    htim4.Init.Prescaler = 400;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = 91;
    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim4) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_TIM_OC_Init(&htim4) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_OC_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) {
        Error_Handler();
    }

    HAL_TIM_MspPostInit(&htim4);

    // enable output compare on TIM4 channel 1
    TIM4->CCER |= TIM_CCER_CC1E;

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void) {

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim5.Instance = TIM5;
    htim5.Init.Prescaler = 16000;
    htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim5.Init.Period = 0;
    htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim5) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }

    // enable output compare on TIM5 channel 1
    TIM5->CCER |= TIM_CCER_CC1E;

}

/**
 * Configures GPIO ports with CubeMX settings
 */
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : B1_Pin */
    GPIO_InitStruct.Pin = B1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : LD2_Pin */
    GPIO_InitStruct.Pin = LD2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/**
 * This function is executed in the case of an error occurrance
 */
void Error_Handler(void) {
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */