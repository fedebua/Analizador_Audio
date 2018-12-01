

/*==================[inclusions]=============================================*/

#include "main.h"
#include "cdc_vcom.h"
#include "board.h"


xSemaphoreHandle semDato;


/*==================[external functions definition]==========================*/


int main(void)
{
	initHardware();

	xTaskCreate(cdcTask, (signed const char *)"cdc", 1024, 0, tskIDLE_PRIORITY+2, 0);
	vSemaphoreCreateBinary(semDato);
	xSemaphoreTake(semDato,0);


	vTaskStartScheduler();

	while(1);
}

/** @} doxygen end group definition */

/*==================[end of file]============================================*/
