/**
 * \file	rc_app.h
 * \brief	Main application header file
 * \details	Exports the functions used in the main application and tasks.
 * 			Includes main page of the Doxygen documentation
 * \author	Cosmin Marcu
 * \date	27.05.2015
 * \version 1.0.1
 */

#ifndef RC_APP_H_
#define RC_APP_H_

/**
 * \mainpage Robot Controller - Embedded Artists AOAA Cortex-M0/M3 board

  This documentation describes the Robot Controller functional modules.
  It consists of:

     - rc_lowlayer module - accesses the peripheral driver functions
     - TBD.

 */

extern void EINT0_IRQHandler(void);
extern void TIMER1_IRQHandler(void);

#endif /* RC_APP_H_ */
