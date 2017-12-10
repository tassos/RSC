/**
 * \file	ecuAppl_GPS.c
 * \brief	GPS functions
 * \details	Implements the functions for GPS module
 * \author	Cosmin Marcu
 * \date	05.05.2017
 * \version 1.0.1
 */

/* Includes */
#include "../ecuAppl_GPS/ecuAppl_GPS.h"

#include "ecuDrv_gpio.h"
#include "ecuDrv_pinsel.h"
#include "ecuDrv_uart.h"
#include "ecuDrv_sys.h"

/**
 * \ingroup  ecuAppl_GPS
 * \defgroup gps_defines GPS Defines
 *  Preprocessor defines for GPS module
 *  @{
 */
/* Defines */
#define		GPS_UART_PORT						ECU_UART3				//!< GPS UART port
#define		GPS_UART_BAUDRATE			 		     9600				//!< GPS UART baud rate
#define 	GPS_UART_DATABIT		  	 E_UART_DATABIT_8				//!< GPS UART databit
#define		GPS_UART_PARITY			   E_UART_PARITY_NONE				//!< GPS UART parity
#define		GPS_UART_STOPBIT		  	 E_UART_STOPBIT_1				//!< GPS UART stopbit
#define		GPS_UART_IRQ					   UART3_IRQn				//!< UART1 Interrupt ID
#define		GPS_RX_BUFFER_SIZE						  128				//!< Size of the RX buffer
 /* Define events timeout [ms] */
#define 	GPS_DATA_RECEIVED_TIMEOUT 				 5000				//!< Timeout on data received
#define 	GPS_RX_INPROGRESS_TIMEOUT			 	  100				//!< Timeout on data reading
/**@} end of group gps_defines */

/**
 * \ingroup  ecuAppl_GPS
 * \defgroup gps_typedefs GPS Types
 *  Types definition for GPS module
 *  @{
 */
/**
 * @brief	Defines GPS module states
 */
typedef enum E_GPS_STATE {
	E_GPS_STATE_INIT = 0u,										//!< Init state
	E_GPS_STATE_IDLE,											//!< Idle state
	E_GPS_STATE_DATA_RECEIVED,									//!< Data received state
	E_GPS_STATE_DATA_PROCESSED,									//!< Data processed state
	E_GPS_STATE_ERROR,											//!< Error state
} T_E_GPS_STATE;

/**
 * @brief	Defines GPS RX states
 */
typedef enum E_GPS_RX_STATE {
	E_GPS_RX_STATE_IDLE = 0u,									//!< Rx Idle state
	E_GPS_RX_STATE_INPROGRESS,									//!< Rx in progress
	E_GPS_RX_STATE_DATAREADY,									//!< Rx data ready
	E_GPS_RX_STATE_ERROR										//!< Rx error
} T_E_GPS_RX_STATE;

/**
 * @brief	Defines GPS events
 */
typedef enum E_GPS_EVENT {
	E_GPS_EVENT_NONE = 0u,										//!< No event
	E_GPS_EVENT_DATA_RECEIVED,									//!< GPS data received
	E_GPS_EVENT_RX_INPROGRESS,									//!< GPS reading in progress
	E_GPS_EVENT_RX_ERROR,										//!< GPS receive error/timeout
} T_E_GPS_EVENT;

//TODO: move in timer/scheduler module
/**
 * @brief	GPS event handler type function
 */
typedef void (*T_GPS_EVENT_HANDLER_FUNC)(void);

/**
 * @brief	Defines Event callback structure
 */
typedef struct {
	T_E_GPS_EVENT e_Event;										//!< Event ID
	T_GPS_EVENT_HANDLER_FUNC pf_EventHandler_Func;				//!< Event handler function
} T_S_GPS_EVENT_HANDLE;

/**
 * @brief	Defines Event timeout structure
 */
