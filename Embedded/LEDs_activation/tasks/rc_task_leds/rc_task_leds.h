/**
 * \file	rc_task_leds.h
 * \brief	rc_task_leds header file
 * \details	Exports definitions and functions for LEDs task
 * \author	Cosmin Marcu
 * \date	Nov 02, 2015
 * \version 1.0.1
 */
#ifndef RC_TASK_LEDS_H_
#define RC_TASK_LEDS_H_

/** \defgroup rc_task_leds LEDs task
 *  FreeRTOS Task for LEDs
 */

/* FreeRTOS headers */
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"

/* Task Stack size definition */
#define RC_STACKSIZE_TASK_LEDS			 256	//!< LEDs task stack size

/* Defines */
#define RCTASK_LEDS_DELAY				 500	//!< LEDs task delay

/* Global variables */
xTaskHandle xHandleLEDs;						//!< LEDs RTOS task handler

/**
 * \brief	Defines possible states of the rc_task_leds
 * \see		To be done...
 */
typedef enum E_RCLEDS_STATE {
	E_RCLEDS_STATE_NONE = 0u,			//!< E_RCLEDS_STATE_NONE - LEDs off
	E_RCLEDS_STATE_LEDS_ON,				//!< E_RCLEDS_STATE_LEDS_ON - both LEDs on
} T_E_RCLEDS_STATE;


/* Exported functions */
extern void rctask_LEDs(void *pvParameters);


#endif /* RC_TASK_LEDS_H_ */
