/**
 * \file	ecuAppl_AppExe.h
 * \brief	Main application header file
 * \details	Exports the functions used in the main application and tasks.
 * 			Includes main page of the Doxygen documentation
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

#ifndef ECUAPPL_APPEXE_H_
#define ECUAPPL_APPEXE_H_

/**
 * \mainpage Custom ECU

  This documentation describes the Custom ECU functional modules.
  It consists of:
     - Processor drivers
     - Software modules
     - Application tasks

 */

/** \defgroup ecu_drivers Drivers
 *  Processor drivers
 */
/** \defgroup ecu_modules Software modules
 *  Software modules
 */
/** \defgroup ecu_tasks Application tasks
 *  Application tasks
 */
/**
 * @brief	Defines main application states
 */

/* Defines */
typedef enum E_APP_STATE {
	E_APP_STATE_INIT = 0u,										//!< Application No State
	E_APP_STATE_RUNNING,										//!< Application running
	E_APP_STATE_ERROR											//!< Application error
} T_E_APP_STATE;

#endif /* ECUAPPL_APPEXE_H_ */