typedef struct {
	T_E_GPS_EVENT e_Event;										//!< Event ID
	T_UWORD	uw_Timeout;											//!< Event timeout value [ms]
} T_S_GPS_EVENT_TIMEOUT_HANDLE;

/**
 * @brief	Defines scheduler queue
 */
typedef struct {
	T_E_GPS_EVENT e_Event;										//!< Event ID
	T_UWORD	uw_TimeoutCounter;									//!< Current event timeout counter value
} T_S_GPS_TIMER_QUEUE;
/**@} end of group gps_typedefs */

/**
 * \ingroup  ecuAppl_GPS
 * \defgroup gps_variables GPS Variables
 *  Global/shared GPS module variables
 *  @{
 */
/* Private variables */
PRIVATE_DATA VOLATILE T_UWORD ruw_ecuAppl_GPS_RxInput_Counter = 0u;				//!< Rx Buffer input counter
PRIVATE_DATA VOLATILE T_UWORD ruw_ecuAppl_GPS_RxInput_Length = 0u;				//!< Rx Buffer input length
PRIVATE_DATA VOLATILE T_UBYTE raub_ecuAppl_GPS_RxBuffer[GPS_RX_BUFFER_SIZE];	//!< Rx Buffer data storage
PRIVATE_DATA VOLATILE T_E_GPS_RX_STATE re_ecuAppl_GPS_RxState;					//!< GPS Rx state
PRIVATE_DATA T_E_GPS_STATE re_ecuAppl_GPS_State;								//!< GPS module state
/**@} end of group gps_variables */


/* Private functions definition */
PRIVATE_FCT void ecuAppl_GPS_RxCallBack(void);
PRIVATE_FCT T_E_BOOL ecuAppl_GPS_SaveRxData(T_UBYTE lub_Data);
PRIVATE_FCT void ecuAppl_GPS_DataReceived(void);
PRIVATE_FCT void ecuAppl_GPS_InitModule(void);
PRIVATE_FCT void ecuAppl_GPS_Config(void);
PRIVATE_FCT void ecuAppl_GPS_ClearRxBuffer(void);
PRIVATE_FCT void ecuAppl_GPS_CheckEventStatus(void);
PRIVATE_FCT void ecuAppl_GPS_ProcessData(void);
PRIVATE_FCT T_UWORD ecuAppl_GPS_GetDataBuffer(T_UBYTE *pub_DataBuf);

/**
 * \ingroup  ecuAppl_GPS
 * \defgroup gps_constants GPS Constants
 *  Constants definition for GPS module
 *  @{
 */
/**
 * \brief	Handler functions list on events
 */
PRIVATE_DATA const T_S_GPS_EVENT_HANDLE cs_ecuAppl_GPS_EventsList[] = {
		{ E_GPS_EVENT_DATA_RECEIVED, &ecuAppl_GPS_DataReceived },		//!< Data received callback
};

/**
 * \brief	List of timeout values on events
 */
PRIVATE_DATA const T_S_GPS_EVENT_TIMEOUT_HANDLE cs_ecuAppl_GPS_TimeoutList[] = {
		{ E_GPS_EVENT_DATA_RECEIVED, GPS_DATA_RECEIVED_TIMEOUT },		//!< Data received timeout event
		{ E_GPS_EVENT_RX_INPROGRESS, GPS_RX_INPROGRESS_TIMEOUT },		//!< Rx in progress timeout event
};
/**@} end of group gps_constants */

/**
 * \ingroup  ecuAppl_GPS
 * \defgroup gps_functions GPS Functions
 *  Functions definitions for GPS module
 *  @{
 */
/* Private functions implementation */
/**
 * \brief	UART Rx callback function
 * \return 	none
 * \attention This function is called in UART1 interrupt
 */
