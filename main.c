#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <time.h>
#include "mcu/uart.h"
#include "mcu/uart0.h"
#include "app/nyancat.h"


// The timer is configured with this tool
// http://www.8bit-era.cz/arduino-timer-interrupts-calculator.html
// It is desirable to get an integer value to get high precision.
// TIMER 2 for interrupt frequency 2500 Hz
// Timer2 can wake up the MCU from sleep.

#define TIMER2_CLOCK_HZ 2500

volatile uint16_t timer2_down_counter;

ISR(TIMER2_COMPA_vect)
{
    if (timer2_down_counter) {
        timer2_down_counter--;
    } else {
        system_tick();
        timer2_down_counter = TIMER2_CLOCK_HZ;
    }
}

FILE uart_str = FDEV_SETUP_STREAM(
    uart0_putchar,
    uart0_getchar,
    _FDEV_SETUP_RW // read/write intent
);

void print_help() {
    printf_P(PSTR("Hello! Enter 'cat' for play Nyan Cat!\n"));
}


int main()
{
    MCUSR = 0;
    wdt_disable();

    // Sync from a Calendar type RTC:
    //struct tm rtc_time;
    //read_rtc(&rtc_time);
    //rtc_time.tm_isdst = 0;
    //set_system_time( mktime(&rtc_time) );
    // set_system_time(TIME - UNIX_OFFSET);

    timer2_down_counter = TIMER2_CLOCK_HZ;

    // TIMER 2 for interrupt frequency 2500 Hz
    TCCR2A = 0; // set entire TCCR2A register to 0
    TCCR2B = 0; // same for TCCR2B
    TCNT2  = 0; // initialize counter value to 0
    // set compare match register for 2500 Hz increments
    OCR2A = 249; // = 20000000 / (32 * 2500) - 1 (must be <256)
    // turn on CTC mode
    TCCR2B |= (1 << WGM21);
    // Set CS22, CS21 and CS20 bits for 32 prescaler
    TCCR2B |= (0 << CS22) | (1 << CS21) | (1 << CS20);
    // enable timer compare interrupt
    TIMSK2 |= (1 << OCIE2A);

    sei();

    uart0_init(UART_BAUD_SELECT(115200));

    stdout = stdin = stderr = &uart_str;

    char buf[20];

    print_help();

    for (;;) {
        if (fgets(buf, sizeof(buf)-1, stdin) != NULL) {
            if (strncmp_P(buf, PSTR("cat"), 3) == 0) {
                play();
            } else {
                printf_P(PSTR("Unknown command: %s\n"), buf);
            }
            print_help();
        }
    }

}
