/**
 * \file	rc_pot.c
 * \brief	Potentiometer functions
 * \details	Implements the functions to init and read on board potentiometer
 * \author	Cosmin Marcu
 * \date	Nov 08, 2015
 * \version 1.0.1
 */

/* Includes */
#include "rc_pot.h"

/* Include module headers */

/**
 * \ingroup  rc_pot
 * \defgroup pot_functions Potentiometer Functions
 *  Functions definitions for built-in Potentiometer
 *  @{
 */

/**
 * \brief	Initializes potentiometer analog input
 * \return 	none
 */
void rcpot_Init(void)
{
	T_RCPINSEL_CFG ls_PinselConfig;

	/* Configure potentiometer ADC pin */
	ls_PinselConfig.e_Port = E_RC_IOPORT1;
	ls_PinselConfig.e_Function = E_RCPINSEL_FUNC3;
	ls_PinselConfig.e_Pin = E_RC_IOPIN31;
	/* Configure pin 1.31 */
	rcpinsel_ConfigPin(ls_PinselConfig);
	/* Init ADC */
	rcadc_Init(RC_ADC_PORT, RCPOT_CLOCKRATE);
	rcadc_SetInterruptState(RC_ADC_PORT, E_RCADC_IRQ_CHANNEL5, E_RC_DISABLE);
	rcadc_SetChannelState(RC_ADC_PORT, E_RCADC_CHANNEL5, E_RC_ENABLE);
}

/**
 * \brief	Start ADC reading
 * \return 	none
 */
void rcpot_StartReading(void)
{
	rcadc_SetStartMode(RC_ADC_PORT, E_RCADC_START_NOW);
}

/**
 * \brief	Start ADC reading
 * \return 	E_RC_NOTDONE if reading is in progress or unsuccessful
 * 			E_RC_DONE if reading successful
 */
T_E_RC_READ_STATUS rcpot_GetReadingStatus(void)
{
	return (T_E_RC_READ_STATUS)rcadc_ReadChannelStatus(RC_ADC_PORT, E_RCADC_IRQ_CHANNEL5, E_RCADC_STATUS_DONE);
}

/**
 * \brief	Converts the digital ADC value into analog value (mV)
 * \return 	Analog voltage
 */
T_UWORD rcpot_GetVoltageAnalog(T_UWORD luw_DigitalVoltage)
{
	//TBD
	return 0;
}

/**
 * \brief	Gets the current potentiometer digital value (digits)
 * \return 	Digital voltage
 */
T_UWORD rcpot_GetVoltageDigital(void)
{
	return rcadc_ReadChannelData(RC_ADC_PORT, E_RCADC_IRQ_CHANNEL5);
}
/*@} end of group pot_functions */

