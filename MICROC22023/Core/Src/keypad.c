/*
 * keypad.c
 *
 *  Created on: 29 may. 2023
 *      Author: wilki
 */

#include "stm32f3xx_hal.h"

#define Drive5_Pin GPIO_PIN_14
#define Drive5_GPIO_Port GPIOC
#define Drive6_Pin GPIO_PIN_15
#define Drive6_GPIO_Port GPIOC
#define Drive1_Pin GPIO_PIN_2
#define Drive1_GPIO_Port GPIOA
#define Drive2_Pin GPIO_PIN_3
#define Drive2_GPIO_Port GPIOA
#define Drive3_Pin GPIO_PIN_5
#define Drive3_GPIO_Port GPIOA
#define Drive4_Pin GPIO_PIN_1
#define Drive4_GPIO_Port GPIOB

void init_keypad(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOC, Drive5_Pin|Drive6_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOA, Drive1_Pin|Drive2_Pin|Drive3_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(Drive4_GPIO_Port, Drive4_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pins : Drive5_Pin Drive6_Pin */
	  GPIO_InitStruct.Pin = Drive5_Pin|Drive6_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  /*Configure GPIO pins : Drive1_Pin Drive2_Pin Drive3_Pin */
	  GPIO_InitStruct.Pin = Drive1_Pin|Drive2_Pin|Drive3_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pins : PA6 PA7 PA9 */
	  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_9;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pin : Drive4_Pin */
	  GPIO_InitStruct.Pin = Drive4_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(Drive4_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pin : PA10 */
	  GPIO_InitStruct.Pin = GPIO_PIN_10;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

char scan_key(void)
{
	char key = 0;
	GPIOC->ODR = GPIOC->ODR | 0x01;
	for (int i = 0; i < 3; ++i)
	{
		HAL_Delay(125);
		key = GPIOB->IDR >> 12 ;
		if(key != 0x00)
		{
			key = GPIOC->ODR << 4;
			key = key | GPIOB->IDR >> 12 ;
			GPIOC->ODR = GPIOC->ODR & 0XF0;
			switch (key) {
				case 0x11:
					key = '1';
					break;
				case 0x12:
					key = '2';
					break;
				case 0x14:
					key = '3';
					break;
				default:
					key = 0;
					break;
			}
			return key;
		}
		GPIOC->ODR = GPIOC->ODR << 1;
	}
	GPIOC->ODR = GPIOC->ODR & 0XF0;

	return 0;
}


