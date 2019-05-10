/**
  ******************************************************************************
  * @file           : usbd_custom_hid_if.c
  * @brief          : USB Device Custom HID interface file.
  ******************************************************************************
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  * 1. Redistributions of source code must retain the above copyright notice,
  * this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  * this list of conditions and the following disclaimer in the documentation
  * and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of its contributors
  * may be used to endorse or promote products derived from this software
  * without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "usbd_custom_hid_if.h"
#include "usb_dfu.h"
/* USER CODE BEGIN INCLUDE */
/* USER CODE END INCLUDE */
/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @{
  */

/** @defgroup USBD_CUSTOM_HID 
  * @brief usbd core module
  * @{
  */ 

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions
  * @{
  */ 
/* USER CODE BEGIN PRIVATE_TYPES  */
/* USER CODE END PRIVATE_TYPES */ 
/**
  * @}
  */ 

/** @defgroup USBD_CUSTOM_HID_Private_Defines
  * @{
  */ 
/* USER CODE BEGIN PRIVATE_DEFINES  */
/* USER CODE END PRIVATE_DEFINES */
  
/**
  * @}
  */ 

/** @defgroup USBD_CUSTOM_HID_Private_Macros
  * @{
  */ 
/* USER CODE BEGIN PRIVATE_MACRO  */
/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */ 

/** @defgroup USBD_AUDIO_IF_Private_Variables
 * @{
 */
 
 #if 0
 __ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
 {
				0x05, 0x8c, /* USAGE_PAGE (ST Page) */
        0x09, 0x01, /* USAGE (Demo Kit) */
        0xa1, 0x01, /* COLLECTION (Application) */
         
        // The Input report 
        0x09,0x03, // USAGE ID - Vendor defined 
        0x15,0x00, // LOGICAL_MINIMUM (0) 
        0x26,0x00, 0xFF, // LOGICAL_MAXIMUM (255) 
        0x75,0x08, // REPORT_SIZE (8bit) 
        0x95,0x40, // REPORT_COUNT (64Byte) 
        0x81,0x02, // INPUT (Data,Var,Abs) 
	 
				0xc0,
   
 };
 #endif
 #if 1
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
	0x06, 0xFF, 0x00,	   /* USAGE_PAGE (Vendor Page: 0xFF00) */						
	0x09, 0x01,			/* USAGE (Demo Kit) 			  */	
	0xa1, 0x01,			/* COLLECTION (Application) 	  */
	

	 
//	Add 2017.5.9 
	0x85,0x03,
	0x09,0x03,
  0x15,0x00,
	0x26,0xff, 0x00,
	0x75,0x08,
	0x95,0x3f,//63BYTE 0x3f
	0x81,0x06,//Input	 
//	Add 2017.5.9  
	 
	 

	 
	0x85,0x01,
	0x09,0x01,
  0x15,0x00,
	0x26,0xff, 0x00,
	0x75,0x08,
	0x95,0x3f,//63BYTE 0x3f
	0x81,0x06,//Input
	 
	0x09,0x01,// UID set feature
	0x85,0x10,
	0x95,0x03,
	0xb1,0x82,
	 
	0x09,0x01,
	0x85,0x02,
	0x95,0x01,
	0x91,0x06,//Output
	
	0x09,0x01,// 
	0x85,0x11,
	0x95,0x3f,
	0xb1,0x82,
	
	0x09,0x01,//SN feature
	0x85,0x03,
	0x95,0x11,
	0xb1,0x82,
    /* 54 */
    
    /* command host --> device */
    0x85, 0x06,            /*     REPORT_ID 6		        */
    0x09, 0x06,            /*     USAGE (command)	        */
    0x15, 0x00,            /*     LOGICAL_MINIMUM (0)        */            
    0x26, 0xff, 0x00,       /*     LOGICAL_MINIMUM (255)     */ 
    0x75, 0x08,            /*     REPORT_SIZE (8)            */        
    0x95, 0x08,            /*     REPORT_COUNT (1)           */       
    0xB1, 0x82,             /*    FEATURE (Data,Var,Abs,Vol) */     
  
    0x85, 0x06,            /*     REPORT_ID 6	              */
    0x09, 0x08,            /*     USAGE (command)           */
    0x91, 0x82,            /*     OUTPUT (Data,Var,Abs,Vol)  */
    /* 54 + 21*/
    
    /* ack device --> host */
    0x85, 0x07,            /*     REPORT_ID (7)              */         
    0x09, 0x07,            /*     USAGE (acd)             */          
    0x15, 0x00,            /*     LOGICAL_MINIMUM (0)        */               
    0x26, 0xff, 0x00,      /*     LOGICAL_MAXIMUM (255)      */                 
    0x75, 0x08,            /*     REPORT_SIZE (8)            */ 
    0x95, 0x08,            /*     REPORT_COUNT (1)           */        
    0x81, 0x82,            /*     INPUT (Data,Var,Abs,Vol)   */                    
    0x85, 0x07,            /*     REPORT_ID (7)              */                 
    0x09, 0x07,            /*     USAGE (ADC in)             */                     
    0xb1, 0x82,            /*     FEATURE (Data,Var,Abs,Vol) */ 
	/* 54 + 21 +21 */
	
	0xc0,
	 
  
};
#endif
/* USB handler declaration */
/* Handle for USB Full Speed IP */
  USBD_HandleTypeDef  *hUsbDevice_0;

/* USER CODE BEGIN PRIVATE_VARIABLES  */
/* USER CODE END  PRIVATE_VARIABLES */
/**
  * @}
  */ 
  
/** @defgroup USBD_CUSTOM_HID_IF_Exported_Variables
  * @{
  */ 
  extern USBD_HandleTypeDef hUsbDeviceFS;
/* USER CODE BEGIN EXPORTED_VARIABLES  */
/* USER CODE END  EXPORTED_VARIABLES */

/**
  * @}
  */ 
  
/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @{
  */
static int8_t CUSTOM_HID_Init_FS     (void);
static int8_t CUSTOM_HID_DeInit_FS   (void);
static int8_t CUSTOM_HID_OutEvent_FS (uint8_t *p_report_buf);
 

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS = 
{
  CUSTOM_HID_ReportDesc_FS,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS,
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  CUSTOM_HID_Init_FS
  *         Initializes the CUSTOM HID media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
  hUsbDevice_0 = &hUsbDeviceFS;
  /* USER CODE BEGIN 4 */ 
  return (0);
  /* USER CODE END 4 */ 
}

/**
  * @brief  CUSTOM_HID_DeInit_FS
  *         DeInitializes the CUSTOM HID media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */ 
  return (0);
  /* USER CODE END 5 */ 
}

/**
  * @brief  CUSTOM_HID_OutEvent_FS
  *         Manage the CUSTOM HID class events       
  * @param  event_idx: event index
  * @param  state: event state
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */


static int8_t CUSTOM_HID_OutEvent_FS  (uint8_t *p_report_buff)
{ 
  /* USER CODE BEGIN 6 */ 
	if(0x02 == p_report_buff[0])
	{
		
	}
	else if(0x03 == p_report_buff[0])
	{
	
	}
	else if(0x06 == p_report_buff[0])
	{
    }

  return (0);
  /* USER CODE END 6 */ 
}

/* USER CODE BEGIN 7 */ 
/**
  * @brief  USBD_CUSTOM_HID_SendReport_FS
  *         Send the report to the Host       
  * @param  report: the report to be sent
  * @param  len: the report length
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
/*  
static int8_t USBD_CUSTOM_HID_SendReport_FS ( uint8_t *report,uint16_t len)
{
  return USBD_CUSTOM_HID_SendReport(hUsbDevice_0, report, len); 
}
*/
/* USER CODE END 7 */ 

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */
/* USER CODE END  PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */ 

/**
  * @}
  */  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
