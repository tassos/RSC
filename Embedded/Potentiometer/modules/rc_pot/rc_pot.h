/**
 * \file	rc_pot.h
 * \brief	rc_pot module header file
 * \details	Exports the functions used to read potentiometer values
 * \author	Cosmin Marcu
 * \date	Nov 08, 2015
 * \version 1.0.1
 */
#ifndef RC_POT_H_
#define RC_POT_H_

/** \defgroup rc_pot Potentiometer module
 *  Functions to initialize Potentiometer module
 */

/* Includes */
#include "rc_stdtypedefs.h"
#include "rc_board.h"
#include "rc_adc.h"
#include "rc_pinsel.h"

/* Defines */
#define RCPOT_CLOCKRATE							200000					//!< ADC Clock Frequency (Hz)

/* Potentiometer public functions group: */
extern void rcpot_Init(void);
extern void rcpot_StartReading(void);
extern T_E_RC_READ_STATUS rcpot_GetReadingStatus(void);
extern T_UWORD rcpot_GetVoltageAnalog(T_UWORD luw_DigitalVoltage);
extern T_UWORD rcpot_GetVoltageDigital(void);

#endif /* RC_POT_H_ */
