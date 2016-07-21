/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"
#include "usb_device.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

void lcdDelay(void){
	uint32_t i;
	i = 0;
	while(i < 100000) i++;
}


uint8_t lcdReadBus(void){
	uint8_t data;
	
	// Configure bus as input
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.Pin = DISP_DB4_Pin|DISP_DB5_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = DISP_DB6_Pin|DISP_DB7_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	data = 0;
	if(HAL_GPIO_ReadPin(GPIOB,DISP_DB4_Pin))	data += 1;
	if(HAL_GPIO_ReadPin(GPIOB,DISP_DB5_Pin))	data += 2;
	if(HAL_GPIO_ReadPin(GPIOC,DISP_DB6_Pin))	data += 4;
	if(HAL_GPIO_ReadPin(GPIOC,DISP_DB7_Pin))	data += 8;
	
	return data;
}

void lcdWriteBus(uint8_t rs, uint8_t data){
	// Configure bus as output
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/*Configure GPIO pins : DISP_DB4_Pin DISP_DB5_Pin */
	GPIO_InitStruct.Pin = DISP_DB4_Pin|DISP_DB5_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : DISP_DB6_Pin DISP_DB7_Pin DISP_E_Pin DISP_RW_Pin */
	GPIO_InitStruct.Pin = DISP_DB6_Pin|DISP_DB7_Pin|DISP_E_Pin|DISP_RW_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : DISP_RS_Pin */
	GPIO_InitStruct.Pin = DISP_RS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DISP_RS_GPIO_Port, &GPIO_InitStruct);
	
	
	lcdDelay();
	if(rs)	HAL_GPIO_WritePin(DISP_RS_GPIO_Port, DISP_RS_Pin, GPIO_PIN_SET);
	else 	HAL_GPIO_WritePin(DISP_RS_GPIO_Port, DISP_RS_Pin, GPIO_PIN_RESET);
	
	
	HAL_GPIO_WritePin(GPIOC, DISP_RW_Pin, GPIO_PIN_RESET);
	
	lcdDelay();
	
	HAL_GPIO_WritePin(GPIOC, DISP_E_Pin, GPIO_PIN_SET);
	
	lcdDelay();
	
	if(data & 0x01)	HAL_GPIO_WritePin(GPIOB, DISP_DB4_Pin, GPIO_PIN_SET);
	else			HAL_GPIO_WritePin(GPIOB, DISP_DB4_Pin, GPIO_PIN_RESET);
		
	if(data & 0x02)	HAL_GPIO_WritePin(GPIOB, DISP_DB5_Pin, GPIO_PIN_SET);
	else			HAL_GPIO_WritePin(GPIOB, DISP_DB5_Pin, GPIO_PIN_RESET);
	
	if(data & 0x04)	HAL_GPIO_WritePin(GPIOC, DISP_DB6_Pin, GPIO_PIN_SET);
	else			HAL_GPIO_WritePin(GPIOC, DISP_DB6_Pin, GPIO_PIN_RESET);
		
	if(data & 0x08)	HAL_GPIO_WritePin(GPIOC, DISP_DB7_Pin, GPIO_PIN_SET);
	else			HAL_GPIO_WritePin(GPIOC, DISP_DB7_Pin, GPIO_PIN_RESET);
	
	lcdDelay();
	
	HAL_GPIO_WritePin(GPIOC, DISP_E_Pin, GPIO_PIN_RESET);
	
	lcdDelay();
}


void lcdInit(void){
	lcdWriteBus(0,0x03);
	
	lcdWriteBus(0,0x02);
	lcdWriteBus(0,0x0F);
	
	lcdWriteBus(0,0x02);
	lcdWriteBus(0,0x0F);
	
	lcdWriteBus(0,0x00);
	lcdWriteBus(0,0x0F);
	
	lcdWriteBus(0,0x00);
	lcdWriteBus(0,0x01);
	
	lcdWriteBus(0,0x00);
	lcdWriteBus(0,0x07);
	
	lcdWriteBus(0,0x08);
	lcdWriteBus(0,0x00);
	
	lcdWriteBus(1,0x03);
	lcdWriteBus(1,0x03);
	
}




/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
	
	uint8_t buffer[32];
	
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USB_DEVICE_Init();

  /* USER CODE BEGIN 2 */
	buffer[0] = 't';
	buffer[1] = 'e';
	buffer[2] = 's';
	buffer[3] = 't';
	buffer[4] = '\n';
	buffer[5] = '\r';
	
	HAL_UART_Transmit(&huart2, &buffer[0], 6, 10);
	
	
	lcdInit();
	
	
	//buffer[0] = lcdReadBus() + 65;
	//HAL_UART_Transmit(&huart2, &buffer[0], 1, 10);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */
	

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DISP_DB4_Pin|DISP_DB5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, DISP_DB6_Pin|DISP_DB7_Pin|DISP_E_Pin|DISP_RW_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DISP_RS_GPIO_Port, DISP_RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : DISP_DB4_Pin DISP_DB5_Pin */
  GPIO_InitStruct.Pin = DISP_DB4_Pin|DISP_DB5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : DISP_DB6_Pin DISP_DB7_Pin DISP_E_Pin DISP_RW_Pin */
  GPIO_InitStruct.Pin = DISP_DB6_Pin|DISP_DB7_Pin|DISP_E_Pin|DISP_RW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : DISP_RS_Pin */
  GPIO_InitStruct.Pin = DISP_RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DISP_RS_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
