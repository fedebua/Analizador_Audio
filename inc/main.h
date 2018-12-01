

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define TAM_BUFFER 128 //Es 128 debido a que cualquier número mayor genera un problema de memoria en la lectura de debuggeo
#define EXPANSION_BUFFER 16 //defino un vector X veces más grande que 128 para poder hacerle la FFT (debe ser potencia de 2)

#define VECTOR_LLENO 2
#define DATO_NUEVO 1
#define SIN_DATO_NUEVO 0

#define LIBRE 1
#define OCUPADO 2

void initHardware (void);
int main(void);
