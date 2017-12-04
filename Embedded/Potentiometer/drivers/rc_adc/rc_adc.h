/**
 * \file	rc_adc.h
 * \brief	rc_adc header file
 * \details	Exports the functions used for ADC configuration and access.
 * \author	Cosmin Marcu
 * \date	27.06.2015
 * \version 1.0.1
 */

#ifndef RC_ADC_H_
#define RC_ADC_H_

/* Includes */
#include "rc_stdtypedefs.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_adc.h"

/**
 * @brief	Defines the ADC type
 */
typedef LPC_ADC_TypeDef	T_RCADC_PORT;

/**
 * @brief ADC Channels
 */
typedef enum E_RCADC_CHANNEL {
	E_RCADC_CHANNEL0 = 0,					//!< ADC Channel 0
	E_RCADC_CHANNEL1, 						//!< ADC Channel 1
	E_RCADC_CHANNEL2, 						//!< ADC Channel 2
	E_RCADC_CHANNEL3, 						//!< ADC Channel 3
	E_RCADC_CHANNEL4, 						//!< ADC Channel 4
	E_RCADC_CHANNEL5, 						//!< ADC Channel 5
	E_RCADC_CHANNEL6, 						//!< ADC Channel 6
	E_RCADC_CHANNEL7, 						//!< ADC Channel 7
} T_E_RCADC_CHANNEL;

/**
 * @brief ADC Channels Status
 */
typedef enum E_RCADC_CHANNEL_STATUS {
	E_RCADC_STATUS_BURST = 0,				//!< ADC Burst status
	E_RCADC_STATUS_DONE, 					//!< ADC Done status
} T_E_RCADC_CHANNEL_STATUS;

/**
 * @brief ADC interrupts type
 */
typedef enum E_RCADC_IRQTYPE
{
	E_RCADC_IRQ_CHANNEL0 = 0,				//!< Interrupt channel 0
	E_RCADC_IRQ_CHANNEL1,					//!< Interrupt channel 1
	E_RCADC_IRQ_CHANNEL2,					//!< Interrupt channel 2
	E_RCADC_IRQ_CHANNEL3,					//!< Interrupt channel 3
	E_RCADC_IRQ_CHANNEL4,					//!< Interrupt channel 4
	E_RCADC_IRQ_CHANNEL5,					//!< Interrupt channel 5
	E_RCADC_IRQ_CHANNEL6,					//!< Interrupt channel 6
	E_RCADC_IRQ_CHANNEL7,					//!< Interrupt channel 7
	E_RCADC_IRQ_GLOBAL						//!< Global interrupt
} T_E_RCADC_IRQTYPE;

/**
 * @brief ADC start mode
 */
typedef enum E_RCADC_START_MODE
{
	E_RCADC_START_CONTINUOUS = 0,			//!< Continuous mode
	E_RCADC_START_NOW,						//!< Start conversion now
	E_RCADC_START_ON_EINT0,					//!< Start conversion when the edge selected occurs on P2.10/EINT0
	E_RCADC_START_ON_CAP01,					//!< Start conversion when the edge selected occurs on P1.27/CAPTURE 0.1
	E_RCADC_START_ON_MAT01,					//!< Start conversion when the edge selected occurs on MATCH 0.1
	E_RCADC_START_ON_MAT03,					//!< Start conversion when the edge selected occurs on MATCH 0.3
	E_RCADC_START_ON_MAT10,					//!< Start conversion when the edge selected 27 occurs on MATCH 1.0
	E_RCADC_START_ON_MAT11					//!< Start conversion when the edge selected occurs on MATCH 1.1
} T_E_RCADC_START_MODE;

/**
 * @brief ADC Edge start config
 */
typedef enum E_RCADC_EDGE_START {
	E_RCADC_EDGE_START_RISING = 0,			//!< Rising edge
	E_RCADC_EDGE_START_FALLING, 			//!< Falling edge
} T_E_RCADC_EDGE_START;


/* Exported ADC functions group: */
extern void rcadc_Init(T_RCADC_PORT *ls_Port, T_ULONG lul_ClockFrequency);
extern void rcadc_DeInit(T_RCADC_PORT *ls_Port);
extern T_UWORD rcadc_ReadChannelData(T_RCADC_PORT *ls_Port, T_E_RCADC_CHANNEL le_Channel);
extern T_E_RC_STATUS rcadc_ReadChannelStatus(T_RCADC_PORT *ls_Port, T_E_RCADC_CHANNEL le_Channel, T_E_RCADC_CHANNEL_STATUS le_StatusType);
extern void rcadc_SetBurstMode(T_RCADC_PORT *ls_Port, T_E_RC_ENABLE le_State);
extern void rcadc_SetStartMode(T_RCADC_PORT *ls_Port, T_E_RCADC_START_MODE le_Mode);
extern void rcadc_SetInterruptState(T_RCADC_PORT *ls_Port, T_E_RCADC_IRQTYPE le_IRQType, T_E_RC_ENABLE le_State);
extern void rcadc_SetChannelState(T_RCADC_PORT *ls_Port, T_E_RCADC_CHANNEL le_Channel, T_E_RC_ENABLE le_State);
extern void rcadc_SetEdgeStart(T_RCADC_PORT *ls_Port, T_E_RCADC_EDGE_START le_Edge);

#endif /* RC_ADC_H_ */
