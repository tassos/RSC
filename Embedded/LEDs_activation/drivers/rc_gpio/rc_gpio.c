/**
 * \file	rc_gpio.c
 * \brief	Implements the interface functions with the GPIO peripheral
 * \details	Implements the functions which communicate directly with the
 * 			GPIO peripheral.
 * \author	Cosmin Marcu
 * \date	29.05.2015
 * \version 1.0.1
 */

/* Includes */
#include "rc_gpio.h"

/* Begin functions implementation */

/** \defgroup rc_gpio GPIO driver
  Contains the functions to set and access GPIO peripheral
*/

/**
 * \ingroup  rc_gpio
 * \defgroup gpio_functions GPIO Functions
 *  Functions definitions for the GPIO setup
 *  @{
 */
/* GPIO Functions Group: */
/**
 * \brief 	Sets a GPIO pin state to HIGH.
 * \param 	lub_Port	GPIO port number
 * \param 	lub_Pin	GPIO pin number
 * \return 	none
 */
void rcgpio_SetPin(T_UBYTE lub_Port, T_UBYTE lub_Pin)
{
	GPIO_SetValue((T_ULONG)lub_Port,RCGPIO_PINMASK(lub_Pin));
}

/**
 * \brief 	Sets a GPIO pin state to LOW.
 * \param 	lub_Port GPIO port number
 * \param 	lub_Pin	GPIO pin number
 * \return	none
 */
void rcgpio_ClearPin(T_UBYTE lub_Port, T_UBYTE lub_Pin)
{
	GPIO_ClearValue((T_ULONG)lub_Port,RCGPIO_PINMASK(lub_Pin));
}

/**
 * \brief 	Reads a GPIO pin state.
 * \param 	lub_Port GPIO port number
 * \param 	lub_Pin	GPIO pin number
 * \return	pin state
 */
T_E_RC_SIGNAL_STATE rcgpio_ReadPin(T_UBYTE lub_Port, T_UBYTE lub_Pin)
{
	T_E_RC_SIGNAL_STATE le_PinState = E_RC_OFF;
	/* Read port value */
	T_ULONG lul_PortValue = GPIO_ReadValue(lub_Port);
	/* Check if pin is ON */
	if(lul_PortValue & (1<<lub_Pin))
	{
		le_PinState = E_RC_ON;
	}
	return le_PinState;
}

/**
 * \brief 	Swaps the current state of a GPIO pin.
 * 		  	If pin is OFF, swaps to ON.
 * 		  	IF pin is ON, swaps to OFF.
 * \param 	lub_Port GPIO port number
 * \param 	lub_Pin	GPIO pin number
 * \return 	none
 */
void rcgpio_SwapPin(T_UBYTE lub_Port, T_UBYTE lub_Pin)
{
	/* Read current pin state */
	T_E_RC_SIGNAL_STATE le_pinState = rcgpio_ReadPin(lub_Port, lub_Pin);
	/* Swap pin state */
	if (E_RC_OFF == le_pinState)
	{
		/* Set pin state to HIGH */
		rcgpio_SetPin(lub_Port, lub_Pin);
	}
	else
	{
		/* Set pin state to LOW */
		rcgpio_ClearPin(lub_Port, lub_Pin);
	}
}

/**
 * \brief 	Sets the direction of a GPIO pin.
 * \param 	lub_Port GPIO port number
 * \param 	lub_Pin  GPIO pin number
 * \param 	le_Direction GPIO pin direction (E_RI_INPUT or E_RI_OUTPUT)
 * \return	none
 */
void rcgpio_SetDirection(T_UBYTE lub_Port, T_UBYTE lub_Pin, T_E_RC_SIGNAL_DIRECTION le_Direction)
{
	GPIO_SetDir(lub_Port, RCGPIO_PINMASK(lub_Pin), (T_UBYTE)le_Direction);
}

/**
 * \brief 	Enable interrupt on a GPIO pin.
 * \param 	lub_Port 	GPIO port number
 * \param 	lub_Pin	 	GPIO pin number
 * \param 	le_Edge 	Interrupt edge sense mode:
 * 					  	0 - Raising Edge
 * 					  	1 - Falling Edge
 * \return	none
 */
void rcgpio_EnableInterrupt(T_UBYTE lub_Port, T_UBYTE lub_Pin, T_E_RCGPIO_IRQEDGE le_Edge)
{
	GPIO_IntCmd(lub_Port, RCGPIO_PINMASK(lub_Pin), (T_UBYTE)le_Edge);
}

/**
 * \brief 	Clears a pending interrupt on a GPIO pin.
 * \param 	lub_Port GPIO port number
 * \param 	lub_Pin	 GPIO pin number
 * \return 	none
 */
void rcgpio_ClearInterrupt(T_UBYTE lub_Port, T_UBYTE lub_Pin)
{
	GPIO_ClearInt(lub_Port, RCGPIO_PINMASK(lub_Pin));
}

/**
 * \brief 	Gets the interrupt status on a GPIO pin.
 * \param 	lub_Port GPIO port number
 * \param 	lub_Pin	 GPIO pin number
 * \param	le_Edge	 Raising or Falling edge check
 * \return 	interrupt status on the lub_Pin
 */
T_E_RC_BOOL rcgpio_GetInterruptStatus(T_UBYTE lub_Port, T_UBYTE lub_Pin, T_E_RCGPIO_IRQEDGE le_Edge)
{
	return (T_E_RC_BOOL)GPIO_GetIntStatus(lub_Port, lub_Pin, (T_UBYTE)le_Edge);
}
/*@} end of group GPIO_functions */
