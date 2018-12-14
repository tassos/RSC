/**
 * \file	ecuAppl_Pot.h
 * \brief	ecuAppl_Pot module header file
 * \details	Exports the functions used to read potentiometer values
 * \author	Cosmin Marcu
 * \date	Nov 08, 2015
 * \version 1.0.1
 */
#ifndef ECUAPPL_POT_H_
#define ECUAPPL_POT_H_

/** \defgroup ecuAppl_pot Potentiometer module
 *  Functions to initialize Potentiometer module
 */

/* Includes */
#include "ecuConfig_Types.h"
#include "ecuConfig_Board.h"
#include "ecuDrv_adc.h"
#include "ecuDrv_pinsel.h"

/* Defines */
#define POT_CLOCKRATE							200000					//!< ADC Clock Frequency (Hz)
#define POT_REF_VOLTAGE							  3300					//!< Reference voltage (mV)
#define POT_REF_VOLTAGE_DIGITAL					  4095					//!< Reference digital voltage

/* Potentiometer public functions group: */
extern void ecuAppl_Pot_Init(void);
extern void ecuAppl_Pot_StartReading(void);
extern T_E_READ_STATUS ecuAppl_Pot_GetReadingStatus(void);
extern T_UWORD ecuAppl_Pot_GetVoltageAnalog(void);
extern T_UWORD ecuAppl_Pot_GetVoltageDigital(void);
extern void ecuAppl_Pot_Task50ms(void);
extern T_UWORD ecuAppl_Pot_GetPotValue(void);

#endif /* ECUAPPL_POT_H_ */
