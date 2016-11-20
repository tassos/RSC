/**
 * \file	rc_uart.h
 * \brief	rc_uart module header file
 * \details	Exports the functions used for communication with the UART peripheral.
 * \author	Cosmin Marcu
 * \date	29.05.2015
 * \version 1.0.1
 */

#ifndef RC_UART_H_
#define RC_UART_H_

/* Includes */
#include "rc_stdtypedefs.h"
#include "lpc17xx_uart.h"

#define RCUART_FIFO_BUFFER_SIZE					16u		//!< Size of the UART FIFO buffer

/**
 * @brief	Defines the UART type
 */
typedef LPC_UART_TypeDef	T_RCUART_PORT;

/**
 * @brief	Defines the UART IRQ status
 */
typedef enum E_RCUART_STATUS {
	E_RCUART_IDLE = 0u,
	E_RCUART_DATAREADY,
	E_RCUART_ERROR
} T_E_RCUART_STATUS;

/**
 * @brief UART Databit type definitions
 */
typedef enum E_RCUART_DATABIT {
	E_RCUART_DATABIT_5 = 0u,		     		/*!< UART 5 bit data mode */
	E_RCUART_DATABIT_6,		     			/*!< UART 6 bit data mode */
	E_RCUART_DATABIT_7,		     			/*!< UART 7 bit data mode */
	E_RCUART_DATABIT_8		     			/*!< UART 8 bit data mode */
} T_E_RCUART_DATABIT;

/**
 * @brief UART Stop bit type definitions
 */
typedef enum E_RCUART_STOPBIT {
	E_RCUART_STOPBIT_1 = 0u, 		  		/*!< UART 1 Stop Bits Select */
	E_RCUART_STOPBIT_2,		 				/*!< UART Two Stop Bits Select */
} T_E_RCUART_STOPBIT;

/**
 * @brief UART Transfer type flag
 */
typedef enum E_RCUART_TRANSFER {
	E_RCUART_TRANSFER_NONBLOCKING = 0u, 	/*!< UART Non Blocking */
	E_RCUART_TRANSFER_BLOCKING		 		/*!< UART Blocking */
} T_E_RCUART_TRANSFER;


/**
 * @brief UART Parity type definitions
 */
typedef enum E_RCUART_PARITY {
	E_RCUART_PARITY_NONE = 0u,				/*!< No parity */
	E_RCUART_PARITY_ODD,	 				/*!< Odd parity */
	E_RCUART_PARITY_EVEN, 					/*!< Even parity */
	E_RCUART_PARITY_SP_1, 					/*!< Forced "1" stick parity */
	E_RCUART_PARITY_SP_0 					/*!< Forced "0" stick parity */
} T_E_RCUART_PARITY;

/**
 * @brief UART Interrupts definitions
 */
typedef enum E_RCUART_IRQ {
	E_RCUART_IRQ_RBR = 0,	/*!< RBR Interrupt enable */
	E_RCUART_IRQ_THRE,		/*!< THR Interrupt enable */
	E_RCUART_IRQ_RLS,		/*!< RX line status interrupt enable */
	E_RCUART_IRQ_MS,		/*!< Modem status interrupt enable (UART1 only) */
	E_RCUART_IRQ_CTS,		/*!< CTS1 signal transition interrupt enable (UART1 only) */
	E_RCUART_IRQ_ABEO,		/*!< Enables the end of auto-baud interrupt */
	E_RCUART_IRQ_ABTO		/*!< Enables the auto-baud time-out interrupt */
} T_E_RCUART_IRQ;

/**
 * @brief UART Call back functions ID
 */
typedef enum E_RCUART_CB_FCT {
	E_RCUART_CALLBACK_RX = 0,	/*!< Rx Callback function */
	E_RCUART_CALLBACK_TX,		/*!< Tx Interrupt enable */
	E_RCUART_CALLBACK_AB,		/*!< Auto Baudrate Callback */
	E_RCUART_CALLBACK_ERR,		/*!< Error Callback */
	E_RCUART_CALLBACK_MS		/*!< Modem Status Callback (UART1 only) */
} T_E_RCUART_CB_FCT;

/**
 * @brief UART Configuration structure
 */
typedef struct {
	T_ULONG ul_Baudrate;				   	//!< Baud rate
	T_E_RCUART_PARITY e_Parity;				//!< Parity selection
	T_E_RCUART_DATABIT e_Databit;			//!< Number of data bits
	T_E_RCUART_STOPBIT e_Stopbit;			//!< Number of stop bits
} T_RCUART_CONFIG;

/* Exported UART functions: */
extern void rcuart_Init(T_RCUART_PORT *ps_Port, T_RCUART_CONFIG ls_Config);
extern void rcuart_DeInit(T_RCUART_PORT *ps_Port);
extern T_E_RC_ERROR rcuart_Send(T_RCUART_PORT *ps_Port, T_UBYTE *lub_UART_TxBuffer, T_ULONG lul_Length, T_E_RCUART_TRANSFER le_Transfer);
extern T_ULONG rcuart_Receive(T_RCUART_PORT *ps_Port, T_UBYTE *lub_UART_RxBuffer, T_ULONG lul_Length, T_E_RCUART_TRANSFER le_Transfer);
extern void rcuart_SetInterrupt(T_RCUART_PORT *ps_Port, T_E_RCUART_IRQ le_UART_IRQType, T_E_RC_ENABLE le_UART_IRQState);
extern void rcuart_TxState(T_RCUART_PORT *ps_Port, T_E_RC_ENABLE le_TxState);
extern void rcuart_SetCallback_Function(T_RCUART_PORT *ps_Port, T_E_RCUART_CB_FCT le_CBFunctionType, void *pv_Function);
extern void rcuart_PORT0_IRQHandler(void);
extern void rcuart_PORT1_IRQHandler(void);
extern void rcuart_PORT2_IRQHandler(void);
extern void rcuart_PORT3_IRQHandler(void);
#endif /* RC_UART_H_ */
