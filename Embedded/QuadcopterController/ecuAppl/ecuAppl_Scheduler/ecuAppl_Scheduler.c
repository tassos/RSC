/**
 * \file	ecuAppl_Scheduler.c
 * \brief	Virtual timer functions
 * \details	Implements the functions for periodical actions
 * \author	Cosmin Marcu
 * \date	Jun 23, 2015
 * \version 1.0.1
 */

/* Includes */
#include "ecuAppl_Keyboard.h"
#include "ecuAppl_LEDs.h"
#include "ecuAppl_Scheduler.h"

#include "ecuAppl_GPS.h"
#include "ecuDrv_pinsel.h"
#include "ecuDrv_timer.h"

/**
 * \ingroup  ecuAppl_Scheduler
 * \defgroup scheduler_variables Scheduler Variables
 *  Includes the definition of scheduler module variables
 *  @{
 */
/* Private variables */
PRIVATE_DATA VOLATILE T_UBYTE rub_ecuAppl_Scheduler_Counter_10ms = SCHEDULER_COUNTER_10MS;		//!< Timer counter for 10 ms task
PRIVATE_DATA VOLATILE T_UBYTE rub_ecuAppl_Scheduler_Counter_50ms = SCHEDULER_COUNTER_50MS;		//!< Timer counter for 50 ms task
PRIVATE_DATA VOLATILE T_UBYTE rub_ecuAppl_SchedulerCounter_100ms = SCHEDULER_COUNTER_100MS;		//!< Timer counter for 100 ms task
/**@} end of group scheduler_functions */

/**
 * \ingroup  ecuAppl_Scheduler
 * \defgroup scheduler_functions Scheduler Functions
 *  Functions definitions for periodical actions
 *  @{
 */
/* Private functions */
PRIVATE_FCT void ecuAppl_Scheduler_Task_5ms(void);
PRIVATE_FCT void ecuAppl_Scheduler_Task_10ms(void);
PRIVATE_FCT void ecuAppl_Scheduler_Task_50ms(void);
PRIVATE_FCT void ecuAppl_Scheduler_Task_100ms(void);

/* IRQ Handers */
/**
* @brief 	Timer0 interrupt handler
* @details 	Handles the Timer0 IRQ every 5 [ms] and updates 10, 50 and 100 [ms] counters.
*/
void ecuAppl_Scheduler_Timer0_IRQHandler(void)
{
	if (E_ON == ecuDrv_timer_GetTimerInterruptStatus(SCHEDULER_TIMER_PORT, E_TMR_IRQ_MR0))
	{
		/* Call 10ms task */
		ecuAppl_Scheduler_Task_5ms();

		/* Check 10ms timer timeout */
		if(rub_ecuAppl_Scheduler_Counter_10ms > 0u)
		{
			/* Decrement counter */
			rub_ecuAppl_Scheduler_Counter_10ms--;
		}
		else
		{
			/* Reload counter */
			rub_ecuAppl_Scheduler_Counter_10ms = SCHEDULER_COUNTER_10MS-1u;
			/* Call 10ms task */
			ecuAppl_Scheduler_Task_10ms();
		}

		/* Check 50ms timer timeout */
		if(rub_ecuAppl_Scheduler_Counter_50ms > 0u)
		{
			/* Decrement counter */
			rub_ecuAppl_Scheduler_Counter_50ms--;
		}
		else
		{
			/* Reload counter */
			rub_ecuAppl_Scheduler_Counter_50ms = SCHEDULER_COUNTER_50MS-1u;
			/* Call 50ms task */
			ecuAppl_Scheduler_Task_50ms();
		}

		/* Check 100ms timer timeout */
		if(rub_ecuAppl_SchedulerCounter_100ms > 0u)
		{
			/* Decrement counter */
			rub_ecuAppl_SchedulerCounter_100ms--;
		}
		else
		{
			/* Reload counter */
			rub_ecuAppl_SchedulerCounter_100ms = SCHEDULER_COUNTER_100MS-1u;
			/* Call 100ms task */
			ecuAppl_Scheduler_Task_100ms();
		}
		/* Clear IRQ and reset Timer0 counter */
		ecuDrv_timer_ClearTimerInterrupt(SCHEDULER_TIMER_PORT, E_TMR_IRQ_MR0);
		ecuDrv_timer_ResetCounter(SCHEDULER_TIMER_PORT);
	}
}

