#include "led.h"

XGpio output;

void led_init(void){
    XGpio_Initialize(&output, XPAR_AXI_GPIO_0_DEVICE_ID);
    XGpio_SetDataDirection(&output, 1, 0x0);
    XGpio_DiscreteWrite(&output, 1, 0x00);
}

void led_set(void){
	XGpio_DiscreteWrite(&output, 1, 0x08);
}

void led_clear(void){
	XGpio_DiscreteWrite(&output, 1, 0x00);
}
