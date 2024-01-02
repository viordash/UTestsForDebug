#include "main.h"

void Comm_ProcessMessages() {
	TCommandId command;
	uint8_t status;
	uint8_t payload[6];

	if (CAN_HandleReceivingCommands(&command, &status, payload, sizeof(payload)) == 0) {
		return;
	}

	switch (command) {
	case TCommandId::cmd_Start:
		Perform_Command_Start();

		CAN_SendCommand(TCommandId::cmd_GetStatus, 1, payload);
		break;

	case TCommandId::cmd_GetStatus:
		Perform_Command_GetStatus();

		CAN_SendCommand(TCommandId::cmd_VeryDifficult, 2, payload);
		break;

	case TCommandId::cmd_VeryDifficult:
		Perform_Command_VeryDifficult();

		CAN_SendCommand(TCommandId::cmd_Start, 0, payload);
		break;

	default:
		break;
	}
}