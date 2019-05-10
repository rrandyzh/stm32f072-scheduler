/* ****************Copyright (c) [2016]. All Rights Reserved.*************************
 *
 * File Name          : app_mcu_utils.c
 * Author             :
 * Version            : $Revision:$
 * Date               : $Date:$
 * Description        : this file includes the source code for the module scheduler
 *
 * HISTORY:
 * Date               | Modification                    | Author
 * 08/06/2016         | Initial Revision                | Randy Zhang

 ****************************************************************************************/
 #include "app_mcu_utils.h"
 
 byte abtBitField[2];
 /* **************************************************************************************
 * Function    : Sets (= "1") the bit number <BitNum> from the bit field
 * Input data  : byte BitNum
 * Ouptut data : none
 * ************************************************************************************** */
void UTL_BitSet(byte BitNum)
{
    SETBIT(abtBitField[BitNum >> 3], BitNum%8);
}

/* **************************************************************************************
 * Function    : Clears (= "0") the bit number <BitNum> from the bit field
 * Input data  : byte BitNum
 * Ouptut data : none
 * ************************************************************************************** */
void UTL_BitClear(byte BitNum)
{
	CLEARBIT(abtBitField[BitNum >> 3], BitNum%8);
}

/* **************************************************************************************
 * Function    : Tests the bit number <BitNum> from the bit field
 * Input data  : byte BitNum
 * Ouptut data : byte
 * ************************************************************************************** */
byte UTL_BitIsOn(byte BitNum)
{
	return( CHECKBIT(abtBitField[BitNum>>3], BitNum%8) );
}