PRIVATE_FCT void ecuAppl_GPS_RxCallBack(void)
{
	T_UBYTE lub_Data = 0u;
	T_ULONG lul_Length = 0u;
	T_E_BOOL le_BytesAvailable = E_TRUE;

	/* Start receiving from UART */
	while(E_TRUE == le_BytesAvailable)
	{
		/* Receive one byte */
		lul_Length = ecuDrv_uart_Receive((T_S_UART_PORT *)GPS_UART_PORT, &lub_Data, 1u, E_UART_TRANSFER_NONBLOCKING);
		if (lul_Length > 0u)
		{
			/* Save Rx data */
			if(E_TRUE == ecuAppl_GPS_SaveRxData(lub_Data)) {};
		}
		else
		{
			le_BytesAvailable = E_FALSE;
		}
	}
}

/**
 * \brief	UART Rx data save function
 * \param	lub_Data Received byte
 * \return 	E_TRUE if Rx buffer is full
 * 			E_FALSE if Rx buffer is not full
 * \attention This function is called in UART1 interrupt
 */
PRIVATE_FCT T_E_BOOL ecuAppl_GPS_SaveRxData(T_UBYTE lub_Data)
{
	T_E_BOOL le_Status = E_FALSE;

	/* Save data and increment buffer offset */
	raub_ecuAppl_GPS_RxBuffer[ruw_ecuAppl_GPS_RxInput_Counter] = lub_Data;
	ruw_ecuAppl_GPS_RxInput_Counter++;

	/* Check if buffer is full */
	if (	(ruw_ecuAppl_GPS_RxInput_Counter > 7u) &&
			(raub_ecuAppl_GPS_RxBuffer[ruw_ecuAppl_GPS_RxInput_Counter-2u] == 13u) &&
			(raub_ecuAppl_GPS_RxBuffer[ruw_ecuAppl_GPS_RxInput_Counter-1u] == 10u)
			)
	{
		ruw_ecuAppl_GPS_RxInput_Length = ruw_ecuAppl_GPS_RxInput_Counter;
		ruw_ecuAppl_GPS_RxInput_Counter = 0u;
		le_Status = E_TRUE;
		if(
				(raub_ecuAppl_GPS_RxBuffer[0u] == '$') &&
				(raub_ecuAppl_GPS_RxBuffer[1u] == 'G') &&
				(raub_ecuAppl_GPS_RxBuffer[2u] == 'P') &&
				(raub_ecuAppl_GPS_RxBuffer[3u] == 'G') &&
				(raub_ecuAppl_GPS_RxBuffer[4u] == 'G') &&
				(raub_ecuAppl_GPS_RxBuffer[5u] == 'A')

				)
		{
			re_ecuAppl_GPS_RxState = E_GPS_RX_STATE_DATAREADY;
		}
		else
		{
			re_ecuAppl_GPS_RxState = E_GPS_RX_STATE_IDLE;
		}
	}
	else if (ruw_ecuAppl_GPS_RxInput_Counter < GPS_RX_BUFFER_SIZE)
	{
		le_Status = E_TRUE;
		re_ecuAppl_GPS_RxState = E_GPS_RX_STATE_INPROGRESS;
	}
	else
	{
		ruw_ecuAppl_GPS_RxInput_Counter = 0u;
		le_Status = E_FALSE;
	}

	return le_Status;
}

/**
 * \brief	Handles the E_GPS_EVENT_DATA_RECEIVED event
 * \return 	none
 */
PRIVATE_FCT void ecuAppl_GPS_DataReceived(void)
{

}

/**
 * \brief	Handles the TODO event
 * \return 	none
 */
PRIVATE_FCT void ecuAppl_GPS_InitModule(void)
{
//	T_UBYTE laub_Cmd[] = "AT+CGPSSTATUS?\r\n";
//	ecuDrv_uart_Send((T_S_UART_PORT *)GPS_UART_PORT, laub_Cmd, (T_ULONG)16u, E_UART_TRANSFER_NONBLOCKING);
	re_ecuAppl_GPS_State = E_GPS_STATE_IDLE;
}

