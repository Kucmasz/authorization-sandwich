/**
  ******************************************************************************
  * @file           : stse01_interface.c
  * @brief          : This file provides code for the interface of
  *                   of the Target/stse01_interface.c instances to stse middleware.
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
#include <stdlib.h>
#include <string.h>
#include "stse_conf.h"
#include "stm32f4xx_hal.h"
#include "stse_return_codes.h"
#include "stse_platform.h"
#include "safel0_L010.h"
#include "cmox_crypto.h"
#include "stsafea_hash.h"

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define KEK_WRAP_IV_SIZE 8
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const PLAT_UI8 KEK_WRAP_IV[KEK_WRAP_IV_SIZE] = {0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6};

cmox_ecc_handle_t Ecc_Ctx;
PLAT_UI8 cmox_math_buffer[2400];

cmox_mac_handle_t *pMAC_Handler;
cmox_cmac_handle_t CMAC_Handler;

/* Private_key */
PLAT_UI8 static_c25519_priv_key[32] = {0x3D, 0xAC, 0x2A, 0xFF, 0x7A, 0x55, 0x9F, 0xAA,
                                       0xAC, 0x1B, 0xB6, 0x46, 0xE9, 0xD5, 0xE0, 0x50,
                                       0x28, 0x72, 0xFE, 0x9F, 0xD5, 0xE8, 0x3B, 0x7E,
                                       0x68, 0x28, 0x7A, 0xB3, 0xF4, 0x7E, 0x59, 0x8F
                                      };

/* Public_key */
PLAT_UI8 static_c25519_pub_key[32] = {0x59, 0x86, 0xA8, 0xA3, 0x51, 0xBB, 0x07, 0xCA,
                                      0x40, 0x01, 0x76, 0xF7, 0x66, 0x8A, 0x4F, 0xBF,
                                      0xA1, 0xA5, 0xE1, 0x9A, 0xCB, 0x57, 0x55, 0xF6,
                                      0x57, 0xF9, 0x43, 0xE9, 0xBC, 0x39, 0x54, 0x0B
                                     };

static PLAT_UI8 I2c_buffer[752U];  /* Set to L010 max input buffer size. Shall be adapted to applicative use case! */
static PLAT_UI16 i2c_frame_size;
static volatile PLAT_UI16 i2c_frame_offset;

/* Global variables ----------------------------------------------------------*/
extern CRC_HandleTypeDef hcrc;

/*  SW CRC16 Implementation ------------------------------------------------- */
static uint16_t crc16_tab[] =
{
  0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
  0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
  0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
  0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
  0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
  0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
  0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
  0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
  0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
  0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
  0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
  0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
  0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
  0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
  0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
  0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
  0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
  0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
  0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
  0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
  0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
  0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
  0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
  0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
  0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
  0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
  0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
  0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
  0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
  0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
  0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
  0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};

uint16_t crc16_val;

/* Private function prototypes -----------------------------------------------*/
extern uint32_t rng_generate_random_number(void);
/* Functions Definition ------------------------------------------------------*/
/**
  * @brief  Initialize CRC16 resources (software table already present)
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_crc16_init(void)
{
  /* No hardware CRC usage by default in template */
  return STSE_OK;
}

/**
  * @brief  Initialize platform random number generation resources
  *         placeholder – adapt if a HW RNG needs explicit init.
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_generate_random_init(void)
{
  return STSE_OK;
}

/**
  * @brief  Calculate CRC16 checksum
  * @param  address: Pointer to the data buffer
  * @param  length: Length of the data buffer
  * @retval CRC16 checksum
  */
uint16_t crc16_Calculate(uint8_t *address, uint16_t length)
{
  uint16_t i = 0;
  crc16_val = 0xffff;

  for (i = 0; i < length; i++)
  {
    crc16_val = ((crc16_val >> 8) ^ crc16_tab [(crc16_val ^ address[i]) & 0x00ff]);
  }

  return ~crc16_val;
}

/**
  * @brief  Accumulate CRC16 checksum
  * @param  address: Pointer to the data buffer
  * @param  length: Length of the data buffer
  * @retval Accumulated CRC16 checksum
  */
uint16_t crc16_Accumulate(uint8_t *address, uint16_t length)
{
  uint16_t i = 0;

  for (i = 0; i < length; i++)
  {
    crc16_val = ((crc16_val >> 8) ^ crc16_tab [(crc16_val ^ address[i]) & 0x00ff]);
  }

  return ~crc16_val;
}

/**
  * @brief  STSAFE Middleware initialization platform abstraction function
  * This function is called by the Middleware on stse_init API execution
  * to initialize low-level Platform specific drivers.
  */
stse_ReturnCode_t stse_services_platform_init(void)
{
  /* Platform Initialization is done by the BSP */
  return STSE_OK;
}

/**
  * @brief  Calculate CRC16 checksum using platform abstraction
  * @param  pbuffer: Pointer to the data buffer
  * @param  length: Length of the data buffer
  * @retval CRC16 checksum
  */
PLAT_UI16 stse_platform_Crc16_Calculate(PLAT_UI8 *pbuffer, PLAT_UI16 length)
{
  return crc16_Calculate(pbuffer, length);
}

/**
  * @brief  Accumulate CRC16 checksum using platform abstraction
  * @param  pbuffer: Pointer to the data buffer
  * @param  length: Length of the data buffer
  * @retval Accumulated CRC16 checksum
  */
PLAT_UI16 stse_platform_Crc16_Accumulate(PLAT_UI8 *pbuffer, PLAT_UI16 length)
{
  return crc16_Accumulate(pbuffer, length);
}

/**
  * @brief  Delay for a specified number of milliseconds
  * @param  delay_val: Number of milliseconds to delay
  * @retval None
  */
void stse_platform_Delay_ms(PLAT_UI32 delay_val)
{
  HAL_Delay(delay_val);
}

/**
  * @brief  Delay service init (placeholder for BSP tick init already done)
  */
stse_ReturnCode_t stse_platform_delay_init(void)
{
  return STSE_OK;
}

/**
  * @brief  Start a timeout in milliseconds
  * @param  timeout_val: Timeout value in milliseconds
  * @retval None
  */
void stse_platform_timeout_ms_start(PLAT_UI16 timeout_val)
{

}

/**
  * @brief  Get the status of the timeout
  * @param  None
  * @retval Timeout status
  */
PLAT_UI8 stse_platform_timeout_ms_get_status(void)
{
  return STSE_OK;/*timeout_ms_get_status; */
}

/**
  * @brief  Power on the platform
  * @param  bus: Bus identifier
  * @param  devAddr: Device address
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_power_on(PLAT_UI8 bus, PLAT_UI8 devAddr)
{
  (void)bus;
  (void)devAddr;

  /* - Power on all the STSAFE SLOTS */
  return STSE_OK;
}

/**
  * @brief  Initialize platform power control lines (GPIO etc.)
  */
stse_ReturnCode_t stse_platform_power_init(void)
{
  return STSE_OK;
}

/**
  * @brief  Power off the platform
  * @param  bus: Bus identifier
  * @param  devAddr: Device address
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_power_off(PLAT_UI8 bus, PLAT_UI8 devAddr)
{
  (void)bus;
  (void)devAddr;

  /* - Power-off all the STSAFE SLOTS */
  return STSE_OK;
}

/**
  * @brief  Initialize I2C platform
  * @param  busID: Bus identifier
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_i2c_init(PLAT_UI8 busID)
{
  (void) busID;
  /* I2C initialized by BSP */
  return STSE_OK;
}

/**
  * @brief  Wake up I2C platform
  * @param  busID: Bus identifier
  * @param  devAddr: Device address
  * @param  speed: I2C speed
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_i2c_wake(PLAT_UI8 busID,
                                         PLAT_UI8 devAddr,
                                         PLAT_UI16 speed)
{
  (void) busID;
  (void) speed;

  HAL_I2CEx_EnableWakeUp(&I2C_HANDLE);

  return STSE_OK;
}

/**
  * @brief  Start I2C send operation
  * @param  busID: Bus identifier
  * @param  devAddr: Device address
  * @param  speed: I2C speed
  * @param  FrameLength: Frame length
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_i2c_send_start(
  PLAT_UI8 busID,
  PLAT_UI8 devAddr,
  PLAT_UI16 speed,
  PLAT_UI16 FrameLength)
{
  (void)busID;
  (void)devAddr;
  (void)speed;

  /* - Check buffer overflow */
  if (FrameLength > sizeof(I2c_buffer) / sizeof(I2c_buffer[0]))
  {
    return STSE_PLATFORM_BUFFER_ERR;
  }

  i2c_frame_size = FrameLength;
  i2c_frame_offset = 0;

  return STSE_OK;
}

