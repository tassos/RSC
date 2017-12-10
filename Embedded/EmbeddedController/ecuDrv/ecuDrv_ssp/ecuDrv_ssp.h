/**
 * \file	ecuDrv_ssp.h
 * \brief	ecuDrv_ssp module header file
 * \details	Exports the functions used for communication with the SSP peripheral.
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

#ifndef ECUDRV_SSP_H_
#define ECUDRV_SSP_H_

/* Includes */
#include "ecuConfig_Types.h"
#include "lpc17xx_ssp.h"

/** Clock phase control bit */
#define SSP_CPHA_1ST				SSP_CPHA_FIRST						//!< Clock phase 1st control bit
#define SSP_CPHA_2ND				SSP_CPHA_SECOND						//!< Clock phase 2nd control bit


/** Clock polarity control bit */
#define SSP_CPOL_HIGH 				SSP_CPOL_HI							//!< Clock polarity 1st control bit
#define SSP_CPOL_LOW				SSP_CPOL_LO							//!< Clock polarity 2nd control bit

/** SSP master mode enable */
#define SSP_MODE_SLAVE				SSP_SLAVE_MODE						//!< Slave mode enable
#define SSP_MODE_MASTER				SSP_MASTER_MODE						//!< Master mode enable

/** SSP data bit number defines */
#define SSP_DATABIT_4				SSP_CR0_DSS(4) 						//!< Databit number = 4
#define SSP_DATABIT_5				SSP_CR0_DSS(5) 			 			//!< Databit number = 5
#define SSP_DATABIT_6				SSP_CR0_DSS(6) 						//!< Databit number = 6
#define SSP_DATABIT_7				SSP_CR0_DSS(7) 						//!< Databit number = 7
#define SSP_DATABIT_8				SSP_CR0_DSS(8) 						//!< Databit number = 8
#define SSP_DATABIT_9				SSP_CR0_DSS(9) 						//!< Databit number = 9
#define SSP_DATABIT_10			    SSP_CR0_DSS(10) 					//!< Databit number = 10
#define SSP_DATABIT_11			    SSP_CR0_DSS(11) 					//!< Databit number = 11
#define SSP_DATABIT_12			    SSP_CR0_DSS(12) 					//!< Databit number = 12
#define SSP_DATABIT_13			    SSP_CR0_DSS(13) 					//!< Databit number = 13
#define SSP_DATABIT_14			    SSP_CR0_DSS(14) 					//!< Databit number = 14
#define SSP_DATABIT_15			    SSP_CR0_DSS(15) 					//!< Databit number = 15
#define SSP_DATABIT_16			    SSP_CR0_DSS(16) 					//!< Databit number = 16

/** SSP Frame Format definition */
#define SSP_FRAME_SPI				SSP_CR0_FRF_SPI						//!< Motorola SPI mode
#define SSP_FRAME_TI				SSP_CR0_FRF_TI						//!< TI synchronous serial mode
#define SSP_FRAME_MICROWIRE			SSP_CR0_FRF_MICROWIRE				//!< National Micro-wire mode

/** SSP Default clock rate */
#define SSP_DEFAULT_CLOCKRATE		1000000								//!< SSP Default clockrate
/**
 * \brief	Defines the SSP type
 */
typedef LPC_SSP_TypeDef		T_S_SSP_PORT;

/**
 * \brief SSP Transfer Type definitions
 */
typedef enum E_SSP_TRANSFER {
	E_SSP_TRANSFER_POLLING = 0,		//!< Polling transfer
	E_SSP_TRANSFER_INTERRUPT		//!< Interrupt transfer
} T_E_SSP_TRANSFER;

/**
 * \brief	SSP Configuration structure
 */
typedef struct {
	T_ULONG ul_Databit; 			//!< Databit number - RCSSP_DATABIT_x
	T_ULONG ul_CPHA;				//!< Clock phase - RCSSP_CPHA_x
	T_ULONG ul_CPOL;				//!< Clock polarity - RCSSP_CPOL_x
	T_ULONG ul_Mode;				//!< SSP mode - RCSSP_MODE_x
	T_ULONG ul_FrameFormat;			//!< Frame Format - RCSSP_FRAME_x
	T_ULONG ul_ClockRate;			//!< Clock rate [Hz]
} T_S_SSP_CONFIG;

/**
 * \brief SPI Data configuration structure
 */
typedef struct {
	void *pv_TxData;				//!< Pointer to transmit data
	T_ULONG ul_TxCounter;			//!< Transmit counter
	void *pv_RxData;				//!< Pointer to transmit data
	T_ULONG ul_RxCounter;			//!< Receive counter
	T_ULONG ul_Length;				//!< Length of transfer data
	T_ULONG ul_Status;				//!< Current status of SSP activity
} T_S_SSP_DATA_SETUP;

/* Exported SSP functions: */
extern void ecuDrv_ssp_Init(T_S_SSP_PORT *ps_Port, T_S_SSP_CONFIG ls_Config);
extern void ecuDrv_ssp_DeInit(T_S_SSP_PORT *ps_Port);
extern void ecuDrv_ssp_ConfigInit(T_S_SSP_CONFIG *ps_Config);
extern void ecuDrv_ssp_SetState(T_S_SSP_PORT *ps_Port, T_E_ENABLE le_State);
extern T_ULONG ecuDrv_ssp_DataTransfer(T_S_SSP_PORT *ps_Port, T_S_SSP_DATA_SETUP *ps_DataConfig, T_E_SSP_TRANSFER le_TransferType);

#endif /* ECUDRV_SSP_H_ */
