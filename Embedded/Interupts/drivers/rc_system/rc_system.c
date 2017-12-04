/**
 * \file	rc_system.c
 * \brief	Implements the interface functions with the core system
 * \details	Implements the functions which configures the core system
 * \author	Cosmin Marcu
 * \date	29.05.2015
 * \version 1.0.1
 */

/* Includes */
#include "system_LPC17xx.h"
#include "rc_stdtypedefs.h"

/* Begin functions implementation */

/** \defgroup rc_system System access driver
  Contains the functions to set and access the system core
*/

/**
 * \ingroup  rc_system
 * \defgroup System_functions System Functions
 *  Functions definitions for the System setup
 *  @{
 */
/* System functions group: */
/**
 * \brief	Initialize the System
 * \return 	none
 */
void rcsys_Init(void)
{
	SystemInit();
}

/**
 * \brief	Updated the Core Clock
 * \return 	none
 */
void rcsys_CoreClockUpdate(void)
{
	SystemCoreClockUpdate();
}

/**
 * \brief	Disable interrupts
 * \return 	none
 */
void rcsys_EnterProtectedMode(void)
{
	__disable_irq();
}

/**
 * \brief	Enable interrupts
 * \return 	none
 */
void rcsys_LeaveProtectedMode(void)
{
	__enable_irq();
}
/*@} end of group System_functions */

