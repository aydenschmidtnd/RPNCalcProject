#include <msp430.h>
#include <stdint.h>

#include "SPI.h"
#include "LCD.h"
#include "main.h"
#include "GPIODriver.h"

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;

    GPIOSetup();
    InitClockTo16MHz();
    __delay_cycles(100000);
    InitSPI();
    __delay_cycles(100000);

    LCDWriteInstruction(60);
    LCDWriteInstruction(4);
    LCDWriteInstruction(14);
    LCDWriteInstruction(INSTRUCTION_CLEAR_LCD);

    bool writeInstruction = true;

    while(1)
    {   
        if(writeInstruction)
        {
            LCDWriteString(LCD_LINE_ONE, 0, "YOU'RE CUTE <3");
            LCDWriteString(LCD_LINE_TWO, 0, "SARAH MY LOVE.");
            writeInstruction = false;
        }
    }
}

void InitClockTo16MHz()
{
    if (CALBC1_16MHZ==0xFF)                  // If calibration constant erased
    {
        while(1);                               // do not load, trap CPU!!
    }
    DCOCTL = 0;                               // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_16MHZ;                    // Set DCO
    DCOCTL = CALDCO_16MHZ;
}
