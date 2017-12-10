/**
 * \file	ecuDrv_adc.h
 * \brief	ecuDrv_adc header file
 * \details	Exports the functions used for ADC configuration and access.
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

#ifndef ECUDRV_ADC_H_
#define ECUDRV_ADC_H_

/* Includes */
#include "ecuConfig_Types.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"

/**
 * @brief	Defines the ADC type
 */
typedef LPC_ADC_TypeDef	T_S_ADC_PORT;

/**
 * @brief ADC Channels
 */
typedef enum E_ADC_CHANNEL {
	E_ADC_CHANNEL0 = 0,						//!< ADC Channel 0
	E_ADC_CHANNEL1, 						//!< ADC Channel 1
	E_ADC_CHANNEL2, 						//!< ADC Channel 2
	E_ADC_CHANNEL3, 						//!< ADC Channel 3
	E_ADC_CHANNEL4, 						//!< ADC Channel 4
	E_ADC_CHANNEL5, 						//!< ADC Channel 5
	E_ADC_CHANNEL6, 						//!< ADC Channel 6
	E_ADC_CHANNEL7, 						//!< ADC Channel 7
} T_E_ADC_CHANNEL;

/**
 * @brief ADC Channels Status
 */
typedef enum E_ADC_CHANNEL_STATUS {
	E_ADC_STATUS_BURST = 0,					//!< ADC Burst status
	E_ADC_STATUS_DONE, 						//!< ADC Done status
} T_E_ADC_CHANNEL_STATUS;

/**
 * @brief ADC interrupts type
 */
typedef enum E_ADC_IRQTYPE
{
	E_ADC_IRQ_CHANNEL0 = 0,				    //!< Interrupt channel 0
	E_ADC_IRQ_CHANNEL1,					    //!< Interrupt channel 1
	E_ADC_IRQ_CHANNEL2,					    //!< Interrupt channel 2
	E_ADC_IRQ_CHANNEL3,					    //!< Interrupt channel 3
	E_ADC_IRQ_CHANNEL4,					    //!< Interrupt channel 4
	E_ADC_IRQ_CHANNEL5,					    //!< Interrupt channel 5
	E_ADC_IRQ_CHANNEL6,					    //!< Interrupt channel 6
	E_ADC_IRQ_CHANNEL7,					    //!< Interrupt channel 7
	E_ADC_IRQ_GLOBAL						//!< Global interrupt
} T_E_ADC_IRQTYPE;

/**
 * @brief ADC start mode
 */
typedef enum E_ADC_START_MODE
{
	E_ADC_START_CONTINUOUS = 0,				//!< Continuous mode
	E_ADC_START_NOW,						//!< Start conversion now
	E_ADC_START_ON_EINT0,					//!< Start conversion when the edge selected occurs on P2.10/EINT0
	E_ADC_START_ON_CAP01,					//!< Start conversion when the edge selected occurs on P1.27/CAPTURE 0.1
	E_ADC_START_ON_MAT01,					//!< Start conversion when the edge selected occurs on MATCH 0.1
	E_ADC_START_ON_MAT03,					//!< Start conversion when the edge selected occurs on MATCH 0.3
	E_ADC_START_ON_MAT10,					//!< Start conversion when the edge selected 27 occurs on MATCH 1.0
	E_ADC_START_ON_MAT11					//!< Start conversion when the edge selected occurs on MATCH 1.1
} T_E_ADC_START_MODE;

/**
 * @brief ADC Edge start config
 */
typedef enum E_ADC_EDGE_START {
	E_ADC_EDGE_START_RISING = 0,			//!< Rising edge
	E_ADC_EDGE_START_FALLING, 				//!< Falling edge
} T_E_ADC_EDGE_START;


/* Exported ADC functions group: */
extern void ecuDrv_adc_Init(T_S_ADC_PORT *ls_Port, T_ULONG lul_ClockFrequency);
extern void ecuDrv_adc_DeInit(T_S_ADC_PORT *ls_Port);
extern T_UWORD ecuDrv_adc_ReadChannelData(T_S_ADC_PORT *ls_Port, T_E_ADC_CHANNEL le_Channel);
extern T_E_STATUS ecuDrv_adc_ReadChannelStatus(T_S_ADC_PORT *ls_Port, T_E_ADC_CHANNEL le_Channel, T_E_ADC_CHANNEL_STATUS le_StatusType);
extern void ecuDrv_adc_SetBurstMode(T_S_ADC_PORT *ls_Port, T_E_ENABLE le_State);
extern void ecuDrv_adc_SetStartMode(T_S_ADC_PORT *ls_Port, T_E_ADC_START_MODE le_Mode);
extern void ecuDrv_adc_SetInterruptState(T_S_ADC_PORT *ls_Port, T_E_ADC_IRQTYPE le_IRQType, T_E_ENABLE le_State);
extern void ecuDrv_adc_SetChannelState(T_S_ADC_PORT *ls_Port, T_E_ADC_CHANNEL le_Channel, T_E_ENABLE le_State);
extern void ecuDrv_adc_SetEdgeStart(T_S_ADC_PORT *ls_Port, T_E_ADC_EDGE_START le_Edge);

#endif /* ECUDRV_ADC_H_ */
