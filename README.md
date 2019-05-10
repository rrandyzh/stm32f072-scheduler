# stm32f072-scheduler
A task scheduler designed for ARM Cortex-Mx devices, it is very scalable, simple and easy to use.

## Task Scheduling
~~~c
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

/* ************************************************************************************
* Implementation of interface definitions.
***************************************************************************************/
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
~~~