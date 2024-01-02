/**
  ******************************************************************************
  * @file    CAN/CAN_LoopBack/Inc/main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor CANx instance used and associated 
   resources */
/* Definition for CANx clock resources */
#define CANx CAN1
#define CANx_CLK_ENABLE() __HAL_RCC_CAN1_CLK_ENABLE()
#define CANx_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()

#define CANx_FORCE_RESET() __HAL_RCC_CAN1_FORCE_RESET()
#define CANx_RELEASE_RESET() __HAL_RCC_CAN1_RELEASE_RESET()

/* Definition for CANx Pins */
#define CANx_TX_PIN GPIO_PIN_12
#define CANx_TX_GPIO_PORT GPIOA
#define CANx_TX_AF GPIO_AF9_CAN1
#define CANx_RX_PIN GPIO_PIN_11
#define CANx_RX_GPIO_PORT GPIOA
#define CANx_RX_AF GPIO_AF9_CAN1

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

static inline void Error_Handler(void) {
	/* User may add here some code to deal with this error */
	/* Turn LED3 on */
	BSP_LED_On(LED3);
	while (1) {
	}
}

typedef enum { cmd_Start = 0,
			   cmd_GetStatus,
			   cmd_VeryDifficult
} TCommandId;

void CAN_Init(bool loopback);
void CAN_SendCommand(TCommandId id, uint8_t status, uint8_t *payload);
bool CAN_HandleReceivingCommands(TCommandId *id, uint8_t *status, uint8_t *payload, size_t payload_size);

void Comm_ProcessMessages();

/*Commands*/
static inline void Perform_Command_Start(void) {
	BSP_LED_On(LED4);
	BSP_LED_Off(LED5);
	BSP_LED_Off(LED6);
}

static inline void Perform_Command_GetStatus(void) {
	BSP_LED_Off(LED4);
	BSP_LED_On(LED5);
	BSP_LED_Off(LED6);
}

static inline void Perform_Command_VeryDifficult(void) {
	BSP_LED_Off(LED4);
	BSP_LED_Off(LED5);
	BSP_LED_On(LED6);
}

#endif /* __MAIN_H */
