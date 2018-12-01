/*
 * driverI2S.h
 *
 *  Created on: 3 oct. 2018
 *      Author: Federico Bua
 */


void envioDatos(uint32_t);
uint8_t esperoDatos(uint32_t *, uint8_t);
void inicTX_I2S (void);
void inicRX_I2S (void);
void InicializarADC(void);
void inicializar_I2S(void);


#define PROFUNDIDAD_TX 8
#define PROFUNDIDAD_RX 8


#define PUERTO_M0		 0
#define PIN_M0			 1
#define PUERTO_M1		 0
#define PIN_M1			 0
#define PUERTO_RST_ADC	 2
#define PIN_RST_ADC		 13




#ifndef PROJECTS_PRUEBA_I2S_INC_DRIVERI2S_H_
#define PROJECTS_PRUEBA_I2S_INC_DRIVERI2S_H_



#endif /* PROJECTS_PRUEBA_I2S_INC_DRIVERI2S_H_ */
