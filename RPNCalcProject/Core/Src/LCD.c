#include "LCD.h"
#include "SPI.h"
#include "GPIODriver.h"

#include <string.h>

#define LCD_WRITE_DELAY    (4000U)
#define LCD_CLEAR_DELAY    (20000U)
#define ENABLE_DELAY       (32U)

#define MAX_LCD_OFFSET     (15U)

#define HIGH true
#define LOW false 

void WriteLCDCharacter(uint8_t characterData)
{
    SetRSPin(HIGH);
    SetRWPin(LOW);

    Write74HC595(characterData);
    SetEnablePin(HIGH);
    __delay_cycles(ENABLE_DELAY);
    SetEnablePin(LOW);

    if(characterData == INSTRUCTION_LCD_CLEAR){__delay_cycles(LCD_CLEAR_DELAY);}
    else{__delay_cycles(LCD_WRITE_DELAY);}
}

void WriteLCDInstruction(const uint8_t instructionData)
{
    SetRSPin(LOW);
    SetRWPin(LOW);

    Write74HC595(instructionData);
    SetEnablePin(HIGH);
    __delay_cycles(ENABLE_DELAY);
    SetEnablePin(LOW);

    __delay_cycles(LCD_WRITE_DELAY);
}

void WriteLCDString(const LCD_LINE lcdLineNumber, uint8_t lcdOffset, const char string[])
{
    if(lcdOffset > MAX_LCD_OFFSET){lcdOffset = MAX_LCD_STRING_LENGTH;}

    switch(lcdLineNumber)
    {
        case LCD_LINE_ONE:
            WriteLCDInstruction(LCD_LINE_ONE + lcdOffset);
            break;

        case LCD_LINE_TWO:
            WriteLCDInstruction(LCD_LINE_TWO + lcdOffset);
            break;
    }

    if((strlen(string) + lcdOffset) > MAX_LCD_STRING_LENGTH){return;}

    /*Write all characters of string to LCD till Null Character*/
    while(*string != '\0'){WriteLCDCharacter(*(string++)); }
}

void InitLCD(void)
{
    WriteLCDInstruction(60);
    WriteLCDInstruction(4);
    WriteLCDInstruction(14);
    WriteLCDInstruction(INSTRUCTION_LCD_CLEAR);
}