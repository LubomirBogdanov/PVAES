#include "led.h"
#include "uart.h"
#include "print.h"
#include "sleep.h"
#include "autoconf.h"

int main(void){
	float my_fpu_array_1[10] = {4.00, 16.00, 3.504, 350.768, 1.14, 1256.13, 4096.00, 56.1212, 98.111, 311.256};
	float my_sqrt[10];
	volatile int i;

        led_init();
        uart_init();       

	for(i = 0; i < 10; i++){
... Place in-line assembly here ...
	}	

	//Expected output:
	//2, 4, 1.871897, 18.728802, 1.067708, 35.441925, 64, 7.491408, 9.905100, 17.642448
	printf("\nmy_sqrt[] = {");
	for(i = 0; i < 10; i++){
		printf("%12.6f, ", my_sqrt[i]);
	}
	printf("}\n");


	while (1){
        	led_set();
       	usleep(1000000);
        	led_clear();
        	usleep(1000000);
	}
}

