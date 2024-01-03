#include "main.h"

int main(void) {
  HAL_Init();

  SystemClock_Config();

  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  BSP_LED_Init(LED5);
  BSP_LED_Init(LED6);
  UART_Init();

  UART_SendCommand(TCommandId::cmd_Start, 0, NULL);

  while (true) {
    Comm_ProcessMessages();
    HAL_Delay(500);
  }
}