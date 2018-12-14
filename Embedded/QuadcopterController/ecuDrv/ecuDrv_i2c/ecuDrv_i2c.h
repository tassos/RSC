/**
 * \file	ecuDrv_i2c.h
 * \brief	ecuDrv_i2c module header file
 * \details	Exports the functions used for communication with the I2C peripheral.
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

#ifndef ECUDRV_I2C_H_
#define ECUDRV_I2C_H_

/* Includes */
#include "ecuConfig_Types.h"
#include "lpc17xx_i2c.h"

/** I2C Default clock rate */
#define I2C_CLOCKRATE_DEFAULT		100000								//!< I2C Default clock rate
/**
 * \brief	Defines the I2C type
 */
typedef LPC_I2C_TypeDef		T_S_I2C_PORT;

/**
 * \brief I2C Transfer Type definitions
 */
typedef enum E_I2C_TRANSFER {
	E_I2C_TRANSFER_POLLING = 0,				//!< Polling transfer
	E_I2C_TRANSFER_INTERRUPT				//!< Interrupt transfer
} T_E_I2C_TRANSFER;

/**
 * \brief I2C Master Data configuration structure
 */
typedef struct {
	  T_ULONG ul_SlaveAddress;				//!< Slave address in 7bit mode
	  T_UBYTE *pub_TxData;					//!< Pointer to Transmit data
	  T_ULONG ul_TxLength;					//!< Transmit data length
	  T_ULONG ul_TxCount;					//!< Current Transmit data counter
	  T_UBYTE *pub_RxData;					//!< Pointer to Receive data
	  T_ULONG ul_RxLength;					//!< Receive data length
	  T_ULONG ul_RxCount;					//!< Current Receive data counter
	  T_ULONG ul_MaxRetry;					//!< Max Re-Transmission value
	  T_ULONG ul_RetryCount;				//!< Current Re-Transmission counter
	  T_ULONG ul_Status;					//!< Current status of I2C activity
	  void (*pf_Callback)(void);			//!< Pointer to IRQ Call back function when transmission complete
} T_S_I2C_MASTER_DATA_SETUP;

/* Exported I2C functions: */
extern void ecuDrv_i2c_Init(T_S_I2C_PORT *ps_Port, T_ULONG lul_ClockRate);
extern void ecuDrv_i2c_DeInit(T_S_I2C_PORT *ps_Port);
extern void ecuDrv_i2c_SetState(T_S_I2C_PORT *ps_Port, T_E_ENABLE le_State);
extern T_E_ERROR ecuDrv_i2c_MasterDataTransfer(T_S_I2C_PORT *ps_Port, T_S_I2C_MASTER_DATA_SETUP *ps_DataConfig, T_E_I2C_TRANSFER le_TransferType);

#endif /* ECUDRV_I2C_H_ */
