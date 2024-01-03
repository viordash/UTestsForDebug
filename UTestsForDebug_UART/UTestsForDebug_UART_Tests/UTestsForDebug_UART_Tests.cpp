#include <CppUTest/CommandLineTestRunner.h>
#include <stm32f4xx_hal.h>

int main(void) {
  HAL_Init();

  const char *p = "";
  CommandLineTestRunner::RunAllTests(0, &p);
  return 0;
}
