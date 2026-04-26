/**
  ******************************************************************************
  * @file           : stse_conf.h
  * @author         : STMicroelectronics
  * @brief          : This file contains definitions for the SAFEA1 components bus interfaces
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
#ifndef STSAFE_CONF_H
#define STSAFE_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup STSAFEA
  * @{
  */

/** @defgroup STSAFEA_CONFIG
  * @{
  */

/** @defgroup STSAFEA_CONFIG_Exported_Constants
  * @{
  */

#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_bus.h"
#include "stm32f4xx_nucleo_errno.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "stse_platform_generic.h"

#define MCU_ERRNO_INCLUDE "stm32f4xx_nucleo_errno.h"

/* Global configuration ---------------------------------------------------*/
/* Defines ---------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
int32_t BSP_I2C1_Wake(void);
/* USER CODE END PFP */

#define SAFEA1_I2C_INIT                BSP_I2C1_Init
#define SAFEA1_I2C_DEINIT              BSP_I2C1_DeInit
#define SAFEA1_I2C_SEND                BSP_I2C1_Send
#define SAFEA1_I2C_RECEIVE             BSP_I2C1_Recv
#define SAFEA1_I2C_WAKEUP              BSP_I2C1_Wake
#define SAFEA1_DELAY                   HAL_Delay
#define STSAFEA_DEVICE_ADDRESS         0x0CU<<1U
extern I2C_HandleTypeDef hi2c1;
#define I2C_HANDLE hi2c1

#define SAFEA1_LED_GPIO_PORT GPIOA
#define SAFEA1_LED_GPIO_PIN GPIO_PIN_5
#define SAFEA1_BUTTON_PIN_PORT GPIOC
#define SAFEA1_BUTTON_PIN GPIO_PIN_13

#define STSE_CONF_USE_I2C

#define STSE_CONF_STSAFE_L_SUPPORT

/************************************************************
  *                STSAFE-L API/SERVICE SETTINGS
  ************************************************************/
#ifdef STSE_CONF_STSAFE_L_SUPPORT

#ifndef STSE_CONF_HASH_SHA_256
#define STSE_CONF_HASH_SHA_256
#endif /*STSE_CONF_HASH_SHA_256*/

#ifndef STSE_CONF_ECC_CURVE_25519
#define STSE_CONF_ECC_CURVE_25519
#endif /*STSE_CONF_ECC_CURVE_25519*/

#ifndef STSE_CONF_ECC_EDWARD_25519
#define STSE_CONF_ECC_EDWARD_25519
#endif /*STSE_CONF_ECC_EDWARD_25519*/

#define STSE_CONF_USE_I2C
/*#define STSE_CONF_USE_ST1WIRE */

#endif /* STSE_CONF_STSAFE_L_SUPPORT */

#if defined(__ICCARM__)
/* New definition from EWARM V9, compatible with EWARM8 */
#ifndef PLAT_PACKED_STRUCT
#define PLAT_PACKED_STRUCT __PACKED
#endif /* PLAT_PACKED_STRUCT */

#elif defined (__CC_ARM) || defined(__ARMCC_VERSION)
/* ARM Compiler 5/6 */
#ifndef PLAT_PACKED_STRUCT
#define PLAT_PACKED_STRUCT __packed
#endif /* PLAT_PACKED_STRUCT */
#ifndef __WEAK
#define __WEAK             __attribute__((weak))
#endif /* __WEAK */

#elif defined(__GNUC__)
#ifndef PLAT_PACKED_STRUCT
#define PLAT_PACKED_STRUCT __packed
#endif /* PLAT_PACKED_STRUCT */
#ifndef __WEAK
#define __WEAK             __attribute__((weak))
#endif /* __WEAK */
#endif /* __ICCARM__ */
/************************************************************
  *                TARGET STSAFE SETTINGS
  ************************************************************
  * This section should be modified according to the
  * personalization options enabled in target STSAFE devices
  ************************************************************/
#define STSAFE_USE_PAIRING_KEY
#define STSAFE_USE_STSAFE_COMPANION
#define STSE_USE_RSP_POLLING
#define STSE_MAX_POLLING_RETRY         100
#define STSE_FIRST_POLLING_INTERVAL    10
#define STSE_POLLING_RETRY_INTERVAL    10
/* #define STSAFE_FRAME_DEBUG_LOG */

/************************************************************
  *                HOST / CA KEYS SETTINGS
  ************************************************************
  * This section should be modified according to the
  * personalization options enabled in target STSAFE devices
  ************************************************************/
#define STSAFE_USE_ENGINEERING_HOST_KEY_PAIR
#define STSAFE_USE_RANDOM_HOST_KEY_PAIR
#define STSAFE_USE_ENGINEERING_CA_PUB_KEY

/************************************************************
  *                HOST/STSAFE I2C SETTINGS
  ************************************************************/
#define STSAFE_I2C_STATIC
/* #define STSAFE_I2C_DYNAMIC */

#if defined(STSAFE_I2C_STATIC) && defined(STSAFE_I2C_DYNAMIC)
#error Define only one HOST/STSAFE I2C setting !!!
#endif /* (STSAFE_I2C_STATIC) && defined(STSAFE_I2C_DYNAMIC) */

/**
  * @}
  */
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STSAFE_CONF_H*/

