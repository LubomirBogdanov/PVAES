#include "led.h"
#include "uart.h"
#include "print.h"
#include "sleep.h"
#include "autoconf.h"



int main(void){
	float val3 = 4.002503;
	float val2 = 4.233456;
	float val1 = 4.789317;
	float val0 = 4.220734;
	float my_result;
	volatile int i;
	
        led_init();
        uart_init();  

	Напишете функция, работеща със стандартната библиотека math ...

	//Expected output: 4.321294158
	printf("The result is --> %12.6f\n", my_result);

	while (1){
        	led_set();
       	usleep(1000000);
        	led_clear();
        	usleep(1000000);
	}
}

