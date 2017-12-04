/**
 * \file	rc_leds.h
 * \brief	rc_leds module header file
 * \details	Exports the functions used to actuate the RGB LEDs
 * \author	Cosmin Marcu
 * \date	Nov 03, 2015
 * \version 1.0.1
 */
#ifndef RC_LEDS_H_
#define RC_LEDS_H_

/** \defgroup rc_leds LEDs module
 *  Functions to initialize LEDs module
 */

/* Includes */
#include "rc_stdtypedefs.h"
#include "rc_board.h"
#include "rc_gpio.h"

/* Defines */
#define		RCLEDS_PORT						   	RC_RGBLEDS_PORT		//!< LEDs port
#define		RCLEDS_RGB1_RED				     RC_RGBLED1_RED_PIN		//!< Red LED on RGB1
#define		RCLEDS_RGB1_GREEN			   RC_RGBLED1_GREEN_PIN		//!< Green LED on RGB1
#define		RCLEDS_RGB1_BLUE			    RC_RGBLED1_BLUE_PIN		//!< Blue LED on RGB1
#define		RCLEDS_RGB2_RED				     RC_RGBLED2_RED_PIN		//!< Red LED on RGB2
#define		RCLEDS_RGB2_GREEN			   RC_RGBLED2_GREEN_PIN		//!< Green LED on RGB2
#define		RCLEDS_RGB2_BLUE			    RC_RGBLED2_BLUE_PIN		//!< Blue LED on RGB2

/**
 * \brief	Defines possible states of the rc_task_leds
 * \see		To be done...
 */
typedef enum E_RCLEDS_STATE {
	E_RCLEDS_STATE_NONE = 0u,			//!< E_RCLEDS_STATE_NONE
	E_RCLEDS_STATE_RED,					//!< E_RCLEDS_STATE_RED - RED LEDs ON
	E_RCLEDS_STATE_BLUE,				//!< E_RCLEDS_STATE_BLUE - BLUE LEDs ON
} T_E_RCLEDS_STATE;


/* LEDs public functions group: */
extern void rcleds_Init(void);
extern void rcleds_ClearLEDs(void);
extern T_E_RCLEDS_STATE rcleds_GetState(void);
extern void rcleds_SetState(T_E_RCLEDS_STATE le_State);

#endif /* RC_LEDS_H_ */
