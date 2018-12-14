/**
 * \file	ecuAppl_GPS.h
 * \brief	ecuAppl_GPS module header file
 * \details	Exports the functions used for communication with GPS module
 * \author	Cosmin Marcu
 * \date	05.05.2017
 * \version 1.0.1
 */
#ifndef ECUAPPL_GPS_H_
#define ECUAPPL_GPS_H_

/** \defgroup ecuAppl_GPS GPS module
 *  \ingroup ecu_modules
 *  Functions to initialize and use GPS module
 */

/* Includes */
#include "ecuConfig_Board.h"
#include "ecuConfig_Types.h"

/* Defines */

/* WiFi public functions group: */
extern void ecuAppl_GPS_Init(void);
extern void ecuAppl_GPS_SM(void);
extern void ecuAppl_GPS_Task_10ms(void);
extern void ecuAppl_GPS_DisableGPS(void);
extern void ecuAppl_GPS_EnableGPS(void);
#endif /* ECUAPPL_GPS_H_ */
