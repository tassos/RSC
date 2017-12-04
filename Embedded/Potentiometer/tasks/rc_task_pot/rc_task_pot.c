/**
 * \file	rc_task_pot.c
 * \brief	Potentiometer task
 * \details	Implements potentiometer task functions
 * \author	Cosmin Marcu
 * \date	Nov 08, 2015
 * \version 1.0.1
 */

/* System and general headers */
#include "rc_task_pot.h"

#include "rc_pot.h"
#include "rc_leds.h"
#include "rc_stdtypedefs.h"
#include "rc_board.h"
#include "rc_gpio.h"

/**
 * \ingroup  rc_task_pot
 * \defgroup Task_pot_functions Potentiometer task
 *  FreeRTOS task for Potentiometer reading
 *  @{
 */

/**
* \brief 	RTOS Potentiometer task
* \details 	TBD.
*/
void rctask_pot(void *pvParameters)
{
	T_UWORD	luw_DigitalVoltage = 0u;
	if (NULL == pvParameters) {};	//avoid compiler warning

	while(1)
	{
		//Read current Potentiometer (digital) value
		rcpot_StartReading();
		vTaskDelay(50);
		if (E_RC_DONE == rcpot_GetReadingStatus())
		{
			luw_DigitalVoltage = rcpot_GetVoltageDigital();
		}

		/* NOTE: luw_DigitalVoltage contains the digital value */
		/* TODO: Add as state for each interval to avoid setting continuous the LEDs state */
		if ((luw_DigitalVoltage >= 0u) && (luw_DigitalVoltage < 500u))
		{
			rcleds_SetState(E_RCLEDS_STATE_RED1);
		}
		if ((luw_DigitalVoltage >= 3500u) && (luw_DigitalVoltage < 4096u))
		{
			rcleds_SetState(E_RCLEDS_STATE_BLUE2);
		}
		vTaskDelay(50);
	}
}

/*@} end of group Task_pot_functions */
