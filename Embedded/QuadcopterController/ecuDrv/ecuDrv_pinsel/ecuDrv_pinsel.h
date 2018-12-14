/**
 * \file	ecuDrv_pinsel.h
 * \brief	ecuDrv_pinsel header file
 * \details	Exports the functions used for pin selection attributes.
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

#ifndef ECUDRV_PINSEL_H_
#define ECUDRV_PINSEL_H_

/* Includes */
#include "ecuConfig_Types.h"
#include "lpc17xx_pinsel.h"

/**
 * @brief Pin function number
 */
typedef enum E_PINSEL_FUNC {
	E_PINSEL_FUNC0 = 0,				//!< Pinsel Function 0
	E_PINSEL_FUNC1,					//!< Pinsel Function 1
	E_PINSEL_FUNC2,					//!< Pinsel Function 2
	E_PINSEL_FUNC3					//!< Pinsel Function 3
} T_E_PINSEL_FUNC;

/**
 * @brief Pin mode
 */
typedef enum E_PINSEL_MODE {
	E_PINSEL_MODE_PULLUP = 0,		//!< Internal pull-up resistor
	E_PINSEL_MODE_TRISTATE,			//!< Tri-state
	E_PINSEL_MODE_PULLDOWN 			//!< Internal pull-down resistor
} T_E_PINSEL_MODE;

/**
 * @brief Drain mode
 */
typedef enum E_PINSEL_DRAIN {
	E_PINSEL_DRAIN_NORMAL = 0,		//!< Pin is in the normal (not open drain) mode
	E_PINSEL_DRAIN_OPEN				//!< Pin is in the open drain mode
} T_E_PINSEL_DRAIN;

/**
 * @brief	Defines the PINSEL config type
 */
typedef struct
{
	T_E_IOPORTS e_Port;				//!< Port number
	T_E_IOPINS e_Pin;				//!< Pin number
	T_E_PINSEL_FUNC e_Function;		//!< Function number
	T_E_PINSEL_MODE e_Mode;			//!< Pin mode
	T_E_PINSEL_DRAIN e_Drain;		//!< Drain mode
} T_S_PINSEL_CFG;

/* Exported pinsel functions group: */
extern void ecuDrv_pinsel_SetPinFunction(T_E_IOPORTS le_Port, T_E_IOPINS le_Pin, T_E_PINSEL_FUNC le_Function);
extern void ecuDrv_pinsel_ConfigTraceFunction(T_E_ENABLE le_State);
extern void ecuDrv_pinsel_SetResistorMode(T_E_IOPORTS le_Port, T_E_IOPINS le_Pin, T_E_PINSEL_MODE le_Mode);
extern void ecuDrv_pinsel_SetDrainMode(T_E_IOPORTS le_Port, T_E_IOPINS le_Pin, T_E_PINSEL_DRAIN le_Drain);
extern void ecuDrv_pinsel_ConfigPin(T_S_PINSEL_CFG ls_Config);

#endif /* RC_PINSEL_H_ */
