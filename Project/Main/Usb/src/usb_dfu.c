/**
  ******************************************************************************
  * @file    usb_dfu.c
  * @author  alex.zhang
  * @version V1.0.0
  * @date    05-March-2016
  * @brief   This file provides usb dfu related functions.
  ******************************************************************************
 
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "usb_dfu.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DISABLE_DFU_DATA_TO_PROG      ((uint16_t)0xabcd)       /* 16-bits value to be programmed */
#define DISABLE_OPT0_READ             ((uint16_t)0x32cd)
#define DISABLE_OPT1_READ             ((uint16_t)0x54ab)

#define ENABLE_DFU_DATA_TO_PROG       ((uint16_t)0x1234)       /* 16-bits value to be programmed */
#define ENABLE_OPT0_READ              ((uint16_t)0xcb34)
#define ENABLE_OPT1_READ              ((uint16_t)0xed12)

/* Error codes used to make the orange led blinking */
#define ERROR_ERASE 0x01
#define ERROR_PROG  0x02
#define ERROR_PROG_FLAG 0x04
#define ERROR_WRITE_PROTECTION 0x08
#define ERROR_UNKNOWN 0x10
#define ERROR_NO    0x00

#define MAX_READ_WRITE_EEPROM_NUM  5

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint16_t error = 0; //initialized at 0 and modified by the functions 
uint32_t test_to_be_performed_twice = 1; //this variable is set to 2 if the option byte Data 0 is yet erased

/**
  * @brief  This function prepares the option byte to be erased or programmed.
  *         It first checks no flash operation is on going,
  *         then unlocks both the flash and the option byte if it is locked.
  *         The flash must be unlocked to unlock the option bytes.
  * @param  None
  * @retval None
  */
unsigned char OptionFlashOperationPreparation(void)
{  
  /* (1) Wait till no operation is on going */
  /* (2) Check that the Flash is unlocked */
  /* (3) Perform unlock sequence for Flash */
  /* (4) Check that the Option Bytes are unlocked */
  /* (5) Perform unlock sequence for Option Bytes */
	uint16_t nCnt; 
  while ((FLASH->SR & FLASH_SR_BSY) != 0) /* (1) */  
  {
    /* For robust implementation, add here time-out management */
		nCnt++;
		if (nCnt >= 2000)	
    {			
			return 1;
		}
  }  
  if ((FLASH->CR & FLASH_CR_LOCK) != 0) /* (2) */
  {    
    	HAL_FLASH_Unlock(); /* (3) */
  }
  if ((FLASH->CR & FLASH_CR_OPTWRE) == 0) /* (4) */
  {
    HAL_FLASH_OB_Unlock(); /* (5) */
  }
	return 0;
}

/**
  * @brief  This function erases all the option bytes.
  * @param  None
  * @retval None
  */
 unsigned char OptionErase(void)
{
  /* (1) Set the OPTER bit in the FLASH_CR register to enable option byte erasing */
  /* (2) Set the STRT bit in the FLASH_CR register to start the erasing */
  /* (3) Wait until the BSY bit is reset in the FLASH_SR register */
  /* (4) Check the EOP flag in the FLASH_SR register */
  /* (5) Clear EOP flag by software by writing EOP at 1 */
  /* (6) Reset the PER Bit to disable the page erase */
	uint16_t nCnt;
  FLASH->CR |= FLASH_CR_OPTER; /* (1) */
  FLASH->CR |= FLASH_CR_STRT; /* (2) */    
  while ((FLASH->SR & FLASH_SR_BSY) != 0) /* (3) */
  {
		nCnt++;
		if (nCnt >= 2000)	
    {			
			return 1;
		}
    /* For robust implementation, add here time-out management */
  }
  if ((FLASH->SR & FLASH_SR_EOP) != 0)  /* (4) */
  {
    FLASH->SR |= FLASH_SR_EOP; /* (5)*/
  }    
  /* Manage the error cases */
  else if ((FLASH->SR & FLASH_SR_WRPERR) != 0) /* Check Write protection error error */
  {
    error |= ERROR_WRITE_PROTECTION; /* Report error */
    FLASH->SR |= FLASH_SR_WRPERR;    /* Clear the flag */
		return 1;
  }
  else
  {
    error = ERROR_UNKNOWN; /* Report error */
		return 1;
  }
  FLASH->CR &= ~FLASH_CR_OPTER; /* (6) */
	return 0;
}


