/**
 * \file	rc_gpio.h
 * \brief	rc_gpio driver header file
 * \details	Exports the functions used GPIO communication with the core drivers.
 * \author	Cosmin Marcu
 * \date	29.05.2015
 * \version 1.0.1
 */

#ifndef RC_GPIO_H_
#define RC_GPIO_H_

/* Includes */
#include "rc_stdtypedefs.h"
#include "lpc17xx_gpio.h"

/**
 * \brief	Defines possible states of the ri_gpio module
 * \see		To be done...
 */
typedef enum E_RCGPIO_STATE {
	E_RCGPIO_STATE_NONE = 0u,				//!< E_RCGPIO_STATE_NONE
} T_E_RCGPIO_STATE;

#define RCGPIO_PINMASK(x)	(1<<(x))		//!< Mask pin number

/**
 * \brief	Defines GPIO interrupt edge sense register values
 */
typedef enum E_RCGPIO_IRQEDGE {
	E_RCGPIO_RISING,						//!< GPIO Rising edge
	E_RCGPIO_FALLING						//!< GPIO Falling edge
} T_E_RCGPIO_IRQEDGE;

/* GPIO exported functions group: */
extern void rcgpio_SetPin(T_UBYTE lub_Port, T_UBYTE lub_Pin);
extern void rcgpio_ClearPin(T_UBYTE lub_Port, T_UBYTE lub_Pin);
extern T_E_RC_SIGNAL_STATE rcgpio_ReadPin(T_UBYTE lub_Port, T_UBYTE lub_Pin);
extern void rcgpio_SwapPin(T_UBYTE lub_Port, T_UBYTE lub_Pin);
extern void rcgpio_SetDirection(T_UBYTE lub_Port, T_UBYTE lub_Pin, T_E_RC_SIGNAL_DIRECTION le_Direction);
extern void rcgpio_EnableInterrupt(T_UBYTE lub_Port, T_UBYTE lub_Pin, T_E_RCGPIO_IRQEDGE le_Edge);
extern void rcgpio_ClearInterrupt(T_UBYTE lub_Port, T_UBYTE lub_Pin);
extern T_E_RC_BOOL rcgpio_GetInterruptStatus(T_UBYTE lub_Port, T_UBYTE lub_Pin, T_E_RCGPIO_IRQEDGE le_Edge);

#endif /* RC_GPIO_H_ */
