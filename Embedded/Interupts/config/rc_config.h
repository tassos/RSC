/**
 * \file	rc_config.h
 * \brief	General configuration file
 * \details	Contains configuration flags for different functionalities
 * \author	Cosmin Marcu
 * \date	May 27, 2015
 * \version 1.0.1
 */
#ifndef RC_CONFIG_H_
#define RC_CONFIG_H_

#include "rc_stdtypedefs.h"

#define	RC_ZCL				RC_ENABLED			//!< Activate Robot Profile (ZigBee-like)
#define RC_USE_FREERTOS		RC_ENABLED			//!< Use FreeRTOS

#define RC_ZIGBEE_BAUDRATE	9600ul				//!< Baudrate for ZigBee UART1 communication
#endif /* RC_CONFIG_H_ */