/**
  * @brief  This function programs an option byte.
  *         The Programming bit (OPTPG) is set at the beginning and reset at the end
  *         of the function, in case of successive programming, these two operations
  *         could be performed outside the function.
  *         This function waits the end of programming, clears the appropriate bit in 
  *         the Status register and eventually reports an error. 
  * @param  opt_addr is the address to be programmed
  *         data is the byte to program
  * @retval None
  */
 unsigned char OptionProg(volatile uint16_t* opt_addr, uint8_t data)
{    
  /* (1) Set the PG bit in the FLASH_CR register to enable programming */
  /* (2) Perform the data write */
  /* (3) Wait until the BSY bit is reset in the FLASH_SR register */
  /* (4) Check the EOP flag in the FLASH_SR register */
  /* (5) Clear the EOP flag by software by writing it at 1 */
  /* (6) Reset the PG Bit to disable programming */
	uint16_t nCnt = 0 ;
	uint16_t mCnt = 0 ;
  FLASH->CR |= FLASH_CR_OPTPG; /* (1) */
  *opt_addr = data; /* (2) */
  while ((FLASH->SR & FLASH_SR_BSY) != 0) /* (3) */
  {
    /* For robust implementation, add here time-out management */
		nCnt++;
		if (nCnt >= 2000)	
    {			
			return 1;
		}
  }  
  if ((FLASH->SR & FLASH_SR_EOP) != 0)  /* (4) */
  {
    FLASH->SR |= FLASH_SR_EOP; /* (5) */
  }
  /* Manage the error cases */
  else if ((FLASH->SR & FLASH_SR_PGERR) != 0) /* Check programming error */
  {
    error = ERROR_PROG_FLAG; /* Report programming error */
    FLASH->SR |= FLASH_SR_PGERR; /* Clear the flag */
		return 1;
  }
  else if ((FLASH->SR & FLASH_SR_WRPERR) != 0)
  {
    error = ERROR_WRITE_PROTECTION; /* Report Write protection error */
    FLASH->SR |= FLASH_SR_WRPERR; /* Clear the flag */
		return 1;
  }     
	while ((FLASH->SR & FLASH_SR_BSY) != 0) /* (3) */
  {
    /* For robust implementation, add here time-out management */
		mCnt++;
		if (mCnt >= 10000)	
    {			
			return 1;			
		}
  }  
  FLASH->CR &= ~FLASH_CR_OPTPG; /* (6) */
	return 0;
	
	
}

/**
  * @brief  Set/Clear the dfu flag to option bytes.
  * @param  DfuMode: DfuMode
  *          This parameter can be one of following parameters:
  *            @arg ENABLE_USB_DFU:
  *            @arg DISABLE_USB_DFU:   
  * @retval Success or failure.
  */
void WriteTheDfuDataToOptionByte(uint16_t DfuMode)
{
	  
    uint16_t ObData0, ObData1,DfuDataToProgrm;
    uint8_t nFault,nWriteCnt = 0;
	  DfuDataToProgrm = DfuMode;
   switch(DfuMode)
	 {
	   case JUMP_TO_APP:
		 {
		   ObData0 = 0x32cd;
			 ObData1 = 0x54ab;
		 }
		 break;
		 case JUMP_TO_DFU:
		 {
		   ObData0 = 0xcb34;
			 ObData1 = 0xed12;
		 }
	   break;
		 case JUMP_TO_EEUPDATE:
		 {
		   ObData0 = 0x8778;
			 ObData1 = 0xa956;
		 }
		 break;
		 default:
		 {
		   ObData0 = 0x32cd;
			 ObData1 = 0x54ab;
		 }
		 break;
	 }
    error = (uint8_t)ERROR_NO;
  do 
  {
    nFault = OptionFlashOperationPreparation();
	  if (nFault == 0)
		{
			if (OB->DATA0 == (uint16_t)0xFFFF)
			{
				test_to_be_performed_twice = 2;
			}
			while(test_to_be_performed_twice-- > 0)
			{
			  nFault = OptionErase();
				if (OB->DATA0 != (uint16_t)0xFFFF) // Check the erasing of user data option byte
        {
          error |= ERROR_ERASE;
					nFault = 1;
        }
        // Program the read protection /
        nFault = OptionProg(&(OB->RDP), (uint8_t)0xAA);
        // Program data 0 option byte /
        nFault = OptionProg(&(OB->DATA0), (uint8_t)DfuDataToProgrm);
        // Program data 0 option byte /    
        nFault = OptionProg(&(OB->DATA1), (uint8_t)(DfuDataToProgrm >> 8)); 
        // Check the programming of the address /
				
				if  ((OB->RDP != 0x55AA) ||(OB->DATA0 != ObData0) || (OB->DATA1 != ObData1)) 
        {
          error |= ERROR_PROG;
					nFault = 1;
				}	
			}	
      HAL_FLASH_OB_Lock();
		  HAL_FLASH_Lock();			
		}
		nWriteCnt++;
	}while(nFault && nWriteCnt < MAX_READ_WRITE_EEPROM_NUM);	
	/*
    if (OB->DATA0 == (uint16_t)0xFFFF) // Check if the option byte data 0 is yet erased, only for this example //
    {
        test_to_be_performed_twice = 2;
    }
    while (test_to_be_performed_twice-- > 0)
    {
        OptionErase();
        if (OB->DATA0 != (uint16_t)0xFFFF) // Check the erasing of user data option byte
        {
          error |= ERROR_ERASE;
        }
        // Program the read protection /
        OptionProg(&(OB->RDP), (uint8_t)0xAA);
        // Program data 0 option byte /
        OptionProg(&(OB->DATA0), (uint8_t)DfuDataToProgrm);
        // Program data 0 option byte /    
        OptionProg(&(OB->DATA1), (uint8_t)(DfuDataToProgrm >> 8)); 
        // Check the programming of the address /
				
				
        if  ((OB->RDP != 0x55AA) ||(OB->DATA0 != ObData0) || (OB->DATA1 != ObData1)) 
        {
          error |= ERROR_PROG;
				}	
        //FLASH->CR |= FLASH_CR_OBL_LAUNCH;
    }
	
	  HAL_FLASH_OB_Lock();
		HAL_FLASH_Lock();
		
    return error;
		*/
}

