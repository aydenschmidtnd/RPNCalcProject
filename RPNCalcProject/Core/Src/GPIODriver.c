#include "GPIODriver.h"
#include <stdint.h>
#include <msp430.h>

static const uint8_t RW = BIT1;
static const uint8_t RS = BIT2;
static const uint8_t ENABLE = BIT7;
static const uint16_t DELAY = 1000;

void GPIOSetup(void)
{
    P1DIR |= 0xFF;
    P2DIR |= 0xFF;
    
    P1SEL = 0;
    P2SEL = 0;
    P1SEL2 = 0;
    P2SEL2 = 0;

    __delay_cycles(DELAY);
}

void SetEnablePin(bool setEnablePin)
{
    if(setEnablePin)
    {
        P2OUT |= ENABLE;
    }
    else 
    {
        P2OUT &= ~ENABLE;
    }
}

void SetRWPin(bool setRWPin)
{
    if(setRWPin)
    {
        P2OUT |= RW;
    }
    else 
    {
        P2OUT &= ~RW;
    }
}

void SetRSPin(bool setRSPin)
{
    if(setRSPin)
    {
        P2OUT |= RS;
    }
    else 
    {
        P2OUT &= ~RS;
    }
}

void SetLCDDataPins(uint8_t data)
{
    P1OUT = data;
}

void ClearLCDDataPins(void)
{
    P1OUT &= ~0xFF;
}
