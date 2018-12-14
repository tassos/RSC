/**
 * \file	ecuDrv_uart.h
 * \brief	ecuDrv_uart module header file
 * \details	Exports the functions used for communication with the UART peripheral.
 * \author	Cosmin Marcu
 * \date	29.05.2017
 * \version 1.0.1
 */

#ifndef ECUDRV_UART_H_
#define ECUDRV_UART_H_

/* Includes */
#include "ecuConfig_Types.h"
#include "lpc17xx_uart.h"

#define UART_FIFO_BUFFER_SIZE					16u		//!< Size of the UART FIFO buffer

/**
 * @brief	Defines the UART type
 */
typedef LPC_UART_TypeDef	T_S_UART_PORT;

/**
 * @brief	Defines the UART IRQ status
 */
typedef enum E_UART_STATUS {
	E_UART_IDLE = 0u,							/*!< UART Idle status */
	E_UART_DATAREADY,							/*!< UART Data ready status */
	E_UART_ERROR								/*!< UART Error status */
} T_E_UART_STATUS;

/**
 * @brief UART Databit type definitions
 */
typedef enum E_UART_DATABIT {
	E_UART_DATABIT_5 = 0u,		     		/*!< UART 5 bit data mode */
	E_UART_DATABIT_6,		     			/*!< UART 6 bit data mode */
	E_UART_DATABIT_7,		     			/*!< UART 7 bit data mode */
	E_UART_DATABIT_8		     			/*!< UART 8 bit data mode */
} T_E_UART_DATABIT;

/**
 * @brief UART Stop bit type definitions
 */
typedef enum E_UART_STOPBIT {
	E_UART_STOPBIT_1 = 0u, 		  			/*!< UART 1 Stop Bits Select */
	E_UART_STOPBIT_2,		 				/*!< UART Two Stop Bits Select */
} T_E_UART_STOPBIT;

/**
 * @brief UART Transfer type flag
 */
typedef enum E_UART_TRANSFER {
	E_UART_TRANSFER_NONBLOCKING = 0u, 		/*!< UART Non Blocking */
	E_UART_TRANSFER_BLOCKING		 		/*!< UART Blocking */
} T_E_UART_TRANSFER;


/**
 * @brief UART Parity type definitions
 */
typedef enum E_UART_PARITY {
	E_UART_PARITY_NONE = 0u,				/*!< No parity */
	E_UART_PARITY_ODD,	 					/*!< Odd parity */
	E_UART_PARITY_EVEN, 					/*!< Even parity */
	E_UART_PARITY_SP_1, 					/*!< Forced "1" stick parity */
	E_UART_PARITY_SP_0 						/*!< Forced "0" stick parity */
} T_E_RCUART_PARITY;

/**
 * @brief UART Interrupts definitions
 */
typedef enum E_UART_IRQ {
	E_UART_IRQ_RBR = 0,		/*!< RBR Interrupt enable */
	E_UART_IRQ_THRE,		/*!< THR Interrupt enable */
	E_UART_IRQ_RLS,			/*!< RX line status interrupt enable */
	E_UART_IRQ_MS,			/*!< Modem status interrupt enable (UART1 only) */
	E_UART_IRQ_CTS,			/*!< CTS1 signal transition interrupt enable (UART1 only) */
	E_UART_IRQ_ABEO,		/*!< Enables the end of auto-baud interrupt */
	E_UART_IRQ_ABTO			/*!< Enables the auto-baud time-out interrupt */
} T_E_UART_IRQ;

/**
 * @brief UART Call back functions ID
 */
typedef enum E_UART_CB_FCT {
	E_UART_CALLBACK_RX = 0,		/*!< Rx Callback function */
	E_UART_CALLBACK_TX,			/*!< Tx Interrupt enable */
	E_UART_CALLBACK_AB,			/*!< Auto Baudrate Callback */
	E_UART_CALLBACK_ERR,		/*!< Error Callback */
	E_UART_CALLBACK_MS			/*!< Modem Status Callback (UART1 only) */
} T_E_UART_CB_FCT;

/**
 * @brief UART Configuration structure
 */
typedef struct {
	T_ULONG ul_Baudrate;				   	//!< Baud rate
	T_E_RCUART_PARITY e_Parity;				//!< Parity selection
	T_E_UART_DATABIT e_Databit;				//!< Number of data bits
	T_E_UART_STOPBIT e_Stopbit;				//!< Number of stop bits
} T_S_UART_CONFIG;

/* Exported UART functions: */
extern void ecuDrv_uart_Init(T_S_UART_PORT *ps_Port, T_S_UART_CONFIG ls_Config);
extern void ecuDrv_uart_DeInit(T_S_UART_PORT *ps_Port);
extern T_E_ERROR ecuDrv_uart_Send(T_S_UART_PORT *ps_Port, T_UBYTE *lub_UART_TxBuffer, T_ULONG lul_Length, T_E_UART_TRANSFER le_Transfer);
extern T_ULONG ecuDrv_uart_Receive(T_S_UART_PORT *ps_Port, T_UBYTE *lub_UART_RxBuffer, T_ULONG lul_Length, T_E_UART_TRANSFER le_Transfer);
extern void ecuDrv_uart_SetInterrupt(T_S_UART_PORT *ps_Port, T_E_UART_IRQ le_UART_IRQType, T_E_ENABLE le_UART_IRQState);
extern void ecuDrv_uart_TxState(T_S_UART_PORT *ps_Port, T_E_ENABLE le_TxState);
extern void ecuDrv_uart_SetCallbackFct(T_S_UART_PORT *ps_Port, T_E_UART_CB_FCT le_CBFunctionType, void *pv_Function);
extern void ecuDrv_uart_PORT0_IRQHandler(void);
extern void ecuDrv_uart_PORT1_IRQHandler(void);
extern void ecuDrv_uart_PORT2_IRQHandler(void);
extern void ecuDrv_uart_PORT3_IRQHandler(void);

#endif /* ECUDRV_UART_H_ */
