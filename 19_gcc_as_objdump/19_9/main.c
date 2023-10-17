#include "led.h"
#include "uart.h"
#include "print.h"
#include "sleep.h"
#include "autoconf.h"

int main(void){   
   float my_fpu_array_1[10] = {1.345239, 1.774125, 57865.412737, 0.850072, 16.142938, 4958.284851, 927.674384, 404.404121, 312.500056, 311.658473};
   float my_fpu_array_2[10] = {1.785993, 1.550390, 55000.328467, 0.851200, 19.372777, 4933.924562, 927.000993, 400.078463, 310.349112, 314.693125};
   float my_fpu_mean[10];
   volatile int i;
	
   led_init();
   uart_init();
   
   for(i = 0; i < 10; i++){
	my_fpu_mean[i] = (my_fpu_array_1[i] + my_fpu_array_2[i])/2;
   }

   //Expected output:     
   //1.565616, 1.662257,  56432.871094, 0.850636, 17.757858,  4946.104492,  927.337646,  402.241272, 311.424591, 313.175781,
   printf("\nmy_fpu_mean[] = {");
   for(i = 0; i < 10; i++){
	printf("%12.6f, ", my_fpu_mean[i]);
   }
   printf("}\n");   

    while(1){
        led_set();
        usleep(1000000);
        led_clear();
        usleep(1000000);
    }

    return 0;
}
