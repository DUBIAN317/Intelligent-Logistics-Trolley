/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ML_Front_A_CH1_Pin GPIO_PIN_0
#define ML_Front_A_CH1_GPIO_Port GPIOA
#define ML_Front_B_CH2_Pin GPIO_PIN_1
#define ML_Front_B_CH2_GPIO_Port GPIOA
#define ML_Behind_A_CH3_Pin GPIO_PIN_2
#define ML_Behind_A_CH3_GPIO_Port GPIOA
#define ML_Behind_B_CH4_Pin GPIO_PIN_3
#define ML_Behind_B_CH4_GPIO_Port GPIOA
#define MR_Behind_B_CH2_Pin GPIO_PIN_4
#define MR_Behind_B_CH2_GPIO_Port GPIOA
#define MR_Behind_A_CH1_Pin GPIO_PIN_6
#define MR_Behind_A_CH1_GPIO_Port GPIOA
#define MR_Front_A_CH3_Pin GPIO_PIN_0
#define MR_Front_A_CH3_GPIO_Port GPIOB
#define MR_Front_B_CH4_Pin GPIO_PIN_1
#define MR_Front_B_CH4_GPIO_Port GPIOB
#define servo_elevator_CH1_Pin GPIO_PIN_8
#define servo_elevator_CH1_GPIO_Port GPIOA
#define servo_grippawl_CH2_Pin GPIO_PIN_9
#define servo_grippawl_CH2_GPIO_Port GPIOA
#define servo_pallet_CH3_Pin GPIO_PIN_10
#define servo_pallet_CH3_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
