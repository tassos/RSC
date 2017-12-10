/**
 * \file	ecuDrv_adc.c
 * \brief	Analog-to-Digital converter functions
 * \details	Implements the functions which configures ADC ports
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

/* Includes */
#include "ecuDrv_adc.h"

/* Begin functions implementation */

/** \defgroup ecuDrv_adc ADC driver
 *  \ingroup ecu_drivers
 *  Contains the functions to configure and read ADC pins
 */

/**
 * \ingroup  ecuDrv_adc
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
void ecuDrv_adc_Init(T_S_ADC_PORT *ls_Port, T_ULONG lul_ClockFrequency)
{
	ADC_Init(ls_Port, lul_ClockFrequency);
}

/**
 * \brief	De-initializes ADC peripheral
 * \param 	ls_Port ADC port structure
 * \return 	none
 */
void ecuDrv_adc_DeInit(T_S_ADC_PORT *ls_Port)
{
	ADC_DeInit(ls_Port);
}

/**
 * \brief	Reads an ADC channel
 * \param 	ls_Port ADC port structure
 * \param 	le_Channel ADC channel to read
 * \return 	none
 */
T_UWORD ecuDrv_adc_ReadChannelData(T_S_ADC_PORT *ls_Port, T_E_ADC_CHANNEL le_Channel)
{
	return ADC_ChannelGetData(ls_Port, (T_ULONG)le_Channel);
}

/**
 * \brief	Reads an ADC channel status
 * \param 	ls_Port ADC port structure
 * \param 	le_Channel ADC channel to read
 * \param 	le_StatusType Status type of the channel:
 * 							 - E_ADC_STATUS_BURST
 * 							 - E_ADC_STATUS_DONE
 * \return 	Status of the channel, based on status type
 */
T_E_STATUS ecuDrv_adc_ReadChannelStatus(T_S_ADC_PORT *ls_Port, T_E_ADC_CHANNEL le_Channel, T_E_ADC_CHANNEL_STATUS le_StatusType)
{
	return (T_E_STATUS)ADC_ChannelGetStatus(ls_Port, le_Channel, le_StatusType);
}

/**
 * \brief	Enable/Disable ADC burst mode
 * \param 	ls_Port ADC port structure
 * \param 	le_State Burst mode state to set
 * \return 	none
 */
void ecuDrv_adc_SetBurstMode(T_S_ADC_PORT *ls_Port, T_E_ENABLE le_State)
{
	 ADC_BurstCmd(ls_Port, le_State);
}

/**
 * \brief	Sets ADC start mode
 * \param 	ls_Port ADC port structure
 * \param 	le_Mode Start mode
 * \return 	none
 */
void ecuDrv_adc_SetStartMode(T_S_ADC_PORT *ls_Port, T_E_ADC_START_MODE le_Mode)
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
void ecuDrv_adc_SetInterruptState(T_S_ADC_PORT *ls_Port, T_E_ADC_IRQTYPE le_IRQType, T_E_ENABLE le_State)
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
void ecuDrv_adc_SetChannelState(T_S_ADC_PORT *ls_Port, T_E_ADC_CHANNEL le_Channel, T_E_ENABLE le_State)
{
	ADC_ChannelCmd(ls_Port, le_Channel, le_State);
}

/**
 * \brief	Configures ADC edge start
 * \param 	ls_Port ADC port structure
 * \param 	le_Edge Edge mode:
 * 					- E_ADC_EDGE_START_RISING
 * 					- E_ADC_EDGE_START_FALLING
 * \return 	none
 */
void ecuDrv_adc_SetEdgeStart(T_S_ADC_PORT *ls_Port, T_E_ADC_EDGE_START le_Edge)
{
	ADC_EdgeStartConfig(ls_Port, le_Edge);
}
/**@} end of group adc_functions */

