/**
 * \file	rc_adc.c
 * \brief	Analog-to-Digital converter functions
 * \details	Implements the functions which configures ADC ports
 * \author	Cosmin Marcu
 * \date	27.06.2015
 * \version 1.0.1
 */

/* Includes */
#include "rc_adc.h"

/* Begin functions implementation */

/** \defgroup rc_adc ADC driver
  Contains the functions to configure and read ADC pins
*/

/**
 * \ingroup  rc_adc
 * \defgroup adc_functions ADC Functions
 *  Functions definitions for the ADC ports
 *  @{
 */

/* ADC functions group: */

/**
 * \brief	Initializes ADC peripheral
 * \param 	ls_Port ADC port structure
 * \param 	lul_ClockFrequency ADC clock frequency
 * \return 	none
 */
void rcadc_Init(T_RCADC_PORT *ls_Port, T_ULONG lul_ClockFrequency)
{
	ADC_Init(ls_Port, lul_ClockFrequency);
}

/**
 * \brief	De-initializes ADC peripheral
 * \param 	ls_Port ADC port structure
 * \return 	none
 */
void rcadc_DeInit(T_RCADC_PORT *ls_Port)
{
	ADC_DeInit(ls_Port);
}

/**
 * \brief	Reads an ADC channel
 * \param 	ls_Port ADC port structure
 * \param 	le_Channel ADC channel to read
 * \return 	none
 */
T_UWORD rcadc_ReadChannelData(T_RCADC_PORT *ls_Port, T_E_RCADC_CHANNEL le_Channel)
{
	return ADC_ChannelGetData(ls_Port, (T_ULONG)le_Channel);
}

/**
 * \brief	Reads an ADC channel status
 * \param 	ls_Port ADC port structure
 * \param 	le_Channel ADC channel to read
 * \param 	le_StatusType Status type of the channel:
 * 							 - E_RCADC_STATUS_BURST
 * 							 - E_RCADC_STATUS_DONE
 * \return 	Status of the channel, based on status type
 */
T_E_RC_STATUS rcadc_ReadChannelStatus(T_RCADC_PORT *ls_Port, T_E_RCADC_CHANNEL le_Channel, T_E_RCADC_CHANNEL_STATUS le_StatusType)
{
	return (T_E_RC_STATUS)ADC_ChannelGetStatus(ls_Port, le_Channel, le_StatusType);
}

/**
 * \brief	Enable/Disable ADC burst mode
 * \param 	ls_Port ADC port structure
 * \param 	le_State Burst mode state to set
 * \return 	none
 */
void rcadc_SetBurstMode(T_RCADC_PORT *ls_Port, T_E_RC_ENABLE le_State)
{
	 ADC_BurstCmd(ls_Port, le_State);
}

/**
 * \brief	Sets ADC start mode
 * \param 	ls_Port ADC port structure
 * \param 	le_Mode Start mode
 * \return 	none
 */
void rcadc_SetStartMode(T_RCADC_PORT *ls_Port, T_E_RCADC_START_MODE le_Mode)
{
	ADC_StartCmd(ls_Port, le_Mode);
}

/**
 * \brief	Sets an ADC interrupt state
 * \param 	ls_Port ADC port structure
 * \param 	le_IRQType Interrupt type
 * \param 	le_State Interrupt state
 * \return 	none
 */
void rcadc_SetInterruptState(T_RCADC_PORT *ls_Port, T_E_RCADC_IRQTYPE le_IRQType, T_E_RC_ENABLE le_State)
{
	ADC_IntConfig(ls_Port, le_IRQType, le_State);
}

/**
 * \brief	Sets an ADC channel state
 * \param 	ls_Port ADC port structure
 * \param 	le_Channel Channel number
 * \param 	le_State Channel state
 * \return 	none
 */
void rcadc_SetChannelState(T_RCADC_PORT *ls_Port, T_E_RCADC_CHANNEL le_Channel, T_E_RC_ENABLE le_State)
{
	ADC_ChannelCmd(ls_Port, le_Channel, le_State);
}

/**
 * \brief	Configures ADC edge start
 * \param 	ls_Port ADC port structure
 * \param 	le_Edge Edge mode:
 * 					- E_RCADC_EDGE_START_RISING
 * 					- E_RCADC_EDGE_START_FALLING
 * \return 	none
 */
void rcadc_SetEdgeStart(T_RCADC_PORT *ls_Port, T_E_RCADC_EDGE_START le_Edge)
{
	ADC_EdgeStartConfig(ls_Port, le_Edge);
}
/*@} end of group adc_functions */

