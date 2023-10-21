#include "led.h"

/*!
* \var output
* \brief This is the global structure that describes
* the GPIO module and is used as the first parameter
* of each GPIO API function.
*/
XGpio output;

/*!
 * \brief This is the initialization API for blinking LED.
 *
 * This function initializes the PL GPIO module number 0 and
 * sets logic 0 to the respective pin.
 *
 * \return None.
*/
void led_init(void){
    XGpio_Initialize(&output, XPAR_AXI_GPIO_0_DEVICE_ID);
    XGpio_SetDataDirection(&output, 1, 0x0);
    XGpio_DiscreteWrite(&output, 1, 0x00);
}

/*!
 * \brief This functions turns on the LED.
 *
 * The proper term for outputting a logic 1 on
 * a pin is "set".
 *
 * \return None.
*/
void led_set(void){
	XGpio_DiscreteWrite(&output, 1, 0x08);
}

/*!
 * \brief This functions turns off the LED.
 *
 * The proper term for outputting a logic 0 on
 * a pin is "clear".
 *
 * \return None.
*/
void led_clear(void){
	XGpio_DiscreteWrite(&output, 1, 0x00);
}
