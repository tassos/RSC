/**
 * \file	ecuAppl_TCPHandler.h
 * \brief	ecuAppl_TCPHandler module header file
 * \details	Exports the functions used for TCP communication
 * \author	Cosmin Marcu
 * \date	18.11.2017
 * \version 1.0.1
 */
#ifndef ECUAPPL_TCPHANDLER_H_
#define ECUAPPL_TCPHANDLER_H_

/** \defgroup ecuAppl_TCP TCP Handler module
 *  \ingroup ecu_modules
 *  Functions to initialize and use TCP Handler module
 */

/* Includes */
#include "ecuConfig_Board.h"
#include "ecuConfig_Types.h"

/* Defines */

#define SETPOINT_0 0
#define SETPOINT_1 1

/* Keyboard public functions group: */
extern void ecuAppl_TCPHandler_Init(T_UWORD luw_Port);

extern void rcpot_SetState (T_UBYTE state);

#endif /* ECUAPPL_TCPHANDLER_H_ */
