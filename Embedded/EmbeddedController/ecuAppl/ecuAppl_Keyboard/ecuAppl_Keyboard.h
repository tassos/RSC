/**
 * \file	ecuAppl_Keyboard.h
 * \brief	ecuAppl_Keyboard module header file
 * \details	Exports the functions used for reading capacitive keyboard
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */
#ifndef ECUAPPL_KEYBOARD_H_
#define ECUAPPL_KEYBOARD_H_

/** \defgroup ecuAppl_Keyboard Keyboard module
 *  \ingroup ecu_modules
 *  Functions to initialize and use capacitive Keyboard
 */

/* Includes */
#include "ecuConfig_Types.h"

/* Defines */

/* Keyboard public functions group: */
extern void ecuAppl_Keyboard_Init(void);
extern void ecuAppl_Keyboard_Task_10ms(void);

#endif /* ECUAPPL_KEYBOARD_H_ */
