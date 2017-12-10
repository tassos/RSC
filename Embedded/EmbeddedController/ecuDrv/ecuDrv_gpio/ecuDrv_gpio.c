/**
 * \file	ecuDrv_gpio.c
 * \brief	Implements the interface functions with the GPIO peripheral
 * \details	Implements the functions which communicate directly with the
 * 			GPIO peripheral.
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

/* Includes */
#include "ecuDrv_gpio.h"

/* Begin functions implementation */

/** \defgroup ecuDrv_gpio GPIO driver
 *  \ingroup ecu_drivers
 *   Contains the functions to set and access GPIO peripheral
 */

/**
 * \ingroup  ecuDrv_gpio
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
void ecuDrv_gpio_SetPin(T_UBYTE lub_Port, T_UBYTE lub_Pin)
{
	GPIO_SetValue((T_ULONG)lub_Port, GPIO_PINMASK(lub_Pin));
}

/**
 * \brief 	Sets a GPIO pin state to LOW.
 * \param 	lub_Port GPIO port number
 * \param 	lub_Pin	GPIO pin number
 * \return	none
 */
void ecuDrv_gpio_ClearPin(T_UBYTE lub_Port, T_UBYTE lub_Pin)
{
	GPIO_ClearValue((T_ULONG)lub_Port, GPIO_PINMASK(lub_Pin));
}

/**
 * \brief 	Reads a GPIO pin state.
 * \param 	lub_Port GPIO port number
 * \param 	lub_Pin	GPIO pin number
 * \return	pin state
 */
T_E_SIGNAL_STATE ecuDrv_gpio_ReadPin(T_UBYTE lub_Port, T_UBYTE lub_Pin)
{
	T_E_SIGNAL_STATE le_PinState = E_OFF;
	/* Read port value */
	T_ULONG lul_PortValue = GPIO_ReadValue(lub_Port);
	/* Check if pin is ON */
	if(lul_PortValue & (1<<lub_Pin))
	{
		le_PinState = E_ON;
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
void ecuDrv_gpio_SwapPin(T_UBYTE lub_Port, T_UBYTE lub_Pin)
{
	/* Read current pin state */
	T_E_SIGNAL_STATE le_pinState = ecuDrv_gpio_ReadPin(lub_Port, lub_Pin);
	/* Swap pin state */
	if (E_OFF == le_pinState)
	{
		/* Set pin state to HIGH */
		ecuDrv_gpio_SetPin(lub_Port, lub_Pin);
	}
	else
	{
		/* Set pin state to LOW */
		ecuDrv_gpio_SetPin(lub_Port, lub_Pin);
	}
}

/**
 * \brief 	Sets the direction of a GPIO pin.
 * \param 	lub_Port GPIO port number
 * \param 	lub_Pin  GPIO pin number
 * \param 	le_Direction GPIO pin direction (E_INPUT or E_OUTPUT)
 * \return	none
 */
void ecuDrv_gpio_SetDirection(T_UBYTE lub_Port, T_UBYTE lub_Pin, T_E_SIGNAL_DIRECTION le_Direction)
{
	GPIO_SetDir(lub_Port, GPIO_PINMASK(lub_Pin), (T_UBYTE)le_Direction);
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
void ecuDrv_gpio_EnableInterrupt(T_UBYTE lub_Port, T_UBYTE lub_Pin, T_E_GPIO_IRQEDGE le_Edge)
{
	GPIO_IntCmd(lub_Port, GPIO_PINMASK(lub_Pin), (T_UBYTE)le_Edge);
}

/**
 * \brief 	Clears a pending interrupt on a GPIO pin.
 * \param 	lub_Port GPIO port number
 * \param 	lub_Pin	 GPIO pin number
 * \return 	none
 */
void ecuDrv_gpio_ClearInterrupt(T_UBYTE lub_Port, T_UBYTE lub_Pin)
{
	GPIO_ClearInt(lub_Port, GPIO_PINMASK(lub_Pin));
}

/**
 * \brief 	Gets the interrupt status on a GPIO pin.
 * \param 	lub_Port GPIO port number
 * \param 	lub_Pin	 GPIO pin number
 * \param	le_Edge	 Raising or Falling edge check
 * \return 	interrupt status on the lub_Pin
 */
T_E_BOOL ecuDrv_gpio_GetInterruptStatus(T_UBYTE lub_Port, T_UBYTE lub_Pin, T_E_GPIO_IRQEDGE le_Edge)
{
	return (T_E_BOOL)GPIO_GetIntStatus(lub_Port, lub_Pin, (T_UBYTE)le_Edge);
}
/**@} end of group gpio_functions */
