/**
 * \file	ecuDrv_sys.h
 * \brief	ecuDrv_sys header file
 * \details	Exports the functions used for system configuration and initialization.
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

#ifndef ECUDRV_SYS_H_
#define ECUDRV_SYS_H_

/* Includes */
#include "ecuConfig_Types.h"

/* Exported system functions group: */
extern void ecuDrv_sys_Init(void);
extern void ecuDrv_sys_CoreClockUpdate(void);
extern void ecuDrv_sys_EnterProtectedMode(void);
extern void ecuDrv_sys_LeaveProtectedMode(void);

#endif /* ECUDRV_SYS_H_ */
