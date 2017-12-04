/**
 * \file	rc_system.h
 * \brief	rc_system header file
 * \details	Exports the functions used for system configuration and initialization.
 * \author	Cosmin Marcu
 * \date	29.05.2015
 * \version 1.0.1
 */

#ifndef RC_SYSTEM_H_
#define RC_SYSTEM_H_

/* Includes */
#include "rc_stdtypedefs.h"

/* Exported system functions group: */
extern void rcsys_Init(void);
extern void rcsys_CoreClockUpdate(void);
extern void rcsys_EnterProtectedMode(void);
extern void rcsys_LeaveProtectedMode(void);

#endif /* RC_SYSTEM_H_ */
