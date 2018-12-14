/**
 * \file	ecuAppl_Keyboard.c
 * \brief	Keyboard functions
 * \details	Implements the functions for capacitive Keyboard
 * \author	Cosmin Marcu
 * \date	Sep 27, 2016
 * \version 1.0.1
 */

/* Includes */
#include "ecuAppl_Keyboard.h"
#include "ecuConfig_Types.h"
#include "ecuDrv_gpio.h"
#include "ecuDrv_i2c.h"

/**
 * \ingroup  ecuAppl_Keyboard
 * \defgroup keyboard_functions Keyboard Functions
 *  Functions definitions for capacitive Keyboard
 *  @{
 */
/**
 * \brief	Initializes Keyboard port and pins
 * \return 	none
 */
void ecuAppl_Keyboard_Init(void)
{
	//TODO: add initialization
}
/**@} end of group keyboard_functions */

/**
 * \ingroup  ecu_tasks
 * \defgroup keyboard_tasks Keyboard Tasks
 *  Tasks definitions for capacitive Keyboard
 *  @{
 */
/**
 * \brief	Periodic 10ms task
 * \return 	none
 * \see		ecuAppl_Scheduler_Task_10ms
 */
void ecuAppl_Keyboard_Task_10ms(void)
{
	//TODO: add periodic callbacks
}
/**@} end of group keyboard_tasks */