/**
 * \brief	Configures GPS module
 * \return 	none
 */
PRIVATE_FCT void ecuAppl_GPS_Config(void)
{
	T_S_PINSEL_CFG ls_PinselConfig;
	T_S_UART_CONFIG ls_UARTConfig;

	/* Configure GPS UART port pins */
	ls_PinselConfig.e_Port = E_IOPORT4;
	ls_PinselConfig.e_Function = E_PINSEL_FUNC3;
	ls_PinselConfig.e_Pin = E_IOPIN28;
	/* Configure pin 0.15 */
	ecuDrv_pinsel_ConfigPin(ls_PinselConfig);
	ls_PinselConfig.e_Pin = E_IOPIN29;
	/* Configure pin 0.16 */
	ecuDrv_pinsel_ConfigPin(ls_PinselConfig);
	/* Configure UART1 registers */
	ls_UARTConfig.ul_Baudrate = GPS_UART_BAUDRATE;
	ls_UARTConfig.e_Databit = GPS_UART_DATABIT;
	ls_UARTConfig.e_Parity = GPS_UART_PARITY;
	ls_UARTConfig.e_Stopbit = GPS_UART_STOPBIT;
	/* Send configuration structure */
	ecuDrv_uart_Init((T_S_UART_PORT *)GPS_UART_PORT, ls_UARTConfig);
	/* Enable UART1 Rx interrupt */
	ecuDrv_uart_SetInterrupt((T_S_UART_PORT *)GPS_UART_PORT, E_UART_IRQ_RBR, E_ENABLE);
	/* Enable UART1 Transmit */
	ecuDrv_uart_TxState((T_S_UART_PORT *)GPS_UART_PORT, E_ENABLE);
	/* Set Rx IRQ callback function */
	ecuDrv_uart_SetCallbackFct((T_S_UART_PORT *)GPS_UART_PORT, E_UART_CALLBACK_RX, &ecuAppl_GPS_RxCallBack);
	/* Enable UART1 port interrupt */
	ECU_ENABLE_IRQ(GPS_UART_IRQ);
}

/**
 * \brief	Clears GPS Rx buffer.
 * \return 	None
 */
PRIVATE_FCT void ecuAppl_GPS_ClearRxBuffer(void)
{
	T_UWORD luw_Index = 0u;

	for (luw_Index = 0u; luw_Index < GPS_RX_BUFFER_SIZE; luw_Index++)
	{
		raub_ecuAppl_GPS_RxBuffer[luw_Index] = 0u;
	}
}

/**
 * \brief	Checks for GPS events (Rx, error).
 * \return 	None
 */
PRIVATE_FCT void ecuAppl_GPS_CheckEventStatus(void)
{
	/* Check if GPS data received and is ready to be processed */
	if (E_GPS_RX_STATE_DATAREADY == re_ecuAppl_GPS_RxState)
	{
		re_ecuAppl_GPS_State = E_GPS_STATE_DATA_RECEIVED;
	}
}

/**
 * \brief	Process GPS received data.
 * \return 	None
 */
PRIVATE_FCT void ecuAppl_GPS_ProcessData(void)
{
	T_UBYTE laub_DataBuffer[GPS_RX_BUFFER_SIZE];
	T_UWORD luw_Length = 0u;
	T_UWORD luw_Index = 0u;

	for (luw_Index = 0u; luw_Index < GPS_RX_BUFFER_SIZE; luw_Index++)
	{
		laub_DataBuffer[luw_Index] = 0u;
	}

	luw_Length = ecuAppl_GPS_GetDataBuffer(laub_DataBuffer);
	if (luw_Length > 0u)
	{
		re_ecuAppl_GPS_State = E_GPS_STATE_IDLE;
		ECU_DISABLE_IRQ(GPS_UART_IRQ);
		//TODO: process buffer
	}
	else
	{
		/* Error processing data */
		re_ecuAppl_GPS_State = E_GPS_STATE_ERROR;
	}

}

