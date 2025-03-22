/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "key.h"
#include "ec11.h"
#include "dht11.h"
#include "timer.h"
#include "st7735s.h"
#include "image.h"
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static uint32_t timerCounter = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	timerCounter++;
	HAL_GPIO_TogglePin(testIO_GPIO_Port, testIO_Pin);
	Ec11StateMachineProcess();
	Dht11Process();
}

void ProcessKey()
{
	static uint32_t lastTick = 0;
	uint32_t currentTick = HAL_GetTick();
	if (currentTick - lastTick < 1) {
		return;
	}
	lastTick = currentTick;

	KeyInfo keyInfo;
	uint8_t remainCount = 0;
	uint8_t ret = 0;
	do {
		GetKeyState(&keyInfo, &remainCount, &ret);
		if (ret != 0) {
			static char message[300];
			sprintf(message,
					"read %s keyState(%s,%d) encodeCounter(%ld) remain count(%d)"
					" timer count(%ld)\n",
					GetKeyName(keyInfo.keyIndex),
					GetKeyEventName(keyInfo.keyState), keyInfo.keyState,
					keyInfo.encodeCounter, remainCount,
					timerCounter);

			send_data_safely(message, strlen(message));

			if (keyInfo.keyIndex == EC11_KEY) {
				if (keyInfo.keyState == EC11_KEY_PRESS) {

				} else if (keyInfo.keyState == EC11_KEY_CLICK) {
					HAL_GPIO_TogglePin(Led0_GPIO_Port, Led0_Pin);
				} else if (keyInfo.keyState == EC11_KEY_DOUBLE_CLICK) {
					HAL_GPIO_TogglePin(testIO_GPIO_Port, testIO_Pin);
					delay_us(20);
					HAL_GPIO_TogglePin(testIO_GPIO_Port, testIO_Pin);
					static char msg[100];
					sprintf(msg, "%s\n", "testxxxx");
					send_data_safely(msg, strlen(msg));
				}
			}
		}

	} while (remainCount != 0);
}

void ProcessDth11()
{
	static uint32_t lastTick = 0;
	uint32_t currentTick = HAL_GetTick();
	if (currentTick - lastTick < 1000) {
		return;
	}
	lastTick = currentTick;

	Dht11Result result;
	GetDht11Result(&result);
	static char message[100];
	sprintf(message, "humidity: %.2f, temperature: %.2f\n",
			result.humidity, result.temperature);
	send_data_safely(message, strlen(message));
}

void ProcessLcd()
{
	static uint32_t lastTick = 0;
	uint32_t currentTick = HAL_GetTick();
	if (currentTick - lastTick < 17) {
		return;
	}
	lastTick = currentTick;

	static uint16_t color = 0x0564;

//	const Rect rect = {{50, 10}, 30, 40};
//	LcdDrawRect(&rect, BLACK_RGB565);
//	LcdDrawBlock(100, 28, 30, 30, 0xF983);
//	LcdDrawLine(0, 0, 3, WHITE_RGB565, LINE_DIR_VERTICAL);
//	LcdDrawLine(10, 30, 25, WHITE_RGB565, LINE_DIR_HORIZONTAL);
//	if (color % 2 == 0) {
//		color += 33;
//	} else {
//		color += 55;
//	}

//	const Rect rect2 = {{10, 10}, 20, 20};
//	LcdDrawRect(&rect2, BLACK_RGB565);

	TFT_ShowChar(0, 0, 'A', 0x7564, YELLOW, 16, true);
	TFT_ShowChar(0, 16, 'B', BLUE, YELLOW, 16, true);
	TFT_ShowChar(0, 32, 'C', BLUE, YELLOW, 16, true);
	TFT_ShowChar(0, 48, 'D', BLUE, YELLOW, 16, true);
	TFT_ShowChar(0, 64, 'E', BLUE, YELLOW, 16, true);
	TFT_ShowChar(0, 80, 'F', BLUE, YELLOW, 16, true);
	TFT_ShowChar(0, 96, 'G', BLUE, YELLOW, 16, true);
	TFT_ShowChar(0, 112, 'H', BLUE, YELLOW, 16, true);
	TFT_ShowChar(0, 128, 'I', BLUE, YELLOW, 16, true);
	TFT_ShowChar(0, 144, 'J', BLUE, YELLOW, 16, true);

	LCD_ShowCharStr(40, 32, 80, "HELLO", YELLOW, BLACK, 16);
	LCD_ShowCharNumber(48,64,128,20,YELLOW,BLACK,12);
	LCD_ShowCharNumber(60,64,128,22,YELLOW,BLACK,12);

	TFT_ShowChar(64, 84, 'Y', BLUE, OLIVE, 32, true);

	// 图像rgb565数组使用utils目录下"image2rgb565scale.py 图片文件 宽 高"命令生成，
	// 可以不指定宽或者高，脚本自动按照图片原始的宽高比计算新的值
	static uint16_t xStart = 0;

	if (xStart > 0 && xStart <= 80) {
		LcdDrawBlock(0, 0, xStart, LCD_HEIGHT, color);
	}

	LcdDrawData(IMG_DATA, xStart, 0, IMG_WIDTH, IMG_HEIGHT);
//	LcdDrawData((uint8_t*)IMG_DATA, xStart, 0, IMG_WIDTH, IMG_HEIGHT);

	if (xStart >= 0 && xStart < 80) {
		LcdDrawBlock(xStart + IMG_WIDTH, 0, LCD_WIDTH - xStart - IMG_WIDTH, LCD_HEIGHT, color);
	}
	xStart++;
	xStart %= 81;
//	color += 100;


//	LcdDrawRgb565(IMG_DATA, 60, 0, IMG_WIDTH, IMG_HEIGHT);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM4_Init();
  MX_USART2_UART_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim4);
	Ec11EncoderInit();
	TIM3_Init();
	LcdInit();
	//	LcdClear(0x7564);
	//		ProcessLcd();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  ProcessKey();
	ProcessDth11();
	ProcessLcd();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
