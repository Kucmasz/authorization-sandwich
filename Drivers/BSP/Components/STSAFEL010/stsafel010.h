/**
  ******************************************************************************
  * @file    stsafel010.h
  * @author  STMicroelectronics - CS application team
  * @brief   STSAFEL010 header driver file
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
#ifndef STSAFEL010_H
#define STSAFEL010_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup BSP BSP
  * @{
  */

/** @addtogroup Component Component
  * @{
  */

/** @addtogroup STSAFE STSAFEL010
  * @{
  */
  
#define STSAFE_OK              0
#define STSAFE_ERROR   	      -1

/** @defgroup STSAFEL0x0_Exported_Functions STSAFEL0x0 Exported Functions
  * @{
  */

 
typedef int32_t     (*STSAFEL010_Init_Func)(void);   
typedef int32_t     (*STSAFEL010_DeInit_Func)(void); 
typedef int32_t     (*STSAFEL010_Transmit_Func)( uint16_t, uint8_t*, uint16_t);
typedef int32_t     (*STSAFEL010_Receive_Func)( uint16_t, uint8_t*, uint16_t);
typedef int32_t     (*STSAFEL010_Wake_Func)( void);
 

typedef struct
{
  STSAFEL010_Init_Func            Init;
  STSAFEL010_DeInit_Func          DeInit;
  STSAFEL010_Transmit_Func        Transmit;
  STSAFEL010_Receive_Func         Receive;
  STSAFEL010_Wake_Func            Wake;
  uint8_t                         Address;
} STSAFEL0x0_IO_t;

typedef struct
{
  STSAFEL0x0_IO_t        IO;
}STSAFEL0x0_Object_t;
/**
 * @brief  STSAFE COMMON driver structure definition
 */
typedef struct
{
  int32_t       (*Init)( STSAFEL0x0_Object_t * );
  int32_t       (*DeInit)( STSAFEL0x0_Object_t * );
  int32_t       (*Send)(STSAFEL0x0_Object_t *, uint16_t  , uint8_t * ,uint16_t );
  int32_t       (*Receive)(STSAFEL0x0_Object_t *, uint16_t  , uint8_t * ,uint16_t );
  int32_t       (*Wake)( STSAFEL0x0_Object_t *);
  void          *pData;
} STSAFEL0x0_CommonDrv_t;


/**
 * @brief  STSAFE A110 driver structure definition
 */
typedef struct
{
  int32_t       (*Init)( STSAFEL0x0_Object_t * );
  int32_t       (*DeInit)( STSAFEL0x0_Object_t * );
  int32_t       (*Send)(STSAFEL0x0_Object_t *, uint16_t  , uint8_t * ,uint16_t );
  int32_t       (*Receive)(STSAFEL0x0_Object_t *, uint16_t  , uint8_t * ,uint16_t ); 
  int32_t       (*Wake)( STSAFEL0x0_Object_t *);
  void          *pData;
} STSAFEL0x0_Drv_t;


int32_t STSAFEL0x0_RegisterBusIO(STSAFEL0x0_Object_t *pObj, STSAFEL0x0_IO_t *pIO);


int32_t STSAFEL0x0_i2c_Init( STSAFEL0x0_Object_t * pObj );
int32_t STSAFEL0x0_i2c_DeInit(STSAFEL0x0_Object_t * pObj );
int32_t STSAFEL0x0_i2c_Send(STSAFEL0x0_Object_t * pObj, uint16_t DevAddr, uint8_t *pData, uint16_t Length);
int32_t STSAFEL0x0_i2c_Receive( STSAFEL0x0_Object_t * pObj, uint16_t DevAddr, uint8_t *pData, uint16_t Length);
int32_t STSAFEL0x0_i2c_Wake(STSAFEL0x0_Object_t * pObj);



/* Exported variables --------------------------------------------------------*/
extern STSAFEL0x0_Drv_t SAFEL0_i2c_Drv;

#ifdef __cplusplus
}
#endif

#endif

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