/**
 * \brief	Process GPS received data.
 * \param	pub_DataBuf Pointer to data buffer
 * \return 	Buffer length
 */
PRIVATE_FCT T_UWORD ecuAppl_GPS_GetDataBuffer(T_UBYTE *pub_DataBuf)
{
	T_UWORD luw_Index = 0u;
	T_UWORD luw_Length = 0u;

	/* Disable interrupts */
	ecuDrv_sys_EnterProtectedMode();
	/* Check if there is data in buffer */
	if (ruw_ecuAppl_GPS_RxInput_Length > 0u)
	{
		/* Copy Rx data buffer */
		for (luw_Index = 0u; luw_Index < ruw_ecuAppl_GPS_RxInput_Length; luw_Index++)
		{
			pub_DataBuf[luw_Index] = raub_ecuAppl_GPS_RxBuffer[luw_Index];
		}
		luw_Length = ruw_ecuAppl_GPS_RxInput_Length;
		re_ecuAppl_GPS_RxState = E_GPS_RX_STATE_IDLE;
	}
	else
	{
		luw_Length = 0u;
	}
	/* Enable interrupts */
	ecuDrv_sys_LeaveProtectedMode();

	return (luw_Length);
}

/* External functions implementation */
/**
 * \brief	Disables GPS communication.
 * \return 	None
 */
void ecuAppl_GPS_DisableGPS(void)
{
	ecuDrv_uart_SetInterrupt((T_S_UART_PORT *)GPS_UART_PORT, E_UART_IRQ_RBR, E_DISABLE);
	ECU_DISABLE_IRQ(GPS_UART_IRQ);
}

/**
 * \brief	Enables GPS communication.
 * \return 	None
 */
void ecuAppl_GPS_EnableGPS(void)
{
	ecuDrv_uart_SetInterrupt((T_S_UART_PORT *)GPS_UART_PORT, E_UART_IRQ_RBR, E_ENABLE);
	ECU_ENABLE_IRQ(GPS_UART_IRQ);
}

/**
 * \brief	Initializes GPS module.
 * \return 	None
 */
void ecuAppl_GPS_Init(void)
{
	/* Initialize counters */
	ruw_ecuAppl_GPS_RxInput_Counter = 0u;

	/* Initialize Rx Buffer */
	ecuAppl_GPS_ClearRxBuffer();

	/* Configure UART port for GPS module */
	ecuAppl_GPS_Config();

	/* Initialize states */
	re_ecuAppl_GPS_RxState = E_GPS_RX_STATE_IDLE;
	re_ecuAppl_GPS_State = E_GPS_STATE_INIT;
}

/**
 * \brief	GPS module state machine.
 * \return 	None
 */
void ecuAppl_GPS_SM(void)
{
	switch (re_ecuAppl_GPS_State)
	{
	case E_GPS_STATE_INIT:
		ecuAppl_GPS_InitModule();
		break;
	case E_GPS_STATE_IDLE:
		ecuAppl_GPS_CheckEventStatus();
		break;
	case E_GPS_STATE_DATA_RECEIVED:
		ecuAppl_GPS_ProcessData();
		break;
	case E_GPS_STATE_DATA_PROCESSED:
		break;
	case E_GPS_STATE_ERROR:
		break;
	default:
		break;
	}
}
/**@} end of group gps_functions */

/**
 * \ingroup  ecu_tasks
 * \defgroup gps_tasks GPS Tasks
 *  Tasks definitions for GPS module
 *  @{
 */
/**
 * \brief	Periodic 10ms GPS task
 * \return 	none
 * \see		ecuAppl_Scheduler_Task_10ms
 */
void ecuAppl_GPS_Task_10ms(void)
{
	//TODO: add periodic callbacks
}
/**@} end of group gps_tasks */

