/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32l1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "math.h"
#include "delay.h"
#include "std.h"
#include "g_structs.h"
#include "csl_memory.h"
#include "peref.h" 
#include "g_Rom.h"  
#include "g_Core.h"  
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define VERSION 25.11.20

#define HZ					10e3		// Частота основного прерывания RTOS
#define PRD_2KHZ				2000		// Периодическая задача 2000 Гц
#define PRD_200HZ				200			// Периодическая задача 200 Гц
#define PRD_50HZ				50			// Периодическая задача 50 Гц
#define PRD_10HZ				10			// Периодическая задача 10 Гц
#define PRD_50HZ				50			// Периодическая задача 50 Гц
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
// Макрос статической проверки, который проверяет истинность выражения "expr"
// если выражение ложно, макрос выводит сообщение об ошибке во время компиляции
#define CONCAT2(First, Second) (First ## Second)
#define CONCAT(First, Second) CONCAT2(First, Second)
#define STATIC_ASSERT(expr) typedef char CONCAT(static_assert_failed_at_line_, __LINE__) [(expr) ? 1 : -1]
  
  
  // Чтение всех параметров
#define ReadAllParams() 			ReadPar(RAM_ADR, &g_Ram, RAM_DATA_SIZE)
// Запись всех параметров
#define WriteAllParams()			WritePar(RAM_ADR, &g_Ram, RAM_DATA_SIZE)
  
  // Адрес элемента в структуре параметров
#define GetAdr(Elem)			((LgUns)&(((TDriveData *)RAM_ADR)->Elem)>>2)
#define SIZE(ELEM)                      (sizeof(ELEM)>> 2)
  
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void emptyFunc(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DE_485_Pin GPIO_PIN_13
#define DE_485_GPIO_Port GPIOC
#define ADC_TEMP_Pin GPIO_PIN_0
#define ADC_TEMP_GPIO_Port GPIOA
#define PEREM_Pin GPIO_PIN_1
#define PEREM_GPIO_Port GPIOA
#define LCD_LOAD_Pin GPIO_PIN_4
#define LCD_LOAD_GPIO_Port GPIOA
#define WP_FRAM_Pin GPIO_PIN_2
#define WP_FRAM_GPIO_Port GPIOB
#define TX_485_Pin GPIO_PIN_10
#define TX_485_GPIO_Port GPIOB
#define RX_485_Pin GPIO_PIN_11
#define RX_485_GPIO_Port GPIOB
#define LCD_ON_Pin GPIO_PIN_12
#define LCD_ON_GPIO_Port GPIOB
#define LCD_SPI_SCK_Pin GPIO_PIN_13
#define LCD_SPI_SCK_GPIO_Port GPIOB
#define LCD_SPI_MOSI_Pin GPIO_PIN_15
#define LCD_SPI_MOSI_GPIO_Port GPIOB
#define IRDA_RX_Pin GPIO_PIN_9
#define IRDA_RX_GPIO_Port GPIOA
#define IRDA_TX_Pin GPIO_PIN_10
#define IRDA_TX_GPIO_Port GPIOA
#define IRDA_SD_Pin GPIO_PIN_11
#define IRDA_SD_GPIO_Port GPIOA
#define SB1_Pin GPIO_PIN_15
#define SB1_GPIO_Port GPIOA
#define SB2_Pin GPIO_PIN_3
#define SB2_GPIO_Port GPIOB
#define SB3_Pin GPIO_PIN_4
#define SB3_GPIO_Port GPIOB
#define V30_ON_Pin GPIO_PIN_5
#define V30_ON_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
extern I2C_HandleTypeDef hi2c1;
extern ADC_HandleTypeDef hadc;
extern RTC_TimeTypeDef Time;
extern RTC_DateTypeDef Date;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
