/**
 * \file	rc_task_pot.h
 * \brief	rc_task_pot header file
 * \details	Exports definitions and functions for potentiometer task
 * \author	Cosmin Marcu
 * \date	Nov 08, 2015
 * \version 1.0.1
 */
#ifndef RC_TASK_POT_H_
#define RC_TASK_POT_H_

/** \defgroup rc_task_pot Potentiometer task
 *  FreeRTOS Task for potentiometer
 */

/* FreeRTOS headers */
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"

/* Task Stack size definition */
#define RC_STACKSIZE_TASK_POT			 256	//!< Potentiometer task stack size

/* Defines */
#define RCTASK_LEDS_DELAY				 500	//!< Potentiometer task delay

/* Global variables */
xTaskHandle xHandlePot;						//!< Potentiometer RTOS task handler

/* Exported functions */
extern void rctask_pot(void *pvParameters);


#endif /* RC_TASK_POT_H_ */
