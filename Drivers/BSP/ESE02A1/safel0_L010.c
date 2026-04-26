/**
  * ******************************************************************************
  * @file	   safel0_L010.c
  * @brief   This file provides X-NUCLEO-ESE02A1 Board 
  *          specific functions
  * @author  SRA-SAIL, STM32ODE
  *
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

/* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include "safel0_L010.h"

/** @addtogroup BSP
 * @{
 */
static STSAFEL0x0_CommonDrv_t *SAFEL0Drv[STSAFE_INSTANCES];
void *SAFEL0CompObj[STSAFE_INSTANCES];

/** @defgroup STSAFEA110 Function Prototypes
 * @{
 */

static int32_t STSAFEL_010_Probe(void);

/* Global variables ----------------------------------------------------------*/

/**
 * @}
 */

/** @defgroup SAFEA1_A1x0_Exported_Functions 
 * @{
 */
/**
 * @brief  Initializes the I2C STSAFE
 * @param  Instance : I2C STSAFE instance to be used
 * @retval BSP status
 */
int32_t STSE01_Init(uint32_t Instance)
{
  int32_t ret = BSP_ERROR_NONE;
  
  switch (Instance)
  {

  case SAFEL_010_0:
    if (STSAFEL_010_Probe() != BSP_ERROR_NONE)
      {
        return BSP_ERROR_NO_INIT;
      }
    break;
   default:
    ret = BSP_ERROR_WRONG_PARAM;
    break;
  }
  
  return ret;
}  

/**
 * @brief  Deinitialize environmental sensor
 * @param  Instance : I2C STSAFE instance to be used
 * @retval BSP status
 */
int32_t SAFEA1_DeInit(uint32_t Instance)
{
  int32_t ret;

  if (Instance >= STSAFE_INSTANCES)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (SAFEL0Drv[Instance]->DeInit(SAFEL0CompObj[Instance]) != BSP_ERROR_NONE)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
 * @brief  Deinitialize environmental sensor
 * @param  Instance : I2C STSAFE instance to be used
 * @retval BSP status
 */
int32_t SAFEL0_Transmit(uint32_t Instance, uint16_t DevAddr, uint8_t *pData, uint16_t Length)
{
  int32_t ret;

  if (Instance >= STSAFE_INSTANCES)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (SAFEL0Drv[Instance]->Send(SAFEL0CompObj[Instance], DevAddr, pData, Length) != BSP_ERROR_NONE)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
 * @brief  Deinitialize environmental sensor
 * @param  Instance : I2C STSAFE instance to be used
 * @retval BSP status
 */
int32_t SAFEL0_Receive(uint32_t Instance,uint16_t DevAddr, uint8_t *pData, uint16_t Length)
{
  int32_t ret;

  if (Instance >= STSAFE_INSTANCES)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (SAFEL0Drv[Instance]->Receive(SAFEL0CompObj[Instance], DevAddr, pData, Length) != BSP_ERROR_NONE)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
 * @brief  Probe and initialize the STSAFEL010 component
 * @retval BSP status
 * @details Registers Bus IOs and initializes the STSAFEL010 instance if the component ID is correct.
 */
static int32_t STSAFEL_010_Probe(void)
{
  int32_t                 ret = BSP_ERROR_NONE;

  static STSAFEL0x0_Object_t STSAFEL010_obj_0;
  STSAFEL0x0_IO_t    io_stsafel010;

  io_stsafel010.Init         = SAFEA1_I2C_INIT;
  io_stsafel010.DeInit       = SAFEA1_I2C_DEINIT;
  io_stsafel010.Transmit     = SAFEA1_I2C_SEND;
  io_stsafel010.Receive      = SAFEA1_I2C_RECEIVE;
  io_stsafel010.Wake         = SAFEA1_I2C_WAKEUP;

  io_stsafel010.Address         = STSAFEA_DEVICE_ADDRESS;
  
    if (STSAFEL0x0_RegisterBusIO(&STSAFEL010_obj_0, &io_stsafel010) != BSP_ERROR_NONE)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  
  SAFEL0CompObj[SAFEL_010_0] = &STSAFEL010_obj_0;
  SAFEL0Drv[SAFEL_010_0] = (STSAFEL0x0_CommonDrv_t *)(void *)&SAFEL0_i2c_Drv;

   if( SAFEL0Drv[SAFEL_010_0]->Init(SAFEL0CompObj[SAFEL_010_0]) != STSAFE_OK)
   {
     ret = BSP_ERROR_COMPONENT_FAILURE;
   }
   else
   {
     ret = BSP_ERROR_NONE;
   }

  return ret;
}

/**
 * @brief  Wake up the STSAFEA1x0 device
 * @param  Instance : STSAFE instance to be used
 * @retval BSP status
 * @details Calls the Wake function for the specified instance.
 */
int32_t SAFEA1_A1x0_Wakeup(uint32_t Instance)
{
  int32_t ret;
  
  if (SAFEL0Drv[Instance]->Wake(SAFEL0CompObj[Instance]) != BSP_ERROR_NONE)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }
   
  return ret;   
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