/**
  * @brief  Continue I2C send operation
  * @param  busID: Bus identifier
  * @param  devAddr: Device address
  * @param  speed: I2C speed
  * @param  pData: Pointer to data buffer
  * @param  data_size: Size of data buffer
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_i2c_send_continue(
  PLAT_UI8 busID,
  PLAT_UI8 devAddr,
  PLAT_UI16 speed,
  PLAT_UI8 *pData,
  PLAT_UI16 data_size)
{
  (void)busID;
  (void)devAddr;
  (void)speed;

  if (data_size != 0)
  {
    if (pData == NULL)
    {
      memset((I2c_buffer + i2c_frame_offset), 0x00, data_size);
    }
    else
    {
      memcpy((I2c_buffer + i2c_frame_offset), pData, data_size);
    }
    i2c_frame_offset += data_size;
  }

  return STSE_OK;
}

/**
  * @brief  Stop I2C send operation
  * @param  busID: Bus identifier
  * @param  devAddr: Device address
  * @param  speed: I2C speed
  * @param  pData: Pointer to data buffer
  * @param  data_size: Size of data buffer
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_i2c_send_stop(
  PLAT_UI8 busID,
  PLAT_UI8 devAddr,
  PLAT_UI16 speed,
  PLAT_UI8 *pData,
  PLAT_UI16 data_size)
{
  stse_ReturnCode_t ret;
  int32_t status = 0;

  ret =  stse_platform_i2c_send_continue(
           busID,
           devAddr,
           speed,
           pData,
           data_size);

  /* - Send I2C frame buffer */
  if (ret == STSE_OK)
  {
    status = SAFEL0_Transmit(SAFEL_010_0, STSAFEA_DEVICE_ADDRESS, I2c_buffer, i2c_frame_size);
  }

  if (status != STSE_OK)
  {
    ret = STSE_PLATFORM_BUS_ACK_ERROR;
  }

  return ret;
}

/**
  * @brief  Start I2C receive operation
  * @param  busID: Bus identifier
  * @param  devAddr: Device address
  * @param  speed: I2C speed
  * @param  pFrame_Length: Pointer to frame length
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_i2c_receive_start(
  PLAT_UI8  busID,
  PLAT_UI8  devAddr,
  PLAT_UI16 speed,
  PLAT_UI16 frameLength)
{
  (void)busID;
  PLAT_I8 ret = 0;

  /* - Store response Length */
  i2c_frame_size = frameLength;

#ifdef STSE_PLATFORM_I2C_DYNAMIC_BUFFER_ALLOCATION
  /* - Allocate Communication buffer */
  pI2c_buffer = malloc(frameLength);
  /* - Check buffer overflow */
  if (pI2c_buffer == NULL)
  {
    return STSE_PLATFORM_BUFFER_ERR;
  }
#endif /* STSE_PLATFORM_I2C_DYNAMIC_BUFFER_ALLOCATION */

  /* - Read full Frame */
#ifdef STSE_PLATFORM_I2C_DYNAMIC_BUFFER_ALLOCATION
  ret = i2c_read(I2C1, devAddr, speed, pI2c_buffer, i2c_frame_size);
#else
  if (SAFEL0_Receive(SAFEL_010_0, STSAFEA_DEVICE_ADDRESS, I2c_buffer, i2c_frame_size) != HAL_OK)
  {
    if (HAL_I2C_GetError(&I2C_HANDLE) != HAL_I2C_ERROR_AF)
    {
      ret = BSP_ERROR_BUS_ACKNOWLEDGE_FAILURE;
    }
    else
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
#endif /* STSE_PLATFORM_I2C_DYNAMIC_BUFFER_ALLOCATION */
    if (ret != 0)
    {
      return STSE_PLATFORM_BUS_ACK_ERROR;
    }
  }

  /* - Reset read offset */
  i2c_frame_offset = 0;

  return STSE_OK;
}

/**
  * @brief  Continue I2C receive operation
  * @param  busID: Bus identifier
  * @param  devAddr: Device address
  * @param  speed: I2C speed
  * @param  pData: Pointer to data buffer
  * @param  data_size: Size of data buffer
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_i2c_receive_continue(
  PLAT_UI8 busID,
  PLAT_UI8 devAddr,
  PLAT_UI16 speed,
  PLAT_UI8 *pData,
  PLAT_UI16 data_size)
{
  (void)busID;
  (void)devAddr;
  (void)speed;

  if (pData != NULL)
  {

    /* Check read overflow */
    if ((i2c_frame_size - i2c_frame_offset) < data_size)
    {
      return STSE_PLATFORM_BUFFER_ERR;
    }

    /* Copy buffer content */
#ifdef STSE_PLATFORM_I2C_DYNAMIC_BUFFER_ALLOCATION
    memcpy(pData, (pI2c_buffer + i2c_frame_offset), data_size);
#else
    memcpy(pData, (I2c_buffer + i2c_frame_offset), data_size);
#endif /* STSE_PLATFORM_I2C_DYNAMIC_BUFFER_ALLOCATION */
  }

  i2c_frame_offset += data_size;

  return STSE_OK;
}

/**
  * @brief  Stop I2C receive operation
  * @param  busID: Bus identifier
  * @param  devAddr: Device address
  * @param  speed: I2C speed
  * @param  pData: Pointer to data buffer
  * @param  data_size: Size of data buffer
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_i2c_receive_stop(
  PLAT_UI8 busID,
  PLAT_UI8 devAddr,
  PLAT_UI16 speed,
  PLAT_UI8 *pData,
  PLAT_UI16 data_size)
{
  stse_ReturnCode_t ret;

  /*- Copy last element*/
  ret = stse_platform_i2c_receive_continue(busID, devAddr, speed, pData, data_size);

  i2c_frame_offset = 0;

#ifdef STSE_PLATFORM_I2C_DYNAMIC_BUFFER_ALLOCATION
  /*- Free i2c buffer*/
  free(pI2c_buffer);
#endif /* STSE_PLATFORM_I2C_DYNAMIC_BUFFER_ALLOCATION */
  return ret;
}

/**
  * @brief  to wake up I2C
  * @param  void
  * @retval BSP status
  */
int32_t BSP_I2C1_Wake(void)
{
  int32_t ret = BSP_ERROR_NONE;

  if (HAL_I2CEx_EnableWakeUp(&I2C_HANDLE) != HAL_OK)
  {
    if (HAL_I2C_GetError(&I2C_HANDLE) != HAL_I2C_ERROR_AF)
    {
      ret = BSP_ERROR_BUS_ACKNOWLEDGE_FAILURE;
    }
    else
    {
      ret =  BSP_ERROR_PERIPH_FAILURE;
    }
  }

  return ret;
}

/************************************************************
  *                STATIC FUNCTIONS
  **************************************************************/
/**
  * @brief  Get CMOX ECC implementation based on key type
  * @param  key_type: ECC key type
  * @retval CMOX ECC implementation
  */
static cmox_ecc_impl_t stse_platform_get_cmox_ecc_impl(stse_ecc_key_type_t key_type)
{
  switch (key_type)
  {
#ifdef STSE_CONF_ECC_NIST_P_256
    case STSE_ECC_KT_NIST_P_256:
      return CMOX_ECC_SECP256R1_LOWMEM;
#endif /* STSE_CONF_ECC_NIST_P_256 */
#ifdef STSE_CONF_ECC_NIST_P_384
    case STSE_ECC_KT_NIST_P_384:
      return CMOX_ECC_SECP384R1_LOWMEM;
#endif /* STSE_CONF_ECC_NIST_P_384 */
#ifdef STSE_CONF_ECC_NIST_P_521
    case STSE_ECC_KT_NIST_P_521:
      return CMOX_ECC_SECP521R1_LOWMEM;
#endif /* STSE_CONF_ECC_NIST_P_521 */
#ifdef STSE_CONF_ECC_BRAINPOOL_P_256
    case STSE_ECC_KT_BP_P_256:
      return CMOX_ECC_BPP256R1_LOWMEM;
#endif /* STSE_CONF_ECC_BRAINPOOL_P_256 */
#ifdef STSE_CONF_ECC_BRAINPOOL_P_384
    case STSE_ECC_KT_BP_P_384:
      return CMOX_ECC_BPP384R1_LOWMEM;
#endif /* STSE_CONF_ECC_BRAINPOOL_P_384 */
#ifdef STSE_CONF_ECC_BRAINPOOL_P_512
    case STSE_ECC_KT_BP_P_512:
      return CMOX_ECC_BPP512R1_LOWMEM;
#endif /* STSE_CONF_ECC_BRAINPOOL_P_512 */
#ifdef STSE_CONF_ECC_CURVE_25519
    case STSE_ECC_KT_CURVE25519:
      return CMOX_ECC_CURVE25519;
#endif /* STSE_CONF_ECC_CURVE_25519 */
#ifdef STSE_CONF_ECC_EDWARD_25519
    case STSE_ECC_KT_ED25519:
      return CMOX_ECC_ED25519_OPT_LOWMEM;
#endif /* STSE_CONF_ECC_EDWARD_25519 */
  default:
    return NULL;
  }
}

/**
  * @brief  Get CMOX ECC private key length based on key type
  * @param  key_type: ECC key type
  * @retval Private key length
  */
