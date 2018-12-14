/**
 * \file	ecuAppl_NFC.h
 * \brief	ecuAppl_NFC module header file
 * \details	Exports the functions used for communication with NFC module
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */
#ifndef ECUAPPL_NFC_H_
#define ECUAPPL_NFC_H_

/** \defgroup ecuAppl_NFC NFC module
 *  \ingroup ecu_modules
 *  Functions to initialize and use NFC module
 */

/* Includes */
#include "ecuConfig_Board.h"
#include "ecuConfig_Types.h"

/* Defines */

/* Keyboard public functions group: */
extern void ecuAppl_NFC_Init(void);
extern void ecuAppl_NFC_Task_10ms(void);

#endif /* ECUAPPL_NFC_H_ */
