#include "main.h"
#include <CppUTest/CommandLineTestRunner.h>
#include <stdio.h>

TEST_GROUP(CommunicationTestGroup){TEST_SETUP(){
        SystemClock_Config();
        CAN_Init(true);
}

TEST_TEARDOWN() {}
}
;

static Led_TypeDef led_On;
void BSP_LED_On(Led_TypeDef Led) { led_On = Led; }

static Led_TypeDef led_Off;
void BSP_LED_Off(Led_TypeDef Led) { led_Off = Led; }

static Led_TypeDef led_Toggle;
void BSP_LED_Toggle(Led_TypeDef Led) { led_Toggle = Led; }

TEST(CommunicationTestGroup, Debug_VeryDifficult_Case) {
  uint8_t payload[6] = {0, 1, 2, 3, 4, 5};

  CAN_SendCommand(TCommandId::cmd_VeryDifficult, 2, payload);
  Comm_ProcessMessages();

  CHECK_EQUAL_TEXT(LED6, led_On,
                   "Perform_Command_VeryDifficult was not called");
  CHECK_EQUAL_TEXT(LED5, led_Off,
                   "Perform_Command_VeryDifficult was not called");
}
