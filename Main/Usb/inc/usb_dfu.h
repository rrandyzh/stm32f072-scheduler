/**
  ******************************************************************************
  * @file    usb_dfu.h
  * @author  alex.zhang
  * @version V1.0.0
  * @date    05-March-2016
  * @brief   This file contains definitions for usb dfu.
  ******************************************************************************
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DFU_H
#define __USB_DFU_H

#ifdef __cplusplus
 extern "C" {
#endif
     
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

     
/* Exported constants --------------------------------------------------------*/
#define USER_DATA_OPTION_BYTE_ADDR (uint32_t)(0x1ffff804)
/** 
  * @brief  Dfu mode enumeration  
  */    
typedef enum
{
    ENABLE_USB_DFU = 0x00,
    DISABLE_USB_DFU = !ENABLE_USB_DFU
}DfuMode_TypeDef;

#define USER_DATA_OPTION_BYTE_ADDR (uint32_t)(0x1ffff804)
#define OPTION_DATA_32BIT          (*(__IO uint32_t*)USER_DATA_OPTION_BYTE_ADDR) 
#define OPTION_DATA1               (uint16_t)((OPTION_DATA_32BIT>>8)&0xFF00)
#define OPTION_DATA0               (uint8_t)(OPTION_DATA_32BIT)
#define OPTION_DATA_16BIT          (uint16_t)(OPTION_DATA1|OPTION_DATA0)
#define JUMP_TO_APP                (0xabcd)
#define JUMP_TO_DFU                (0x1234)
#define JUMP_TO_EEUPDATE           (0x5678)
   
extern void WriteTheDfuDataToOptionByte(uint16_t DfuMode);
#ifdef __cplusplus
}
#endif

#endif /* __USB_DFU_H */

