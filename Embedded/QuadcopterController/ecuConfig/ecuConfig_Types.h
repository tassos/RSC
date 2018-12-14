/**
 * \file	ecuConfig_Types.h
 * \brief	Application type definitions
 * \details	Defines types and enumerators
 * \author	Cosmin Marcu
 * \date	04.05.2015
 * \version 1.0.1
 */

#ifndef ECUCONFIG_TYPES_H_
#define ECUCONFIG_TYPES_H_

#include "lpc17xx_libcfg_default.h"
#include "LPC17xx.h"
#include "system_LPC17xx.h"

/* Defines */
#define PRIVATE_FCT			static					//!< Static function definition
#define INLINE_FCT			inline					//!< Inline function definition
#define PRIVATE_DATA		static					//!< Static data definition
#define VOLATILE			volatile				//!< Volatile data definition

/* Define ADC port address */
#define ECU_ADC			   LPC_ADC					//!< ADC Port address

/* Define UART ports addresses */
#define ECU_UART0 		 LPC_UART0					//!< UART0 Port address
#define ECU_UART1  		 LPC_UART1					//!< UART1 Port address
#define ECU_UART2  		 LPC_UART2					//!< UART2 Port address
#define ECU_UART3  		 LPC_UART3					//!< UART3 Port address

/* Define Timer ports addresses */
#define ECU_TIMER0		  LPC_TIM0					//!< Timer 0 address
#define ECU_TIMER1		  LPC_TIM1					//!< Timer 1 address
#define ECU_TIMER2		  LPC_TIM2					//!< Timer 2 address
#define ECU_TIMER3		  LPC_TIM3					//!< Timer 3 address

/* Define SSP ports addresses */
#define ECU_SSP0 		  LPC_SSP0					//!< SSP0 Port address
#define ECU_SSP1  		  LPC_SSP1					//!< SSP1 Port address

/* Define I2C ports addresses */
#define ECU_I2C0 		  LPC_I2C0					//!< I2C0 Port address
#define ECU_I2C1 		  LPC_I2C1					//!< I2C1 Port address
#define ECU_I2C2 		  LPC_I2C2					//!< I2C2 Port address

/* Define CAN ports addresses */
#define ECU_CAN1		  LPC_CAN1					//!< CAN1 Port address
#define ECU_CAN2		  LPC_CAN2					//!< CAN2 Port address

/* Define CAN Acceptance Filter */
#define ECU_CAN_AF		  LPC_CANAF					//!< CAN Acceptance Filter

/* Macros */
#define	ECU_ENABLE_IRQ(x) NVIC_EnableIRQ(x) 		//!< Macro to IRQ Enable function
#define	ECU_DISABLE_IRQ(x) NVIC_DisableIRQ(x) 		//!< Macro to IRQ Disable function

/* Typedefs */
/* 1 byte type */
typedef unsigned char		T_UBYTE;				//!< 8 bit unsigned
typedef signed char			T_SBYTE;				//!< 8 bit signed

/* 2 bytes type */
typedef unsigned short int	T_UWORD;				//!< 16 bit unsigned
typedef signed short int	T_SWORD;				//!< 16 bit signed

/* 4 bytes type */
typedef unsigned long int	T_ULONG;				//!< 32 bit unsigned
typedef signed long int		T_SLONG;				//!< 32 bit signed

/**
 * @brief	Defines Boolean states
 */
typedef enum E_BOOL {
	E_FALSE = 0u,									//!< E_FALSE
	E_TRUE											//!< E_TRUE
} T_E_BOOL;

/**
 * @brief	Defines Error states
 */
typedef enum E_ERROR {
	E_SUCCESS = 0u,									//!< E_SUCCESS
	E_ERROR											//!< E_ERROR
} T_E_ERROR;

/**
 * @brief	Defines general Enable/Disable states
 */
typedef enum E_ENABLE {
	E_DISABLE = 0u,									//!< E_DISABLE
	E_ENABLE										//!< E_ENABLE
} T_E_ENABLE;

