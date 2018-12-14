/**
 * \file	ecuDrv_sys.c
 * \brief	Implements the interface functions with the core system
 * \details	Implements the functions which configures the core system
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

/* Includes */
#include "../../ecuConfig/ecuConfig_Types.h"
#include "system_LPC17xx.h"

/* Begin functions implementation */

/** \defgroup ecuDrv_sys System driver
 *  \ingroup ecu_drivers
 *   Contains the functions to set and access the system core
 */

/**
 * \ingroup  ecuDrv_sys
 * \defgroup system_functions System Functions
 *  Functions definitions for the System setup
 *  @{
 */
/* System functions group: */
/**
 * \brief	Initialize the System
 * \return 	none
 */
void ecuDrv_sys_Init(void)
{
	SystemInit();
}

/**
 * \brief	Updated the Core Clock
 * \return 	none
 */
void ecuDrv_sys_CoreClockUpdate(void)
{
	SystemCoreClockUpdate();
}

/**
 * \brief	Disable interrupts
 * \return 	none
 */
void ecuDrv_sys_EnterProtectedMode(void)
{
	__disable_irq();
}

/**
 * \brief	Enable interrupts
 * \return 	none
 */
void ecuDrv_sys_LeaveProtectedMode(void)
{
	__enable_irq();
}
/**@} end of group system_functions */

