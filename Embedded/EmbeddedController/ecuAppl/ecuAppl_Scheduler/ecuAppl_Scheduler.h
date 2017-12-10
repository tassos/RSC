/**
 * \file	ecuAppl_Scheduler.h
 * \brief	ecuAppl_Scheduler module header file
 * \details	Exports the functions used by the scheduler
 * \author	Cosmin Marcu
 * \date	Jun 23, 2015
 * \version 1.0.1
 */
#ifndef ECUAPPL_SCHEDULER_H_
#define ECUAPPL_SCHEDULER_H_

/** \defgroup ecuAppl_Scheduler Scheduler module
 *  \ingroup ecu_modules
 *  Functions to initialize scheduler
 */

/* Includes */
#include "ecuConfig_Types.h"
#include "ecuDrv_pinsel.h"
#include "ecuDrv_timer.h"

/* Defines */
#define		SCHEDULER_TIMER_PORT					LPC_TIM0		//!< Timer port
#define		SCHEDULER_PRESCALE_VALUE			   		 500		//!< Timer prescaler value (5 ms)
#define		SCHEDULER_MATCH0_VALUE					      10		//!< Match channel 0 value [ms]
#define		SCHEDULER_MATCH1_VALUE					     100		//!< Match channel 1 value [ms]
#define		SCHEDULER_COUNTER_10MS					       2		//!< Counter for 10 ms task
#define		SCHEDULER_COUNTER_50MS					      10		//!< Counter for 50 ms task
#define		SCHEDULER_COUNTER_100MS					      20		//!< Counter for 100 ms task

/* IRQ Handlers */
extern void ecuAppl_Scheduler_Timer0_IRQHandler(void);

/* Scheduler public functions group: */
extern void ecuAppl_Scheduler_Init(void);

#endif /* ECUAPPL_SCHEDULER_H_ */
