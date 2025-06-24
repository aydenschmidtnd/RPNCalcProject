#include <msp430.h>
#include <stdint.h>

#include "LCD.h"
#include "GPIODriver.h"

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    GPIOSetup();

    LCDInstruction(1);
    LCDInstruction(6);
    LCDInstruction(14);
    LCDInstruction(56);

    bool writeInstruction = true;

    while(1)
    {
        if(writeInstruction)
        {
            LCDWriteString("123 <3");
            writeInstruction = false;
        }
    }
}
