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

#include "../../modules/rc_leds/rc_leds.h"
#include "rc_stdtypedefs.h"
#include "rc_board.h"
#include "rc_gpio.h"

/**
 * \ingroup  rc_task_leds
 * \defgroup Task_LEDs_functions LEDs task
 *  FreeRTOS task for LEDs
 *  @{
 */

/**
* \brief 	RTOS LEDs task
* \details 	TBD.
*/
void rctask_LEDs(void *pvParameters)
{
	T_E_RCLEDS_STATE le_LedsState = E_RCLEDS_STATE_NONE;

	if (NULL == pvParameters) {};	//avoid compiler warning

	while(1)
	{
		//Read current LEDs state
		le_LedsState = rcleds_GetState();

		//Check the current state of the task
		switch(le_LedsState)
		{
		case E_RCLEDS_STATE_RED:
			//Turn off all LEDS
			rcleds_ClearLEDs();
			//Turn on RED LEDs
			rcgpio_ClearPin(RC_RGBLEDS_PORT, RC_RGBLED1_RED_PIN);
			rcgpio_ClearPin(RC_RGBLEDS_PORT, RC_RGBLED2_RED_PIN);
			//Switch to State None
			rcleds_SetState(E_RCLEDS_STATE_NONE);
			break;
		case E_RCLEDS_STATE_BLUE:
			//Turn off all LEDS
			rcleds_ClearLEDs();
			//Turn on BLUE LEDs
			rcgpio_ClearPin(RC_RGBLEDS_PORT, RC_RGBLED1_BLUE_PIN);
			rcgpio_ClearPin(RC_RGBLEDS_PORT, RC_RGBLED2_BLUE_PIN);
			//Switch to State None
			rcleds_SetState(E_RCLEDS_STATE_NONE);
			break;
		default:
			//Do nothing
			break;
		}
		vTaskDelay(100);
	}
}

/*@} end of group Task_LEDs_functions */
