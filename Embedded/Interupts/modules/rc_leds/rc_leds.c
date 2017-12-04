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

PRIVATE_DATA VOLATILE T_E_RCLEDS_STATE re_rcleds_state;					//!< Current state of the LEDs task (private)

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

/**
 * \brief	Clear LEDs
 * \return 	none
 */
void rcleds_ClearLEDs(void)
{
	rcgpio_SetPin(RCLEDS_PORT, RCLEDS_RGB1_RED);
	rcgpio_SetPin(RCLEDS_PORT, RCLEDS_RGB1_BLUE);
	rcgpio_SetPin(RCLEDS_PORT, RCLEDS_RGB1_GREEN);
	rcgpio_SetPin(RCLEDS_PORT, RCLEDS_RGB2_RED);
	rcgpio_SetPin(RCLEDS_PORT, RCLEDS_RGB2_BLUE);
	rcgpio_SetPin(RCLEDS_PORT, RCLEDS_RGB2_GREEN);
}

/**
 * \brief	Gets the current LEDs state
 * \return 	LEDs state
 */
T_E_RCLEDS_STATE rcleds_GetState(void)
{
	return re_rcleds_state;
}

/**
 * \brief	Sets the current LEDs state
 * \param	le_State new state to be set
 * \return 	none
 */
void rcleds_SetState(T_E_RCLEDS_STATE le_State)
{
	re_rcleds_state = le_State;
}
/*@} end of group leds_functions */

