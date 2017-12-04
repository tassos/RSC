/**
 * \file	rc_board.h
 * \brief	EA Board configuration file
 * \details	Contains definitions for EA Board
 * \author	Cosmin Marcu
 * \date	May 27, 2015
 * \version 1.0.1
 */
#ifndef RC_BOARD_H_
#define RC_BOARD_H_

#include "rc_stdtypedefs.h"

/* RGB LEDs */
#define	RC_RGBLEDS_PORT			E_RC_IOPORT2
#define	RC_RGBLED1_RED_PIN		E_RC_IOPIN0
#define	RC_RGBLED1_BLUE_PIN		E_RC_IOPIN1
#define	RC_RGBLED1_GREEN_PIN	E_RC_IOPIN2
#define	RC_RGBLED2_RED_PIN		E_RC_IOPIN3
#define	RC_RGBLED2_BLUE_PIN		E_RC_IOPIN4
#define	RC_RGBLED2_GREEN_PIN	E_RC_IOPIN5

/* User buttons */
#define RC_SW2_PORT				E_RC_IOPORT2
#define RC_SW2_PIN				E_RC_IOPIN11
#define RC_SW3_PORT				E_RC_IOPORT2
#define RC_SW3_PIN				E_RC_IOPIN12

/* XBee port */
#define RC_XB_PORT				RC_UART1

/* ADC port */
#define RC_ADC_PORT				RC_ADC

#endif /* RC_BOARD_H_ */
