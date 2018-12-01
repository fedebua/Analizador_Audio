/*
 * tickHook.c
 *
 *  Created on: 30 nov. 2018
 *      Author: Federico Bua
 */
#include "board.h"
#include "main.h"
//uint32_t prompt=0, datoNuevo=0;
//extern xSemaphoreHandle semDato;
/*
void vApplicationTickHook(void)
{
	static uint32_t contador=0;
	portBASE_TYPE xTaskSwitchRequired = pdFALSE;
	if(prompt) //En caso de que esté conectado
	{
		contador+=10000;
		datoNuevo=contador;
		Board_LED_Toggle(0);
		xSemaphoreGiveFromISR(semDato, &xTaskSwitchRequired);
	}
	if(contador>=16000000)
		contador=0;

	portEND_SWITCHING_ISR(xTaskSwitchRequired);
}*/
