/**
  ******************************************************************************
  * @file    stsafel010.c
  * @author  STMicroelectronics SRA-SAIL, STM32ODE
  * @brief   STSAFEL010 driver file
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
#include "stsafel010.h"

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup Component Component
  * @{
  */

/** @addtogroup STSAFE STSAFEL010
  * @{
  */

/** @defgroup STSAFEL0x0_Exported_Types STSAFEL0x0 Exported Variables
  * @{
  */
STSAFEL0x0_Drv_t SAFEL0_i2c_Drv =
{
 STSAFEL0x0_i2c_Init,
 STSAFEL0x0_i2c_DeInit,
 STSAFEL0x0_i2c_Send,
 STSAFEL0x0_i2c_Receive,
 STSAFEL0x0_i2c_Wake,
 NULL
};
/**
  * @}
  */

/** @defgroup STSAFEL0x0_Private_Function_Prototypes STSAFEL0x0 Private Function Prototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup STSAFEL0x0_Exported_Functions STSAFEL0x0 Exported Functions
  * @{
  */
 
/**
  * @brief  Register Handler for Bus IO operations
  * @param  pSTSE the device Handle
  * @param  pIO pointer to io object
  * @retval 0 in case of success, an error code otherwise
  */
int32_t  STSAFEL0x0_RegisterBusIO(STSAFEL0x0_Object_t *pObj, STSAFEL0x0_IO_t *pIO)
{
  int32_t  ret = STSAFE_ERROR;

  if (pObj == NULL)
  {
    ret = STSAFE_ERROR;
  }
  else
  {
    pObj->IO.Init         = pIO->Init;
    pObj->IO.DeInit       = pIO->DeInit;
    pObj->IO.Receive      = pIO->Receive;
    pObj->IO.Transmit     = pIO->Transmit;
    pObj->IO.Address      = pIO->Address;
    pObj->IO.Wake         = pIO->Wake;

    if (pObj->IO.Init == NULL)
    {
      ret = STSAFE_ERROR;
    }
    else
    {
      ret = STSAFE_OK;
    }
  }

  return ret;
}

/**
  * @brief  STSAFE I2C Initialization
  * @param  pSTSE the device Handle
  * @retval STSAFE enum status
  */
int32_t  STSAFEL0x0_i2c_Init(STSAFEL0x0_Object_t *pObj)
{ 
  /* Configure the low level interface */
  if (pObj->IO.Init()!= STSAFE_OK)
  {
    return STSAFE_ERROR;
  }
  return STSAFE_OK;
}

/**
  * @brief  STSAFE I2C De-Initialization
  * @param  pSTSE the device Handle
  * @retval STSAFE enum status
  */
int32_t  STSAFEL0x0_i2c_DeInit(STSAFEL0x0_Object_t *pObj)
{ 
  int32_t ret = STSAFE_OK;
  
  if (pObj->IO.DeInit() != STSAFE_OK)
  {
    ret = STSAFE_ERROR;
  }
  /* Configure the low level interface */
  return ret;
}

/**
 * @brief  Send data to the STSAFE device over I2C
 * @param  pObj    Pointer to the device object
 * @param  DevAddr Device I2C address
 * @param  pData   Pointer to data buffer to send
 * @param  Length  Length of data to send
 * @retval STSAFE_OK on success, STSAFE_ERROR otherwise
 * @details Calls the registered Transmit function for the device.
 */
int32_t STSAFEL0x0_i2c_Send(STSAFEL0x0_Object_t * pObj, uint16_t DevAddr, uint8_t *pData, uint16_t Length)
{
  int32_t ret = STSAFE_OK;
  if(pObj->IO.Transmit( DevAddr, pData, Length) != STSAFE_OK)
  {
    ret = STSAFE_ERROR;
  }
  return ret;
}


/**
 * @brief  Receive data from the STSAFE device over I2C
 * @param  pObj    Pointer to the device object
 * @param  DevAddr Device I2C address
 * @param  pData   Pointer to data buffer to receive
 * @param  Length  Length of data to receive
 * @retval STSAFE_OK on success, STSAFE_ERROR otherwise
 * @details Calls the registered Receive function for the device.
 */
int32_t STSAFEL0x0_i2c_Receive( STSAFEL0x0_Object_t * pObj, uint16_t DevAddr, uint8_t *pData, uint16_t Length)
{
  int32_t ret = STSAFE_OK;
  if(pObj->IO.Receive( DevAddr, pData, Length) != STSAFE_OK)
  {
    ret = STSAFE_ERROR;
  }
  return ret;
}

/**
 * @brief  Wake up the STSAFE device
 * @param  pObj Pointer to the device object
 * @retval STSAFE_OK on success, STSAFE_ERROR otherwise
 * @details Calls the registered Wake function for the device.
 */
int32_t STSAFEL0x0_i2c_Wake(STSAFEL0x0_Object_t * pObj)
{
  int32_t ret = STSAFE_OK;
  if(pObj->IO.Wake() != STSAFE_OK)
  {
    ret = STSAFE_ERROR;
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
