/* ****************Copyright (c) [2016]. All Rights Reserved.*************************
 *
 * File Name          : app_scheduler.c
 * Author             : 
 * Version            : $Revision:$
 * Date               : $Date:$
 * Description        : this file includes the source code for the module scheduler
 *                      
 * HISTORY:
 * Date               | Modification                    | Author
 * 08/06/2016         | Initial Revision                | Randy Zhang
 
 ****************************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "sys_scheduler.h"
#include "system_init.h"
/* Variable definitions******************************************************* */
/* Target value of the tick counter */
volatile uint8_t SbtTickCounterTarg;

/* Current value of the tick counter : Init with 0 */
static uint8_t SbtTickCounterCurr_;

#define SIZE_SYS_InitPrivMode_   (sizeof(SYS_InitPrivMode_) / sizeof(T_pfVoidFuncVoid))

const T_pfVoidFuncVoid SYS_InitPrivMode_[] =
{
    /* 0. sysclock init & init all gpios to reduce power consumption */
    SystemClock_Config,
    
    /* 1. SPI,I2C,USB,AD,TIMER,GPIO,EXIT */
    General_GPIO_Init,
    
    TIM2_Init,
    
    /* 2. Touch,Motor,EM7180,Chirp,Tirgger,Battery */
    
    NULL,
};
extern void Task_Toggle_PIN_4(void);
extern void Task_Toggle_PIN_2(void);
extern void Task_Toggle_PIN_3(void);
extern void Task_Toggle_PIN_5(void);
extern void Task_Toggle_PIN_6(void);
extern void Task_Toggle_PIN_7(void);
extern void Task_Toggle_PIN_8(void);
extern void Task_Toggle_PIN_9(void);

const T_pfVoidFuncVoid SYS_TaskMode_12_5_ms_[] =
{
    // Button Touch
    Task_Toggle_PIN_2,
    NULL
};

const T_pfVoidFuncVoid SYS_TaskMode_25_ms_[] =
{
    // MMI,Motor
    Task_Toggle_PIN_3,
    Task_Toggle_PIN_4,
    NULL,
};

const T_pfVoidFuncVoid SYS_TaskMode_50_ms_[] =
{
    // Mode
    Task_Toggle_PIN_5,
    NULL
};

const T_pfVoidFuncVoid SYS_TaskMode_100_ms_[] =
{
    // AD
    Task_Toggle_PIN_6,
    NULL
};

const T_pfVoidFuncVoid SYS_TaskMode_200_ms_[] =
{
    // Charging
    Task_Toggle_PIN_7,
    NULL
};

const T_pfVoidFuncVoid SYS_TaskMode_400_ms_[] =
{
    Task_Toggle_PIN_8,
    NULL
};
const T_pfVoidFuncVoid SYS_TaskMode_800_ms_[] =
{
    Task_Toggle_PIN_9,
    NULL
};

const T_pfVoidFuncVoid SYS_TaskMode_1600_ms_[] =
{
    NULL
};

const T_pfVoidFuncVoid SYS_TaskMode_1600B_ms_[] =
{ 
	NULL
};


T_pfVoidFuncVoid const * const CapfTasksTable[] =
{ 
	SYS_TaskMode_12_5_ms_
  , SYS_TaskMode_25_ms_
  , SYS_TaskMode_50_ms_
  , SYS_TaskMode_100_ms_
  , SYS_TaskMode_200_ms_
  , SYS_TaskMode_400_ms_
  , SYS_TaskMode_800_ms_
  , SYS_TaskMode_1600_ms_
  , SYS_TaskMode_1600B_ms_
};


const uint8_t CabtTasksTableSize[] =
{ 
	sizeof(SYS_TaskMode_12_5_ms_)  / sizeof(T_pfVoidFuncVoid)
  , sizeof(SYS_TaskMode_25_ms_)    / sizeof(T_pfVoidFuncVoid)
  , sizeof(SYS_TaskMode_50_ms_)    / sizeof(T_pfVoidFuncVoid)
  , sizeof(SYS_TaskMode_100_ms_)   / sizeof(T_pfVoidFuncVoid)
  , sizeof(SYS_TaskMode_200_ms_)   / sizeof(T_pfVoidFuncVoid)
  , sizeof(SYS_TaskMode_400_ms_)   / sizeof(T_pfVoidFuncVoid)
  , sizeof(SYS_TaskMode_800_ms_)   / sizeof(T_pfVoidFuncVoid)
  , sizeof(SYS_TaskMode_1600_ms_)  / sizeof(T_pfVoidFuncVoid)
  , sizeof(SYS_TaskMode_1600B_ms_) / sizeof(T_pfVoidFuncVoid)
};

/* ***************************************************************************************
 *
 * Implementation of interface definitions.
 *
*****************************************************************************************/
void app_scheduler_init(void)
{
	/* Task pointer to be executed */
	T_pfVoidFuncVoid pfTaskFunc;
		
	/* Function number to be executed for the task */
	uint8_t btFuncNum;                 
	/* Private initialization of modules */
   
	for ( btFuncNum = 0; btFuncNum < SIZE_SYS_InitPrivMode_; btFuncNum ++)
	{
		pfTaskFunc = (SYS_InitPrivMode_[btFuncNum]);
				
		if ( pfTaskFunc != NULL )
		{
			pfTaskFunc();
		}
	}  
}

void app_scheduler_run(void)
{
	/* Task number to be executed */
	uint8_t btTaskNum = 0xFF;
	/* Function number to be executed for the task */
	uint8_t btFuncNum;                       
	/* Task pointer to be executed */	
	T_pfVoidFuncVoid pfTaskFunc;
		
	/* Infinite loop */
	for (;;)
	{
        while ( SbtTickCounterTarg == SbtTickCounterCurr_ )
        {
        }
        
        SbtTickCounterCurr_ ++;    // Current tick treatment
        btTaskNum = 0;             // Task number to be executed
        
        /* Choose the eligible cyclic task ; 
			the smallest task number stands for the highest task priority  */
        while ( CHECKBIT(SbtTickCounterCurr_, btTaskNum) != 0 )
        {
            btTaskNum++;
        }
	
        /* Call the selected cyclic task */
        for (btFuncNum = 0; btFuncNum < CabtTasksTableSize[btTaskNum]; btFuncNum++)
        {
            pfTaskFunc = CapfTasksTable[btTaskNum][btFuncNum];
            if ( pfTaskFunc != NULL )
            {
                pfTaskFunc();
            }
        }
    }
}  

/**
 * @}
 */
