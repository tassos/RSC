/**
 * \file	rc_stdtypedefs.h
 * \brief	Application type definitions
 * \details	Defines types and enumerators
 * \author	Cosmin Marcu
 * \date	27.05.2015
 * \version 1.0.1
 */

#ifndef RC_STDTYPEDEFS_H_
#define RC_STDTYPEDEFS_H_

#include "LPC17xx.h"
#include "lpc17xx_libcfg_default.h"
#include "system_LPC17xx.h"
#include "core_cmFunc.h"

/* Defines */
#define PRIVATE_FCT			static					//!< Static function definition
#define INLINE_FCT			inline					//!< Inline function definition
#define PRIVATE_DATA		static					//!< Static data definition
#define VOLATILE			volatile				//!< Volatile data definition

#define RC_DISABLED				0u					//!< Disabled
#define RC_ENABLED				1u					//!< Enabled

/* Define UART ports addresses */
#define RC_UART0 		 LPC_UART0					//!< UART0 Port address
#define RC_UART1  		 LPC_UART1					//!< UART1 Port address
#define RC_UART2  		 LPC_UART2					//!< UART2 Port address
#define RC_UART3  		 LPC_UART3					//!< UART3 Port address

#define RC_TIMER0		  LPC_TIM0					//!< Timer 0 address
#define RC_TIMER1		  LPC_TIM1					//!< Timer 1 address
#define RC_TIMER2		  LPC_TIM2					//!< Timer 2 address
#define RC_TIMER3		  LPC_TIM3					//!< Timer 3 address

/* Macros */
#define	RC_ENABLE_IRQ(x) NVIC_EnableIRQ(x) 			//!< Macro to IRQ Enable function

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
typedef enum E_RC_BOOL {
	E_RC_FALSE = 0u,								//!< E_RC_FALSE
	E_RC_TRUE										//!< E_RC_TRUE
} T_E_RC_BOOL;

/**
 * @brief	Defines Error states
 */
typedef enum E_RC_ERROR {
	E_RC_SUCCESS = 0u,								//!< E_RC_SUCCESS
	E_RC_ERROR										//!< E_RC_ERROR
} T_E_RC_ERROR;

/**
 * @brief	Defines general Enable/Disable states
 */
typedef enum E_RC_ENABLE {
	E_RC_DISABLE = 0u,								//!< E_RC_DISABLE
	E_RC_ENABLE										//!< E_RC_ENABLE
} T_E_RC_ENABLE;

/**
 * @brief	Defines general status
 */
typedef enum E_RC_STATUS {
	E_RC_DISABLED = 0u,								//!< E_RC_DISABLED
	E_RC_ENABLED									//!< E_RC_ENABLED
} T_E_RC_STATUS;

/**
 * @brief	Defines I/O pins direction
 */
typedef enum E_RC_SIGNAL_DIRECTION {
	E_RC_INPUT = 0u,								//!< E_RC_INPUT
	E_RC_OUTPUT										//!< E_RC_OUTPUT
} T_E_RC_SIGNAL_DIRECTION;

/**
 * @brief	Defines general On/Off states
 */
typedef enum E_RC_SIGNAL_STATE {
	E_RC_OFF = 0u,									//!< E_RC_OFF
	E_RC_ON											//!< E_RC_ON
} T_E_RC_SIGNAL_STATE;

/**
 * \brief	Defines the processor PORTs indexes
 */
typedef enum E_RC_IOPORTS {
	E_RC_IOPORT0 = 0u,
	E_RC_IOPORT1,
	E_RC_IOPORT2,
	E_RC_IOPORT3,
	E_RC_IOPORT4
} T_E_RC_IOPORTS;

/**
 * \brief	Defines the processor I/O pins indexes
 */
typedef enum E_RC_IOPINS {
	E_RC_IOPIN0 = 0u,
	E_RC_IOPIN1,
	E_RC_IOPIN2,
	E_RC_IOPIN3,
	E_RC_IOPIN4,
	E_RC_IOPIN5,
	E_RC_IOPIN6,
	E_RC_IOPIN7,
	E_RC_IOPIN8,
	E_RC_IOPIN9,
	E_RC_IOPIN10,
	E_RC_IOPIN11,
	E_RC_IOPIN12,
	E_RC_IOPIN13,
	E_RC_IOPIN14,
	E_RC_IOPIN15,
	E_RC_IOPIN16,
	E_RC_IOPIN17,
	E_RC_IOPIN18,
	E_RC_IOPIN19,
	E_RC_IOPIN20,
	E_RC_IOPIN21,
	E_RC_IOPIN22,
	E_RC_IOPIN23,
	E_RC_IOPIN24,
	E_RC_IOPIN25,
	E_RC_IOPIN26,
	E_RC_IOPIN27,
	E_RC_IOPIN28,
	E_RC_IOPIN29,
	E_RC_IOPIN30,
	E_RC_IOPIN31
} T_E_RC_IOPINS;

#endif /* RC_STDTYPEDEFS_H_ */