static size_t stse_platform_get_cmox_ecc_priv_key_len(stse_ecc_key_type_t key_type)
{
  switch (key_type)
  {
#ifdef STSE_CONF_ECC_NIST_P_256
    case STSE_ECC_KT_NIST_P_256:
      return CMOX_ECC_SECP256R1_PRIVKEY_LEN;
#endif /* STSE_CONF_ECC_NIST_P_256 */
#ifdef STSE_CONF_ECC_NIST_P_384
    case STSE_ECC_KT_NIST_P_384:
      return CMOX_ECC_SECP384R1_PRIVKEY_LEN;
#endif /* STSE_CONF_ECC_NIST_P_384 */
#ifdef STSE_CONF_ECC_NIST_P_521
    case STSE_ECC_KT_NIST_P_521:
      return CMOX_ECC_SECP521R1_PRIVKEY_LEN;
#endif /* STSE_CONF_ECC_NIST_P_521 */
#ifdef STSE_CONF_ECC_BRAINPOOL_P_256
    case STSE_ECC_KT_BP_P_256:
      return CMOX_ECC_BPP256R1_PRIVKEY_LEN;
#endif /* STSE_CONF_ECC_BRAINPOOL_P_256 */
#ifdef STSE_CONF_ECC_BRAINPOOL_P_384
    case STSE_ECC_KT_BP_P_384:
      return CMOX_ECC_BPP384R1_PRIVKEY_LEN;
#endif /* STSE_CONF_ECC_BRAINPOOL_P_384 */
#ifdef STSE_CONF_ECC_BRAINPOOL_P_512
    case STSE_ECC_KT_BP_P_512:
      return CMOX_ECC_BPP512R1_PRIVKEY_LEN;
#endif /* STSE_CONF_ECC_BRAINPOOL_P_512 */
#ifdef STSE_CONF_ECC_CURVE_25519
    case STSE_ECC_KT_CURVE25519:
      return CMOX_ECC_CURVE25519_PRIVKEY_LEN;
#endif /* STSE_CONF_ECC_CURVE_25519 */
#ifdef STSE_CONF_ECC_EDWARD_25519
    case STSE_ECC_KT_ED25519:
      return CMOX_ECC_ED25519_PRIVKEY_LEN;
#endif /* STSE_CONF_ECC_EDWARD_25519 */
  default:
    return 0u;
  }
}

/**
  * @brief  Get CMOX ECC public key length based on key type
  * @param  key_type: ECC key type
  * @retval Public key length
  */
static size_t stse_platform_get_cmox_ecc_pub_key_len(stse_ecc_key_type_t key_type)
{
  switch (key_type)
  {
#ifdef STSE_CONF_ECC_NIST_P_256
    case STSE_ECC_KT_NIST_P_256:
      return CMOX_ECC_SECP256R1_PUBKEY_LEN;
#endif /* STSE_CONF_ECC_NIST_P_256 */
#ifdef STSE_CONF_ECC_NIST_P_384
    case STSE_ECC_KT_NIST_P_384:
      return CMOX_ECC_SECP384R1_PUBKEY_LEN;
#endif /* STSE_CONF_ECC_NIST_P_384 */
#ifdef STSE_CONF_ECC_NIST_P_521
    case STSE_ECC_KT_NIST_P_521:
      return CMOX_ECC_SECP521R1_PUBKEY_LEN;
#endif /* STSE_CONF_ECC_NIST_P_521 */
#ifdef STSE_CONF_ECC_BRAINPOOL_P_256
    case STSE_ECC_KT_BP_P_256:
      return CMOX_ECC_BPP256R1_PUBKEY_LEN;
#endif /* STSE_CONF_ECC_BRAINPOOL_P_256 */
#ifdef STSE_CONF_ECC_BRAINPOOL_P_384
    case STSE_ECC_KT_BP_P_384:
      return CMOX_ECC_BPP384R1_PUBKEY_LEN;
#endif /* STSE_CONF_ECC_BRAINPOOL_P_384 */
#ifdef STSE_CONF_ECC_BRAINPOOL_P_512
    case STSE_ECC_KT_BP_P_512:
      return CMOX_ECC_BPP512R1_PUBKEY_LEN;
#endif /* STSE_CONF_ECC_BRAINPOOL_P_512 */
#ifdef STSE_CONF_ECC_CURVE_25519
    case STSE_ECC_KT_CURVE25519:
      return CMOX_ECC_CURVE25519_PUBKEY_LEN;
#endif /* STSE_CONF_ECC_CURVE_25519 */
#ifdef STSE_CONF_ECC_EDWARD_25519
    case STSE_ECC_KT_ED25519:
      return CMOX_ECC_ED25519_PUBKEY_LEN;
#endif /* STSE_CONF_ECC_EDWARD_25519 */
  default:
    return 0u;
  }
}

/**
  * @brief  Get CMOX ECC signature length based on key type
  * @param  key_type: ECC key type
  * @retval Signature length
  */
static size_t stse_platform_get_cmox_ecc_sig_len(stse_ecc_key_type_t key_type)
{
  switch (key_type)
  {
#ifdef STSE_CONF_ECC_NIST_P_256
    case STSE_ECC_KT_NIST_P_256:
      return CMOX_ECC_SECP256R1_SIG_LEN;
#endif /* STSE_CONF_ECC_NIST_P_256 */
#ifdef STSE_CONF_ECC_NIST_P_384
    case STSE_ECC_KT_NIST_P_384:
      return CMOX_ECC_SECP384R1_SIG_LEN;
#endif /* STSE_CONF_ECC_NIST_P_384 */
#ifdef STSE_CONF_ECC_NIST_P_521
    case STSE_ECC_KT_NIST_P_521:
      return CMOX_ECC_SECP521R1_SIG_LEN;
#endif /* STSE_CONF_ECC_NIST_P_521 */
#ifdef STSE_CONF_ECC_BRAINPOOL_P_256
    case STSE_ECC_KT_BP_P_256:
      return CMOX_ECC_BPP256R1_SIG_LEN;
#endif /* STSE_CONF_ECC_BRAINPOOL_P_256 */
#ifdef STSE_CONF_ECC_BRAINPOOL_P_384
    case STSE_ECC_KT_BP_P_384:
      return CMOX_ECC_BPP384R1_SIG_LEN;
#endif /* STSE_CONF_ECC_BRAINPOOL_P_384 */
#ifdef STSE_CONF_ECC_BRAINPOOL_P_512
    case STSE_ECC_KT_BP_P_512:
      return CMOX_ECC_BPP512R1_SIG_LEN;
#endif /* STSE_CONF_ECC_BRAINPOOL_P_512 */
#ifdef STSE_CONF_ECC_CURVE_25519
    case STSE_ECC_KT_CURVE25519:
      return STSE_OK; /* No signature with curve25519 */
#endif /* STSE_CONF_ECC_CURVE_25519 */
#ifdef STSE_CONF_ECC_EDWARD_25519
    case STSE_ECC_KT_ED25519:
      return CMOX_ECC_ED25519_SIG_LEN;
#endif /* STSE_CONF_ECC_EDWARD_25519 */
    default:
      return 0u;
  }
}

/**
  * @brief  Get CMOX hash algorithm based on hash type
  * @param  hash_algo: Hash algorithm type
  * @retval CMOX hash algorithm
  */
static cmox_hash_algo_t stse_platform_get_cmox_hash_algo(stse_hash_algorithm_t hash_algo)
{
  switch (hash_algo)
  {
#ifdef STSE_CONF_HASH_SHA_1
    case STSE_SHA_1:
    return CMOX_SHA1_ALGO;
#endif /* STSE_CONF_HASH_SHA_1 */
#ifdef STSE_CONF_HASH_SHA_224
    case STSE_SHA_224:
    return CMOX_SHA224_ALGO;
#endif /* STSE_CONF_HASH_SHA_224 */
#ifdef STSE_CONF_HASH_SHA_256
    case STSE_SHA_256:
    return CMOX_SHA256_ALGO;
#endif /* STSE_CONF_HASH_SHA_256 */
#ifdef STSE_CONF_HASH_SHA_384
    case STSE_SHA_384:
    return CMOX_SHA384_ALGO;
#endif /* STSE_CONF_HASH_SHA_384 */
#ifdef STSE_CONF_HASH_SHA_512
    case STSE_SHA_512:
    return CMOX_SHA512_ALGO;
#endif /* STSE_CONF_HASH_SHA_512 */
#ifdef STSE_CONF_HASH_SHA_3_256
    case STSE_SHA3_256:
    return CMOX_SHA3_256_ALGO;
#endif /* STSE_CONF_HASH_SHA_3_256 */
#ifdef STSE_CONF_HASH_SHA_3_384
    case STSE_SHA3_384:
    return CMOX_SHA3_384_ALGO;
#endif /* STSE_CONF_HASH_SHA_3_384 */
#ifdef STSE_CONF_HASH_SHA_3_512
    case STSE_SHA3_512:
    return CMOX_SHA3_512_ALGO;
#endif /* STSE_CONF_HASH_SHA_3_512 */
    default:
      return NULL;
  }
}
/************************************************************
  *                STSAFE CRYPTO HAL
  **************************************************************/
/**
  * @brief  Initialize cryptographic platform
  * @param  None
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_crypto_init(void)
{
  stse_ReturnCode_t ret = STSE_OK;

  /* - Initialize cryptographic library */
  if (cmox_initialize(NULL) != CMOX_INIT_SUCCESS)
  {
    ret = STSE_PLATFORM_CRYPTO_INIT_ERROR;
  }

  /* - Initialize Random Number Generator */

  return ret;
}

/**
  * @brief  Backward compatibility wrapper for cryptographic platform init
  *         Calls stse_platform_crypto_init().
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_crypto_platform_init(void)
{
  return stse_platform_crypto_init();
}

/**
  * @brief  Generate a random number
  * @param  None
  * @retval Random number
  */
PLAT_UI32 stse_platform_generate_random(void)
{
  return rng_generate_random_number();
}

