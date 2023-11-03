#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xparameters.h"

#define ABS_GRADIENT_OUT_BASE	XPAR_ABS_GRADIENT_OUT_0_S00_AXI_BASEADDR

typedef struct {
	int32_t grad_0; //0x00
	int32_t grad_1; //0x04
	int32_t grad_2; //0x08
	int32_t grad_3; //0x0c
	int32_t grad_4; //0x10
	int32_t grad_5; //0x14
	int32_t grad_out; //0x18

	int32_t abs_in0; //0x1c
	int32_t abs_in1; //0x20
	int32_t abs_div; //0x24
	uint32_t abs_out; //0x28

	uint32_t abs_interrupt; //0x2c
	uint32_t gpio_out; //0x30
}abs_gradient_out_t;

#define ABSGRADOUT0	((volatile abs_gradient_out_t *) ABS_GRADIENT_OUT_BASE)

int main(){
	int i = 0;

	init_platform();

	print("Starting ...\n\r");

	while(1){
		ABSGRADOUT0->abs_interrupt = 0x01;

		ABSGRADOUT0->gpio_out = 0x1;

		ABSGRADOUT0->grad_0 = i + 2;
		ABSGRADOUT0->grad_1 = i + 5;
		ABSGRADOUT0->grad_2 = i + 2;
		ABSGRADOUT0->grad_3 = i - 5;
		ABSGRADOUT0->grad_4 = i - 5;
		ABSGRADOUT0->grad_5 = i - 5;

		ABSGRADOUT0->abs_div = 4;
		ABSGRADOUT0->abs_in0 = i - 50;
		ABSGRADOUT0->abs_in1 = i - 50;

		ABSGRADOUT0->abs_out;

		i++;

		ABSGRADOUT0->abs_interrupt = 0x00;

		ABSGRADOUT0->gpio_out = 0x2;
	}

	cleanup_platform();

	return 0;
}
