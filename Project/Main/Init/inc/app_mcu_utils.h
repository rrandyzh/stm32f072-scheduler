/* ****************Copyright (c) [2016 Pico]. All Rights Reserved.*************************
 *
 * File Name          : app_mcu_utils.h
 * Author             : 
 * Version            : $Revision:$
 * Date               : $Date:$
 * Description        : this file includes the source code for the module scheduler
 *                      
 * HISTORY:
 * Date               | Modification                    | Author
 * 08/06/2016         | Initial Revision                | Alex Zhang
 
 ****************************************************************************************/
 #ifndef __APP_MCU_UTILS_H__
 #define __APP_MCU_UTILS_H__
 
 #include <stdint.h>
 #include <stdbool.h>
 #define byte uint8_t
 
 typedef unsigned long ulong;
 typedef unsigned int  word;
 
 /* **************************************************************************************
                            Standard Macro
 **********************************************************************************************************/

/* **************************************************************************************
 * MACRO DEFINITION
 * **************************************************************************************
 * Name         : GET_ABS_DIF
 * Description  : Returns absolute difference
 * ************************************************************************************** */
 #define GET_ABS_DIF(value1 ,value2) ( (value1 > value2)?(value1-value2):(value2-value1) )

/* --------------------------------------------------------------------------------------
 * --------------------------------------------------------------------------------------
 *
 * BITS MANIPULATION
 *
 * --------------------------------------------------------------------------------------
 * -------------------------------------------------------------------------------------- */

/* **************************************************************************************
 * MACRO DEFINITION
 * **************************************************************************************
 * Name         : BITMASK
 * Description  : Returns a mask composed of a "1" set at the position <BitNum>.
 * ************************************************************************************** */
#define BITMASK(BitNum)   ( 1 << (BitNum) )

/* **************************************************************************************
 * MACRO DEFINITION
 * **************************************************************************************
 * Name         : SETBIT
 * Description  : Sets (= "1") the bit number <BitNum> from <Mask>.
 * ************************************************************************************** */
#define SETBIT(Mask, BitNum)          ( Mask |= BITMASK(BitNum) )

/* **************************************************************************************
 * MACRO DEFINITION
 * **************************************************************************************
 * Name         : CLEARBIT
 * Description  : Clears (= "0") the bit number <BitNum> from <Mask>.
 * ************************************************************************************** */
#define CLEARBIT(Mask, BitNum)        ( Mask &= (~BITMASK(BitNum)) )

/* **************************************************************************************
 * MACRO DEFINITION
 * **************************************************************************************
 * Name         : COMPLEMENTBIT
 * Description  : Complements the bit number <BitNum> from <Mask>.
 * ************************************************************************************** */
#define COMPLEMENTBIT(Mask, NumBit)   ( Mask ^= BITMASK(NumBit) )

/* **************************************************************************************
 * MACRO DEFINITION
 * **************************************************************************************
 * Name         : CHECKBIT
 * Description  : Determines whether the bit number <BitNum> from <Mask> is set or not.
 * ************************************************************************************** */
#define CHECKBIT(Mask, BitNum)        ( (Mask) & BITMASK(BitNum) )

/* **************************************************************************************
 * MACRO DEFINITION
 * **************************************************************************************
 * Name         : GETBIT
 * Description  : Returns the bit number <BitNum> from <Mask>.
 * ************************************************************************************** */
#define GETBIT(Mask, BitNum)          ( ((Mask) >> (BitNum)) & 1 )

/* **************************************************************************************
 * MACRO DEFINITION
 * **************************************************************************************
 * Name         : GETLSB_FROM_BYTE
 * Description  : Returns the <NbBits> less significant bits from <Mask>.
 * ************************************************************************************** */
#define GETLSB_FROM_BYTE(Mask, NbBit)    ( (Mask) & (0xFF >> (8 - (NbBit))) )

//#define TRUE      1
//#define FALSE     0

// For code size optimisation, use these global static bits instead of local dynamic flags
// List of all flags from the bit field (ATT: 8 * 8 max).

typedef enum
{
    BT_POWER_ON,
    POWER_ON_PSENSOR_FAR,						
    PSENSOR_BLE_CONNECTED,								
    PSENSOR_SLEEP_DETECT_START,								      
    PIAR_TIMEOUT_SLEEP,
    POWER_ON_FIRST,          
    LPC_SET_BT_POWER_OFF,                 
    LPC_SET_BT_POWER_ON,      
    LPC_SET_BT_POWER_ON_MFB_,									
    AUDIO_JACK_STATE_CHANGE,
    LPC_PSENSOR_NEAR_DETECT,
    REBOOT_FROM_BOOTLOADER,
    START_OTA_DISABLE_LPC,                     
    OTA_PRC_END_FLAG,
    FREE_14,
    FREE_15
}T_eBitField;

extern byte abtBitField[2];

void UTL_BitSet(byte);
void UTL_BitClear(byte);
byte UTL_BitIsOn(byte);

 #endif /* __APP_MCU_UTILS_H__*/

