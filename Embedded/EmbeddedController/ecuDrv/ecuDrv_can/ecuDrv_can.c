/**
 * \file	ecuDrv_can.c
 * \brief	Implements the interface functions with the CAN drivers
 * \details	Implements the functions which configures the CAN peripheral
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

/* Includes */
#include "ecuDrv_can.h"

/* Begin functions implementation */

/** \defgroup ecuDrv_can CAN driver
 *  \ingroup ecu_drivers
 *   Contains the functions to set and access the CAN peripheral
 */

/**
 * \ingroup  ecuDrv_can
 * \defgroup can_functions CAN Functions
 *  Functions definitions for the CAN peripheral setup
 *  @{
 */
/* CAN functions group: */
/**
 * \brief	Initialize the CAN peripheral
 * \param	ps_Port	CAN port to be initialized
 * \param	lul_Baudrate Baud rate for the CAN port
 * \return 	none
 */
void ecuDrv_can_Init(T_S_CAN_PORT *ps_Port, T_ULONG lul_Baudrate)
{
	CAN_Init(ps_Port, lul_Baudrate);
}

/**
 * \brief	De-initializes CAN peripheral
 * \param 	ps_Port CAN port structure
 * \return 	none
 */
void ecuDrv_can_DeInit(T_S_CAN_PORT *ps_Port)
{
	CAN_DeInit(ps_Port);
}

/**
 * \brief 	Configures an interrupt on CAN.
 * \param	ps_Port				Pointer to LPC_CANx port structure
 * \param 	le_CAN_IRQType		IRQ Type
 * \param	le_CAN_IRQState		IRQ State
 * \return	none
 */
void ecuDrv_can_SetInterrupt(T_S_CAN_PORT *ps_Port, T_E_CAN_IRQTYPE le_CAN_IRQType, T_E_ENABLE le_CAN_IRQState)
{
	CAN_IRQCmd(ps_Port, (CAN_INT_EN_Type)le_CAN_IRQType, (FunctionalState)le_CAN_IRQState);
}

/**
 * \brief 	Gets the CAN Interrupt status
 * \param	ps_Port	Pointer to LPC_CANx port structure
 * \return	Interrupt status
 */
T_ULONG ecuDrv_can_GetInterruptStatus(T_S_CAN_PORT *ps_Port)
{
	return CAN_IntGetStatus(ps_Port);
}

/**
 * \brief 	Configures CAN Acceptance Filter type
 * \param	ps_CAN_AF			Pointer to LPC_CANAF structure
 * \param 	le_CAN_AFMode		Acceptance Filter mode
 * \return	none
 */
void ecuDrv_can_SetAFMode(T_S_CAN_AF *ps_CAN_AF, T_E_CAN_AFMODE le_CAN_AFMode)
{
	CAN_SetAFMode(ps_CAN_AF, (CAN_AFMODE_Type)le_CAN_AFMode);
}

/**
 * \brief	Sends a message to CAN
 * \param	ps_Port	CAN port to be used
 * \param	ps_Message CAN Message structure
 * \return 	E_SUCCESS if message has been sent
 * 			E_ERROR if message send failed
 */
T_E_ERROR ecuDrv_can_SendMessage(T_S_CAN_PORT *ps_Port, T_S_CAN_MESSAGE *ps_Message)
{
	T_E_ERROR le_Status = E_ERROR;

	/* Return values of CAN_SendMsg are reversed */
	if (1u == CAN_SendMsg(ps_Port, (CAN_MSG_Type *)ps_Message))
	{
		le_Status = E_SUCCESS;
	}
	return le_Status;
}

/**
 * \brief	Gets a message from CAN
 * \param	ps_Port	CAN port to be used
 * \param	ps_Message CAN Message structure
 * \return 	E_SUCCESS if message has been received
 * 			E_ERROR if message receive failed
 */
T_E_ERROR ecuDrv_can_ReceiveMessage(T_S_CAN_PORT *ps_Port, T_S_CAN_MESSAGE *ps_Message)
{
	T_E_ERROR le_Status = E_ERROR;

	/* Return values of CAN_ReceiveMsg are reversed */
	if (1u == CAN_ReceiveMsg(ps_Port, (CAN_MSG_Type *)ps_Message))
	{
		le_Status = E_SUCCESS;
	}
	return le_Status;
}
/*@} end of group can_functions */

