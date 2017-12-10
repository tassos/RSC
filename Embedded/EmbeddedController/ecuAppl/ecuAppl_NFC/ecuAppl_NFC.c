/**
 * \file	ecuAppl_NFC.c
 * \brief	NFC functions
 * \details	Implements the functions for pn532 NFC module
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

/* Includes */
#include "ecuAppl_NFC.h"
#include "ecuDrv_gpio.h"
#include "ecuDrv_ssp.h"

/**
 * \ingroup  ecuAppl_NFC
 * \defgroup nfc_functions NFC Functions
 *  Functions definitions for NFC module
 *  @{
 */
/**
 * \brief	Initializes NFC module
 * \return 	none
 */
void ecuAppl_NFC_Init(void)
{
	//TODO: add initialization
}
/**@} end of group nfc_functions */

/**
 * \ingroup  ecu_tasks
 * \defgroup nfc_tasks NFC Tasks
 *  Tasks definitions for NFC module
 *  @{
 */
/**
 * \brief	Periodic 10ms NFC task
 * \return 	none
 * \see		ecuAppl_Scheduler_Task_10ms
 */
void ecuAppl_NFC_Task_10ms(void)
{
	//TODO: add periodic callbacks
}
/**@} end of group nfc_tasks */