/**
  * @brief  Compute hash using platform abstraction
  * @param  hash_algo: Hash algorithm type
  * @param  pPayload: Pointer to payload data
  * @param  payload_length: Length of payload data
  * @param  pHash: Pointer to hash output buffer
  * @param  hash_length: Pointer to hash length
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_hash_compute(stse_hash_algorithm_t hash_algo,
                                             PLAT_UI8 *pPayload, PLAT_UI16 payload_length,
                                             PLAT_UI8 *pHash, PLAT_UI16 *hash_length)
{
#if defined(STSE_CONF_HASH_SHA_1)        || \
  defined(STSE_CONF_HASH_SHA_224)      || \
  defined(STSE_CONF_HASH_SHA_256)      || \
  defined(STSE_CONF_HASH_SHA_384)      || \
  defined(STSE_CONF_HASH_SHA_512)      || \
  defined(STSE_CONF_HASH_SHA_3_256)    || \
  defined(STSE_CONF_HASH_SHA_3_284)    || \
  defined(STSE_CONF_HASH_SHA_3_512)

  cmox_hash_retval_t retval;
  size_t cmox_hash_length = *hash_length;

  retval = cmox_hash_compute(stse_platform_get_cmox_hash_algo(hash_algo),
                             pPayload,
                             payload_length,
                             pHash,
                             *hash_length,
                             &cmox_hash_length);

  /*- Verify Hash compute return */
  if (retval != CMOX_HASH_SUCCESS || cmox_hash_length != *hash_length)
  {
    return STSE_PLATFORM_HASH_ERROR;
  }

  return STSE_OK;
#else
  return STSE_PLATFORM_HASH_ERROR;
#endif /* STSE_CONF_HASH_SHA_1 || STSE_CONF_HASH_SHA_224 ||\
          STSE_CONF_HASH_SHA_256 || STSE_CONF_HASH_SHA_384 || STSE_CONF_HASH_SHA_512 ||\
          STSE_CONF_HASH_SHA_3_256 || STSE_CONF_HASH_SHA_3_284 || STSE_CONF_HASH_SHA_3_512 */
}

/**
  * @brief  Generate Curve25519 key pair
  * @param  P_pEccCtx: Pointer to ECC context
  * @param  P_CurveParams: Curve parameters
  * @param  P_pRandom: Pointer to random data
  * @param  P_RandomLen: Length of random data
  * @param  P_pPrivKey: Pointer to private key buffer
  * @param  P_pPrivKeyLen: Pointer to private key length
  * @param  P_pPubKey: Pointer to public key buffer
  * @param  P_pPubKeyLen: Pointer to public key length
  * @retval CMOX ECC return value
  */
cmox_ecc_retval_t stsafe_cmox_curve25519_generate_key_pair(
  cmox_ecc_handle_t     *P_pEccCtx,
  const cmox_ecc_impl_t P_CurveParams,
  const uint8_t         *P_pRandom,
  size_t                P_RandomLen,
  uint8_t               *P_pPrivKey,
  size_t                *P_pPrivKeyLen,
  uint8_t               *P_pPubKey,
  size_t                *P_pPubKeyLen)
{
  (void)P_pPrivKeyLen;
  cmox_ecc_retval_t retval;

  /* base point */
  const PLAT_UI8 base[32] = {9u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                             0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u
                            };

  /* check for NULL parameters */
  if (P_pPrivKey     == NULL
      || P_pPubKey      == NULL
      || P_pRandom      == NULL
      || P_CurveParams != CMOX_ECC_CURVE25519
      || P_RandomLen      <  32u)
  {
    return CMOX_ECC_ERR_BAD_PARAMETERS;
  }

  memcpy(P_pPrivKey, P_pRandom, 32u);

  /* Clamp private key */
  P_pPrivKey[0]  &= 248u;
  P_pPrivKey[31] &= 127u;
  P_pPrivKey[31] |= 64u;

  /* Perform scalar multiplication to obtain the public key */
  retval = cmox_ecdh(
             P_pEccCtx, P_CurveParams,
             P_pPrivKey, 32u,
             base, 32u,
             P_pPubKey, P_pPubKeyLen);

  return retval;
}

/**
  * @brief  Generate ECC key pair
  * @param  key_type: ECC key type
  * @param  pPrivKey: Pointer to private key buffer
  * @param  pPubKey: Pointer to public key buffer
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_ecc_generate_key_pair(
  stse_ecc_key_type_t key_type,
  PLAT_UI8 *pPrivKey,
  PLAT_UI8 *pPubKey)
{
#if defined(STSE_CONF_ECC_NIST_P_256)        || \
  defined(STSE_CONF_ECC_NIST_P_384)        || \
  defined(STSE_CONF_ECC_NIST_P_521)        || \
  defined(STSE_CONF_ECC_BRAINPOOL_P_256)   || \
  defined(STSE_CONF_ECC_BRAINPOOL_P_384)   || \
  defined(STSE_CONF_ECC_BRAINPOOL_P_512)   || \
  defined(STSE_CONF_ECC_CURVE_25519)       || \
  defined(STSE_CONF_ECC_EDWARD_25519)
  cmox_ecc_retval_t retval;

  /*- Set ECC context */
  cmox_ecc_construct(&Ecc_Ctx,              /* ECC context */
                     CMOX_MATH_FUNCS_SMALL, /* Small math functions */
                     cmox_math_buffer,      /* Crypto math buffer */
                     sizeof(cmox_math_buffer)); /* buffer size */

  /* Minimum random length equal the private key length */
  size_t randomLength = stse_platform_get_cmox_ecc_priv_key_len(key_type);
  /* Align the random length to modulo 4 */
  randomLength += 4 - (randomLength & 0x3);
  /* Add 32bytes to random length if the key is Curve25519 because it will use the Ed25519 key gen */
#ifdef STSE_CONF_ECC_CURVE_25519
  randomLength += ((key_type == STSE_ECC_KT_CURVE25519) ? 32 : 0);
#endif /* STSE_CONF_ECC_CURVE_25519 */
  /* Retry loop in case the RNG isn't strong enough */
  do
  {
    /* - Generate a random number */
    PLAT_UI8 randomNumber[randomLength];
    for (uint8_t i = 0; i < randomLength; i += 4)
    {
      *((PLAT_UI32 *)&randomNumber[i]) = stse_platform_generate_random();
    }

    /*- Generate EdDSA key pair */
#ifdef STSE_CONF_ECC_EDWARD_25519
    if (key_type == STSE_ECC_KT_ED25519)
    {
      retval = cmox_eddsa_keyGen(&Ecc_Ctx,                                  /* ECC context */
                                 stse_platform_get_cmox_ecc_impl(key_type), /* Curve param */
                                 randomNumber,                              /* Random number */
                                 randomLength,                              /* Random number length */
                                 pPrivKey,                                  /* Private key */
                                 NULL,                                      /* Private key length*/
                                 pPubKey,                                   /* Public key */
                                 NULL);                                     /* Public key length */
    }
    else
#endif /* STSE_CONF_ECC_EDWARD_25519 */
#ifdef STSE_CONF_ECC_CURVE_25519
    if (key_type == STSE_ECC_KT_CURVE25519)
    {
      memcpy(pPrivKey, static_c25519_priv_key, 32);
      memcpy(pPubKey, static_c25519_pub_key, 32);

      retval = CMOX_ECC_SUCCESS;
    }
    else
#endif /* STSE_CONF_ECC_CURVE_25519 */
    {
      retval = cmox_ecdsa_keyGen(&Ecc_Ctx,                                  /* ECC context */
                                 stse_platform_get_cmox_ecc_impl(key_type), /* Curve param */
                                 randomNumber,                              /* Random number */
                                 randomLength,                              /* Random number length */
                                 pPrivKey,                                  /* Private key */
                                 NULL,                                      /* Private key length*/
                                 pPubKey,                                   /* Public key */
                                 NULL);                                     /* Public key length */
    }
  } while (retval == CMOX_ECC_ERR_WRONG_RANDOM);

  /* - Clear ECC context */
  cmox_ecc_cleanup(&Ecc_Ctx);

  if (retval != CMOX_ECC_SUCCESS)
  {
    return STSE_PLATFORM_ECC_GENERATE_KEY_PAIR_ERROR;
  }

  return STSE_OK;
#else
  return STSE_PLATFORM_ECC_GENERATE_KEY_PAIR_ERROR;
#endif /* STSE_CONF_ECC_NIST_P_256 || STSE_CONF_ECC_NIST_P_384 || STSE_CONF_ECC_NIST_P_521 ||\
          STSE_CONF_ECC_BRAINPOOL_P_256 || STSE_CONF_ECC_BRAINPOOL_P_384 || STSE_CONF_ECC_BRAINPOOL_P_512 ||\
          STSE_CONF_ECC_CURVE_25519 || STSE_CONF_ECC_EDWARD_25519 */
}

/**
  * @brief  Verify ECC signature
  * @param  key_type: ECC key type
  * @param  pPubKey: Pointer to public key buffer
  * @param  pDigest: Pointer to digest buffer
  * @param  digestLen: Length of digest
  * @param  pSignature: Pointer to signature buffer
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_ecc_verify(
  stse_ecc_key_type_t key_type,
  const PLAT_UI8 *pPubKey,
  PLAT_UI8 *pDigest,
  PLAT_UI16 digestLen,
  PLAT_UI8 *pSignature)
{
#if defined(STSE_CONF_ECC_NIST_P_256)        || \
  defined(STSE_CONF_ECC_NIST_P_384)        || \
  defined(STSE_CONF_ECC_NIST_P_521)        || \
  defined(STSE_CONF_ECC_BRAINPOOL_P_256)   || \
  defined(STSE_CONF_ECC_BRAINPOOL_P_384)   || \
  defined(STSE_CONF_ECC_BRAINPOOL_P_512)   || \
  defined(STSE_CONF_ECC_CURVE_25519)       || \
  defined(STSE_CONF_ECC_EDWARD_25519)
  cmox_ecc_retval_t retval;
  PLAT_UI32 faultCheck;

  /*- Set ECC context */
  cmox_ecc_construct(&Ecc_Ctx,              /* ECC context */
                     CMOX_MATH_FUNCS_SMALL, /* Small math functions */
                     cmox_math_buffer,      /* Crypto math buffer */
                     sizeof(cmox_math_buffer)); /* buffer size */

