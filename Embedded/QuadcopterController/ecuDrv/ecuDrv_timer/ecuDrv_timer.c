/**
 * \file	ecuDrv_timer.c
 * \brief	Timer configuration functions
 * \details	Implements the functions for Timer configuration
 * \author	Cosmin Marcu
 * \date	19.06.2017
 * \version 1.0.1
 */

/* Includes */
#include "lpc17xx_timer.h"
#include "ecuDrv_timer.h"

/* Begin functions implementation */

/** \defgroup ecuDrv_timer Timer driver
 *  \ingroup ecu_drivers
 *   Contains the functions to set the Timers attributes
 */

/**
 * \ingroup  ecuDrv_timer
 * \defgroup timer_functions Timer Functions
 *  Functions definitions for the timer attributes
 *  @{
 */

PRIVATE_DATA VOLATILE T_ULONG rul_ecuDrv_timer_Timer1_TimeMs = 0ul;			//!< Counter for Timer1

/* Timer functions group: */
/**
 * \brief 	Initializes Timer.
 * \param	ps_Timer	Pointer to LPC_TIMx structure
 * \param	le_Mode		Timer mode (Timer or Counter)
 * \param	ps_Config	Pointer to config structure
 * \return	none
 */
void ecuDrv_timer_Init(T_S_TMR_PORT *ps_Timer, T_E_TMR_MODE le_Mode, void *ps_Config)
{
	TIM_Init(ps_Timer, le_Mode, ps_Config);
}

/**
 * \brief 	De-Initializes a Timer.
 * \param	ps_Timer Pointer to LPC_TIMx structure
 * \return	none
 */
void ecuDrv_timer_DeInit(T_S_TMR_PORT *ps_Timer)
{
	TIM_DeInit(ps_Timer);
}

/**
 * \brief 	Configures Timer state.
 * \param	ps_Timer	Pointer to LPC_TIMx structure
 * \param	le_State	New timer state
 * \return	none
 */
void ecuDrv_timer_SetTimerState(T_S_TMR_PORT *ps_Timer, T_E_ENABLE le_State)
{
	TIM_Cmd(ps_Timer, le_State);
}

/**
 * \brief 	Reads a Timer interrupt state.
 * \param	ps_Timer	Pointer to LPC_TIMx structure
 * \param	le_IRQType	Timer interrupt type
 * \return	State of the interrupt (Or or Off)
 */
T_E_SIGNAL_STATE ecuDrv_timer_GetTimerInterruptStatus(T_S_TMR_PORT *ps_Timer, T_E_TMR_IRQTYPE le_IRQType)
{
	return (T_E_SIGNAL_STATE)TIM_GetIntStatus(ps_Timer, (T_UBYTE)le_IRQType);
}

/**
 * \brief 	Reads a Timer capture interrupt state.
 * \param	ps_Timer	Pointer to LPC_TIMx structure
 * \param	le_IRQType	Timer interrupt type
 * \return	State of the interrupt (Or or Off)
 */
T_E_SIGNAL_STATE ecuDrv_timer_GetCaptureInterruptStatus(T_S_TMR_PORT *ps_Timer, T_E_TMR_IRQTYPE le_IRQType)
{
	return (T_E_SIGNAL_STATE)TIM_GetIntCaptureStatus(ps_Timer, (T_UBYTE)le_IRQType);
}

/**
 * \brief 	Clears a timer pending interrupt.
 * \param	ps_Timer	Pointer to LPC_TIMx structure
 * \param	le_IRQType	Timer interrupt type
 * \return	None
 */
void ecuDrv_timer_ClearTimerInterrupt(T_S_TMR_PORT *ps_Timer, T_E_TMR_IRQTYPE le_IRQType)
{
	TIM_ClearIntPending(ps_Timer, (T_UBYTE)le_IRQType);
}

/**
 * \brief 	Clears a capture pending interrupt.
 * \param	ps_Timer	Pointer to LPC_TIMx structure
 * \param	le_IRQType	Timer interrupt type
 * \return	None
 */