/**
 * @brief	Defines general status
 */
typedef enum E_STATUS {
	E_DISABLED = 0u,								//!< E_DISABLED
	E_ENABLED										//!< E_ENABLED
} T_E_STATUS;

/**
 * @brief	Defines general status
 */
typedef enum E_STD_STATUS {
	E_OK = 0u,										//!< E_OK
	E_NOT_OK										//!< E_NOT_OK
} T_E_STD_STATUS;

/**
 * @brief	Defines I/O pins direction
 */
typedef enum E_SIGNAL_DIRECTION {
	E_INPUT = 0u,									//!< E_INPUT
	E_OUTPUT										//!< E_OUTPUT
} T_E_SIGNAL_DIRECTION;

/**
 * @brief	Defines general On/Off states
 */
typedef enum E_SIGNAL_STATE {
	E_OFF = 0u,										//!< E_OFF
	E_ON											//!< E_ON
} T_E_SIGNAL_STATE;

/**
 * \brief	Defines the processor PORTs indexes
 */
typedef enum E_IOPORTS {
	E_IOPORT0 = 0u,									//!< HW IO port 0
	E_IOPORT1,                                      //!< HW IO port 1
	E_IOPORT2,                                      //!< HW IO port 2
	E_IOPORT3,                                      //!< HW IO port 3
	E_IOPORT4                                       //!< HW IO port 4
} T_E_IOPORTS;

/**
 * @brief	Defines reading status
 */
typedef enum E_READ_STATUS {
	E_NOTDONE = 0u,									//!< E_NOTDONE
	E_DONE											//!< E_DONE
} T_E_READ_STATUS;


/**
 * \brief	Defines the processor I/O pins indexes
 */
typedef enum E_IOPINS {
	E_IOPIN0 = 0u,                                  //!< HW IO pin 0
	E_IOPIN1,                                       //!< HW IO pin 1
	E_IOPIN2,                                       //!< HW IO pin 2
	E_IOPIN3,                                       //!< HW IO pin 3
	E_IOPIN4,                                       //!< HW IO pin 4
	E_IOPIN5,                                       //!< HW IO pin 5
	E_IOPIN6,                                       //!< HW IO pin 6
	E_IOPIN7,                                       //!< HW IO pin 7
	E_IOPIN8,                                       //!< HW IO pin 8
	E_IOPIN9,                                       //!< HW IO pin 9
	E_IOPIN10,                                      //!< HW IO pin 10
	E_IOPIN11,                                      //!< HW IO pin 11
	E_IOPIN12,                                      //!< HW IO pin 12
	E_IOPIN13,                                      //!< HW IO pin 13
	E_IOPIN14,                                      //!< HW IO pin 14
	E_IOPIN15,                                      //!< HW IO pin 15
	E_IOPIN16,                                      //!< HW IO pin 16
	E_IOPIN17,                                      //!< HW IO pin 17
	E_IOPIN18,                                      //!< HW IO pin 18
	E_IOPIN19,                                      //!< HW IO pin 19
	E_IOPIN20,                                      //!< HW IO pin 20
	E_IOPIN21,                                      //!< HW IO pin 21
	E_IOPIN22,                                      //!< HW IO pin 22
	E_IOPIN23,                                      //!< HW IO pin 23
	E_IOPIN24,                                      //!< HW IO pin 24
	E_IOPIN25,                                      //!< HW IO pin 25
	E_IOPIN26,                                      //!< HW IO pin 26
	E_IOPIN27,                                      //!< HW IO pin 27
	E_IOPIN28,                                      //!< HW IO pin 28
	E_IOPIN29,                                      //!< HW IO pin 29
	E_IOPIN30,                                      //!< HW IO pin 30
	E_IOPIN31                                       //!< HW IO pin 31
} T_E_IOPINS;

#endif /* ECUCONFIG_TYPES_H_ */
