/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

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
#define BUTTON1_Pin GPIO_PIN_5
#define BUTTON1_GPIO_Port GPIOA
#define TESEO_WKUP_Pin GPIO_PIN_1
#define TESEO_WKUP_GPIO_Port GPIOB
#define TESEO_NRST_Pin GPIO_PIN_2
#define TESEO_NRST_GPIO_Port GPIOB
#define RYLR_3V3_EN_Pin GPIO_PIN_12
#define RYLR_3V3_EN_GPIO_Port GPIOB
#define MAG_ACC_DRDY_Pin GPIO_PIN_13
#define MAG_ACC_DRDY_GPIO_Port GPIOB
#define MAG_ACC_INT1_Pin GPIO_PIN_14
#define MAG_ACC_INT1_GPIO_Port GPIOB
#define LED_DATA_Pin GPIO_PIN_15
#define LED_DATA_GPIO_Port GPIOB
#define MAG_ACC_INT2_Pin GPIO_PIN_6
#define MAG_ACC_INT2_GPIO_Port GPIOC
#define TESEO_3V3_EN_Pin GPIO_PIN_7
#define TESEO_3V3_EN_GPIO_Port GPIOC
#define SD_DETECT_Pin GPIO_PIN_8
#define SD_DETECT_GPIO_Port GPIOA
#define RYLR998_UART_TX_Pin GPIO_PIN_9
#define RYLR998_UART_TX_GPIO_Port GPIOA
#define RYLR998_UART_RX_Pin GPIO_PIN_10
#define RYLR998_UART_RX_GPIO_Port GPIOA
#define RYLR998_NRST_Pin GPIO_PIN_11
#define RYLR998_NRST_GPIO_Port GPIOA
#define ACC_MAG_1V8_EN_Pin GPIO_PIN_12
#define ACC_MAG_1V8_EN_GPIO_Port GPIOA
#define BUTTON2_Pin GPIO_PIN_8
#define BUTTON2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
