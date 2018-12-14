/**
 * \file	ecuDrv_can.h
 * \brief	ecuDrv_can header file
 * \details	Exports the functions used for CAN configuration and initialization.
 * \author	Cosmin Marcu
 * \date	04.05.2017
 * \version 1.0.1
 */

#ifndef ECUDRV_CAN_H_
#define ECUDRV_CAN_H_

/* Includes */
#include "ecuConfig_Types.h"
#include "lpc17xx_can.h"
#include "lpc17xx_pinsel.h"

/**
 * @brief	Defines the CAN type
 */
typedef LPC_CAN_TypeDef	T_S_CAN_PORT;

/**
 * @brief	Defines the CAN Acceptance Filter type
 */
typedef LPC_CANAF_TypeDef T_S_CAN_AF;

/**
 * @brief Error values that functions can return
 */
typedef enum E_CAN_ERR{
	E_CAN_ERR_OK = 1, 				    //!< No error
	E_CAN_ERR_OBJECTS_FULL,		 	    //!< No more rx or tx objects available
	E_CAN_ERR_OBJ_NOT_RCV, 			    //!< Full CAN object not received
	E_CAN_ERR_NO_RECEIVE_DATA, 		    //!< No have receive data available
	E_CAN_ERR_AF_ENTRY,		 		    //!< Entry load in AFLUT is unvalid
	E_CAN_ERR_CONFLICT_ID,	 		    //!< Conflict ID occur
	E_CAN_ERR_ENTRY_NOT_EXIT			//!< Entry remove outo AFLUT is not exit
} T_E_CAN_ERR;

/**
 * @brief CAN ID format definition
 */
typedef enum E_CAN_FORMAT {
	E_CAN_FORMAT_STANDARD = 0,			//!< Use standard ID format (11 bit ID)
	E_CAN_FORMAT_EXTENDED				//!< Use extended ID format (29 bit ID)
} T_E_CAN_FORMAT;

/**
 * @brief Symbolic names for type of CAN message
 */
typedef enum E_CAN_FRAMETYPE {
	E_CAN_FRAMETYPE_DATA= 0,		 	//!< Data frame
	E_CAN_FRAMETYPE_REMOTE				//!< Remote frame
} T_E_CAN_FRAMETYPE;

/**
 * @brief CAN interrupt enable type definition
 */
typedef enum E_CAN_IRQTYPE {
	E_CAN_IRQTYPE_RIE = 0, 				//!< CAN Receiver Interrupt Enable
	E_CAN_IRQTYPE_TIE1, 				//!< CAN Transmit Interrupt Enable
	E_CAN_IRQTYPE_EIE, 					//!< CAN Error Warning Interrupt Enable
	E_CAN_IRQTYPE_DOIE, 				//!< CAN Data Overrun Interrupt Enable
	E_CAN_IRQTYPE_WUIE, 				//!< CAN Wake-Up Interrupt Enable
	E_CAN_IRQTYPE_EPIE, 				//!< CAN Error Passive Interrupt Enable
	E_CAN_IRQTYPE_ALIE, 				//!< CAN Arbitration Lost Interrupt Enable
	E_CAN_IRQTYPE_BEIE, 				//!< CAN Bus Error Interrupt Enable
	E_CAN_IRQTYPE_IDIE, 				//!< CAN ID Ready Interrupt Enable
	E_CAN_IRQTYPE_TIE2, 				//!< CAN Transmit Interrupt Enable for Buffer2
	E_CAN_IRQTYPE_TIE3, 				//!< CAN Transmit Interrupt Enable for Buffer3
	E_CAN_IRQTYPE_FCE					//!< FullCAN Interrupt Enable
} T_E_CAN_IRQTYPE;

/**
 * \brief Acceptance Filter Mode type definition
 */
typedef enum E_CAN_AFMODE {
	E_CAN_AFMODE_NORMAL = 0, 			//!< Normal Mode
	E_CAN_AFMODE_OFF, 					//!< Acceptance Filter Off Mode
	E_CAN_AFMODE_BYPASS, 				//!< Acceptance Filter Bypass Mode
	E_CAN_AFMODE_FULL					//!< FullCAN Mode Enhancement
} T_E_CAN_AFMODE;

/**
 * @brief CAN Message type
 */
typedef struct {
	T_ULONG ul_Id;			 			//!< 29 or 11 bit identifier, it depend on "format" value
	T_UBYTE ub_DataA[4]; 				//!< Data field A
	T_UBYTE ub_DataB[4]; 				//!< Data field B
	T_UBYTE ub_Length;		 			//!< Length of data field in bytes
	T_E_CAN_FORMAT e_Format;	 		//!< Identifier Format
	T_E_CAN_FRAMETYPE e_FrameType;		//!< CAN Frame type
} T_S_CAN_MESSAGE;

/* Exported CAN functions group: */
extern void ecuDrv_can_Init(T_S_CAN_PORT *ps_Port, T_ULONG lul_Baudrate);
extern void ecuDrv_can_DeInit(T_S_CAN_PORT *ps_Port);
extern void ecuDrv_can_SetInterrupt(T_S_CAN_PORT *ps_Port, T_E_CAN_IRQTYPE le_CAN_IRQType, T_E_ENABLE le_CAN_IRQState);
extern T_ULONG ecuDrv_can_GetInterruptStatus(T_S_CAN_PORT *ps_Port);
extern void ecuDrv_can_SetAFMode(T_S_CAN_AF *ps_CAN_AF, T_E_CAN_AFMODE le_CAN_AFMode);
extern T_E_ERROR ecuDrv_can_SendMessage(T_S_CAN_PORT *ps_Port, T_S_CAN_MESSAGE *ps_Message);
extern T_E_ERROR ecuDrv_can_ReceiveMessage(T_S_CAN_PORT *ps_Port, T_S_CAN_MESSAGE *ps_Message);
#endif /* ECUDRV_CAN_H_ */
