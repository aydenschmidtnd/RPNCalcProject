#include "GPIODriver.h"
#include "SPI.h"
#include <stdint.h>
#include <msp430.h>

void GPIOSetup(void)
{
    //Sets up LCD pins for Output
    P2DIR |= LCD_ENABLE + LCD_RW + LCD_RS + SHIFT_REGISTER_RCLK;
    //Sets up LCD pins for GPIO
    P2SEL2 = 0;
    P2SEL = 0;
}

/* LCD FUNCTIONS ========================================================================================================*/

/*Sets the Enable Pin */
void SetEnablePin(bool setEnablePin)
{
    if(setEnablePin)
    {
        P2OUT |= LCD_ENABLE;
    }
    else 
    {
        P2OUT &= ~LCD_ENABLE;
    }
}

void SetRWPin(bool setRWPin)
{
    if(setRWPin)
    {
        P2OUT |= LCD_RW;
    }
    else 
    {
        P2OUT &= ~LCD_RW;
    }
}

void SetRSPin(bool setRSPin)
{
    if(setRSPin)
    {
        P2OUT |= LCD_RS;
    }
    else 
    {
        P2OUT &= ~LCD_RS;
    }
}

/* LCD FUNCTIONS ========================================================================================================*/
