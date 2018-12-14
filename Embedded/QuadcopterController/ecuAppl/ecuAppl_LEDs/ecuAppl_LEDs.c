/**
 * \file	ecuAppl_LEDs.c
 * \brief	RGB LEDs functions
 * \details	Implements the functions for RGB LEDs
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

/* Includes */
#include "ecuAppl_LEDs.h"
#include "ecuDrv_gpio.h"

/* Include module headers */

PRIVATE_DATA T_UBYTE rub_Counter = 0u;

/**
 * \ingroup  ecuAppl_LEDs
 * \defgroup leds_functions LEDs Functions
 *  Functions definitions for RGB LEDs
 *  @{
 */
/**
 * \brief	Initializes LEDs port and pins
 * \return 	none
 */
void ecuAppl_LEDs_Init(void)
{
	/* RGB LEDs */
	ecuDrv_gpio_SetDirection(LEDS_PORT, LEDS_RGB1_RED, E_OUTPUT);
	ecuDrv_gpio_SetDirection(LEDS_PORT, LEDS_RGB1_BLUE, E_OUTPUT);
	ecuDrv_gpio_SetDirection(LEDS_PORT, LEDS_RGB1_GREEN, E_OUTPUT);
	ecuDrv_gpio_SetDirection(LEDS_PORT, LEDS_RGB2_RED, E_OUTPUT);
	ecuDrv_gpio_SetDirection(LEDS_PORT, LEDS_RGB2_BLUE, E_OUTPUT);
	ecuDrv_gpio_SetDirection(LEDS_PORT, LEDS_RGB2_GREEN, E_OUTPUT);
	ecuDrv_gpio_SetPin(LEDS_PORT, LEDS_RGB1_RED);
	ecuDrv_gpio_SetPin(LEDS_PORT, LEDS_RGB1_BLUE);
	ecuDrv_gpio_SetPin(LEDS_PORT, LEDS_RGB1_GREEN);
	ecuDrv_gpio_SetPin(LEDS_PORT, LEDS_RGB2_RED);
	ecuDrv_gpio_SetPin(LEDS_PORT, LEDS_RGB2_BLUE);
	ecuDrv_gpio_SetPin(LEDS_PORT, LEDS_RGB2_GREEN);

	ecuDrv_gpio_SetDirection(E_IOPORT2, E_IOPIN6, E_OUTPUT);
	ecuDrv_gpio_SetPin(E_IOPORT2, E_IOPIN6);
	ecuDrv_gpio_SetDirection(E_IOPORT2, E_IOPIN7, E_OUTPUT);
	ecuDrv_gpio_SetPin(E_IOPORT2, E_IOPIN7);
}
/**@} end of group leds_functions */

/**
 * \ingroup  ecu_tasks
 * \defgroup leds_tasks LEDs Tasks
 *  Tasks definitions for RGB LEDs
 *  @{
 */
/**
 * \brief	LEDs periodical 10m task
 * \return 	none
 */
void ecuAppl_LEDs_Task_10ms(void)
{
	if(rub_Counter<100u)
	{
		ecuDrv_gpio_ClearPin(LEDS_PORT, LEDS_RGB1_RED);		//Turn on RED LED
		ecuDrv_gpio_ClearPin(E_IOPORT2, E_IOPIN6);			//Turn on Relay 1
		ecuDrv_gpio_SetPin(E_IOPORT2, E_IOPIN7);			//Turn off Relay 2
		rub_Counter++;
	}
	else if(rub_Counter<199u)
	{
		ecuDrv_gpio_SetPin(LEDS_PORT, LEDS_RGB1_RED);		//Turn off RED LED
		ecuDrv_gpio_SetPin(E_IOPORT2, E_IOPIN6);			//Turn off Relay 1
		ecuDrv_gpio_ClearPin(E_IOPORT2, E_IOPIN7);			//Turn on Relay 2
		rub_Counter++;
	}
	else
	{
		rub_Counter = 0u;
	}
	//TODO: add periodic callbacks
}
/**@} end of group leds_tasks */

