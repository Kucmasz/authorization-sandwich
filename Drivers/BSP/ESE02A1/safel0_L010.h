/**
 ******************************************************************************
  * @file    safel0_L010.h
  * @author  SRA-SAIL, STM32ODE
  * @brief   header of SAFE expansion board based on stsafe1xx series devices
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
#ifndef __SAFEL0XX_H
#define __SAFEL0XX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stsafel010.h" 
#include "stse_conf.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup X_NUCLEO_ESE02A1
  * @{
  */

/* Exported types ------------------------------------------------------------*/


/**
 * @brief  STSAFE enumerator definition
 */

/**

  * @}
  */
/* Exported constants --------------------------------------------------------*/
/** @defgroup SAFEL0_Exported_Constants   STSAFE L010 Exported Constants
  * @{
  */


/* External variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define STSE_FRAME_CRC_SIZE             2U
#define STSE_FRAME_LENGTH_SIZE          2U
#define STSE_RSP_FRAME_HEADER_SIZE      1U
   
#define STSAFE_INSTANCES                3U
#define SAFEA1_A110_0                   0U
#define SAFEA1_A120_0                   1U
#define SAFEL_010_0                     2U
/* Exported functions ------------------------------------------------------- */
/** @defgroup SAFEL0_Exported_Functions   STSAFE L010 Exported Functions
  * @{
  */
int32_t STSE01_DeInit(uint32_t Instance);
int32_t STSE01_Init(uint32_t Instance);
int32_t SAFEL0_Transmit(uint32_t Instance, uint16_t DevAddr, uint8_t *pData, uint16_t Length);
int32_t SAFEL0_Receive(uint32_t Instance, uint16_t DevAddr, uint8_t *pData, uint16_t Length);
int32_t SAFEL0_Lx0_Wakeup(uint32_t Instance);

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
#endif /* __SAFEL0XX_H */

