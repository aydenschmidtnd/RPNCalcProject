#ifndef _LCD_H_
#define _LCD_H_

#include <stdint.h>
#include <stdbool.h>

#define MAX_LCD_BUFFER 17

typedef enum
{
    LCD_LINE_ONE = 0x80,
    LCD_LINE_TWO = 0xC0,
} LCD_LINE;

typedef enum
{
    INSTRUCTION_CLEAR_LCD = 1,
    INSTRUCTION_RETURN_HOME = 2,
} INSTRUCTION;

void LCDWriteCharacter(uint8_t characterData);
void LCDWriteInstruction(uint8_t instructionData);

/*
* Description: Writes a string to a 16x2 LCD screen. 
* Parameters: *lcdLineNumber: LCD line to write to.
*             *lcdOffset: lcdOffset from first column of LCD.
*             *string: String to write to LCD.
*/
void LCDWriteString(const LCD_LINE lcdLineNumber, const uint8_t lcdOffset, const char string[]);
void InitLCD(void);

#endif