void ecuDrv_timer_ClearCaptureInterrupt(T_S_TMR_PORT *ps_Timer, T_E_TMR_IRQTYPE le_IRQType)
{
	TIM_ClearIntCapturePending(ps_Timer, (T_UBYTE)le_IRQType);
}

/**
 * \brief 	Initialize timer configuration structure.
 * \param	le_Prescale	Prescale option
 * \param	pvs_Config	Pointer to configuration structure
 * \return	None
 */
void ecuDrv_timer_InitConfig(T_E_TMR_PRESCALE_OPT le_Prescale, void *pvs_Config)
{
	TIM_ConfigStructInit(le_Prescale, pvs_Config);
}

/**
 * \brief 	Reset timer counter.
 * \param	ps_Timer Pointer to LPC_TIMx structure
 * \return	None
 */
void ecuDrv_timer_ResetCounter(T_S_TMR_PORT *ps_Timer)
{
	TIM_ResetCounter(ps_Timer);
}

/**
 * \brief 	Configures timer match.
 * \param	ps_Timer Pointer to LPC_TIMx structure
 * \param	ls_MatchConfig	Match configuration structure
 * \return	None
 */
void ecuDrv_timer_ConfigMatch(T_S_TMR_PORT *ps_Timer, T_S_TMR_MATCH_CONFIG ls_MatchConfig)
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
void ecuDrv_timer_ConfigCapture(T_S_TMR_PORT *ps_Timer, T_S_TMR_CAPTURE_CONFIG ls_CaptureConfig)
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
T_ULONG ecuDrv_timer_GetCaptureValue(T_S_TMR_PORT *ps_Timer, T_E_TMR_CAPTURE le_CaptureChannel)
{
	return TIM_GetCaptureValue(ps_Timer, le_CaptureChannel);
}

/**
 * \brief 	Initializes Timer1.
 * \return	None
 */
void ecuDrv_timer_Timer1_Init(void)
{
	  TIM_TIMERCFG_Type TIM_ConfigStruct;
	  TIM_MATCHCFG_Type TIM_MatchConfigStruct ;

	  // Initialize timer 0, prescale count time of 100uS
	  TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
	  TIM_ConfigStruct.PrescaleValue  = 100;

	  // use channel 0, MR0
	  TIM_MatchConfigStruct.MatchChannel = 0;
	  // Enable interrupt when MR0 matches the value in TC register
	  TIM_MatchConfigStruct.IntOnMatch   = TRUE;
	  //Enable reset on MR0: TIMER will reset if MR0 matches it
	  TIM_MatchConfigStruct.ResetOnMatch = TRUE;
	  //Stop on MR0 if MR0 matches it
	  TIM_MatchConfigStruct.StopOnMatch  = FALSE;
	  //Toggle MR0.0 pin if MR0 matches it
	  TIM_MatchConfigStruct.ExtMatchOutputType =TIM_EXTMATCH_NOTHING;
	  // Set Match value, count value of 10 (10 * 100uS = 1000uS = 1ms --> 1000 Hz)
	  TIM_MatchConfigStruct.MatchValue   = 10;

	  TIM_Init(LPC_TIM1, TIM_TIMER_MODE,&TIM_ConfigStruct);
	  TIM_ConfigMatch(LPC_TIM1,&TIM_MatchConfigStruct);

	  NVIC_EnableIRQ(TIMER1_IRQn);
	  // To start timer 0
	  TIM_Cmd(LPC_TIM1,ENABLE);
}

/**
 * \brief 	Interrupt handler for Timer1 (triggered every 1 ms).
 * \return	None
 */
void ecuDrv_timer_Timer1_IRQHandler(void)
{
	rul_ecuDrv_timer_Timer1_TimeMs++;
	TIM_ClearIntPending(LPC_TIM1, TIM_MR0_INT);
}

/**
 * \brief 	Gets current value of the Timer1 counter.
 * \return	Timer current value
 */
T_ULONG ecuDrv_timer_GetTimer1_value(void)
{
	return (rul_ecuDrv_timer_Timer1_TimeMs);
}
/**@} end of group timer_functions */

