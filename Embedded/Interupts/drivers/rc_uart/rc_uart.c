/**
 * \file	rc_uart.c
 * \brief	Implements the interface functions with the UART peripheral
 * \details	Implements the functions which communicate directly with the
 * 			LPC17xx UART peripheral
 * \author	Cosmin Marcu
 * \date	29.05.2015
 * \version 1.0.1
 */

/* Includes */
#include "rc_uart.h"

/* Begin functions implementation */

/** \defgroup rc_uart  UART driver
  Contains the functions to set the pins attributes
*/

/**
 * \ingroup  rc_uart
 * \defgroup uart_functions UART Functions
 *  Functions definitions for the UART setup
 *  @{
 */

/* UART Functions Group: */
/**
 * \brief 	Initializes UART.
 * \param	ps_Port		Pointer to LPC_UARTx port structure
 * \param	ls_Config	UART config structure
 * \return	none
 */
void rcuart_Init(T_RCUART_PORT *ps_Port, T_RCUART_CONFIG ls_Config)
{
	UART_CFG_Type UART_ConfigStruct[1u];
	/* Fill UART config structure */
	UART_ConfigStruct[0].Baud_rate = ls_Config.ul_Baudrate;
	UART_ConfigStruct[0].Databits = ls_Config.e_Databit;
	UART_ConfigStruct[0].Parity = ls_Config.e_Parity;
	UART_ConfigStruct[0].Stopbits = ls_Config.e_Stopbit;
	/* Call driver initializer */
	UART_Init(ps_Port, UART_ConfigStruct);
}

/**
 * \brief 	De-Initializes UART.
 * \param	ps_Port	Pointer to LPC_UARTx port structure
 * \return	none
 */
void rcuart_DeInit(T_RCUART_PORT *ps_Port)
{
	UART_DeInit(ps_Port);
}

/**
 * \brief 	Send a block of data to the UART.
 * \param	ps_Port				Pointer to LPC_UARTx port structure
 * \param 	lub_UART_TxBuffer	buffer containing the data to be sent
 * \param	lul_Length			number of bytes to be sent
 * \param	le_Transfer			Transfer type (Non Blocking or Blocking)
 * \return	Transmit status (E_RC_SUCCES if all bytes were transmitted)
 */
T_E_RC_ERROR rcuart_Send(T_RCUART_PORT *ps_Port, T_UBYTE *lub_UART_TxBuffer, T_ULONG lul_Length, T_E_RCUART_TRANSFER le_Transfer)
{
	T_ULONG lul_BytesTransmitted = 0u;
	T_ULONG lul_TotalBytesTransmitted = 0u;
	T_ULONG lul_BytesRemaining = 0u;
	T_E_RC_ERROR le_Status = E_RC_ERROR;

	/* Transmit data available in buffer */
	while (lul_TotalBytesTransmitted < lul_Length)
	{
		lul_BytesRemaining = lul_Length-lul_TotalBytesTransmitted;
		/* Send segments of 16 bytes */
		if(lul_BytesRemaining > RCUART_FIFO_BUFFER_SIZE)
		{
			lul_BytesTransmitted = UART_Send(ps_Port, &lub_UART_TxBuffer[lul_TotalBytesTransmitted], RCUART_FIFO_BUFFER_SIZE, (TRANSFER_BLOCK_Type)le_Transfer);
		}
		/* Send last segment */
		else
		{
			lul_BytesTransmitted = UART_Send(ps_Port, &lub_UART_TxBuffer[lul_TotalBytesTransmitted], lul_BytesRemaining, (TRANSFER_BLOCK_Type)le_Transfer);
		}
		/* Count transmitted bytes */
		lul_TotalBytesTransmitted += lul_BytesTransmitted;
	}
	/* Check if all bytes were transmitted */
	if (lul_TotalBytesTransmitted == lul_Length)
	{
		le_Status = E_RC_SUCCESS;
	}
	return le_Status;
}

/**
 * \brief 	Receives a block of data from UART.
 * \param	ps_Port				Pointer to LPC_UARTx port structure
 * \param 	lub_UART_RxBuffer	buffer where data will be saved
 * \param	lul_Length			number of received bytes
 * \param	le_Transfer			Transfer type (Non Blocking or Blocking)
 * \return	Number of transferred bytes
 */
T_ULONG rcuart_Receive(T_RCUART_PORT *ps_Port, T_UBYTE *lub_UART_RxBuffer, T_ULONG lul_Length, T_E_RCUART_TRANSFER le_Transfer)
{
	return UART_Receive(ps_Port, lub_UART_RxBuffer, lul_Length, (TRANSFER_BLOCK_Type)le_Transfer);
}

/**
 * \brief 	Configures an interrupt on UART.
 * \param	ps_Port				Pointer to LPC_UARTx port structure
 * \param 	le_UART_IRQType		IRQ Type
 * \param	le_UART_IRQState	IRQ State
 * \return	none
 */
void rcuart_SetInterrupt(T_RCUART_PORT *ps_Port, T_E_RCUART_IRQ le_UART_IRQType, T_E_RC_ENABLE le_UART_IRQState)
{
	UART_IntConfig(ps_Port, (UART_INT_Type)le_UART_IRQType, (FunctionalState)le_UART_IRQState);
}

/**
 * \brief 	Configures UART Transmit state.
 * \param	ps_Port		Pointer to LPC_UARTx port structure
 * \param	le_TxState	New transmit state
 * \return	none
 */
void rcuart_TxState(T_RCUART_PORT *ps_Port, T_E_RC_ENABLE le_TxState)
{
	UART_TxCmd(ps_Port, (FunctionalState)le_TxState);
}

/**
 * \brief 	Configures callback functions.
 * \param	ps_Port				Pointer to LPC_UARTx port structure
 * \param	le_CBFunctionType	Callback function type
 * \param	pv_Function			Pointer to callback function
 * \return	none
 */
void rcuart_SetCallback_Function(T_RCUART_PORT *ps_Port, T_E_RCUART_CB_FCT le_CBFunctionType, void *pv_Function)
{
	UART_SetupCbs(ps_Port, (T_UBYTE)le_CBFunctionType, pv_Function);
}

/**
 * \brief 	Standard UART0 IRQHandler
 * \return	none
 */
void rcuart_PORT0_IRQHandler(void)
{
	UART0_StdIntHandler();
}

/**
 * \brief 	Standard UART1 IRQHandler
 * \return	none
 */
void rcuart_PORT1_IRQHandler(void)
{
	UART1_StdIntHandler();
}

/**
 * \brief 	Standard UART2 IRQHandler
 * \return	none
 */
void rcuart_PORT2_IRQHandler(void)
{
	UART2_StdIntHandler();
}

/**
 * \brief 	Standard UART3 IRQHandler
 * \return	none
 */
void rcuart_PORT3_IRQHandler(void)
{
	UART3_StdIntHandler();
}
/*@} end of group UART_functions */
