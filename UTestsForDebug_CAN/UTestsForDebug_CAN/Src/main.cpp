/**
  ******************************************************************************
  * @file    CAN/CAN_LoopBack/Src/main.c 
  * @author  MCD Application Team
  * @brief   This example provides a description of how to set a communication 
  *          with the CAN in loopback mode.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup CAN_LoopBack
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void) {

	/* STM32F4xx HAL library initialization:
	     - Configure the Flash prefetch, instruction and Data caches
	     - Configure the Systick to generate an interrupt each 1 msec
	     - Set NVIC Group Priority to 4
	     - Global MSP (MCU Support Package) initialization
	*/
	HAL_Init();

	/* Configure the system clock to 168 MHz */
	SystemClock_Config();

	/* Configure LEDx */
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	BSP_LED_Init(LED6);
	CAN_Init(false);

	CAN_SendCommand(TCommandId::cmd_Start, 0, NULL);

	/* Infinite loop */
	while (true) {
		Comm_ProcessMessages();
		HAL_Delay(500);
	}
}

/**
  * @}
  */

/**
  * @}
  */
