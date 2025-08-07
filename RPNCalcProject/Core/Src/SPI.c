#include <stdint.h>
#include <stdbool.h>
#include <msp430.h>
#include "SPI.h"
#include "GPIODriver.h"

void InitSPI()
{
    //Clock Polarity: The inactive state is high
    //MSB First, 8-bit, Master, 3-pin mode, Synchronous
    UCA0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;
    UCA0CTL1 |= UCSSEL_2;                     // SMCLK
    UCA0BR0 |= 0x02;                          // 500Khz SCLK
    UCA0BR1 = 0;                              // 500Khz SCLK
    UCA0MCTL = 0;                             // No modulation must be cleared for SPI

    P1SEL  |= SHIFT_REGISTER_SER + SHIFT_REGISTER_SRCLK;  // SIMO, SCLK
    P1SEL2 |= SHIFT_REGISTER_SER + SHIFT_REGISTER_SRCLK;  // SIMO, SCLK

    UCA0CTL1 &= ~UCSWRST;                     // Initialize USCI state machine
    __delay_cycles(100000);
}

void Write74HC595(uint8_t data)
{
    while (!(IFG2 & UCA0TXIFG));   // wait for TX buffer ready
    UCA0TXBUF = data;              // send data to TX buffer
    _delay_cycles(10000);          // wait for data to send before latching RCLK

    P2OUT |= SHIFT_REGISTER_RCLK;  // Turn RCLK on and off to latch data
    P2OUT &= ~SHIFT_REGISTER_RCLK;

    _delay_cycles(10000); 
}
