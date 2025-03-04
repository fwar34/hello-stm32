#include "key.h"
#include "stm32f1xx_hal.h"
#include "string.h"
#include "stdio.h"

extern UART_HandleTypeDef huart2;

static KeyNum keyNum = KEY_INVALID;

int8_t GetKeyNum()
{
	int8_t ret = keyNum;
	if (keyNum != KEY_INVALID) {
		keyNum = KEY_INVALID;
	}
	return ret;
}

void KeyTickProcess()
{
	static uint8_t keyCurState = 0;
	GPIO_PinState keyPrevState = keyCurState;
	keyCurState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10);

	static char message[100];
	sprintf(message, "prev = %d, current = %d\n", keyPrevState, keyCurState);
//	HAL_UART_Transmit_IT(&huart2, (uint8_t*)message, strlen(message));
	if (keyPrevState == GPIO_PIN_RESET && keyCurState != GPIO_PIN_RESET) {
		keyNum = KEY_0;
		const char* keyProcessMsg = "Key0 pressed!\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)keyProcessMsg, strlen(keyProcessMsg), 0);
	}
}
