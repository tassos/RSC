/**
 * \file	rc_timer.h
 * \brief	rc_timer header file
 * \details	Exports the functions used for timer attributes.
 * \author	Cosmin Marcu
 * \date	19.06.2015
 * \version 1.0.1
 */

#ifndef RC_TIMER_H_
#define RC_TIMER_H_

/* Includes */
#include "rc_stdtypedefs.h"

/**
 * @brief	Defines the TIMER type
 */
typedef LPC_TIM_TypeDef	T_RCTMR_PORT;

/**
 * @brief Timer mode
 */
typedef enum E_RCTMR_MODE {
	E_RCTMR_MODE_TIMER = 0,					//!< Timer mode
	E_RCTMR_MODE_COUNTER_RISING,			//!< Counter rising edge mode
	E_RCTMR_MODE_COUNTER_FALLING,			//!< Counter falling edge mode
	E_RCTMR_MODE_COUNTER_ANY				//!< Counter any mode
} T_E_RCTMR_MODE;

/**
 * @brief Timer prescale option
 */
typedef enum E_RCTMR_PRESCALE_OPT {
	E_RCTMR_PRESCALE_TICKVAL = 0,			//!< Prescale in absolute value
	E_RCTMR_PRESCALE_USVAL					//!< Prescale in microsecond value
} T_E_RCTMR_PRESCALE_OPT;

/**
 * @brief Match channels
 */
typedef enum E_RCTMR_MATCH {
	E_RCTMR_MATCH0 = 0,						//!< Timer match 0
	E_RCTMR_MATCH1,							//!< Timer match 1
	E_RCTMR_MATCH2,							//!< Timer match 2
	E_RCTMR_MATCH3							//!< Timer match 3
} T_E_RCTMR_MATCH;

/**
 * @brief External Match options
 */
typedef enum E_RCTMR_EXTMATCH {
	E_RCTMR_EXTMATCH_NONE = 0,				//!< Do nothing for external output pin if match
	E_RCTMR_EXTMATCH_LOW,					//!< Force external output pin to low if match
	E_RCTMR_EXTMATCH_HIGH,					//!< Force external output pin to high if match
	E_RCTMR_EXTMATCH_TOGGLE					//!< Toggle external output pin if match
} T_E_RCTMR_EXTMATCH;

/**
 * @brief Capture channels
 */
typedef enum E_RCTMR_CAPTURE {
	E_RCTMR_CAPTURE0 = 0,					//!< Capture channel 0
	E_RCTMR_CAPTURE1,						//!< Capture channel 1
} T_E_RCTMR_CAPTURE;

/**
 * @brief Timer Interrupt types
 */
typedef enum E_RCTMR_IRQTYPE
{
	E_RCTMR_IRQ_MR0 = 0, 					//!< Interrupt for Match channel 0
	E_RCTMR_IRQ_MR1,	 					//!< Interrupt for Match channel 1
	E_RCTMR_IRQ_MR2,	 					//!< Interrupt for Match channel 2
	E_RCTMR_IRQ_MR3,	 					//!< Interrupt for Match channel 3
	E_RCTMR_IRQ_CR0,	 					//!< Interrupt for Capture channel 0
	E_RCTMR_IRQ_CR1,	 					//!< Interrupt for Capture channel 1
} T_E_RCTMR_IRQTYPE;

/**
 * @brief Timer configuration structure
 */
typedef struct {
	T_E_RCTMR_PRESCALE_OPT ub_PrescaleOption;	//!< Timer prescale mode
	T_UBYTE aub_Reserved[3u];					//!< Reserved
	T_ULONG ul_PrescaleValue;					//!< Prescale value
} T_RCTMR_TIMER_CONFIG;

/**
 * @brief Counter configuration structure
 */
typedef struct {
	T_UBYTE ub_CounterOption;				//!< Counter option
	T_UBYTE ub_CountInputSelect;			//!< Counter input select
	T_UBYTE aub_Reserved[2];				//!< Reserved
} T_RCTMR_COUNTER_CONFIG;

/**
 * @brief Match configuration structure
 */
typedef struct {
	T_E_RCTMR_MATCH e_MatchChannel;			//!< Match channel number
	T_E_RC_ENABLE e_IRQOnMatch;				//!< Interrupt On match
	T_E_RC_ENABLE e_StopOnMatch;			//!< Stop On match
	T_E_RC_ENABLE e_ResetOnMatch;			//!< Reset On match
	T_E_RCTMR_EXTMATCH e_ExtMatch;			//!< External Match Output type
	T_UBYTE aub_Reserved[3];				//!< Reserved
	T_ULONG ul_MatchValue;					//!< Match value
} T_RCTMR_MATCH_CONFIG;

/**
 * @brief Capture configuration structure
 */
typedef struct {
	T_E_RCTMR_CAPTURE e_CaptureChannel;		//!< Capture channel
	T_E_RC_ENABLE e_RisingEdge;				//!< Caption rising edge
	T_E_RC_ENABLE e_FallingEdge;			//!< Caption falling edge
	T_E_RC_ENABLE e_IRQOnCaption;			//!< Interrupt On caption
} T_RCTMR_CAPTURE_CONFIG;

/* Exported timer functions group: */
extern void rctimer_Init(T_RCTMR_PORT *ps_Timer, T_E_RCTMR_MODE le_Mode, void *pvs_Config);
extern void rctimer_DeInit(T_RCTMR_PORT *ps_Timer);
extern void rctimer_SetTimerState(T_RCTMR_PORT *ps_Timer, T_E_RC_ENABLE le_State);
extern T_E_RC_SIGNAL_STATE rctimer_GetTimerInterruptStatus(T_RCTMR_PORT *ps_Timer, T_E_RCTMR_IRQTYPE le_IRQType);
extern T_E_RC_SIGNAL_STATE rctimer_GetCaptureInterruptStatus(T_RCTMR_PORT *ps_Timer, T_E_RCTMR_IRQTYPE le_IRQType);
extern void rctimer_ClearTimerInterrupt(T_RCTMR_PORT *ps_Timer, T_E_RCTMR_IRQTYPE le_IRQType);
extern void rctimer_ClearCaptureInterrupt(T_RCTMR_PORT *ps_Timer, T_E_RCTMR_IRQTYPE le_IRQType);
extern void rctimer_InitConfig(T_E_RCTMR_PRESCALE_OPT le_Prescale, void *pvs_Config);
extern void rctimer_ResetCounter(T_RCTMR_PORT *ps_Timer);
extern void rctimer_ConfigMatch(T_RCTMR_PORT *ps_Timer, T_RCTMR_MATCH_CONFIG ls_MatchConfig);
extern void rctimer_ConfigCapture(T_RCTMR_PORT *ps_Timer, T_RCTMR_CAPTURE_CONFIG ls_CaptureConfig);
extern T_ULONG rctimer_GetCaptureValue(T_RCTMR_PORT *ps_Timer, T_E_RCTMR_CAPTURE le_CaptureChannel);

#endif /* RC_TIMER_H_ */