/* Private functions implementation */
/**
 * @brief	Application scheduler 5ms Task
 * @return 	none
 */
PRIVATE_FCT void ecuAppl_Scheduler_Task_5ms(void)
{
	//TODO: Add a list of callback functions
}

/* Private functions implementation */
/**
 * @brief	Application scheduler 10ms Task
 * @return 	none
 */
PRIVATE_FCT void ecuAppl_Scheduler_Task_10ms(void)
{
	//TODO: Add a list of callback functions

	/* LEDs 10ms task */
	ecuAppl_LEDs_Task_10ms();
	/* Keyboard 10ms task */
	ecuAppl_Keyboard_Task_10ms();
	/* WiFi 10ms task */
	ecuAppl_GPS_Task_10ms();
}

/**
 * \brief	50ms Task
 * \return 	none
 */
PRIVATE_FCT void ecuAppl_Scheduler_Task_50ms(void)
{
	//TODO: Add a list of callback functions
}

/**
 * \brief	100ms Task
 * \return 	none
 */
PRIVATE_FCT void ecuAppl_Scheduler_Task_100ms(void)
{
	//TODO: Add a list of callback functions
}

/**
 * \brief	Initializes scheduler/timers
 * \return 	none
 */
void ecuAppl_Scheduler_Init(void)
{
	T_S_PINSEL_CFG ls_PinselConfig;					//!< Timer pins configuration structure
	T_S_TMR_TIMER_CONFIG ls_TimerConfig;			//!< Timer attributes configuration structure
	T_S_TMR_MATCH_CONFIG ls_MatchConfig;			//!< Timer match configuration structure

	/* Configure Timer Port pins */
	ls_PinselConfig.e_Port = E_IOPORT1;
	ls_PinselConfig.e_Function = E_PINSEL_FUNC3;
	ls_PinselConfig.e_Pin = E_IOPIN28;
	ls_PinselConfig.e_Mode = E_PINSEL_MODE_PULLUP;
	ls_PinselConfig.e_Drain = E_PINSEL_DRAIN_NORMAL;
	/* Configure pin 1.28 */
	ecuDrv_pinsel_ConfigPin(ls_PinselConfig);

	/* Initialize timer configuration structure */
	ls_TimerConfig.ub_PrescaleOption = E_TMR_PRESCALE_USVAL;
	ls_TimerConfig.ul_PrescaleValue = SCHEDULER_PRESCALE_VALUE;

	/* Initialize match configuration structure MATCH0 */
	ls_MatchConfig.e_MatchChannel = E_TMR_MATCH0;
	ls_MatchConfig.e_IRQOnMatch = E_ENABLE;
	ls_MatchConfig.e_ResetOnMatch = E_ENABLE;
	ls_MatchConfig.e_StopOnMatch = E_DISABLE;
	ls_MatchConfig.e_ExtMatch = E_TMR_EXTMATCH_NONE;
	ls_MatchConfig.ul_MatchValue = SCHEDULER_MATCH0_VALUE;
	/* Configure timer match */
	ecuDrv_timer_ConfigMatch(SCHEDULER_TIMER_PORT, ls_MatchConfig);

	/* Initialize Timer */
	ecuDrv_timer_Init(SCHEDULER_TIMER_PORT, E_TMR_MODE_TIMER, &ls_TimerConfig);

	/* Set IRQ priority */
	NVIC_SetPriority(TIMER0_IRQn, ((0x01<<3)|0x02));
	/* Enable Timer 0 port interrupt */
	ECU_ENABLE_IRQ(TIMER0_IRQn);
	ecuDrv_timer_SetTimerState(SCHEDULER_TIMER_PORT, E_ENABLE);
}
/**@} end of group scheduler_functions */

