#ifndef _LCD_H_
#define _LCD_H_

#include <stdint.h>
#include <stdbool.h>

#define MAX_LCD_BUFFER        (17U)
#define MAX_LCD_STRING_LENGTH (16U)

typedef enum
{
    LCD_LINE_ONE = 0x80,
    LCD_LINE_TWO = 0xC0,
} LCD_LINE;

typedef enum
{
    INSTRUCTION_LCD_CLEAR = 1,
    INSTRUCTION_LCD_RETURN_HOME = 2,
} INSTRUCTION_LCD;

void WriteLCDCharacter(uint8_t characterData);
void WriteLCDInstruction(uint8_t instructionData);

/*
* Description: Writes a string to a 16x2 LCD screen. 
* Parameters: *lcdLineNumber: LCD line to write to.
*             *lcdOffset: lcdOffset from first column of LCD.
*             *string: String to write to LCD.
*/
void WriteLCDString(const LCD_LINE lcdLineNumber, const uint8_t lcdOffset, const char string[]);
void InitLCD(void);

#endif
