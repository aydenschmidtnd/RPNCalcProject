#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include "I2C.h"

void InitI2C(void)
{
    P1SEL |= I2CSCL + I2CSDA;                 // Assign pins 1.6 and 1.7 to I2C
    P1SEL2 |= I2CSCL + I2CSDA;                // Assign pins 1.6 and 1.7 to I2C
    UCB0CTL1 |= UCSWRST;                      // Enable SW reset
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode, 7-bit addressing
    UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
    UCB0BR0 = 160;                             // fSCL = SMCLK/160 = ~100kHz
    UCB0BR1 = 0;                              // fSCL = SMCLK/160 = ~100kHz
    UCB0I2CSA = 0x20;                         // Slave address is 0x20 for MCP23017
    UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
    __delay_cycles(100000);
}

bool WriteMCP23017(uint8_t registerAddress, uint8_t data)
{
    UCB0CTL1 |= UCTR + UCTXSTT;                    // I2C start condition TXs
    UCB0TXBUF = registerAddress;                  // Set which register to write to
    while(UCB0CTL1 & UCTXSTT);                     // Loop until I2C STT is sent
    while((IFG2 & UCB0TXIFG) == 0);               // Wait til data is fully sent

    UCB0TXBUF = data;
    while((IFG2 & UCB0TXIFG) == 0);               // Wait til data is fully sent

    UCB0CTL1 |= UCTXSTP;                          // Stop bit
    while (UCB0CTL1 & UCTXSTP);
    return true;
}

uint8_t ReadMCP23017(uint8_t registerAddress)
{
    UCB0CTL1 |= UCTR + UCTXSTT;                    // I2C start condition TXs
    UCB0TXBUF = registerAddress;                  // Set which register to write to
    while(UCB0CTL1 & UCTXSTT);                     // Loop until I2C STT is sent
    while((IFG2 & UCB0TXIFG) == 0);               // Wait til data is fully sent

    UCB0CTL1 &= ~UCTR; 
    UCB0CTL1 |= UCTXSTT;
    while(UCB0CTL1 & UCTXSTT);

    UCB0CTL1 |= UCTXSTP;
    while(UCB0CTL1 & UCTXSTP);

    while((IFG2 & UCB0RXIFG) == 0);
    return UCB0RXBUF;
}

void InitMCP23017(void)
{
    WriteMCP23017(0x00, 0x00); //Set PORTA to outputs
    WriteMCP23017(0x01, 0x7F); //Set PORTB to inputs
    WriteMCP23017(0x0D, 0x7F); //Set PORTB pull-ups (100k)
    WriteMCP23017(0x03, 0x7F); //Invert PORTB input readings
}


/*
void ReadMCP23017(uint8_t registerAddress, uint8_t data)
{
    UCB0CTL1 &= ~UCTR;                      // RX
    UCB0CTL1 |= UCTXSTT;                    // I2C start condition
    while(UCBCTL1 & UCTXSTT);                     // Loop until I2C STT is sent

}
*/