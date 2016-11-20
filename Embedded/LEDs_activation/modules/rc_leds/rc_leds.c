/**
 * \file	rc_leds.c
 * \brief	RGB LEDs functions
 * \details	Implements the functions for RGB LEDs
 * \author	Cosmin Marcu
 * \date	Nov 03, 2015
 * \version 1.0.1
 */

/* Includes */
#include "rc_leds.h"

/* Include module headers */

/**
 * \ingroup  rc_leds
 * \defgroup leds_functions LEDs Functions
 *  Functions definitions for RGB LEDs
 *  @{
 */

/**
 * \brief	Initializes LEDs port and pins
 * \return 	none
 */
void rcleds_Init(void)
{
	/* RGB LEDs */
	rcgpio_SetDirection(RCLEDS_PORT, RCLEDS_RGB1_RED, E_RC_OUTPUT);
	rcgpio_SetDirection(RCLEDS_PORT, RCLEDS_RGB1_BLUE, E_RC_OUTPUT);
	rcgpio_SetDirection(RCLEDS_PORT, RCLEDS_RGB1_GREEN, E_RC_OUTPUT);
	rcgpio_SetDirection(RCLEDS_PORT, RCLEDS_RGB2_RED, E_RC_OUTPUT);
	rcgpio_SetDirection(RCLEDS_PORT, RCLEDS_RGB2_BLUE, E_RC_OUTPUT);
	rcgpio_SetDirection(RCLEDS_PORT, RCLEDS_RGB2_GREEN, E_RC_OUTPUT);
	rcgpio_SetPin(RCLEDS_PORT, RCLEDS_RGB1_RED);
	rcgpio_SetPin(RCLEDS_PORT, RCLEDS_RGB1_BLUE);
	rcgpio_SetPin(RCLEDS_PORT, RCLEDS_RGB1_GREEN);
	rcgpio_SetPin(RCLEDS_PORT, RCLEDS_RGB2_RED);
	rcgpio_SetPin(RCLEDS_PORT, RCLEDS_RGB2_BLUE);
	rcgpio_SetPin(RCLEDS_PORT, RCLEDS_RGB2_GREEN);
}
/*@} end of group leds_functions */

