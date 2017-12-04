/**
 * \file	rc_pinsel.h
 * \brief	rc_pinsel header file
 * \details	Exports the functions used for pin selection attributes.
 * \author	Cosmin Marcu
 * \date	12.06.2015
 * \version 1.0.1
 */

#ifndef RC_PINSEL_H_
#define RC_PINSEL_H_

/* Includes */
#include "rc_stdtypedefs.h"
#include "lpc17xx_pinsel.h"

/**
 * @brief Pin function number
 */
typedef enum E_RCPINSEL_FUNC {
	E_RCPINSEL_FUNC0 = 0,			//!< Pinsel Function 0
	E_RCPINSEL_FUNC1,				//!< Pinsel Function 1
	E_RCPINSEL_FUNC2,				//!< Pinsel Function 2
	E_RCPINSEL_FUNC3				//!< Pinsel Function 3
} T_E_RCPINSEL_FUNC;

/**
 * @brief Pin mode
 */
typedef enum E_RCPINSEL_MODE {
	E_RCPINSEL_MODE_PULLUP = 0,		//!< Internal pull-up resistor
	E_RCPINSEL_MODE_TRISTATE,		//!< Tri-state
	E_RCPINSEL_MODE_PULLDOWN 		//!< Internal pull-down resistor
} T_E_RCPINSEL_MODE;

/**
 * @brief Drain mode
 */
typedef enum E_RCPINSEL_DRAIN {
	E_RCPINSEL_DRAIN_NORMAL = 0,	//!< Pin is in the normal (not open drain) mode
	E_RCPINSEL_DRAIN_OPEN			//!< Pin is in the open drain mode
} T_E_RCPINSEL_DRAIN;

/**
 * @brief	Defines the PINSEL config type
 */
typedef struct
{
	T_E_RC_IOPORTS e_Port;			//!< Port number
	T_E_RC_IOPINS e_Pin;			//!< Pin number
	T_E_RCPINSEL_FUNC e_Function;	//!< Function number
	T_E_RCPINSEL_MODE e_Mode;		//!< Pin mode
	T_E_RCPINSEL_DRAIN e_Drain;		//!< Drain mode
} T_RCPINSEL_CFG;

/* Exported pinsel functions group: */
extern void rcpinsel_SetPinFunction(T_E_RC_IOPORTS le_Port, T_E_RC_IOPINS le_Pin, T_E_RCPINSEL_FUNC le_Function);
extern void rcpinsel_ConfigTraceFunction(T_E_RC_ENABLE le_State);
extern void rcpinsel_SetResistorMode(T_E_RC_IOPORTS le_Port, T_E_RC_IOPINS le_Pin, T_E_RCPINSEL_MODE le_Mode);
extern void rcpinsel_SetDrainMode(T_E_RC_IOPORTS le_Port, T_E_RC_IOPINS le_Pin, T_E_RCPINSEL_DRAIN le_Drain);
extern void rcpinsel_ConfigPin(T_RCPINSEL_CFG ls_Config);

#endif /* RC_PINSEL_H_ */
