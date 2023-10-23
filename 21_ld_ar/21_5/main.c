#include <stdlib.h>
#include "led.h"
#include "uart.h"
#include "print.h"
#include "sleep.h"
#include "autoconf.h"

unsigned long start_of_heap_get(void){
	extern uint32_t _heap_start; /* Defined by the linker */
	return (unsigned long)&_heap_start;
}

int main(void){
	const uint32_t static_arr_1[10] = {0x11111111, 0x22222222, 0x33333333, 0x44444444, 0x55555555, 0x66666666, 0x77777777, 0x88888888, 0x99999999, 0xaaaaaaaa};
	const uint16_t static_arr_2[4] = {0xbaba, 0xdede, 0xcece, 0xfefe};
	const uint8_t static_arr_3[4] = {0xde, 0xad, 0xbe, 0xef};
	uint32_t *dynamic_arr_1;
	uint16_t *dynamic_arr_2;
	uint8_t *dynamic_arr_3;
	int i;
	
    led_init();
    uart_init();

	printf("The start of the HEAP segment: 0x%08X\n\r", start_of_heap_get());

	dynamic_arr_1 = (uint32_t *)malloc(sizeof(uint32_t)*10);

	for(i = 0; i < 10; i++){
		dynamic_arr_1[i] = static_arr_1[i];
	}

	dynamic_arr_2 = (uint16_t *)malloc(sizeof(uint16_t)*4);

	for(i = 0; i < 4; i++){
		dynamic_arr_2[i] = static_arr_2[i];
	}

	printf("\n dynamic_arr_1[ ] = {\n\r");
	for(i = 0; i < 10; i++){
		printf("0x%08X\n\r", dynamic_arr_1[i]);
	}
	printf("}\n\r");

	printf("\n dynamic_arr_2[ ] = {\n\r");
	for(i = 0; i < 4; i++){
		printf("0x%04X\n\r", dynamic_arr_2[i]);
	}
	printf("}\n\r");

	free(dynamic_arr_1);

	dynamic_arr_3 = (uint8_t *)malloc(sizeof(uint16_t)*4);

	for(i = 0; i < 4; i++){
		dynamic_arr_3[i] = static_arr_3[i];
	}

	printf("\n dynamic_arr_3[ ] = {\n\r");
	for(i = 0; i < 4; i++){
		printf("0x%02X\n\r", dynamic_arr_3[i]);
	}
	printf("}\n\r");

	free(dynamic_arr_2);
	free(dynamic_arr_3);

	while (1){
        	led_set();
       	usleep(1000000);
        	led_clear();
        	usleep(1000000);
	}
}

