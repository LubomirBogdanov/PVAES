#include <xgpio.h>
#include "xparameters.h"
#include "sleep.h"

XGpio output;

int main(){   
    XGpio_Initialize(&output, XPAR_AXI_GPIO_0_DEVICE_ID);
    XGpio_SetDataDirection(&output, 1, 0x0);
    XGpio_DiscreteWrite(&output, 1, 0x0f);	

    while(1){
        XGpio_DiscreteWrite(&output, 1, 0x08);
        usleep(100000);
        XGpio_DiscreteWrite(&output, 1, 0x00);
        usleep(100000);
    }

    return 0;
}
