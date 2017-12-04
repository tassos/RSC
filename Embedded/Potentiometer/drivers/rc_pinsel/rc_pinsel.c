/**
 * \file	rc_pinsel.c
 * \brief	Pin selection functions
 * \details	Implements the functions which configures pins selection
 * \author	Cosmin Marcu
 * \date	12.06.2015
 * \version 1.0.1
 */

/* Includes */
#include "rc_pinsel.h"

/* Begin functions implementation */

/** \defgroup rc_pinsel Pin selection driver
  Contains the functions to set the pins attributes
*/

/**
 * \ingroup  rc_pinsel
 * \defgroup Pinsel_functions Pin Selection Functions
 *  Functions definitions for the pin selection attributes
 *  @{
 */
/* Pinsel functions group: */
/**
 * \brief	Setup the pin selection function
 * \param	le_Port		Port number
 * \param	le_Pin		Pin number
 * \param	le_Function	Pin function number
 * \return 	none
 */
void rcpinsel_SetPinFunction(T_E_RC_IOPORTS le_Port, T_E_RC_IOPINS le_Pin, T_E_RCPINSEL_FUNC le_Function)
{
	PINSEL_SetPinFunc((T_UBYTE)le_Port, (T_UBYTE)le_Pin, (T_UBYTE)le_Function);
}

/**
 * \brief	Enable/Disable the trace function
 * \param	le_State	State of the trace function
 * \return 	none
 */
void rcpinsel_ConfigTraceFunction(T_E_RC_ENABLE le_State)
{
	PINSEL_ConfigTraceFunc((T_UBYTE)le_State);
}

/**
 * \brief	Setup the pin resistor mode
 * \param	le_Port		Port number
 * \param	le_Pin		Pin number
 * \param	le_Mode		Resistor mode (pullup, tri-state, pulldown)
 * \return 	none
 */
void rcpinsel_SetResistorMode(T_E_RC_IOPORTS le_Port, T_E_RC_IOPINS le_Pin, T_E_RCPINSEL_MODE le_Mode)
{
	PINSEL_SetResistorMode((T_UBYTE)le_Port, (T_UBYTE)le_Pin, (T_UBYTE)le_Mode);
}

/**
 * \brief	Setup the pin drain mode
 * \param	le_Port		Port number
 * \param	le_Pin		Pin number
 * \param	le_Drain	Drain mode (Normal or Open)
 * \return 	none
 */
void rcpinsel_SetDrainMode(T_E_RC_IOPORTS le_Port, T_E_RC_IOPINS le_Pin, T_E_RCPINSEL_DRAIN le_Drain)
{
	PINSEL_SetOpenDrainMode((T_UBYTE)le_Port, (T_UBYTE)le_Pin, (T_UBYTE)le_Drain);
}

/**
 * \brief	Configure Pin specific parameters
 * \param	ls_Config	Pin configuration structure
 * \return 	none
 */
void rcpinsel_ConfigPin(T_RCPINSEL_CFG ls_Config)
{
	PINSEL_CFG_Type ls_Pinsel_Config[1u];
	/* Fill PINSEL configuration structure */
	ls_Pinsel_Config[0].Portnum = ls_Config.e_Port;
	ls_Pinsel_Config[0].Pinnum = ls_Config.e_Pin;
	ls_Pinsel_Config[0].Funcnum = ls_Config.e_Function;
	ls_Pinsel_Config[0].Pinmode = ls_Config.e_Mode;
	ls_Pinsel_Config[0].OpenDrain = ls_Config.e_Drain;
	/* Call driver initializer */
	PINSEL_ConfigPin(ls_Pinsel_Config);
}
/*@} end of group Pinsel_functions */

