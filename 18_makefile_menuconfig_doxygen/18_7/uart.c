#include "uart.h"

void uart_init(void){
    //Initialized during bitstream load
}


void uart_send(UINTPTR BaseAddress, u8 Data){
	while (XUartLite_IsTransmitFull(BaseAddress));
	XUartLite_WriteReg(BaseAddress, XUL_TX_FIFO_OFFSET, Data);
}

u8 uart_receive(UINTPTR BaseAddress){
	while (XUartLite_IsReceiveEmpty(BaseAddress));
	return (u8)XUartLite_ReadReg(BaseAddress, XUL_RX_FIFO_OFFSET);
}

//For the alternative printf function ...
void _putchar(char character){
	uart_send(XPAR_AXI_UARTLITE_0_BASEADDR, character);
}
