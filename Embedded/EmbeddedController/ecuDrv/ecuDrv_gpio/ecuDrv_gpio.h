/**
 * \file	ecuDrv_gpio.h
 * \brief	ecuDrv_gpio driver header file
 * \details	Exports the functions used GPIO communication with the core drivers.
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

#ifndef ECUDRV_GPIO_H_
#define ECUDRV_GPIO_H_

/* Includes */
#include "ecuConfig_Types.h"
#include "lpc17xx_gpio.h"

#define GPIO_PINMASK(x)	(1<<(x))			//!< Mask pin number

/**
 * \brief	Defines GPIO interrupt edge sense register values
 */
typedef enum E_GPIO_IRQEDGE {
	E_GPIO_RISING,							//!< GPIO Rising edge
	E_GPIO_FALLING							//!< GPIO Falling edge
} T_E_GPIO_IRQEDGE;

/* GPIO exported functions group: */
extern void ecuDrv_gpio_SetPin(T_UBYTE lub_Port, T_UBYTE lub_Pin);
extern void ecuDrv_gpio_ClearPin(T_UBYTE lub_Port, T_UBYTE lub_Pin);
extern T_E_SIGNAL_STATE ecuDrv_gpio_ReadPin(T_UBYTE lub_Port, T_UBYTE lub_Pin);
extern void ecuDrv_gpio_SwapPin(T_UBYTE lub_Port, T_UBYTE lub_Pin);
extern void ecuDrv_gpio_SetDirection(T_UBYTE lub_Port, T_UBYTE lub_Pin, T_E_SIGNAL_DIRECTION le_Direction);
extern void ecuDrv_gpio_EnableInterrupt(T_UBYTE lub_Port, T_UBYTE lub_Pin, T_E_GPIO_IRQEDGE le_Edge);
extern void ecuDrv_gpio_ClearInterrupt(T_UBYTE lub_Port, T_UBYTE lub_Pin);
extern T_E_BOOL ecuDrv_gpio_GetInterruptStatus(T_UBYTE lub_Port, T_UBYTE lub_Pin, T_E_GPIO_IRQEDGE le_Edge);

#endif /* ECUDRV_GPIO_H_ */