#ifdef STSE_CONF_ECC_EDWARD_25519
  if (key_type == STSE_ECC_KT_ED25519)
  {
    /* - Perform EDDSA verify */
    retval = cmox_eddsa_verify(&Ecc_Ctx,                                         /* ECC context */
                               stse_platform_get_cmox_ecc_impl(key_type),        /* Curve param */
                               pPubKey,                                          /* Public key */
                               stse_platform_get_cmox_ecc_pub_key_len(key_type), /* Public key length */
                               pDigest,                                          /* Message */
                               digestLen,                                        /* Message length */
                               pSignature,                                       /* Pointer to signature */
                               stse_platform_get_cmox_ecc_sig_len(key_type),     /* Signature size */
                               &faultCheck);                                     /* Fault check variable */
  }
  else
#endif /* STSE_CONF_ECC_EDWARD_25519 */
  {
    /* - Perform ECDSA verify */
    retval = cmox_ecdsa_verify(&Ecc_Ctx,                                         /* ECC context */
                               stse_platform_get_cmox_ecc_impl(key_type),        /* Curve : SECP256R1 */
                               pPubKey,                                          /* Public key */
                               stse_platform_get_cmox_ecc_pub_key_len(key_type), /* Public key length */
                               pDigest,                                          /* Message */
                               digestLen,                                        /* Message length */
                               pSignature,                                       /* Pointer to signature */
                               stse_platform_get_cmox_ecc_sig_len(key_type),     /* Signature size */
                               &faultCheck                                       /* Fault check variable */
                              );
  }

  /* - Clear ECC context */
  cmox_ecc_cleanup(&Ecc_Ctx);

  if (retval != CMOX_ECC_AUTH_SUCCESS)
  {
    return STSE_PLATFORM_ECC_VERIFY_ERROR;
  }

  return STSE_OK;
#else
  return STSE_PLATFORM_ECC_VERIFY_ERROR;
#endif /* STSE_CONF_ECC_NIST_P_256 || STSE_CONF_ECC_NIST_P_384 || STSE_CONF_ECC_NIST_P_521 ||\
          STSE_CONF_ECC_BRAINPOOL_P_256 || STSE_CONF_ECC_BRAINPOOL_P_384 || STSE_CONF_ECC_BRAINPOOL_P_512 ||\
          STSE_CONF_ECC_CURVE_25519 || STSE_CONF_ECC_EDWARD_25519 */
}

/**
  * @brief  Sign data using ECC
  * @param  key_type: ECC key type
  * @param  pPrivKey: Pointer to private key buffer
  * @param  pDigest: Pointer to digest buffer
  * @param  digestLen: Length of digest
  * @param  pSignature: Pointer to signature buffer
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_ecc_sign(
  stse_ecc_key_type_t key_type,
  PLAT_UI8 *pPrivKey,
  PLAT_UI8 *pDigest,
  PLAT_UI16 digestLen,
  PLAT_UI8 *pSignature)
{
#if defined(STSE_CONF_ECC_NIST_P_256)        || \
  defined(STSE_CONF_ECC_NIST_P_384)        || \
  defined(STSE_CONF_ECC_NIST_P_521)        || \
  defined(STSE_CONF_ECC_BRAINPOOL_P_256)   || \
  defined(STSE_CONF_ECC_BRAINPOOL_P_384)   || \
  defined(STSE_CONF_ECC_BRAINPOOL_P_512)   || \
  defined(STSE_CONF_ECC_CURVE_25519)       || \
  defined(STSE_CONF_ECC_EDWARD_25519)
  cmox_ecc_retval_t retval;

  if (pPrivKey == NULL)
  {
    return STSE_PLATFORM_INVALID_PARAMETER;
  }

  /*- Set ECC context */
  cmox_ecc_construct(&Ecc_Ctx,              /* ECC context */
                     CMOX_MATH_FUNCS_SMALL, /* Small math functions */
                     cmox_math_buffer,      /* Crypto math buffer */
                     sizeof(cmox_math_buffer)); /* buffer size */

#ifdef STSE_CONF_ECC_EDWARD_25519
  if (key_type == STSE_ECC_KT_ED25519)
  {
    /* - Perform EDDSA sign */
    retval = cmox_eddsa_sign(&Ecc_Ctx,                                          /* ECC context */
                             stse_platform_get_cmox_ecc_impl(key_type),         /* Curve param */
                             pPrivKey,                                          /* Private key */
                             stse_platform_get_cmox_ecc_priv_key_len(key_type), /* Private key length*/
                             pDigest,                                           /* Message */
                             digestLen,                                         /* Message length */
                             pSignature,                                        /* Signature */
                             NULL);                                             /* Signature length */
  }
  else
#endif /* STSE_CONF_ECC_EDWARD_25519 */
  {
    do
    {
      /* - Generate a random number */
      size_t priv_key_len = stse_platform_get_cmox_ecc_priv_key_len(key_type);
      size_t align = 4 - (priv_key_len & 0x3);
      size_t randomLength = priv_key_len + align;
      PLAT_UI8 randomNumber[randomLength];
      for (uint8_t i = 0; i < randomLength; i += 4)
      {
        *((PLAT_UI32 *)&randomNumber[i]) = stse_platform_generate_random();
      }

      /* - Perform ECDSA sign */
      retval = cmox_ecdsa_sign(&Ecc_Ctx,                                  /* ECC context */
                               stse_platform_get_cmox_ecc_impl(key_type), /* Curve param */
                               randomNumber,
                               stse_platform_get_cmox_ecc_priv_key_len(key_type),
                               pPrivKey,                                          /* Private key */
                               stse_platform_get_cmox_ecc_priv_key_len(key_type), /* Private key length*/
                               pDigest,                                           /* Message */
                               digestLen,                                         /* Message length */
                               pSignature,                                        /* Signature */
                               NULL                                               /* Signature length */
                              );
    } while (retval == CMOX_ECC_ERR_WRONG_RANDOM);
  }

  /* - Clear ECC context */
  cmox_ecc_cleanup(&Ecc_Ctx);

  if (retval != CMOX_ECC_SUCCESS)
  {
    return STSE_PLATFORM_ECC_SIGN_ERROR;
  }

  return STSE_OK;
#else
  return STSE_PLATFORM_ECC_SIGN_ERROR;
#endif /* STSE_CONF_ECC_NIST_P_256 || STSE_CONF_ECC_NIST_P_384 || STSE_CONF_ECC_NIST_P_521 ||\
          STSE_CONF_ECC_BRAINPOOL_P_256 || STSE_CONF_ECC_BRAINPOOL_P_384 || STSE_CONF_ECC_BRAINPOOL_P_512 ||\
          STSE_CONF_ECC_CURVE_25519 || STSE_CONF_ECC_EDWARD_25519 */
}

/**
  * @brief  Perform ECC ECDH key exchange
  * @param  key_type: ECC key type
  * @param  pPubKey: Pointer to public key buffer
  * @param  pPrivKey: Pointer to private key buffer
  * @param  pSharedSecret: Pointer to shared secret buffer
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_ecc_ecdh(
  stse_ecc_key_type_t key_type,
  const PLAT_UI8 *pPubKey,
  const PLAT_UI8 *pPrivKey,
  PLAT_UI8 *pSharedSecret)
{
  cmox_ecc_retval_t retval;

  /*- Set ECC context */
  cmox_ecc_construct(&Ecc_Ctx,              /* ECC context */
                     CMOX_MATH_FUNCS_SMALL, /* Small math functions */
                     cmox_math_buffer,      /* Crypto math buffer */
                     sizeof(cmox_math_buffer)); /* buffer size */

  retval = cmox_ecdh(&Ecc_Ctx,                                   /* ECC context */
                     stse_platform_get_cmox_ecc_impl(key_type),  /* Curve param */
                     pPrivKey,                                   /* Private key (local) */
                     stse_platform_get_cmox_ecc_priv_key_len(key_type), /* Private key length */
                     pPubKey,                                    /* Public key (remote) */
                     stse_platform_get_cmox_ecc_pub_key_len(key_type),  /* Public key length */
                     pSharedSecret,                              /* Shared secret */
                     NULL);                                      /* Shared secret length */

  /* - Clear ECC context */
  cmox_ecc_cleanup(&Ecc_Ctx);

  if (retval != CMOX_ECC_SUCCESS)
  {
    return STSE_PLATFORM_ECC_ECDH_ERROR;
  }
  else
  {
    return STSE_OK;
  }
}

/**
  * @brief  Initialize AES CMAC
  * @param  pKey: Pointer to key buffer
  * @param  key_length: Length of key
  * @param  exp_tag_size: Expected tag size
  * @retval STSAFE return code
  */
/* AES CMAC functions */
#if defined(STSE_CONF_USE_HOST_KEY_ESTABLISHMENT) || \
  defined(STSE_CONF_USE_SYMMETRIC_KEY_ESTABLISHMENT) || \
  defined(STSE_CONF_USE_HOST_SESSION)
