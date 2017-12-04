/**
 * \file	rc_timer.c
 * \brief	Timer configuration functions
 * \details	Implements the functions for Timer configuration
 * \author	Cosmin Marcu
 * \date	19.06.2015
 * \version 1.0.1
 */

/* Includes */
#include "rc_timer.h"
#include "lpc17xx_timer.h"

/* Begin functions implementation */

/** \defgroup rc_timer Timer driver
  Contains the functions to set the Timers attributes
*/

/**
 * \ingroup  rc_timer
 * \defgroup Timer_functions Timer Functions
 *  Functions definitions for the timer attributes
 *  @{
 */
/* Timer functions group: */
/**
 * \brief 	Initializes Timer.
 * \param	ps_Timer	Pointer to LPC_TIMx structure
 * \param	le_Mode		Timer mode (Timer or Counter)
 * \param	ps_Config	Pointer to config structure
 * \return	none
 */
void rctimer_Init(T_RCTMR_PORT *ps_Timer, T_E_RCTMR_MODE le_Mode, void *ps_Config)
{
	TIM_Init(ps_Timer, le_Mode, ps_Config);
}

/**
 * \brief 	De-Initializes a Timer.
 * \param	ps_Timer Pointer to LPC_TIMx structure
 * \return	none
 */
void rctimer_DeInit(T_RCTMR_PORT *ps_Timer)
{
	TIM_DeInit(ps_Timer);
}

/**
 * \brief 	Configures Timer state.
 * \param	ps_Timer	Pointer to LPC_TIMx structure
 * \param	le_State	New timer state
 * \return	none
 */
void rctimer_SetTimerState(T_RCTMR_PORT *ps_Timer, T_E_RC_ENABLE le_State)
{
	TIM_Cmd(ps_Timer, le_State);
}

/**
 * \brief 	Reads a Timer interrupt state.
 * \param	ps_Timer	Pointer to LPC_TIMx structure
 * \param	le_IRQType	Timer interrupt type
 * \return	State of the interrupt (Or or Off)
 */
T_E_RC_SIGNAL_STATE rctimer_GetTimerInterruptStatus(T_RCTMR_PORT *ps_Timer, T_E_RCTMR_IRQTYPE le_IRQType)
{
	return (T_E_RC_SIGNAL_STATE)TIM_GetIntStatus(ps_Timer, (T_UBYTE)le_IRQType);
}

/**
 * \brief 	Reads a Timer capture interrupt state.
 * \param	ps_Timer	Pointer to LPC_TIMx structure
 * \param	le_IRQType	Timer interrupt type
 * \return	State of the interrupt (Or or Off)
 */
T_E_RC_SIGNAL_STATE rctimer_GetCaptureInterruptStatus(T_RCTMR_PORT *ps_Timer, T_E_RCTMR_IRQTYPE le_IRQType)
{
	return (T_E_RC_SIGNAL_STATE)TIM_GetIntCaptureStatus(ps_Timer, (T_UBYTE)le_IRQType);
}

/**
 * \brief 	Clears a timer pending interrupt.
 * \param	ps_Timer	Pointer to LPC_TIMx structure
 * \param	le_IRQType	Timer interrupt type
 * \return	None
 */
void rctimer_ClearTimerInterrupt(T_RCTMR_PORT *ps_Timer, T_E_RCTMR_IRQTYPE le_IRQType)
{
	TIM_ClearIntPending(ps_Timer, (T_UBYTE)le_IRQType);
}

/**
 * \brief 	Clears a capture pending interrupt.
 * \param	ps_Timer	Pointer to LPC_TIMx structure
 * \param	le_IRQType	Timer interrupt type
 * \return	None
 */
void rctimer_ClearCaptureInterrupt(T_RCTMR_PORT *ps_Timer, T_E_RCTMR_IRQTYPE le_IRQType)
{
	TIM_ClearIntCapturePending(ps_Timer, (T_UBYTE)le_IRQType);
}

/**
 * \brief 	Initialize timer configuration structure.
 * \param	le_Prescale	Prescale option
 * \param	pvs_Config	Pointer to configuration structure
 * \return	None
 */
void rctimer_InitConfig(T_E_RCTMR_PRESCALE_OPT le_Prescale, void *pvs_Config)
{
	TIM_ConfigStructInit(le_Prescale, pvs_Config);
}

/**
 * \brief 	Reset timer counter.
 * \param	ps_Timer Pointer to LPC_TIMx structure
 * \return	None
 */
void rctimer_ResetCounter(T_RCTMR_PORT *ps_Timer)
{
	TIM_ResetCounter(ps_Timer);
}

/**
 * \brief 	Configures timer match.
 * \param	ps_Timer Pointer to LPC_TIMx structure
 * \param	ls_MatchConfig	Match configuration structure
 * \return	None
 */
void rctimer_ConfigMatch(T_RCTMR_PORT *ps_Timer, T_RCTMR_MATCH_CONFIG ls_MatchConfig)
{
	TIM_MATCHCFG_Type TMR_MatchConfig[1u];

	/* Fill Timer match config structure */
	TMR_MatchConfig[0u].MatchChannel = ls_MatchConfig.e_MatchChannel;
	TMR_MatchConfig[0u].IntOnMatch = ls_MatchConfig.e_IRQOnMatch;
	TMR_MatchConfig[0u].StopOnMatch = ls_MatchConfig.e_StopOnMatch;
	TMR_MatchConfig[0u].ResetOnMatch = ls_MatchConfig.e_StopOnMatch;
	TMR_MatchConfig[0u].ExtMatchOutputType = ls_MatchConfig.e_ExtMatch;
	TMR_MatchConfig[0u].MatchValue = ls_MatchConfig.ul_MatchValue;

	TIM_ConfigMatch(ps_Timer, TMR_MatchConfig);
}

/**
 * \brief 	Configures timer capture.
 * \param	ps_Timer Pointer to LPC_TIMx structure
 * \param	ls_CaptureConfig Capture configuration structure
 * \return	None
 */
void rctimer_ConfigCapture(T_RCTMR_PORT *ps_Timer, T_RCTMR_CAPTURE_CONFIG ls_CaptureConfig)
{
	TIM_CAPTURECFG_Type TMR_CaptureConfig[1u];

	/* Fill Timer capture config structure */
	TMR_CaptureConfig[0u].CaptureChannel = ls_CaptureConfig.e_CaptureChannel;
	TMR_CaptureConfig[0u].IntOnCaption = ls_CaptureConfig.e_IRQOnCaption;
	TMR_CaptureConfig[0u].FallingEdge = ls_CaptureConfig.e_FallingEdge;
	TMR_CaptureConfig[0u].RisingEdge = ls_CaptureConfig.e_RisingEdge;

	TIM_ConfigCapture(ps_Timer, TMR_CaptureConfig);
}

/**
 * \brief 	Gets current capture value.
 * \param	ps_Timer Pointer to LPC_TIMx structure
 * \param	le_CaptureChannel Timer capture channel to be read
 * \return	None
 */
T_ULONG rctimer_GetCaptureValue(T_RCTMR_PORT *ps_Timer, T_E_RCTMR_CAPTURE le_CaptureChannel)
{
	return TIM_GetCaptureValue(ps_Timer, le_CaptureChannel);
}

/*@} end of group Pinsel_functions */

