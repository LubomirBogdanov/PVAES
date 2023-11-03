/*
 * main_mb.c
 *
 *  Created on: Oct 31, 2023
 *      Author: lbogdanov
 */
#include <stdio.h>
#include <xgpio.h>
#include "xparameters.h"
#include "sleep.h"
#include "xil_exception.h"
#include "xintc.h"

typedef struct {
	UINTPTR BaseAddress;
	u32 IsReady;
	int InterruptPresent;
	int IsDual;
} abs_gradient_out_t;

XGpio output;
abs_gradient_out_t abs_module_0;
XIntc intc_0;

void abs_gradient_interrupt_0(void){
	static int flag = 1;
	if(flag){
		flag = 0;
		XGpio_DiscreteWrite(&output, 1, 0x01);
	}
	else{
		flag = 1;
		XGpio_DiscreteWrite(&output, 1, 0x00);
	}
}

int main(void){
	abs_module_0.BaseAddress = (volatile uint32_t)XPAR_ABS_GRADIENT_OUT_0_S00_AXI_BASEADDR;
	abs_module_0.IsReady = 1;
	abs_module_0.IsDual = 0;
	abs_module_0.InterruptPresent = 1;

	XGpio_Initialize(&output, XPAR_AXI_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection(&output, 1, 0x0);

	XIntc_Initialize(&intc_0, XPAR_INTC_0_DEVICE_ID);
	XIntc_SelfTest(&intc_0);
	XIntc_Connect(&intc_0, XPAR_MICROBLAZE_0_AXI_INTC_ABS_GRADIENT_OUT_0_INTERRUPT_0_INTR, (XInterruptHandler)abs_gradient_interrupt_0, &abs_module_0);
	XIntc_Start(&intc_0, XIN_REAL_MODE);
	XIntc_Enable(&intc_0, XPAR_MICROBLAZE_0_AXI_INTC_ABS_GRADIENT_OUT_0_INTERRUPT_0_INTR);
	Xil_ExceptionInit();
	Xil_ExceptionEnable();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XIntc_InterruptHandler, &intc_0);
	XIntc_Acknowledge(&intc_0, XPAR_MICROBLAZE_0_AXI_INTC_ABS_GRADIENT_OUT_0_INTERRUPT_0_INTR);

	while(1){

	}

	return 0;
}
