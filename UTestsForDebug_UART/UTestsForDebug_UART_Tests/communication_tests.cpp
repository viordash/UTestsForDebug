#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <CppUTest/CommandLineTestRunner.h>

#include "main.h"
#include <stdio.h>

TEST_GROUP(CommunicationTestGroup){TEST_SETUP(){SystemClock_Config();
}
TEST_TEARDOWN() { mock().clear(); }
}
;

TEST(CommunicationTestGroup, Debug_VeryDifficult_Case) {
  TCommandId id;

  id = TCommandId::cmd_VeryDifficult;

  mock()
      .expectOneCall("UART_HandleReceivingCommands")
      .withOutputParameterReturning("id", &id, sizeof(id))
      .andReturnValue(true);

  mock()
      .expectOneCall("UART_SendCommand")
      .withParameter("id", TCommandId::cmd_Start)
      .withParameter("status", 0);

  mock().expectOneCall("BSP_LED_On").withParameter("Led", LED6);
  mock().expectOneCall("BSP_LED_Off").withParameter("Led", LED4);
  mock().expectOneCall("BSP_LED_Off").withParameter("Led", LED5);

  Comm_ProcessMessages();

  mock().checkExpectations();
}

/* mocking work module*/

void UART_Init() { mock().actualCall("UART_Init"); }

void UART_SendCommand(TCommandId id, uint8_t status, uint8_t *payload) {
  (void)payload;

  mock()
      .actualCall("UART_SendCommand")
      .withIntParameter("id", id)
      .withUnsignedIntParameter("status", status);
}

bool UART_HandleReceivingCommands(TCommandId *id, uint8_t *status,
                                  uint8_t *payload, size_t payload_size) {
  (void)status;
  (void)payload;
  (void)payload_size;

  return mock()
      .actualCall("UART_HandleReceivingCommands")
      .withOutputParameter("id", id)
      .returnBoolValue();
}

void BSP_LED_On(Led_TypeDef Led) {
  mock().actualCall("BSP_LED_On").withIntParameter("Led", Led);
}

void BSP_LED_Off(Led_TypeDef Led) {
  mock().actualCall("BSP_LED_Off").withIntParameter("Led", Led);
}

void BSP_LED_Toggle(Led_TypeDef Led) {
  mock().actualCall("BSP_LED_Toggle").withIntParameter("Led", Led);
}
