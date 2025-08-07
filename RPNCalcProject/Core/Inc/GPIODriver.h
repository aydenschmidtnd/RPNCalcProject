#ifndef _GPIO_DRIVER_H_
#define _GPIO_DRIVER_H_

#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

/*PORT 2*/
#define LCD_ENABLE BIT0
#define LCD_RW     BIT1
#define LCD_RS     BIT2

void InitGPIO(void);

/*
* Description: Sets the enable pin to control the 16x2 LCD.
*              This is required for enabling interation with the LCD.
* Parameters: *setEnablePin: Sets enable high if true and low if false.
*/
void SetEnablePin(bool setEnablePin);

/*
* Description: Sets the RW pin to control the 16x2 LCD. 
               If RW = 0, write; If RW = 1, read
* Parameters: *setRWPin: Sets RW high if true and low if false.
*/
void SetRWPin(bool setRWPin);

/*
* Description: Sets the RS pin to control the 16x2 LCD. Determines whether
               data being sent will be interpreted as a character or an instruction.
               If RS = 0, instruction; If RS = 1, character
* Parameters: *setRSPin: Sets RS high if true and low if false.
*/
void SetRSPin(bool setRSPin);

/*
* Description: Sets the LCD data pins to control the 16x2 LCD.
* Parameters: *data: Data to be sent to the LCD.
*/

#endif
