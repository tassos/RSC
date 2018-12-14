/**
 * \file	ecuDrv_pinsel.c
 * \brief	Pin selection functions
 * \details	Implements the functions which configures pins selection
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

/* Includes */
#include "ecuDrv_pinsel.h"

/* Begin functions implementation */

/** \defgroup ecuDrv_pinsel PinSel driver
 *  \ingroup ecu_drivers
 *   Contains the functions to set the pins attributes
 */

/**
 * \ingroup  ecuDrv_pinsel
 * \defgroup pinsel_functions Pin Selection Functions
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
void ecuDrv_pinsel_SetPinFunction(T_E_IOPORTS le_Port, T_E_IOPINS le_Pin, T_E_PINSEL_FUNC le_Function)
{
	PINSEL_SetPinFunc((T_UBYTE)le_Port, (T_UBYTE)le_Pin, (T_UBYTE)le_Function);
}

/**
 * \brief	Enable/Disable the trace function
 * \param	le_State	State of the trace function
 * \return 	none
 */
void ecuDrv_pinsel_ConfigTraceFunction(T_E_ENABLE le_State)
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
void ecuDrv_pinsel_SetResistorMode(T_E_IOPORTS le_Port, T_E_IOPINS le_Pin, T_E_PINSEL_MODE le_Mode)
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
void ecuDrv_pinsel_SetDrainMode(T_E_IOPORTS le_Port, T_E_IOPINS le_Pin, T_E_PINSEL_DRAIN le_Drain)
{
	PINSEL_SetOpenDrainMode((T_UBYTE)le_Port, (T_UBYTE)le_Pin, (T_UBYTE)le_Drain);
}

/**
 * \brief	Configure Pin specific parameters
 * \param	ls_Config	Pin configuration structure
 * \return 	none
 */
void ecuDrv_pinsel_ConfigPin(T_S_PINSEL_CFG ls_Config)
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
/**@} end of group pinsel_functions */

