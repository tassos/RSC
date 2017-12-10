/**
 * \file	ecuDrv_i2c.c
 * \brief	Implements the interface functions with the I2C peripheral
 * \details	Implements the functions which communicate directly with the
 * 			LPC17xx I2C peripheral
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

/* Includes */
#include "ecuDrv_i2c.h"

/* Begin functions implementation */

/** \defgroup ecuDrv_i2c  I2C driver
 *  \ingroup ecu_drivers
 *   Contains the functions to set the I2C pins attributes
 */

/**
 * \ingroup  ecuDrv_i2c
 * \defgroup i2c_functions I2C Functions
 *  Functions definitions for the I2C setup
 *  @{
 */

/* I2C Functions Group: */
/**
 * \brief 	Initializes I2C.
 * \param	ps_Port			Pointer to LPC_I2Cx port structure
 * \param	lul_ClockRate	I2C clock rate
 * \return	none
 */
void ecuDrv_i2c_Init(T_S_I2C_PORT *ps_Port, T_ULONG lul_ClockRate)
{
	/* Call driver initializer */
	I2C_Init(ps_Port, lul_ClockRate);
}

/**
 * \brief 	De-Initializes I2C.
 * \param	ps_Port	Pointer to LPC_I2Cx port structure
 * \return	none
 */
void ecuDrv_i2c_DeInit(T_S_I2C_PORT *ps_Port)
{
	I2C_DeInit(ps_Port);
}

/**
 * \brief 	Sets the state of a I2C Port.
 * \param	ps_Port		Pointer to LPC_I2Cx port structure
 * \param	le_State	New state of the I2C (E_ENABLE or E_DISABLE)
 * \return	none
 */
void ecuDrv_i2c_SetState(T_S_I2C_PORT *ps_Port, T_E_ENABLE le_State)
{
	I2C_Cmd(ps_Port, (FunctionalState)le_State);
}

/**
 * \brief 	Master data transfer function.
 * \param	ps_Port			Pointer to LPC_I2Cx port structure
 * \param	ps_DataConfig	Pointer to master data configuration structure
 * \param	le_TransferType	Transfer type (polling or interrupt)
 * \return	Transfer state
 */
T_E_ERROR ecuDrv_i2c_MasterDataTransfer(T_S_I2C_PORT *ps_Port, T_S_I2C_MASTER_DATA_SETUP *ps_DataConfig, T_E_I2C_TRANSFER le_TransferType)
{
	T_E_ERROR le_Status = E_ERROR;
	I2C_M_SETUP_Type dataCfg[1];

	dataCfg[0].sl_addr7bit = ps_DataConfig->ul_SlaveAddress;
	dataCfg[0].tx_data = ps_DataConfig->pub_TxData;
	dataCfg[0].tx_length = ps_DataConfig->ul_TxLength;
	dataCfg[0].tx_count = ps_DataConfig->ul_TxCount;
	dataCfg[0].rx_data = ps_DataConfig->pub_RxData;
	dataCfg[0].rx_length = ps_DataConfig->ul_RxLength;
	dataCfg[0].rx_count = ps_DataConfig->ul_RxCount;
	dataCfg[0].status = ps_DataConfig->ul_Status;
	dataCfg[0].retransmissions_max = ps_DataConfig->ul_MaxRetry;
	dataCfg[0].retransmissions_count = ps_DataConfig->ul_RetryCount;
	dataCfg[0].callback = ps_DataConfig->pf_Callback;

	if ((Status)1u == I2C_MasterTransferData(ps_Port, dataCfg, (I2C_TRANSFER_OPT_Type)le_TransferType))
	{
		le_Status = E_SUCCESS;
	}
	return le_Status;
}
/**@} end of group i2c_functions */
