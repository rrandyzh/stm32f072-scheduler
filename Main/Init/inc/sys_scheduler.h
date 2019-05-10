/* **************************************************************************************
 * All Rights Reserved
 * Invensys Appliance Controls SA - Thyez, France
 * **************************************************************************************
 * Name :
 *    SYS_Scheduler_pub.h
 *
 * Description :
 *    This module provide a cyclic task scheduler.
 *
 *    Assumptions :
 *    - the more prioritary the task is, the higher its frequency is.
 *    - from one priority to the other, the frequency ratio is 2.
 *    - the highest task frequency is defined by half of the scheduler frequency
 *    - the scheduler implement a task overflow control, thus each task must not last 
 *      more than 'SYS_SCHEDULER_RESOLUTION_IN_uS' us.
 *    - the number of concurrent cyclic tasks is defined by SYS_SCHEDULER_TASKS_MAX_NB.
 *
 *    Limitations :
 *    - SYS_SCHEDULER_TASKS_MAX_NB must be <= 8 because the counter used to recover the task
 *      frequency is coded on 8 bits.
 *
 *    Specific parts definitions :
 *    - SYS_SCHEDULER_RESOLUTION_IN_uS
 *    - SYS_SCHEDULER_TASKS_MAX_NB
 *
 * Debug : DEBUG_SCHEDULER enables traces to be printed on stdout terminal.
 *
 * Autor :
 *    FP
 *
 * Date :
 *    Wed 19/09/01 13:36:53
 *
 * ************************************************************************************** */

#ifndef __SYS_SCHEDULER_H
#define __SYS_SCHEDULER_H

#include "stdint.h"
#include "stddef.h"

/* **************************************************************************************
 * TYPE DEFINITION
 * **************************************************************************************
 * Name         : T_pfVoidFuncVoid
 * Description  : Generic function pointer type, no return value, no parameters.
 * ************************************************************************************** */
typedef void (* T_pfVoidFuncVoid)(void);

/* **************************************************************************************
 * TYPE DEFINITION
 * **************************************************************************************
 * Name         : T_pfByteFuncByte
 * Description  : Generic function pointer type, return value is byte, 1 byte parameter.
 * ************************************************************************************** */
typedef uint8_t (* T_pfByteFuncByte)(uint8_t);

/* **************************************************************************************
 * TYPE DEFINITION
 * **************************************************************************************
 * Name         : T_pfByteFuncWord
 * Description  : Generic function pointer type, return value is byte, 1 word parameter.
 * ************************************************************************************** */
typedef uint8_t (* T_pfByteFuncWord)(unsigned int);

/* **************************************************************************************
 * TYPE DEFINITION
 * **************************************************************************************
 * Name         : T_pfNByteFuncNByte
 * Description  : Generic function pointer type, return value is nbyte, 1 byte parameter.
 * ************************************************************************************** */
typedef signed char (* T_pfNByteFuncByte)(uint8_t);

/* **************************************************************************************
 * TYPE DEFINITION
 * **************************************************************************************
 * Name         : T_pfByteFuncVoid
 * Description  : Generic function pointer type, return value is byte, no parameter.
 * ************************************************************************************** */
typedef uint8_t (* T_pfByteFuncVoid)(void);

/* **************************************************************************************
 * TYPE DEFINITION
 * **************************************************************************************
 * Name         : T_pfVoidFuncByte
 * Description  : Generic function pointer type, return value is void, 1 byte parameter.
 * ************************************************************************************** */
typedef void (* T_pfVoidFuncNByte)(signed char);
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
 * Name         : CHECKBIT
 * Description  : Determines whether the bit number <BitNum> from <Mask> is set or not.
 * ************************************************************************************** */
#define CHECKBIT(Mask, BitNum)        ( (Mask) & BITMASK(BitNum) )

extern volatile uint8_t SbtTickCounterTarg;

void app_scheduler_init(void);
void app_scheduler_run(void);
void app_scheduler_launchTick(void);

#endif
