/*
 * driverI2S.c
 *
 *  Created on: 3 oct. 2018
 *      Author: Federico Bua
 */

#include "board.h"
#include "driverI2S.h"
#include "main.h"

/*
extern uint32_t buffer[TAM_BUFFER];
extern uint32_t flag_dato_listo;
extern  uint32_t buffer_multiplos[EXPANSION_BUFFER];
*/
uint32_t prompt=0, datoNuevo=0;
extern xSemaphoreHandle semDato;

void I2S_IRQHandler(void)
{
	static uint32_t aux=0,contador=0;
	aux=Chip_I2S_Receive(LPC_I2S);
	portBASE_TYPE xTaskSwitchRequired = pdFALSE;

	contador++;
	if(contador>=9600)
	{
		contador=0;
		Board_LED_Toggle(0);
	}

	if(prompt) //En caso de que esté conectado
	{


		aux=aux>>8;//Para que no sea mayor que los 24bits (los últimos 8 son 0)

		if(aux<8388608)
			aux+=8388608;
		else
			aux-=8388608;

		if(aux!=8388608) //Elimino datos error
			datoNuevo=aux;

		xSemaphoreGiveFromISR(semDato, &xTaskSwitchRequired);
	}
	portEND_SWITCHING_ISR(xTaskSwitchRequired);
}


/*
uint8_t esperoDatos(uint32_t * vector,uint8_t estado)
{
	static uint32_t i=0,j=0;
	if(estado==OCUPADO)
	{
		if(flag_dato_listo==1)
		{
			if(j<EXPANSION_BUFFER)
			{
				for(i=0;i<TAM_BUFFER;i++)
				{
					vector[i+j*TAM_BUFFER]=buffer[i];
					if(i+j*TAM_BUFFER == 128)
						return 8;
				}
				flag_dato_listo=0;
				i=0;
				j++;
				return DATO_NUEVO;
			}
			else
			{
				i=0;
				flag_dato_listo=0;
				j=0;
				return VECTOR_LLENO;
			}
		}
	}
	return SIN_DATO_NUEVO;
}



void envioDatos(uint32_t multiplo)
{
	uint32_t aux=0;
	static uint32_t contador=0;
	while(aux<TAM_BUFFER)
			{
				while(Chip_I2S_GetTxLevel(LPC_I2S)>=PROFUNDIDAD_TX);
				Chip_I2S_Send(LPC_I2S,contador++);
				aux++;
			}

}
*/
