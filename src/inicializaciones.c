/*
 * inicializaciones.c
 *
 *  Created on: 3 oct. 2018
 *      Author: Federico Bua
 */

#include "board.h"
#include "driverI2S.h"
#include "main.h"

void initHardware(void)
{
    SystemCoreClockUpdate();

    /*En el Infotronic*/
    Board_Init();
    /*En la placa del analizador*/
    //inicializarLed0();

    InicializarADC();
    inicializar_I2S();

}

void inicTX_I2S(void)
{
	I2S_AUDIO_FORMAT_T I2S_ConfigTX; //Podría declarar una estructura y pasar el argumento a Chip_I2S_RxConfig(..,&I2S_configuracioN)
	I2S_ConfigTX.ChannelNumber=1; //Elijo (1=mono) (2=stereo)
	I2S_ConfigTX.SampleRate=96000; //Elijo 96KHz (Máximo que permite LPC1769)
	I2S_ConfigTX.WordWidth=24; //Elijo 24 bits de palabra aunque luego la función lo pone en 32

	/*=================================[Configuración PINSEL]=============================================*/
	Chip_IOCON_PinMux(LPC_IOCON, 0 , 7, IOCON_MODE_INACT, IOCON_FUNC1 ); //Configuro P0.7 como I2STX_CLK
	Chip_IOCON_PinMux(LPC_IOCON, 0 , 8, IOCON_MODE_INACT, IOCON_FUNC1 ); //Configuro P0.8 como I2STX_WS
	Chip_IOCON_PinMux(LPC_IOCON, 0 , 9, IOCON_MODE_INACT, IOCON_FUNC1 ); //Configuro P0.9 como I2STX_SDA

	/*=================================[Configuraciones opciones]==========================================*/
	/*Configuraciones opciones:
	 * Con TxModeConfig deshabilito MCLK, 4-pin y el clock es el modo por defecto
	 * El bitrate será el por defecto
	 * Al seleccionar divisor 0, 0 dejo el MCLK como está*/
	Chip_I2S_SetTxXYDivider(LPC_I2S, 0, 0);
	Chip_I2S_SetTxBitRate(LPC_I2S,0);
	Chip_I2S_TxModeConfig(LPC_I2S, I2S_RXMODE_CLKSEL(0), 0, 0);
	/*=======================================================================================================*/

	Chip_I2S_TxConfig(LPC_I2S, &I2S_ConfigTX);
	Chip_I2S_TxStop(LPC_I2S);
	Chip_I2S_TxStart(LPC_I2S);
	Chip_I2S_Int_TxCmd(LPC_I2S,DISABLE,PROFUNDIDAD_TX);

}

void InicializarADC(void)
{
    Chip_GPIO_Init(LPC_GPIO);
    Chip_IOCON_Init(LPC_IOCON);
    /*Defino como salidas a todos los pines de control del ADC*/
    Chip_GPIO_SetPinDIR(LPC_GPIO, PUERTO_M0, PIN_M0, true);
    Chip_GPIO_SetPinDIR(LPC_GPIO, PUERTO_M1, PIN_M1, true);
    Chip_GPIO_SetPinDIR(LPC_GPIO, PUERTO_RST_ADC, PIN_RST_ADC, true);
    /*Seteo RST=1 para que el ADC comience a convertir*/
    /*Seteo del modo de funcionamiento Double speed
    M1	 M0	 		Mode Sample Rate (Fs) 			De-Emphasis
    0	 0 		Single Speed Mode 4 kHz - 50 kHz	  44.1 kHz
    0 	 1 		Single Speed Mode 4 kHz - 50 kHz 		Off
    1 	 0 		Double Speed Mode 50 kHz - 100 kHz 		Off
    1	 1 		Quad Speed Mode 100 kHz - 200 kHz 		Off*/
    Chip_GPIO_SetPinState(LPC_GPIO, PUERTO_M0, PIN_M0, false);
    Chip_GPIO_SetPinState(LPC_GPIO, PUERTO_M1, PIN_M1, true);
    Chip_GPIO_SetPinState(LPC_GPIO, PUERTO_RST_ADC, PIN_RST_ADC, true);
}



void inicRX_I2S(void)
{
	I2S_AUDIO_FORMAT_T I2S_ConfigRX; //Podría declarar una estructura y pasar el argumento a Chip_I2S_RxConfig(..,&I2S_configuracioN)
	I2S_ConfigRX.ChannelNumber=1; //Elijo (1=mono) (2=stereo)
	I2S_ConfigRX.SampleRate=96000; //Elijo 96KHz (Máximo que permite LPC1769)
	I2S_ConfigRX.WordWidth=32; //Elijo 24 bits de palabra

	/*=================================[Configuración PINSEL]=============================================*/
	Chip_IOCON_PinMux(LPC_IOCON, 0 , 23, IOCON_MODE_INACT, IOCON_FUNC2 ); //Configuro P0.23 como I2SRX_CLK
	Chip_IOCON_PinMux(LPC_IOCON, 0 , 24, IOCON_MODE_INACT, IOCON_FUNC2 ); //Configuro P0.24 como I2SRX_WS
	Chip_IOCON_PinMux(LPC_IOCON, 0 , 25, IOCON_MODE_INACT, IOCON_FUNC2 ); //Configuro P0.25 como I2SRX_SDA
	//Chip_IOCON_PinMux(LPC_IOCON, 4 , 28, IOCON_MODE_INACT, IOCON_FUNC1 ); //Configuro P4.28 como RX_MCLK

	Chip_I2S_RxConfig(LPC_I2S, &I2S_ConfigRX);
	LPC_I2S -> DAI |= I2S_SLAVE_MODE;	//RxConfig pone como MASTER, se modifica para que RX sea SLAVE
	Chip_I2S_RxStop(LPC_I2S);
	Chip_I2S_RxStart(LPC_I2S);
	Chip_I2S_SetRxBitRate(LPC_I2S,0); //Bit Rate = 0+1=> no divide el clock que le llega
	Chip_I2S_Int_RxCmd(LPC_I2S,ENABLE,PROFUNDIDAD_RX);
}
void inicializar_I2S()
{
	Chip_I2S_Init(LPC_I2S); //Activo PCONP
	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_I2S, 1);  //En teoría esto configura el PCLK de I2S para igualarlo al CCLK
	//inicTX_I2S();
	inicRX_I2S();

	/*Acá inicializaría el DMA si utilizase*/

	NVIC_EnableIRQ(I2S_IRQn); //Habilito la interrupción en el ISER0
}
