/**
 * \file	ecuDrv_ssp.c
 * \brief	Implements the interface functions with the SSP peripheral
 * \details	Implements the functions which communicate directly with the
 * 			LPC17xx SSP peripheral
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

/* Includes */
#include "ecuDrv_ssp.h"

/* Begin functions implementation */

/** \defgroup ecuDrv_ssp SSP driver
 *  \ingroup ecu_drivers
 *   Contains the functions to set the SSP pins attributes
 */

/**
 * \ingroup  ecuDrv_ssp
 * \defgroup ssp_functions SSP Functions
 *  Functions definitions for the SSP setup
 *  @{
 */

/* SSP Functions Group: */
/**
 * \brief 	Initializes SSP.
 * \param	ps_Port		Pointer to LPC_SSPx port structure
 * \param	ls_Config	SSP configuration structure
 * \return	none
 */
void ecuDrv_ssp_Init(T_S_SSP_PORT *ps_Port, T_S_SSP_CONFIG ls_Config)
{
	SSP_CFG_Type SSP_ConfigStruct[1u];
	/* Fill SSP configuration structure */
	SSP_ConfigStruct[0].Databit = ls_Config.ul_Databit;
	SSP_ConfigStruct[0].CPHA = ls_Config.ul_CPHA;
	SSP_ConfigStruct[0].CPOL = ls_Config.ul_CPOL;
	SSP_ConfigStruct[0].Mode = ls_Config.ul_Mode;
	SSP_ConfigStruct[0].FrameFormat = ls_Config.ul_FrameFormat;
	SSP_ConfigStruct[0].ClockRate = ls_Config.ul_ClockRate;
	/* Call driver initializer */
	SSP_Init(ps_Port, SSP_ConfigStruct);
}

/**
 * \brief 	De-Initializes SSP.
 * \param	ps_Port	Pointer to LPC_SSPx port structure
 * \return	none
 */
void ecuDrv_ssp_DeInit(T_S_SSP_PORT *ps_Port)
{
	SSP_DeInit(ps_Port);
}

/**
 * \brief 	Initializes SSP configuration structure.
 * \param	ps_Config	Pointer to configuration structure
 * \return	none
 */
void ecuDrv_ssp_ConfigInit(T_S_SSP_CONFIG *ps_Config)
{
	ps_Config->ul_Databit = SSP_DATABIT_8;
	ps_Config->ul_CPHA = SSP_CPHA_1ST;
	ps_Config->ul_CPOL = SSP_CPOL_HIGH;
	ps_Config->ul_FrameFormat = SSP_FRAME_SPI;
	ps_Config->ul_Mode = SSP_MODE_MASTER;
	ps_Config->ul_ClockRate = SSP_DEFAULT_CLOCKRATE;
}

/**
 * \brief 	Sets the state of a SSP Port.
 * \param	ps_Port		Pointer to LPC_SSPx port structure
 * \param	le_State	New state of the SSP (E_ENABLE or E_DISABLE)
 * \return	none
 */
void ecuDrv_ssp_SetState(T_S_SSP_PORT *ps_Port, T_E_ENABLE le_State)
{
	SSP_Cmd(ps_Port, (FunctionalState)le_State);
}

/**
 * \brief 	Data transfer function.
 * \param	ps_Port			Pointer to LPC_SSPx port structure
 * \param	ps_DataConfig	Pointer to data configuration structure
 * \param	le_TransferType	Transfer type (polling or interrupt)
 * \return	Number of transferred bytes
 */
T_ULONG ecuDrv_ssp_DataTransfer(T_S_SSP_PORT *ps_Port, T_S_SSP_DATA_SETUP *ps_DataConfig, T_E_SSP_TRANSFER le_TransferType)
{
	SSP_DATA_SETUP_Type dataCfg[1];
	dataCfg[0].tx_data = ps_DataConfig->pv_TxData;
	dataCfg[0].tx_cnt = ps_DataConfig->ul_TxCounter;
	dataCfg[0].rx_data = ps_DataConfig->pv_RxData;
	dataCfg[0].rx_cnt = ps_DataConfig->ul_RxCounter;
	dataCfg[0].length = ps_DataConfig->ul_Length;
	dataCfg[0].status = ps_DataConfig->ul_Status;
	return SSP_ReadWrite(ps_Port, dataCfg, (SSP_TRANSFER_Type)le_TransferType);
}
/**@} end of group ssp_functions */
