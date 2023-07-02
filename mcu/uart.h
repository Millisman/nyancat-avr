#ifndef UART_H
#define UART_H

#define UART_BAUD_SELECT(BAUD) ((F_CPU+8UL*BAUD)/(16UL*BAUD)-1UL)

/*
 * Baudrate expression for ATmega (double speed mode)
 * BAUD in bps, e.g. 1200, 2400, 9600
 */
#define UART_BAUD_SELECT_DOUBLE_SPEED(BAUD) (((F_CPU+4UL*BAUD)/(8UL*BAUD)-1) | 0x8000)

#endif // UART_H
