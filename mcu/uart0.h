/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <joerg@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Joerg Wunsch
 * ----------------------------------------------------------------------------
 *
 * Stdio demo, UART declarations
 *
 * $Id: uart.h 1008 2005-12-28 21:38:59Z joerg_wunsch $
 */

#ifndef UART0_H
#define UART0_H

#include <stdint.h>
#include <stdio.h>

/*
 * Perform UART startup initialization.
 */
void	uart0_init(uint16_t baudrate);

/*
 * Send one character to the UART.
 */
int	uart0_putchar(char c, FILE *stream);

/*
 * Size of internal line buffer used by uart_getchar().
 */


/*
 * Receive one character from the UART.  The actual reception is
 * line-buffered, and one character is returned from the buffer at
 * each invokation.
 */
int	uart0_getchar(FILE *stream);

#endif // UART0_H
