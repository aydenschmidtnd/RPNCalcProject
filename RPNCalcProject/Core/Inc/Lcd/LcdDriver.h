#ifndef _LCD_DRIVER_H
#define _LCD_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

/*
* Description: Writes a string to a 16x2 LCD screen. 
* Parameters: *lcdLineNumber: LCD line to write to.
*             *lcdOffset: lcdOffset from first column of LCD.
*             *string: String to write to LCD.
*/
void WriteLCDString(const LCD_LINE lcdLineNumber, const uint8_t lcdOffset, const char string[]);
void InitLCD(void);
void InitLcdPeripherals(void);

#endif /* _LCD_DRIVER_H_ */