stse_ReturnCode_t stse_platform_aes_cmac_init(const PLAT_UI8     *pKey,
                                              PLAT_UI16         key_length,
                                              PLAT_UI16         exp_tag_size)
{
  cmox_mac_retval_t retval;

  /* - Call CMAC constructor */
  pMAC_Handler = cmox_cmac_construct(&CMAC_Handler, CMOX_CMAC_AESSMALL);

  /* - Init MAC */
  retval = cmox_mac_init(pMAC_Handler);
  if (retval != CMOX_MAC_SUCCESS)
  {
    return STSE_PLATFORM_AES_CMAC_COMPUTE_ERROR;
  }
  /* - Set Tag length */
  retval = cmox_mac_setTagLen(pMAC_Handler, exp_tag_size);
  if (retval != CMOX_MAC_SUCCESS)
  {
    return STSE_PLATFORM_AES_CMAC_COMPUTE_ERROR;
  }
  /* - Set Key  */
  retval = cmox_mac_setKey(pMAC_Handler, pKey, key_length);
  if (retval != CMOX_MAC_SUCCESS)
  {
    return STSE_PLATFORM_AES_CMAC_COMPUTE_ERROR;
  }

  return STSE_OK;
}

/**
  * @brief  Append data to AES CMAC
  * @param  pInput: Pointer to input data buffer
  * @param  length: Length of input data
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_aes_cmac_append(PLAT_UI8 *pInput,
                                                PLAT_UI16 length)
{
  cmox_mac_retval_t retval;

  retval = cmox_mac_append(pMAC_Handler, pInput, length);

  if (retval != CMOX_MAC_SUCCESS)
  {
    return STSE_PLATFORM_AES_CMAC_COMPUTE_ERROR;
  }

  return STSE_OK;
}

/**
  * @brief  Finish AES CMAC computation
  * @param  pTag: Pointer to tag buffer
  * @param  pTagLen: Pointer to tag length
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_aes_cmac_compute_finish(PLAT_UI8 *pTag, PLAT_UI8 *pTagLen)
{
  cmox_mac_retval_t retval;
  size_t cmox_tag_len = *pTagLen;

  retval = cmox_mac_generateTag(pMAC_Handler, pTag, &cmox_tag_len);
  if (retval != CMOX_MAC_SUCCESS)
  {
    return STSE_PLATFORM_AES_CMAC_COMPUTE_ERROR;
  }

  *pTagLen = (PLAT_UI8)cmox_tag_len;

  retval = cmox_mac_cleanup(pMAC_Handler);
  if (retval != CMOX_MAC_SUCCESS)
  {
    return STSE_PLATFORM_AES_CMAC_COMPUTE_ERROR;
  }

  return STSE_OK;
}

/**
  * @brief  Finish AES CMAC verification
  * @param  pTag: Pointer to tag buffer
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_aes_cmac_verify_finish(PLAT_UI8 *pTag)
{
  cmox_mac_retval_t retval;
  uint32_t cmox_mac_fault_check = 0;

  retval = cmox_mac_verifyTag(
    pMAC_Handler,
    pTag,
    &cmox_mac_fault_check);

  cmox_mac_cleanup(pMAC_Handler);

  if ((retval != CMOX_MAC_AUTH_SUCCESS) || (cmox_mac_fault_check != CMOX_MAC_AUTH_SUCCESS))
  {
    return STSE_PLATFORM_AES_CMAC_VERIFY_ERROR;
  }

  return STSE_OK;
}

/**
  * @brief  Compute AES CMAC
  * @param  pPayload: Pointer to payload data
  * @param  payload_length: Length of payload data
  * @param  pKey: Pointer to key buffer
  * @param  key_length: Length of key
  * @param  exp_tag_size: Expected tag size
  * @param  pTag: Pointer to tag buffer
  * @param  pTag_length: Pointer to tag length
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_aes_cmac_compute(const PLAT_UI8 *pPayload,
                                                 PLAT_UI16         payload_length,
                                                 const PLAT_UI8     *pKey,
                                                 PLAT_UI16         key_length,
                                                 PLAT_UI16         exp_tag_size,
                                                 PLAT_UI8         *pTag,
                                                 PLAT_UI16         *pTag_length)
{
  cmox_mac_retval_t retval;
  size_t cmox_tag_len = *pTag_length;

  retval = cmox_mac_compute(CMOX_CMAC_AESSMALL_ALGO, /* Use AES CMAC algorithm */
                            pPayload,                /* Message */
                            payload_length,          /* Message length*/
                            pKey,                    /* AES key */
                            key_length,              /* AES key length */
                            NULL,                    /* Custom Data */
                            0,                       /* Custom Data length */
                            pTag,                    /* Tag */
                            exp_tag_size,            /* Expected Tag size */
                            &cmox_tag_len            /* Generated Tag size */
                           );

  if (retval != CMOX_MAC_SUCCESS)
  {
    return STSE_PLATFORM_AES_CMAC_VERIFY_ERROR;
  }

  *pTag_length = (PLAT_UI16)cmox_tag_len;

  return STSE_OK;
}

/**
  * @brief  Verify AES CMAC
  * @param  pPayload: Pointer to payload data
  * @param  payload_length: Length of payload data
  * @param  pKey: Pointer to key buffer
  * @param  key_length: Length of key
  * @param  pTag: Pointer to tag buffer
  * @param  tag_length: Length of tag
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_aes_cmac_verify(const PLAT_UI8 *pPayload,
                                                PLAT_UI16         payload_length,
                                                const PLAT_UI8     *pKey,
                                                PLAT_UI16         key_length,
                                                const PLAT_UI8     *pTag,
                                                PLAT_UI16         tag_length)
{
  cmox_mac_retval_t retval;

  /* - Perform CMAC verification */
  retval = cmox_mac_verify(CMOX_CMAC_AESSMALL_ALGO, /* Use AES CMAC algorithm */
                           pPayload,                /* Message length */
                           payload_length,          /* Message length */
                           pKey,                    /* AES key */
                           key_length,              /* AES key length */
                           NULL,                    /* Custom data */
                           0,                       /* Custom data length*/
                           pTag,                    /* Tag */
                           tag_length               /* Tag size */
                          );

  if (retval != CMOX_MAC_AUTH_SUCCESS)
  {
    return STSE_PLATFORM_AES_CMAC_VERIFY_ERROR;
  }

  return STSE_OK;
}
#endif /* defined(STSE_CONF_USE_HOST_KEY_ESTABLISHMENT) || \
          defined(STSE_CONF_USE_SYMMETRIC_KEY_ESTABLISHMENT) || \
          defined(STSE_CONF_USE_HOST_SESSION) */

/**
  * @brief  Encrypt data using AES CCM
  * @param  pPlaintext: Pointer to plaintext data
  * @param  plaintext_length: Length of plaintext data
  * @param  pKey: Pointer to key buffer
  * @param  key_length: Length of key
  * @param  pNonce: Pointer to nonce buffer
  * @param  nonce_length: Length of nonce
  * @param  pAssocData: Pointer to associated data buffer
  * @param  assocData_length: Length of associated data
  * @param  pEncryptedtext: Pointer to encrypted text buffer
  * @param  pEncryptedtext_length: Pointer to encrypted text length
  * @param  pTag: Pointer to tag buffer
  * @param  tag_length: Length of tag
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_aes_ccm_enc(const PLAT_UI8 *pPlaintext,
                                            PLAT_UI16         plaintext_length,
                                            const PLAT_UI8     *pKey,
                                            PLAT_UI16          key_length,
                                            const PLAT_UI8     *pNonce,
                                            PLAT_UI16          nonce_length,
                                            const PLAT_UI8     *pAssocData,
                                            PLAT_UI16          assocData_length,
                                            PLAT_UI8           *pEncryptedtext,
                                            PLAT_UI16         *pEncryptedtext_length,
                                            PLAT_UI8           *pTag,
                                            PLAT_UI16          tag_length)
{
  cmox_cipher_retval_t retval;
  PLAT_UI8 pCiphertext[ *pEncryptedtext_length + tag_length ];
  size_t ciphertext_length;

  retval = cmox_aead_encrypt(CMOX_AESSMALL_CCM_ENC_ALGO,    /* Use AES CCM algorithm */
                             pPlaintext,                                 /* Plain text */
                             plaintext_length,                            /* Plain text length */
                             tag_length,                                    /* Tag length*/
                             pKey,                                        /* AES key */
                             key_length,                                    /* AES key length*/
                             pNonce,                                        /* Nonce */
                             nonce_length,                                /* Nonce length */
                             pAssocData,                                    /* Associated Data */
                             assocData_length,                            /* Associated Data length */
                             pCiphertext,                                /* Ciphered text */
                             &ciphertext_length                            /* Ciphered length */
                            );

  if (retval != CMOX_CIPHER_SUCCESS)
  {
    return STSE_PLATFORM_AES_CCM_ENCRYPT_ERROR;
  }

  memcpy(pEncryptedtext, pCiphertext, *pEncryptedtext_length);
  memcpy(pTag, &pCiphertext[*pEncryptedtext_length], tag_length);

  return STSE_OK;
}

