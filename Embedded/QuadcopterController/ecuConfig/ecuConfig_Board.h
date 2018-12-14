/**
 * \file	ecuConfig_board.h
 * \brief	EA Board configuration file
 * \details	Contains definitions for EA Board
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */
#ifndef ECUCONFIG_BOARD_H_
#define ECUCONFIG_BOARD_H_

#include "ecuConfig_Types.h"

/* RGB LEDs */
#define	AOAA_RGBLEDS_PORT			E_IOPORT2
#define	AOAA_RGBLED1_RED_PIN		E_IOPIN0
#define	AOAA_RGBLED1_BLUE_PIN		E_IOPIN1
#define	AOAA_RGBLED1_GREEN_PIN		E_IOPIN2
#define	AOAA_RGBLED2_RED_PIN		E_IOPIN3
#define	AOAA_RGBLED2_BLUE_PIN		E_IOPIN4
#define	AOAA_RGBLED2_GREEN_PIN		E_IOPIN5

/* User buttons */
#define AOAA_SW2_PORT				E_IOPORT2
#define AOAA_SW2_PIN				E_IOPIN11
#define AOAA_SW3_PORT				E_IOPORT2
#define AOAA_SW3_PIN				E_IOPIN12

#endif /* ECUCONFIG_BOARD_H_ */
