#ifndef _LCD_H_
#define _LCD_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    CHARACTER_NUMBER_ZERO = 48,
    CHARACTER_NUMBER_ONE,
    CHARACTER_NUMBER_TWO,
    CHARACTER_NUMBER_THREE,
    CHARACTER_NUMBER_FOUR,
    CHARACTER_NUMBER_FIVE,
    CHARACTER_NUMBER_SIX,
    CHARACTER_NUMBER_SEVEN,
    CHARACTER_NUMBER_EIGHT,
    CHARACTER_NUMBER_NINE,
} CHARACTER_NUMBER;

void LCDWriteCharacter(uint8_t characterData);
void LCDInstruction(uint8_t instructionData);
void LCDWriteString(char string[]);

#endif
