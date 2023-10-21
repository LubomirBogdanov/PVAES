#include "uart.h"

/*!
 * \brief This is initialization API for the
 * Uartlite module.
 *
 * The Uartlite module is so "lite", it does not
 * allow to change its configuration such as baudrate,
 * stop bits, parity, etc. The configuration is set
 * during the synthesis of the design. So, be very
 * careful what you set in Vivado!
 *
 * \return None.
*/
void uart_init(void){
    //Initialized during bitstream load
}

/*!
 * \brief This is the API for sending a single byte.
 *
 * This function checks whether the TX register is
 * full. If it is, the function blocks. If it isn't,
 * the function continues by writing to the TX register.
 *
 * \param BaseAddress - the physical address of the 
 * Uartlite module in the design. Check the memory map.
 *
 * \param Data - the byte to be sent.
 *
 * \return None.
*/
void uart_send(UINTPTR BaseAddress, u8 Data){
	while (XUartLite_IsTransmitFull(BaseAddress));
	XUartLite_WriteReg(BaseAddress, XUL_TX_FIFO_OFFSET, Data);
}

/*!
 * \brief This is the API for receiving a single byte.
 *
 * This function checks whether the RX register is
 * full. If it isn't, the function blocks. If it is,
 * the function continues by reading the RX register.
 *
 * \param BaseAddress - the physical address of the 
 * Uartlite module in the design. Check the memory map.
 *
 * \return An unsigned byte that has been received over
 * the Uartlite interface.
*/
u8 uart_receive(UINTPTR BaseAddress){
	while (XUartLite_IsReceiveEmpty(BaseAddress));
	return (u8)XUartLite_ReadReg(BaseAddress, XUL_RX_FIFO_OFFSET);
}

/*!
 * \brief This function is needed for the alternative
 * printf port used in this application.
 *
 * The print.c file requires that you provide your own
 * function for sending a byte to the UART. This function
 * has to have this exact name and input parameters.
 *
 * \param character - a byte to be sent over the Uartlite.
 *
 * \return None.
*/
void _putchar(char character){
	uart_send(XPAR_AXI_UARTLITE_0_BASEADDR, character);
}
