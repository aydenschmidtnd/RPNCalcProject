#include "LCD.h"
#include "SPI.h"
#include "GPIODriver.h"

#include <string.h>

static const uint16_t LCD_WRITE_DELAY = 4000;
static const uint16_t LCD_CLEAR_DELAY = 20000;
static const uint8_t ENABLE_DELAY = 32;

static const uint8_t MAX_LCD_CHARACTERS = 16;
static const uint8_t MAX_LCD_OFFSET = 15;

static LCD_LINE CurrentLCDLine;

void LCDWriteCharacter(uint8_t characterData)
{
    SetRSPin(true);
    SetRWPin(false);

    WriteShiftRegister(characterData);
    SetEnablePin(true);
    __delay_cycles(ENABLE_DELAY);
    SetEnablePin(false);

    if(characterData == INSTRUCTION_CLEAR_LCD){__delay_cycles(LCD_CLEAR_DELAY);}
    else{__delay_cycles(LCD_WRITE_DELAY);}
}

void LCDWriteInstruction(const uint8_t instructionData)
{
    SetRSPin(false);
    SetRWPin(false);

    WriteShiftRegister(instructionData);
    SetEnablePin(true);
    __delay_cycles(ENABLE_DELAY);
    SetEnablePin(false);

    __delay_cycles(LCD_WRITE_DELAY);
}

void LCDWriteString(const LCD_LINE lcdLineNumber, uint8_t lcdOffset, const char string[])
{
    if(lcdOffset > MAX_LCD_OFFSET)
    {
        lcdOffset = MAX_LCD_OFFSET;
    }

    if((lcdLineNumber == LCD_LINE_ONE))
    {
        LCDWriteInstruction(LCD_LINE_ONE + lcdOffset);
        CurrentLCDLine = LCD_LINE_ONE;
    }
    else if((lcdLineNumber == LCD_LINE_TWO))
    {
        LCDWriteInstruction(LCD_LINE_TWO + lcdOffset);
        CurrentLCDLine = LCD_LINE_TWO;
    }

    if((strlen(string) + lcdOffset) > MAX_LCD_CHARACTERS)
    {
        return;
    }
    /*Write all characters of string to LCD till Null Character*/
    while(*string != '\0')
    {
        LCDWriteCharacter(*(string++));
    }
}

void InitLCD(void)
{
    LCDWriteInstruction(60);
    LCDWriteInstruction(4);
    LCDWriteInstruction(14);
    LCDWriteInstruction(INSTRUCTION_CLEAR_LCD);
}