/**
  * @brief  Decrypt data using AES CCM
  * @param  pEncryptedtext: Pointer to encrypted text buffer
  * @param  encryptedtext_length: Length of encrypted text
  * @param  pTag: Pointer to tag buffer
  * @param  tag_length: Length of tag
  * @param  pKey: Pointer to key buffer
  * @param  key_length: Length of key
  * @param  pNonce: Pointer to nonce buffer
  * @param  nonce_length: Length of nonce
  * @param  pAssocData: Pointer to associated data buffer
  * @param  assocData_length: Length of associated data
  * @param  pPlaintext: Pointer to plaintext buffer
  * @param  plaintext_length: Length of plaintext
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_aes_ccm_dec(const PLAT_UI8 *pEncryptedtext, PLAT_UI16 encryptedtext_length,
                                            const PLAT_UI8 *pTag,
                                            PLAT_UI16 tag_length,
                                            const PLAT_UI8 *pKey,
                                            PLAT_UI16 key_length,
                                            const PLAT_UI8 *pNonce,
                                            PLAT_UI16 nonce_length,
                                            const PLAT_UI8 *pAssocData,
                                            PLAT_UI16 assocData_length,
                                            const PLAT_UI8 *pPlaintext,
                                            PLAT_UI16 plaintext_length)
{
  cmox_cipher_retval_t retval;

  size_t ciphertext_length = (size_t)encryptedtext_length + (size_t)tag_length;
  PLAT_UI8 pCiphertext[ ciphertext_length ];

  memcpy(pCiphertext, pEncryptedtext, (size_t)encryptedtext_length);

  memcpy(&pCiphertext[encryptedtext_length], pTag, tag_length);

  retval = cmox_aead_decrypt(CMOX_AESSMALL_CCM_DEC_ALGO,    /* Use AES CCM algorithm */
                             pCiphertext,                                /* Ciphered Text */
                             ciphertext_length,                            /* Ciphered Text length */
                             tag_length,                                   /* Tag length */
                             pKey,                                        /* AES Key*/
                             key_length,                                    /* AES Key length*/
                             pNonce,                                        /* Nonce */
                             nonce_length,                                /* Nonce length */
                             pAssocData,                                    /* Associated Data */
                             assocData_length,                            /* Associated Data length */
                             (PLAT_UI8 *)pPlaintext,                        /* Plain Text */
                             (size_t *)&plaintext_length                    /* Plain Text length*/
                            );

  if (retval != CMOX_CIPHER_AUTH_SUCCESS)
  {
    return STSE_PLATFORM_AES_CCM_DECRYPT_ERROR;
  }
  else
  {
    return STSE_OK;
  }
}

/**
  * @brief  Encrypt data using AES CBC
  * @param  pPlaintext: Pointer to plaintext data
  * @param  plaintext_length: Length of plaintext data
  * @param  pInitial_value: Pointer to initial value buffer
  * @param  pKey: Pointer to key buffer
  * @param  key_length: Length of key
  * @param  pEncryptedtext: Pointer to encrypted text buffer
  * @param  pEncryptedtext_length: Pointer to encrypted text length
  * @retval STSAFE return code
  */
/* AES CBC / ECB functions */
#if defined(STSE_CONF_USE_HOST_KEY_ESTABLISHMENT) || \
  defined(STSE_CONF_USE_HOST_SESSION)
stse_ReturnCode_t stse_platform_aes_cbc_enc(const PLAT_UI8 *pPlaintext,
                                            PLAT_UI16  plaintext_length,
                                            PLAT_UI8 *pInitial_value,
                                            const PLAT_UI8 *pKey,
                                            PLAT_UI16  key_length,
                                            PLAT_UI8  *pEncryptedtext,
                                            PLAT_UI16 *pEncryptedtext_length)
{
  cmox_cipher_retval_t retval;
  size_t cmox_encryptedtext_len = *pEncryptedtext_length;

  /*- Perform AES ECB Encryption */
  retval = cmox_cipher_encrypt(CMOX_AESSMALL_CBC_ENC_ALGO, /* Use AES CBC algorithm */
                               pPlaintext,                 /* Plain Text */
                               plaintext_length,           /* Plain Text length*/
                               pKey,                       /* AES Key */
                               key_length,                 /* AES Key length*/
                               pInitial_value,             /* Initial Value */
                               16,                         /* Initial Value length */
                               pEncryptedtext,             /* Ciphered Text */
                               &cmox_encryptedtext_len     /* Ciphered Text length*/
                              );

  /*- Verify AES ECB Encryption status */
  if (retval != CMOX_CIPHER_SUCCESS)
  {
    return STSE_PLATFORM_AES_CBC_ENCRYPT_ERROR;
  }

  *pEncryptedtext_length = (PLAT_UI16)cmox_encryptedtext_len;

  return STSE_OK;
}

/**
  * @brief  Decrypt data using AES CBC
  * @param  pEncryptedtext: Pointer to encrypted text buffer
  * @param  encryptedtext_length: Length of encrypted text
  * @param  pInitial_value: Pointer to initial value buffer
  * @param  pKey: Pointer to key buffer
  * @param  key_length: Length of key
  * @param  pPlaintext: Pointer to plaintext buffer
  * @param  pPlaintext_length: Pointer to plaintext length
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_aes_cbc_dec(const PLAT_UI8 *pEncryptedtext,
                                            PLAT_UI16  encryptedtext_length,
                                            PLAT_UI8 *pInitial_value,
                                            const PLAT_UI8 *pKey,
                                            PLAT_UI16  key_length,
                                            PLAT_UI8  *pPlaintext,
                                            PLAT_UI16 *pPlaintext_length)
{
  cmox_cipher_retval_t retval;
  size_t cmox_plaintext_len = *pPlaintext_length;

  /*- Perform AES ECB decryption */
  retval = cmox_cipher_decrypt(CMOX_AESSMALL_CBC_DEC_ALGO, /* Use AES CBC algorithm */
                               pEncryptedtext,             /* Ciphered Text */
                               encryptedtext_length,       /* Ciphered Text length */
                               pKey,                       /* AES key length */
                               key_length,                 /* AES key */
                               pInitial_value,             /* Initial Value */
                               16,                         /* Initial Value length*/
                               pPlaintext,                 /* Plain Text */
                               &cmox_plaintext_len         /* Plain Text length*/
                              );

  /*- Verify AES ECB decrypt return */
  if (retval != CMOX_CIPHER_SUCCESS)
  {
    return STSE_PLATFORM_AES_CBC_DECRYPT_ERROR;
  }

  *pPlaintext_length = (PLAT_UI16)cmox_plaintext_len;

  return STSE_OK;
}

/**
  * @brief  Encrypt data using AES ECB
  * @param  pPlaintext: Pointer to plaintext data
  * @param  plaintext_length: Length of plaintext data
  * @param  pKey: Pointer to key buffer
  * @param  key_length: Length of key
  * @param  pEncryptedtext: Pointer to encrypted text buffer
  * @param  pEncryptedtext_length: Pointer to encrypted text length
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_aes_ecb_enc(const PLAT_UI8 *pPlaintext,
                                            PLAT_UI16  plaintext_length,
                                            const PLAT_UI8 *pKey,
                                            PLAT_UI16  key_length,
                                            PLAT_UI8  *pEncryptedtext,
                                            PLAT_UI16 *pEncryptedtext_length)
{
  cmox_cipher_retval_t retval;
  PLAT_UI8 IV[16] = {0};
  size_t cmox_encryptedtext_len = *pEncryptedtext_length;

  /*- Perform AES ECB Encryption */
  retval = cmox_cipher_encrypt(CMOX_AESSMALL_ECB_ENC_ALGO, /* Use AES ECB algorithm */
                               pPlaintext,                 /* Plain Text */
                               plaintext_length,           /* Plain Text length*/
                               pKey,                       /* AES Key */
                               key_length,                 /* AES Key length*/
                               IV,                         /* Initial Value */
                               16,                         /* Initial Value length */
                               pEncryptedtext,             /* Ciphered Text */
                               &cmox_encryptedtext_len     /* Ciphered Text length*/
                              );

  /*- Verify AES ECB Encryption status */
  if (retval != CMOX_CIPHER_SUCCESS)
  {
    return STSE_PLATFORM_AES_ECB_ENCRYPT_ERROR;
  }

  *pEncryptedtext_length = (PLAT_UI16)cmox_encryptedtext_len;

  return STSE_OK;
}

/**
  * @brief  Decrypt data using AES ECB
  * @param  pEncryptedtext: Pointer to encrypted text buffer
  * @param  encryptedtext_length: Length of encrypted text
  * @param  pKey: Pointer to key buffer
  * @param  key_length: Length of key
  * @param  pPlaintext: Pointer to plaintext buffer
  * @param  pPlaintext_length: Pointer to plaintext length
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_aes_ecb_dec(const PLAT_UI8 *pEncryptedtext,
                                            PLAT_UI16  encryptedtext_length,
                                            const PLAT_UI8 *pKey,
                                            PLAT_UI16  key_length,
                                            PLAT_UI8  *pPlaintext,
                                            PLAT_UI16 *pPlaintext_length)
{
  cmox_cipher_retval_t retval;
  PLAT_UI8 IV[16] = {0};
  size_t cmox_plaintext_len = *pPlaintext_length;

  /*- Perform AES ECB decryption */
  retval = cmox_cipher_decrypt(CMOX_AESSMALL_ECB_DEC_ALGO, /* Use AES ECB algorithm */
                               pEncryptedtext,             /* Ciphered Text */
                               encryptedtext_length,       /* Ciphered Text length */
                               pKey,                       /* AES key length */
                               key_length,                 /* AES key */
                               IV,                         /* Initial Value */
                               16,                         /* Initial Value length*/
                               pPlaintext,                 /* Plain Text */
                               &cmox_plaintext_len         /* Plain Text length*/
                              );

  /*- Verify AES ECB decrypt return */
  if (retval != CMOX_CIPHER_SUCCESS)
  {
    return STSE_PLATFORM_AES_ECB_DECRYPT_ERROR;
  }

  *pPlaintext_length = (PLAT_UI16)cmox_plaintext_len;

  return STSE_OK;
}
#endif /* defined(STSE_CONF_USE_HOST_KEY_ESTABLISHMENT) || \
          defined(STSE_CONF_USE_HOST_SESSION) */

