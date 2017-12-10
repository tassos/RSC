/**\file 	ecuAppl_AppExe.c
 * \brief 	Accessories ECU application
 * \details Implements the mail function call for running the Accessories ECU application
 * \author 	Cosmin Marcu
 * \date 	04.05.2017
 */

/* System and general headers */
#include "LPC17xx.h"
#include "ecuAppl_AppExe.h"

#include "ecuAppl_GPS.h"
#include "ecuConfig_Board.h"
#include "ecuConfig_Types.h"

/* Driver headers */
#include "ecuDrv_adc.h"
#include "ecuDrv_gpio.h"
#include "ecuDrv_i2c.h"
#include "ecuDrv_ssp.h"
#include "ecuDrv_sys.h"
#include "ecuDrv_timer.h"

/* Modules headers */
#include "ecuAppl_Keyboard.h"
#include "ecuAppl_LEDs.h"
#include "ecuAppl_NFC.h"
#include "ecuAppl_Scheduler.h"
#include "ecuAppl_Ethernet.h"
#include "ecuAppl_TCPHandler.h"
#include "ecuAppl_Pot.h"

/* Defines */
#define	APPEXE_TCP_PORT		(7u)

/* Private variables */
PRIVATE_DATA T_E_APP_STATE re_ecuAppl_AppExe_State = E_APP_STATE_INIT;				//!< Main application state variable
/* IRQ Handlers */
/**
* @brief 	External GPIO3 interrupt handler
* @details 	TBD.
*/
void EINT3_IRQHandler(void)
{
	if(E_TRUE == ecuDrv_gpio_GetInterruptStatus(AOAA_SW2_PORT, AOAA_SW2_PIN, E_GPIO_RISING))
	{
		rcpot_SetState(SETPOINT_0);
		ecuDrv_gpio_ClearInterrupt(AOAA_SW2_PORT, AOAA_SW2_PIN);
	}

	if(E_TRUE == ecuDrv_gpio_GetInterruptStatus(AOAA_SW2_PORT, AOAA_SW2_PIN, E_GPIO_FALLING))
	{
		ecuDrv_gpio_ClearInterrupt(AOAA_SW2_PORT, AOAA_SW2_PIN);
	}

	if(E_TRUE == ecuDrv_gpio_GetInterruptStatus(AOAA_SW3_PORT, AOAA_SW3_PIN, E_GPIO_RISING))
	{
		ecuDrv_gpio_ClearInterrupt(AOAA_SW3_PORT, AOAA_SW3_PIN);
	}

	if(E_TRUE == ecuDrv_gpio_GetInterruptStatus(AOAA_SW3_PORT, AOAA_SW3_PIN, E_GPIO_FALLING))
	{
		rcpot_SetState(SETPOINT_1);
		ecuDrv_gpio_ClearInterrupt(AOAA_SW3_PORT, AOAA_SW3_PIN);
	}
}

/* Private functions */
PRIVATE_FCT void ecuAppl_AppExe_SetupHardware(void);

/**
* @brief 	Hardware initialization
* @details 	Initialize system clock and I/O ports/pins
*/
PRIVATE_FCT void ecuAppl_AppExe_SetupHardware(void)
{
	/* Refresh system clock */
	ecuDrv_sys_CoreClockUpdate();
	/* Initialize core system */
	ecuDrv_sys_Init();
	/* Initialize GPIO pins */
	/* RGB LEDs */
	ecuAppl_LEDs_Init();
	/* Keyboard init */
	ecuAppl_Keyboard_Init();
	/* NFC init */
	ecuAppl_NFC_Init();
	/* ADC init */
	ecuAppl_Pot_Init();
	/* User buttons */
	ecuDrv_gpio_SetDirection(AOAA_SW2_PORT, AOAA_SW2_PIN, E_INPUT);
	ecuDrv_gpio_SetDirection(AOAA_SW3_PORT, AOAA_SW3_PIN, E_INPUT);
	/* Enable interrupts */
	ecuDrv_gpio_EnableInterrupt(AOAA_SW3_PORT, AOAA_SW3_PIN, E_GPIO_FALLING);
	ecuDrv_gpio_EnableInterrupt(AOAA_SW2_PORT, AOAA_SW2_PIN, E_GPIO_RISING);
	NVIC_EnableIRQ(EINT2_IRQn);
	NVIC_EnableIRQ(EINT3_IRQn);
	/* Init Application Scheduler */
	ecuAppl_Scheduler_Init();
	/* Init GPS module */
	ecuAppl_GPS_Init();
	/* Init timer 1 for ETH task */
	ecuDrv_timer_Timer1_Init();
	(void)ecuAppl_Ethernet_Init();
	ecuAppl_TCPHandler_Init(APPEXE_TCP_PORT);

	/* Switch application to running state */
	re_ecuAppl_AppExe_State = E_APP_STATE_RUNNING;
}

/**
* @brief 	Main code block
* @details 	Initialize system and create tasks
*/
int main(void)
{
	/* Main application state machine */
	while(E_TRUE)
	{
		switch(re_ecuAppl_AppExe_State)
		{
		case E_APP_STATE_INIT:
			/* Initialize hardware */
			ecuAppl_AppExe_SetupHardware();
			break;
		case E_APP_STATE_RUNNING:
			ecuAppl_Ethernet_Task_2s();
			ecuAppl_Pot_Task50ms();
			//ecuAppl_GPS_SM();
			break;
		case E_APP_STATE_ERROR:
			break;
		default:
			break;
		}
	}
	/* Exit main application */
	return (int)E_ERROR;
}
