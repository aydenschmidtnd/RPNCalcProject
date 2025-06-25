#include "LCD.h"
#include "GPIODriver.h"

#include <string.h>

static const uint16_t DELAY = 1000;
static const uint8_t ENABLE_DELAY = 32;
static const uint8_t MAX_LCD_CHARACTERS = 16;

void LCDWriteCharacter(uint8_t characterData)
{
    SetRSPin(true);
    SetRWPin(false);

    SetLCDDataPins(characterData);

    SetEnablePin(true);
    __delay_cycles(ENABLE_DELAY);
    SetEnablePin(false);

    __delay_cycles(DELAY);
}

void LCDInstruction(uint8_t instructionData)
{
    SetRSPin(false);
    SetRWPin(false);

    SetLCDDataPins(instructionData);

    SetEnablePin(true);
    __delay_cycles(ENABLE_DELAY);
    SetEnablePin(false);

    __delay_cycles(DELAY);
}

void LCDWriteString(char string[])
{
    if(strlen(string) > MAX_LCD_CHARACTERS)
    {
        return;
    }
    while(*string != '\0')
    {
        LCDWriteCharacter(*(string++));
    }
}
