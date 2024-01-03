#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f4_discovery.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>

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

static inline void Error_Handler(void) {
  /* User may add here some code to deal with this error */
  /* Turn LED3 on */
  BSP_LED_On(LED3);
  while (1) {
  }
}

typedef enum { cmd_Start = 0, cmd_GetStatus, cmd_VeryDifficult } TCommandId;

void CAN_Init(bool loopback);
void CAN_SendCommand(TCommandId id, uint8_t status, uint8_t *payload);
bool CAN_HandleReceivingCommands(TCommandId *id, uint8_t *status,
                                 uint8_t *payload, size_t payload_size);

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

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 168000000
 *            HCLK(Hz)                       = 168000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 25000000
 *            PLL_M                          = 25
 *            PLL_N                          = 336
 *            PLL_P                          = 2
 *            PLL_Q                          = 7
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 5
 * @param  None
 * @retval None
 */
static inline void SystemClock_Config(void) {
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device
     is clocked below the maximum system frequency, to update the voltage
     scaling value regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                                 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
  if (HAL_GetREVID() == 0x1001) {
    /* Enable the Flash prefetch */
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
}

#endif /* __MAIN_H */
