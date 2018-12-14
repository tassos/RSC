/**
 * \file	ecuDrv_timer.h
 * \brief	ecuDrv_timer header file
 * \details	Exports the functions used for timer attributes.
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

#ifndef ECUDRV_TIMER_H_
#define ECUDRV_TIMER_H_

/* Includes */
#include "ecuConfig_Types.h"

/**
 * @brief	Defines the TIMER type
 */
typedef LPC_TIM_TypeDef	T_S_TMR_PORT;

/**
 * @brief Timer mode
 */
typedef enum E_TMR_MODE {
	E_TMR_MODE_TIMER = 0,					//!< Timer mode
	E_TMR_MODE_COUNTER_RISING,				//!< Counter rising edge mode
	E_TMR_MODE_COUNTER_FALLING,				//!< Counter falling edge mode
	E_TMR_MODE_COUNTER_ANY					//!< Counter any mode
} T_E_TMR_MODE;

/**
 * @brief Timer prescale option
 */
typedef enum E_TMR_PRESCALE_OPT {
	E_TMR_PRESCALE_TICKVAL = 0,				//!< Prescale in absolute value
	E_TMR_PRESCALE_USVAL					//!< Prescale in microsecond value
} T_E_TMR_PRESCALE_OPT;

/**
 * @brief Match channels
 */
typedef enum E_TMR_MATCH {
	E_TMR_MATCH0 = 0,						//!< Timer match 0
	E_TMR_MATCH1,							//!< Timer match 1
	E_TMR_MATCH2,							//!< Timer match 2
	E_TMR_MATCH3							//!< Timer match 3
} T_E_TMR_MATCH;

/**
 * @brief External Match options
 */
typedef enum E_TMR_EXTMATCH {
	E_TMR_EXTMATCH_NONE = 0,				//!< Do nothing for external output pin if match
	E_TMR_EXTMATCH_LOW,						//!< Force external output pin to low if match
	E_TMR_EXTMATCH_HIGH,					//!< Force external output pin to high if match
	E_TMR_EXTMATCH_TOGGLE					//!< Toggle external output pin if match
} T_E_TMR_EXTMATCH;

/**
 * @brief Capture channels
 */
typedef enum E_TMR_CAPTURE {
	E_TMR_CAPTURE0 = 0,						//!< Capture channel 0
	E_TMR_CAPTURE1,							//!< Capture channel 1
} T_E_TMR_CAPTURE;

/**
 * @brief Timer Interrupt types
 */
typedef enum E_TMR_IRQTYPE
{
	E_TMR_IRQ_MR0 = 0, 						//!< Interrupt for Match channel 0
	E_TMR_IRQ_MR1,	 						//!< Interrupt for Match channel 1
	E_TMR_IRQ_MR2,	 						//!< Interrupt for Match channel 2
	E_TMR_IRQ_MR3,	 						//!< Interrupt for Match channel 3
	E_TMR_IRQ_CR0,	 						//!< Interrupt for Capture channel 0
	E_TMR_IRQ_CR1,	 						//!< Interrupt for Capture channel 1
} T_E_TMR_IRQTYPE;

/**
 * @brief Timer configuration structure
 */
typedef struct {
	T_E_TMR_PRESCALE_OPT ub_PrescaleOption;		//!< Timer prescale mode
	T_UBYTE aub_Reserved[3u];					//!< Reserved
	T_ULONG ul_PrescaleValue;					//!< Prescale value
} T_S_TMR_TIMER_CONFIG;

/**
 * @brief Counter configuration structure
 */
typedef struct {
	T_UBYTE ub_CounterOption;				//!< Counter option
	T_UBYTE ub_CountInputSelect;			//!< Counter input select
	T_UBYTE aub_Reserved[2u];				//!< Reserved
} T_S_TMR_COUNTER_CONFIG;

/**
 * @brief Match configuration structure
 */
typedef struct {
	T_E_TMR_MATCH e_MatchChannel;			//!< Match channel number
	T_E_ENABLE e_IRQOnMatch;				//!< Interrupt On match
	T_E_ENABLE e_StopOnMatch;				//!< Stop On match
	T_E_ENABLE e_ResetOnMatch;				//!< Reset On match
	T_E_TMR_EXTMATCH e_ExtMatch;			//!< External Match Output type
	T_UBYTE aub_Reserved[3u];				//!< Reserved
	T_ULONG ul_MatchValue;					//!< Match value
} T_S_TMR_MATCH_CONFIG;

/**
 * @brief Capture configuration structure
 */
typedef struct {
	T_E_TMR_CAPTURE e_CaptureChannel;		//!< Capture channel
	T_E_ENABLE e_RisingEdge;				//!< Caption rising edge
	T_E_ENABLE e_FallingEdge;				//!< Caption falling edge
	T_E_ENABLE e_IRQOnCaption;				//!< Interrupt On caption
} T_S_TMR_CAPTURE_CONFIG;

/* Exported timer functions group: */
extern void ecuDrv_timer_Init(T_S_TMR_PORT *ps_Timer, T_E_TMR_MODE le_Mode, void *pvs_Config);
extern void ecuDrv_timer_DeInit(T_S_TMR_PORT *ps_Timer);
extern void ecuDrv_timer_SetTimerState(T_S_TMR_PORT *ps_Timer, T_E_ENABLE le_State);
extern T_E_SIGNAL_STATE ecuDrv_timer_GetTimerInterruptStatus(T_S_TMR_PORT *ps_Timer, T_E_TMR_IRQTYPE le_IRQType);
extern T_E_SIGNAL_STATE ecuDrv_timer_GetCaptureInterruptStatus(T_S_TMR_PORT *ps_Timer, T_E_TMR_IRQTYPE le_IRQType);
extern void ecuDrv_timer_ClearTimerInterrupt(T_S_TMR_PORT *ps_Timer, T_E_TMR_IRQTYPE le_IRQType);
extern void ecuDrv_timer_ClearCaptureInterrupt(T_S_TMR_PORT *ps_Timer, T_E_TMR_IRQTYPE le_IRQType);
extern void ecuDrv_timer_InitConfig(T_E_TMR_PRESCALE_OPT le_Prescale, void *pvs_Config);
extern void ecuDrv_timer_ResetCounter(T_S_TMR_PORT *ps_Timer);
extern void ecuDrv_timer_ConfigMatch(T_S_TMR_PORT *ps_Timer, T_S_TMR_MATCH_CONFIG ls_MatchConfig);
extern void ecuDrv_timer_ConfigCapture(T_S_TMR_PORT *ps_Timer, T_S_TMR_CAPTURE_CONFIG ls_CaptureConfig);
extern T_ULONG ecuDrv_timer_GetCaptureValue(T_S_TMR_PORT *ps_Timer, T_E_TMR_CAPTURE le_CaptureChannel);

extern void ecuDrv_timer_Timer1_Init(void);
extern void ecuDrv_timer_Timer1_IRQHandler(void);
extern T_ULONG ecuDrv_timer_GetTimer1_value(void);

#endif /* ECUDRV_TIMER_H_ */
