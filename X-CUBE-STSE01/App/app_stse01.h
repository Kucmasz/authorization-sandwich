/**
  ******************************************************************************
  * @file           : app_stse01.h
  * @brief          :  This file provides code for the configuration
  *                    of the STMicroelectronics.X-CUBE-STSE01.2.0.0 instances.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_STSE01_H
#define __APP_STSE01_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "stse_conf.h"

/* Exported Functions --------------------------------------------------------*/
void MX_X_CUBE_STSE01_Init(void);
void MX_X_CUBE_STSE01_Process(void);

void MX_STSE01_MULTI_STEP_AUTHENTICATION_Init(void);
void MX_STSE01_MULTI_STEP_AUTHENTICATION_Process(void);

#ifdef __cplusplus
}
#endif
#endif /* __APP_STSE01_H */

