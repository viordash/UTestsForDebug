#include "main.h"
#include "stm32f4_discovery.h"
#include "stm32f4xx_hal.h"
#include "string.h"

UART_HandleTypeDef UartHandle;

static uint16_t Buffercmp(uint8_t *pBuffer1, uint8_t *pBuffer2, uint16_t BufferLength);

typedef struct {
	uint8_t Id;
	uint8_t Status;
	uint8_t Payload[256];
} __attribute__((packed)) TCommand;

void UART_Init() {
	/*##-1- Configure the UART peripheral ######################################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART1 configured as follow:
      - Word Length = 8 Bits
      - Stop Bit = One Stop bit
      - Parity = None
      - BaudRate = 9600 baud
      - Hardware flow control disabled (RTS and CTS signals) */
	UartHandle.Instance = USARTx;

	UartHandle.Init.BaudRate = 9600;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits = UART_STOPBITS_1;
	UartHandle.Init.Parity = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&UartHandle) != HAL_OK) {
		Error_Handler();
	}
}

void UART_SendCommand(TCommandId id, uint8_t status, uint8_t *payload) {
	TCommand command = {};
	command.Id = id;
	command.Status = status;
	if (payload != NULL) {
		memcpy(command.Payload, payload, sizeof(command.Payload));
	}

	/* The board sends the message */

	/*##-2- Start the transmission process #####################################*/
	/* While the UART in reception process, user can transmit data through 
     "aTxBuffer" buffer */
	if (HAL_UART_Transmit(&UartHandle, (uint8_t *)&command, sizeof(command), 5000) != HAL_OK) {
		Error_Handler();
	}
}

bool UART_HandleReceivingCommands(TCommandId *id, uint8_t *status, uint8_t *payload, size_t payload_size) {
	TCommand command = {};

	/*##-3- Put UART peripheral in reception process ###########################*/
	if (HAL_UART_Receive(&UartHandle, (uint8_t *)&command, sizeof(command), 5000) != HAL_OK) {
		BSP_LED_Toggle(LED3);
		return false;
	}

	*id = (TCommandId)command.Id;
	*status = command.Status;
	memcpy(payload, command.Payload, payload_size);
	return true;
}

/**
  * @brief  UART error callbacks
  * @param  UartHandle: UART handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle) {
	/* Turn LED3 on: Transfer error in reception/transmission process */
	BSP_LED_On(LED3);
}