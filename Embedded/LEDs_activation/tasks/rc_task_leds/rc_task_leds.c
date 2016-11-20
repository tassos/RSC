/**
 * \file	rc_task_leds.c
 * \brief	LEDs task
 * \details	Implements LEDs functions
 * \author	Cosmin Marcu
 * \date	Nov 02, 2015
 * \version 1.0.1
 */

/* System and general headers */
#include "rc_task_leds.h"

#include "rc_leds.h"
#include "rc_stdtypedefs.h"
#include "rc_board.h"
#include "rc_gpio.h"

/**
 * \ingroup  rc_task_leds
 * \defgroup Task_LEDs_functions LEDs task
 *  FreeRTOS task for LEDs
 *  @{
 */


PRIVATE_DATA T_E_RCLEDS_STATE re_rcleds_state;					//!< Current state of the LEDs task (private)

/**
* \brief 	RTOS LEDs task
* \details 	TBD.
*/
void rctask_LEDs(void *pvParameters)
{
	if (NULL == pvParameters) {};	//avoid compiler warning

	while(1)
	{
		//Check the current state of the task
		switch(re_rcleds_state)
		{
		case E_RCLEDS_STATE_NONE:
			rcgpio_ClearPin(RC_RGBLEDS_PORT, RC_RGBLED1_RED_PIN);
			rcgpio_ClearPin(RC_RGBLEDS_PORT, RC_RGBLED2_RED_PIN);
			re_rcleds_state = E_RCLEDS_STATE_LEDS_ON;
			vTaskDelay(1000);
			break;
		case E_RCLEDS_STATE_LEDS_ON:
			rcgpio_SetPin(RC_RGBLEDS_PORT, RC_RGBLED1_RED_PIN);
			rcgpio_SetPin(RC_RGBLEDS_PORT, RC_RGBLED2_RED_PIN);
			re_rcleds_state = E_RCLEDS_STATE_NONE;
			vTaskDelay(1000);
			break;
		default:
			re_rcleds_state = E_RCLEDS_STATE_NONE;
			vTaskDelay(1000);
			break;
		}
		vTaskDelay(100);
	}
}

/*@} end of group Task_LEDs_functions */
