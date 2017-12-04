/**\file 	hooks.c
 * \brief 	RTOS hooks
 * \details RTOS events hooks functions
 * \author 	Cosmin Marcu
 * \date 	20.12.2014
 */

//TODO: config assert
#include <assert.h>

/**
* \brief 	Free RTOS idle hook
* \details 	TBD.
*/
void vApplicationIdleHook(void)
{
	assert(1);
}

/**
* \brief 	Free RTOS tick hook
* \details 	TBD.
*/
void vApplicationTickHook(void)
{

}

/**
* \brief 	Free RTOS memory allocation fail hook
* \details 	TBD.
*/
void vApplicationMallocFailedHook(void)
{

}

