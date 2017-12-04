/**\file 	rc_app.c
 * \brief 	Embedded Artists AOAA Cortex M3 Template application
 * \details Sample code for Embedded Artists AOAA board
 * \author 	Cosmin Marcu
 * \date 	27.05.2015
 */

/* System and general headers */
#include "LPC17xx.h"
#include "rc_app.h"

#include "rc_config.h"
#include "rc_version.h"
#include "rc_stdtypedefs.h"
#include "rc_board.h"

/* Driver headers */
#include "rc_system.h"
#include "rc_gpio.h"
#include "rc_uart.h"
#include "rc_adc.h"

/* Modules headers */
#include "rc_leds.h"

/* FreeRTOS headers */
#if RC_USE_FREERTOS
	#include "FreeRTOS.h"
	#include "task.h"
	#include "FreeRTOSConfig.h"
#endif

/* Tasks headers */
#include "tasks/rc_task_leds/rc_task_leds.h"

/* IRQ Handlers */
/**
* @brief 	External GPIO3 interrupt handler
* @details 	TBD.
*/
void EINT3_IRQHandler(void)
{
	//Button1 Push
	if(E_RC_TRUE == rcgpio_GetInterruptStatus(RC_SW2_PORT, RC_SW2_PIN, E_RCGPIO_RISING))
	{
		rcleds_SetState(E_RCLEDS_STATE_RED);
		rcgpio_ClearInterrupt(RC_SW2_PORT, RC_SW2_PIN);
	}
	//Button1 Release
	if(E_RC_TRUE == rcgpio_GetInterruptStatus(RC_SW2_PORT, RC_SW2_PIN, E_RCGPIO_FALLING))
	{
		rcgpio_ClearInterrupt(RC_SW2_PORT, RC_SW2_PIN);
	}

	//Button2 Push
	if(E_RC_TRUE == rcgpio_GetInterruptStatus(RC_SW3_PORT, RC_SW3_PIN, E_RCGPIO_RISING))
	{
		rcleds_SetState(E_RCLEDS_STATE_BLUE);
		rcgpio_ClearInterrupt(RC_SW3_PORT, RC_SW3_PIN);
	}
	//Button2 Release
	if(E_RC_TRUE == rcgpio_GetInterruptStatus(RC_SW3_PORT, RC_SW3_PIN, E_RCGPIO_FALLING))
	{
		rcgpio_ClearInterrupt(RC_SW3_PORT, RC_SW3_PIN);
	}
}

/* Private functions */
PRIVATE_FCT void rcapp_SetupHardware(void);

/**
* @brief 	Hardware initialization
* @details 	Initialize system clock and I/O ports/pins
*/
PRIVATE_FCT void rcapp_SetupHardware(void)
{
	/* Refresh system clock */
	rcsys_CoreClockUpdate();
	/* Initialize core system */
	rcsys_Init();
	/* Initialize LEDs pins */
	rcleds_Init();
	/* Initialize User buttons */
	rcgpio_SetDirection(RC_SW2_PORT, RC_SW2_PIN, E_RC_INPUT);
	rcgpio_SetDirection(RC_SW3_PORT, RC_SW3_PIN, E_RC_INPUT);
	/* Enable interrupts */
	rcgpio_EnableInterrupt(RC_SW2_PORT, RC_SW2_PIN, E_RCGPIO_RISING);
	rcgpio_EnableInterrupt(RC_SW2_PORT, RC_SW2_PIN, E_RCGPIO_FALLING);
	rcgpio_EnableInterrupt(RC_SW3_PORT, RC_SW3_PIN, E_RCGPIO_RISING);
	rcgpio_EnableInterrupt(RC_SW3_PORT, RC_SW3_PIN, E_RCGPIO_FALLING);
	NVIC_EnableIRQ(EINT3_IRQn);
}

/**
* @brief 	Main code block
* @details 	Initialize system and create tasks
*/
int main(void)
{
	/* Initialize hardware */
	rcapp_SetupHardware();
	/* Create application tasks */
	xTaskCreate(rctask_LEDs, (const char *) "LEDs task",
			RC_STACKSIZE_TASK_LEDS, NULL, (tskIDLE_PRIORITY + 1UL),
			&xHandleLEDs);
	/* Start FreeRTOS task scheduler */
	vTaskStartScheduler();
	/* Exit main application */
	return (int)E_RC_ERROR;
}
