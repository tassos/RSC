/**
 * \file	ecuAppl_Ethernet.h
 * \brief	ecuAppl_Ethernet module header file
 * \details	Exports the functions used for communication with Ethernet controler
 * \author	Cosmin Marcu
 * \date	18.11.2017
 * \version 1.0.1
 */
#ifndef ECUAPPL_ETHERNET_H_
#define ECUAPPL_ETHERNET_H_

/** \defgroup ecuAppl_Ethernet Ethernet module
 *  \ingroup ecu_modules
 *  Functions to initialize and use Ethernet module
 */

/* Includes */
#include "ecuConfig_Board.h"
#include "ecuConfig_Types.h"

/* Defines */

/* Keyboard public functions group: */
extern T_E_ERROR ecuAppl_Ethernet_Init(void);
extern void ecuAppl_Ethernet_Task_2s(void);

#endif /* ECUAPPL_ETHERNET_H_ */
