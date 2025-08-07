#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include "I2C.h"

typedef enum
{
    MCP23017_ADDRESS_IODIRA = 0x00,
    MCP23017_ADDRESS_IODIRB = 0x01,
    MCP23017_ADDRESS_IPOLB  = 0x03,
    MCP23017_ADDRESS_GPPUB  = 0x0D,
} MCP23017_ADDRESS;

void InitI2C(void)
{
    P1SEL |= I2CSCL + I2CSDA;                     // Assign pins 1.6 and 1.7 to I2C
    P1SEL2 |= I2CSCL + I2CSDA;                    // Assign pins 1.6 and 1.7 to I2C
    UCB0CTL1 |= UCSWRST;                          // Enable SW reset
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;         // I2C Master, synchronous mode, 7-bit addressing
    UCB0CTL1 = UCSSEL_2 + UCSWRST;                // Use SMCLK, keep SW reset
    UCB0BR0 = 160;                                // fSCL = SMCLK/160 = ~100kHz
    UCB0BR1 = 0;                                  // fSCL = SMCLK/160 = ~100kHz
    UCB0I2CSA = MCP23017_DEVICE_ADDRESS;                 // Slave address is 0x20 for MCP23017
    UCB0CTL1 &= ~UCSWRST;                         // Clear SW reset, resume operation
    __delay_cycles(100000);
}

void InitMCP23017(void)
{
    WriteMCP23017(MCP23017_ADDRESS_IODIRA, 0x00); // Set PORTA to outputs
    WriteMCP23017(MCP23017_ADDRESS_IODIRB, 0x7F); // Set PORTB to inputs
    WriteMCP23017(MCP23017_ADDRESS_GPPUB,  0x7F); // Set PORTB pull-ups (100k)
    WriteMCP23017(MCP23017_ADDRESS_IPOLB,  0x7F); // Invert PORTB input readings
}

bool WriteMCP23017(uint8_t registerAddress, uint8_t data)
{
    UCB0CTL1 |= UCTR + UCTXSTT;                   // I2C start condition TXs
    UCB0TXBUF = registerAddress;                  // Set which register to write to
    while(UCB0CTL1 & UCTXSTT);                    // Loop until I2C STT is sent
    while((IFG2 & UCB0TXIFG) == 0);               // Wait til data is fully sent

    UCB0TXBUF = data;
    while((IFG2 & UCB0TXIFG) == 0);               // Wait til data is fully sent

    UCB0CTL1 |= UCTXSTP;                          // Stop bit
    while (UCB0CTL1 & UCTXSTP);                   // Wait til stop bit is sent

    return true;                                  
}

uint8_t ReadMCP23017(uint8_t registerAddress)
{
    UCB0CTL1 |= UCTR + UCTXSTT;                   // I2C start condition TXs
    UCB0TXBUF = registerAddress;                  // Set which register to write to
    while(UCB0CTL1 & UCTXSTT);                    // Loop until I2C STT is sent
    while((IFG2 & UCB0TXIFG) == 0);               // Wait til data is fully sent

    UCB0CTL1 &= ~UCTR;                            // Set I2C for read operation
    UCB0CTL1 |= UCTXSTT;                          // I2C start condition
    while(UCB0CTL1 & UCTXSTT);                    // Loop until I2C STT is sent
        
    UCB0CTL1 |= UCTXSTP;                          // Stop bit
    while(UCB0CTL1 & UCTXSTP);                    // Wait til stop bit is sent

    while((IFG2 & UCB0RXIFG) == 0);               // Wait til RX buffer is full
    return UCB0RXBUF;
}