#if defined(STSE_CONF_USE_HOST_KEY_PROVISIONING_WRAPPED) || \
  defined(STSE_CONF_USE_HOST_KEY_PROVISIONING_WRAPPED_AUTHENTICATED) || \
  defined(STSE_CONF_USE_SYMMETRIC_KEY_PROVISIONING_WRAPPED) || \
  defined(STSE_CONF_USE_SYMMETRIC_KEY_PROVISIONING_WRAPPED_AUTHENTICATED)
/**
  * @brief  Encrypt data using NIST key wrap
  * @param  pPayload: Pointer to payload data
  * @param  payload_length: Length of payload data
  * @param  pKey: Pointer to key buffer
  * @param  key_length: Length of key
  * @param  pOutput: Pointer to output buffer
  * @param  pOutput_length: Pointer to output length
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_nist_kw_encrypt(PLAT_UI8 *pPayload, PLAT_UI32 payload_length,
                                                PLAT_UI8 *pKey, PLAT_UI8 key_length,
                                                PLAT_UI8 *pOutput, PLAT_UI32 *pOutput_length)
{
  cmox_cipher_retval_t retval;
  size_t cmox_output_length = *pOutput_length;

  retval = cmox_cipher_encrypt(
             CMOX_AESSMALL_KEYWRAP_ENC_ALGO,
             pPayload, payload_length,
             pKey, key_length,
             KEK_WRAP_IV, KEK_WRAP_IV_SIZE,
             pOutput, &cmox_output_length);

  if (retval != CMOX_CIPHER_SUCCESS)
  {
    return STSE_PLATFORM_KEYWRAP_ERROR;
  }

  *pOutput_length = (PLAT_UI32)cmox_output_length;
  return STSE_OK;
}
#endif /* STSE_CONF_USE_HOST_KEY_PROVISIONING_WRAPPED || \
          STSE_CONF_USE_HOST_KEY_PROVISIONING_WRAPPED_AUTHENTICATED || \
          STSE_CONF_USE_SYMMETRIC_KEY_PROVISIONING_WRAPPED || \
          STSE_CONF_USE_SYMMETRIC_KEY_PROVISIONING_WRAPPED_AUTHENTICATED */
/**
  * @brief  Compute HMAC-SHA256
  * @param  pSalt: Pointer to salt buffer
  * @param  salt_length: Length of salt
  * @param  pInput_keying_material: Pointer to input keying material buffer
  * @param  input_keying_material_length: Length of input keying material
  * @param  pInfo: Pointer to info buffer
  * @param  info_length: Length of info
  * @param  pOutput_keying_material: Pointer to output keying material buffer
  * @param  output_keying_material_length: Length of output keying material
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_hmac_sha256_compute(PLAT_UI8 *pSalt, PLAT_UI16 salt_length,
                                                    PLAT_UI8 *pInput_keying_material,
                                                    PLAT_UI16 input_keying_material_length,
                                                    PLAT_UI8 *pInfo, PLAT_UI16 info_length,
                                                    PLAT_UI8 *pOutput_keying_material,
                                                    PLAT_UI16 output_keying_material_length)
{
  stse_ReturnCode_t retval;
  PLAT_UI8 pPseudorandom_key[STSAFEA_SHA_256_HASH_SIZE];

  /* Extract pseudo-random key from input keying material */
  retval = stse_platform_hmac_sha256_extract(pSalt,
                                             salt_length,
                                             pInput_keying_material,
                                             input_keying_material_length,
                                             pPseudorandom_key,
                                             STSAFEA_SHA_256_HASH_SIZE);

  if (retval != 0)
  {
    memset(pPseudorandom_key, 0, STSAFEA_SHA_256_HASH_SIZE);
    return retval;
  }

  /* Expand output key from pseudo-random key */
  retval = stse_platform_hmac_sha256_expand(pPseudorandom_key,
                                            STSAFEA_SHA_256_HASH_SIZE,
                                            pInfo,
                                            info_length,
                                            pOutput_keying_material,
                                            output_keying_material_length);

  /* Pseudo-random key no more needed, cleanup */
  memset(pPseudorandom_key, 0, STSAFEA_SHA_256_HASH_SIZE);

  return retval;
}

/**
  * @brief  Extract HMAC-SHA256
  * @param  pSalt: Pointer to salt buffer
  * @param  salt_length: Length of salt
  * @param  pInput_keying_material: Pointer to input keying material buffer
  * @param  input_keying_material_length: Length of input keying material
  * @param  pPseudorandom_key: Pointer to pseudorandom key buffer
  * @param  pseudorandom_key_expected_length: Expected length of pseudorandom key
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_hmac_sha256_extract(PLAT_UI8 *pSalt, PLAT_UI16 salt_length,
                                                    PLAT_UI8 *pInput_keying_material,
                                                    PLAT_UI16 input_keying_material_length,
                                                    PLAT_UI8 *pPseudorandom_key,
                                                    PLAT_UI16 pseudorandom_key_expected_length)
{
  cmox_mac_retval_t retval;

  size_t pseudorandom_key_length = pseudorandom_key_expected_length;

  retval = cmox_mac_compute(CMOX_HMAC_SHA256_ALGO,
                            pInput_keying_material,
                            input_keying_material_length,
                            pSalt,
                            salt_length,
                            NULL,
                            0,
                            pPseudorandom_key,
                            pseudorandom_key_expected_length,
                            &pseudorandom_key_length);

  /*- Verify MAC compute return */
  if (retval != CMOX_MAC_SUCCESS)
  {
    return STSE_PLATFORM_HKDF_ERROR;
  }

  return STSE_OK;
}

/**
  * @brief  Expand HMAC-SHA256
  * @param  pPseudorandom_key: Pointer to pseudorandom key buffer
  * @param  pseudorandom_key_length: Length of pseudorandom key
  * @param  pInfo: Pointer to info buffer
  * @param  info_length: Length of info
  * @param  pOutput_keying_material: Pointer to output keying material buffer
  * @param  output_keying_material_length: Length of output keying material
  * @retval STSAFE return code
  */
stse_ReturnCode_t stse_platform_hmac_sha256_expand(PLAT_UI8  *pPseudorandom_key, PLAT_UI16 pseudorandom_key_length,
                                                   PLAT_UI8  *pInfo, PLAT_UI16 info_length,
                                                   PLAT_UI8  *pOutput_keying_material,
                                                   PLAT_UI16 output_keying_material_length)
{
  cmox_mac_retval_t retval = CMOX_MAC_SUCCESS;

  PLAT_UI8       tmp[CMOX_SHA256_SIZE];
  PLAT_UI16   tmp_length = 0;
  PLAT_UI16    out_index = 0;
  PLAT_UI8       n = 0x1;

  cmox_mac_handle_t *pMac_handle;
  cmox_hmac_handle_t hmac_handle;

  /*    RFC 5869 : output keying material must be
   *         - L <= 255*HashLen
   *         - N = ceil(L/HashLen) */
  if (pOutput_keying_material == NULL
      || ((output_keying_material_length / CMOX_SHA256_SIZE) +
          ((output_keying_material_length % CMOX_SHA256_SIZE) != 0)) > 255)
  {
    return STSE_COMMUNICATION_ERROR;
  }

  pMac_handle = cmox_hmac_construct(&hmac_handle, CMOX_HMAC_SHA256);
  retval = cmox_mac_init(pMac_handle);

  if (retval != CMOX_MAC_SUCCESS)
  {
    return STSE_COMMUNICATION_ERROR;
  }

  while (out_index < output_keying_material_length)
  {
    PLAT_UI16 left = output_keying_material_length - out_index;

    retval = cmox_mac_setKey(pMac_handle, pPseudorandom_key, pseudorandom_key_length);
    if (retval != CMOX_MAC_SUCCESS)
    {
      break;
    }
    retval = cmox_mac_append(pMac_handle, tmp, tmp_length);
    if (retval != CMOX_MAC_SUCCESS)
    {
      break;
    }
    retval = cmox_mac_append(pMac_handle, pInfo, info_length);
    if (retval != CMOX_MAC_SUCCESS)
    {
      break;
    }
    retval = cmox_mac_append(pMac_handle, &n, 1);
    if (retval != CMOX_MAC_SUCCESS)
    {
      break;
    }
    retval = cmox_mac_generateTag(pMac_handle, tmp, NULL);
    if (retval != CMOX_MAC_SUCCESS)
    {
      break;
    }

    left = left < CMOX_SHA256_SIZE ? left : CMOX_SHA256_SIZE;
    memcpy(pOutput_keying_material + out_index, tmp, left);

    tmp_length = CMOX_SHA256_SIZE;
    out_index += CMOX_SHA256_SIZE;
    n++;
  }

  cmox_mac_cleanup(pMac_handle);

  /*- Verify MAC compute return */
  if (retval != CMOX_MAC_SUCCESS)
  {
    memset(tmp, 0, CMOX_SHA256_SIZE);
    memset(pOutput_keying_material, 0, output_keying_material_length);
    return STSE_COMMUNICATION_ERROR;
  }
  else
  {
    return STSE_OK;
  }
}

/**
  * @}
  */

