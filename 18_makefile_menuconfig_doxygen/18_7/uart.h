#ifndef __UART_H__
#define __UART_H__

#include "xil_io.h"
#include "xil_types.h"
#include "xparameters.h"
#include "xuartlite_l.h"

#define XUL_CR_ENABLE_INTR		0x10	
#define XUL_CR_FIFO_RX_RESET		0x02	
#define XUL_CR_FIFO_TX_RESET		0x01

#define XUL_SR_PARITY_ERROR		0x80
#define XUL_SR_FRAMING_ERROR		0x40
#define XUL_SR_OVERRUN_ERROR		0x20
#define XUL_SR_INTR_ENABLED		0x10	
#define XUL_SR_TX_FIFO_FULL		0x08	
#define XUL_SR_TX_FIFO_EMPTY		0x04	
#define XUL_SR_RX_FIFO_FULL		0x02	
#define XUL_SR_RX_FIFO_VALID_DATA	0x01	
#define XUL_FIFO_SIZE			16

#define XUL_STOP_BITS			1
#define XUL_PARITY_NONE		0
#define XUL_PARITY_ODD			1
#define XUL_PARITY_EVEN		2

#define XUartLite_In32  Xil_In32
#define XUartLite_Out32 Xil_Out32

#define XUartLite_WriteReg(BaseAddress, RegOffset, Data) \
	XUartLite_Out32((BaseAddress) + (RegOffset), (u32)(Data))

#define XUartLite_ReadReg(BaseAddress, RegOffset) \
	XUartLite_In32((BaseAddress) + (RegOffset))
	
#define XUartLite_IsReceiveEmpty(BaseAddress) \
  ((XUartLite_GetStatusReg((BaseAddress)) & XUL_SR_RX_FIFO_VALID_DATA) != \
	XUL_SR_RX_FIFO_VALID_DATA)

#define XUartLite_IsTransmitFull(BaseAddress) \
	((XUartLite_GetStatusReg((BaseAddress)) & XUL_SR_TX_FIFO_FULL) == \
	  XUL_SR_TX_FIFO_FULL)
	  	
	
#if (XPAR_XUARTLITE_USE_DCR_BRIDGE != 0)
#define XUL_RX_FIFO_OFFSET		0	
#define XUL_TX_FIFO_OFFSET		1	
#define XUL_STATUS_REG_OFFSET		2	
#define XUL_CONTROL_REG_OFFSET	3

#else

#define XUL_RX_FIFO_OFFSET		0
#define XUL_TX_FIFO_OFFSET		4
#define XUL_STATUS_REG_OFFSET		8
#define XUL_CONTROL_REG_OFFSET	12

#endif

void uart_init(void);
void uart_send(UINTPTR BaseAddress, u8 Data);
u8 uart_receive(UINTPTR BaseAddress);

#endif
