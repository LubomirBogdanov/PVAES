#include "led.h"
#include "uart.h"
#include "print.h"
#include "sleep.h"
#include "autoconf.h"

extern float asm_rms(float dig3, float dig2, float dig1, float dig0);

int main(void){
	float val3 = 4.002503;
	float val2 = 4.233456;
	float val1 = 4.789317;
	float val0 = 4.220734;
	float my_result;
	volatile int i;
	
        led_init();
        uart_init();  

	my_result = asm_rms(val3, val2, val1, val0);

	//Expected output: 4.321294158
	printf("The result is --> %12.6f\n", my_result);

	while (1){
        	led_set();
       	usleep(1000000);
        	led_clear();
        	usleep(1000000);
	}
}

