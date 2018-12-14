/**
 * \file	ecuAppl_Pot.c
 * \brief	Potentiometer functions
 * \details	Implements the functions to init and read on board potentiometer
 * \author	Cosmin Marcu
 * \date	Nov 08, 2015
 * \version 1.0.1
 */

/* Includes */
#include "ecuAppl_Pot.h"
#include "ecuDrv_timer.h"

#define POT_READ_CHECK_MS	50u

/* Include module headers */

PRIVATE_DATA T_ULONG rul_lastSysCheck = 0ul;
PRIVATE_DATA T_UWORD ruw_PotValue = 0u;

/**
 * \ingroup  ecuAppl_pot
 * \defgroup pot_functions Potentiometer Functions
 *  Functions definitions for built-in Potentiometer
 *  @{
 */

/**
 * \brief	Initializes potentiometer analog input
 * \return 	none
 */
void ecuAppl_Pot_Init(void)
{
	T_S_PINSEL_CFG ls_PinselConfig;

	/* Configure potentiometer ADC pin */
	ls_PinselConfig.e_Port = E_IOPORT1;
	ls_PinselConfig.e_Function = E_PINSEL_FUNC3;
	ls_PinselConfig.e_Pin = E_IOPIN31;
	/* Configure pin 1.31 */
	ecuDrv_pinsel_ConfigPin(ls_PinselConfig);
	/* Init ADC */
	ecuDrv_adc_Init(ECU_ADC, POT_CLOCKRATE);
	ecuDrv_adc_SetInterruptState(ECU_ADC, E_ADC_IRQ_CHANNEL5, E_DISABLE);
	ecuDrv_adc_SetChannelState(ECU_ADC, E_ADC_CHANNEL5, E_ENABLE);
}

/**
 * \brief	Start ADC reading
 * \return 	none
 */
void ecuAppl_Pot_StartReading(void)
{
	ecuDrv_adc_SetStartMode(ECU_ADC, E_ADC_START_NOW);
}

/**
 * \brief	Start ADC reading
 * \return 	E_RC_NOTDONE if reading is in progress or unsuccessful
 * 			E_RC_DONE if reading successful
 */
T_E_READ_STATUS ecuAppl_Pot_GetReadingStatus(void)
{
	return (T_E_READ_STATUS)ecuDrv_adc_ReadChannelStatus(ECU_ADC, E_ADC_IRQ_CHANNEL5, E_ADC_STATUS_DONE);
}

/**
 * \brief	Converts the digital ADC value into analog value (mV)
 * \return 	Analog voltage
 */
T_UWORD ecuAppl_Pot_GetVoltageAnalog(void)
{
	T_UWORD luw_Voltage_mV = 0u;
	T_UWORD luw_DigitalVoltage = ecuAppl_Pot_GetVoltageDigital();

	/* Calculate voltage (mV) */
	luw_Voltage_mV = (T_UWORD)((POT_REF_VOLTAGE * luw_DigitalVoltage)/POT_REF_VOLTAGE_DIGITAL);
	return luw_Voltage_mV;
}

/**
 * \brief	Gets the current potentiometer digital value (digits)
 * \return 	Digital voltage
 */
T_UWORD ecuAppl_Pot_GetVoltageDigital(void)
{
	return ecuDrv_adc_ReadChannelData(ECU_ADC, E_ADC_IRQ_CHANNEL5);
}

/**
 * \brief	Pot reading task
 * \return 	Digital voltage
 */
void ecuAppl_Pot_Task50ms(void)
{

  T_ULONG lul_SysNow = ecuDrv_timer_GetTimer1_value();

  if (lul_SysNow > rul_lastSysCheck + POT_READ_CHECK_MS) {
	  rul_lastSysCheck = lul_SysNow;
	  ecuAppl_Pot_StartReading();
  }

  if(E_DONE == ecuAppl_Pot_GetReadingStatus())
  {
	  ruw_PotValue = ecuAppl_Pot_GetVoltageAnalog();
  }
}

/**
 * \brief	Read last measured Pot value
 * \return 	Analog voltage (mV)
 */
T_UWORD ecuAppl_Pot_GetPotValue(void)
{
	return (ruw_PotValue);
}
/*@} end of group pot_functions */

