#include <stm32f4xx_hal.h>
#include <CppUTest/CommandLineTestRunner.h>

//#ifdef __cplusplus
//extern "C"
//#endif
//void SysTick_Handler(void) {
//	HAL_IncTick();
//	HAL_SYSTICK_IRQHandler();
//}

int main(void) {
	HAL_Init();

	const char *p = "";
	CommandLineTestRunner::RunAllTests(0, &p);
	return 0;
}
