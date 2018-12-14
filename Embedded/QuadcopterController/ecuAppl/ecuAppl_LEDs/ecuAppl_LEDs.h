/**
 * \file	ecuAppl_LEDs.h
 * \brief	ecuAppl_LEDs module header file
 * \details	Exports the functions used to actuate the RGB LEDs
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */
#ifndef ECUAPPL_LEDS_H_
#define ECUAPPL_LEDS_H_

/** \defgroup ecuAppl_LEDs LEDs module
 *  \ingroup ecu_modules
 *  Functions to initialize LEDs module
 */

/* Includes */
#include "ecuConfig_Board.h"
#include "ecuConfig_Types.h"

/* Defines */
#define		LEDS_PORT						AOAA_RGBLEDS_PORT			//!< LEDs port
#define		LEDS_RGB1_RED				    AOAA_RGBLED1_RED_PIN		//!< Red LED on RGB1
#define		LEDS_RGB1_GREEN			   		AOAA_RGBLED1_GREEN_PIN		//!< Green LED on RGB1
#define		LEDS_RGB1_BLUE			    	AOAA_RGBLED1_BLUE_PIN		//!< Blue LED on RGB1
#define		LEDS_RGB2_RED				    AOAA_RGBLED2_RED_PIN		//!< Red LED on RGB2
#define		LEDS_RGB2_GREEN			   		AOAA_RGBLED2_GREEN_PIN		//!< Green LED on RGB2
#define		LEDS_RGB2_BLUE			    	AOAA_RGBLED2_BLUE_PIN		//!< Blue LED on RGB2

/* LEDs public functions group: */
extern void ecuAppl_LEDs_Init(void);
extern void ecuAppl_LEDs_Task_10ms(void);

#endif /* ECUAPPL_LEDS_H_ */
