#include "stm32f4_discovery.h"
#include "stm32f4xx_hal.h"
#include "main.h"
#include "string.h"

CAN_HandleTypeDef CanHandle;
uint32_t TxMailbox;

typedef struct {
	uint8_t Id;
	uint8_t Status;
	uint8_t Payload[6];
} __attribute__((packed)) TCommand;

void CAN_Init(bool loopback) {
	CAN_FilterTypeDef sFilterConfig;

	/*##-1- Configure the CAN peripheral #######################################*/
	CanHandle.Instance = CANx;

	CanHandle.Init.TimeTriggeredMode = DISABLE;
	CanHandle.Init.AutoBusOff = DISABLE;
	CanHandle.Init.AutoWakeUp = DISABLE;
	CanHandle.Init.AutoRetransmission = ENABLE;
	CanHandle.Init.ReceiveFifoLocked = DISABLE;
	CanHandle.Init.TransmitFifoPriority = DISABLE;
	CanHandle.Init.Mode = loopback ? CAN_MODE_LOOPBACK : CAN_MODE_NORMAL;
	CanHandle.Init.SyncJumpWidth = CAN_SJW_1TQ;
	CanHandle.Init.TimeSeg1 = CAN_BS1_4TQ;
	CanHandle.Init.TimeSeg2 = CAN_BS2_2TQ;
	CanHandle.Init.Prescaler = 6;

	if(HAL_CAN_Init(&CanHandle) != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}

	/*##-2- Configure the CAN Filter ###########################################*/
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;

	if(HAL_CAN_ConfigFilter(&CanHandle, &sFilterConfig) != HAL_OK) {
		/* Filter configuration Error */
		Error_Handler();
	}

	/*##-3- Start the CAN peripheral ###########################################*/
	if(HAL_CAN_Start(&CanHandle) != HAL_OK) {
		/* Start Error */
		Error_Handler();
	}
}

void CAN_SendCommand(TCommandId id, uint8_t status, uint8_t *payload) {
	CAN_TxHeaderTypeDef header;
	TCommand command = { };
	command.Id = id;
	command.Status = status;
	if(payload != NULL) {
		memcpy(command.Payload, payload, sizeof(command.Payload));
	}

	/*##-4- Start the Transmission process #####################################*/
	header.StdId = 0x11;
	header.RTR = CAN_RTR_DATA;
	header.IDE = CAN_ID_STD;
	header.DLC = sizeof(command);
	header.TransmitGlobalTime = DISABLE;

	/* Request transmission */
	if(HAL_CAN_AddTxMessage(&CanHandle, &header, (uint8_t *)&command, &TxMailbox) != HAL_OK) {
		/* Transmission request Error */
		Error_Handler();
	}

	/* Wait transmission complete */
	while(HAL_CAN_GetTxMailboxesFreeLevel(&CanHandle) != 3) {
		BSP_LED_Toggle(LED3);
		HAL_Delay(100);
	}
}

bool CAN_HandleReceivingCommands(TCommandId *id, uint8_t *status, uint8_t *payload, size_t payload_size) {
	CAN_RxHeaderTypeDef header;
	TCommand command = { };

	/*##-5- Start the Reception process ########################################*/
	if(HAL_CAN_GetRxFifoFillLevel(&CanHandle, CAN_RX_FIFO0) != 1) {
		/* Reception Missing */
		Error_Handler();
	}

	if(HAL_CAN_GetRxMessage(&CanHandle, CAN_RX_FIFO0, &header, (uint8_t *)&command) != HAL_OK) {
		/* Reception Error */
		return false;
	}

	if((header.StdId != 0x11) ||
		(header.RTR != CAN_RTR_DATA) ||
		(header.IDE != CAN_ID_STD) ||
		(header.DLC != sizeof(command))) {
		/* Rx message Error */
		return false;
	}
	*id = (TCommandId)command.Id;
	*status = command.Status;
	memcpy(payload, command.Payload, payload_size);
	return true;
}