#include <stdint.h>
#include <msp430.h>
#include <string.h>

#include "LcdDriver.h"
#include "ShiftRegisterDriver.h"

/*COMMANDS FOR HD44780 16x2 LCD START========================================================================*/
typedef enum
{
    LCD_LINE_ONE = 0x80,
    LCD_LINE_TWO = 0xC0,
} LCD_LINE;


typedef enum
{
    ENTRY_MODE_SET_MASK            = 4,
        INCREMENT_ENABLE           = 2,
        DISPLAY_SHIFT_ENABLE       = 1,
      
    DISPLAY_CONTROL_MASK           = 8,
        DISPLAY_ENABLE             = 4,
        CURSOR_ENABLE              = 2,
        CURSOR_BLINK_ENABLE        = 1,

    FUNCTION_SET_MASK              = 32,
        INTERFACE_DATA_LENGTH_8BIT = 16,
        DISPLAY_LINES_TWO          = 8,
        CHARACTER_FONT_5X10        = 4,
} INSTRUCTION_LCD_COMMAND_MASK;


typedef enum
{
    INSTRUCTION_LCD_CLEAR           = 1,
    INSTRUCTION_LCD_RETURN_HOME     = 2,

    INSTRUCTION_LCD_DISPLAY_CONTROL = DISPLAY_CONTROL_MASK + 
                                      DISPLAY_ENABLE +  
                                      CURSOR_ENABLE,
                                    /*CURSOR_BLINK_OFF*/
                                  
    INSTRUCTION_LCD_ENTRY_MODE      = ENTRY_MODE_SET_MASK,
                                    /*INCREMENT_DISABLE*/
                                    /*DISPLAY_SHIFT_DISABLE*/

    INSTRUCTION_LCD_FUNCTION_SET    = FUNCTION_SET_MASK + 
                                      INTERFACE_DATA_LENGTH_8BIT + 
                                      DISPLAY_LINES_TWO + 
                                      CHARACTER_FONT_5X10,
} INSTRUCTION_LCD;
/*COMMANDS FOR HD44780 16x2 LCD END==========================================================================*/


#define MAX_LCD_STRING_LENGTH  (16U)
#define MAX_LCD_BUFFER         (MAX_LCD_STRING_LENGTH + 1U)

#define LCD_WRITE_DELAY_CYCLES (4000U)
#define LCD_CLEAR_DELAY_CYCLES (20000U)
#define ENABLE_DELAY_CYCLES    (32U)

#define MAX_LCD_OFFSET (15U)

#define HIGH (true)
#define LOW  (false)

/*PORT 2*/
#define LCD_ENABLE (BIT0)
#define LCD_RW     (BIT1)
#define LCD_RS     (BIT2)

static void WriteLCDCharacter(uint8_t characterData);
static void WriteLCDInstruction(uint8_t instructionData);
/*
* Description: Sets the enable pin to control the 16x2 LCD.
*              This is required for enabling interation with the LCD.
* Parameters: *setEnablePin: Sets enable high if true and low if false.
*/
static void SetEnablePin(bool setEnablePin);

/*
* Description: Sets the RW pin to control the 16x2 LCD. 
               If RW = 0, write; If RW = 1, read
* Parameters: *setRWPin: Sets RW high if true and low if false.
*/
static void SetRWPin(bool setRWPin);

/*
* Description: Sets the RS pin to control the 16x2 LCD. Determines whether
               data being sent will be interpreted as a character or an instruction.
               If RS = 0, instruction; If RS = 1, character
* Parameters: *setRSPin: Sets RS high if true and low if false.
*/
static void SetRSPin(bool setRSPin);

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

    //Write all characters of string to LCD
    while(*string != '\0'){WriteLCDCharacter(*(string++)); }
}

void InitLcdPeripherals(void)
{
    //Sets up LCD pins for Output
    P2DIR |= LCD_ENABLE + LCD_RW + LCD_RS + SHIFT_REGISTER_RCLK;
    //Sets up LCD pins for GPIO
    P2SEL2 = 0;
    P2SEL  = 0;
}

void InitLCD(void)
{
    WriteLCDInstruction(INSTRUCTION_LCD_FUNCTION_SET);
    WriteLCDInstruction(INSTRUCTION_LCD_ENTRY_MODE);
    WriteLCDInstruction(INSTRUCTION_LCD_DISPLAY_CONTROL);
    WriteLCDInstruction(INSTRUCTION_LCD_CLEAR);
}

static void WriteLCDCharacter(uint8_t characterData)
{
    SetRSPin(HIGH);
    SetRWPin(LOW);

    Write74HC595(characterData);
    SetEnablePin(HIGH);
    __delay_cycles(ENABLE_DELAY_CYCLES);
    SetEnablePin(LOW);

    if(characterData == INSTRUCTION_LCD_CLEAR){__delay_cycles(LCD_CLEAR_DELAY_CYCLES);}
    else{__delay_cycles(LCD_WRITE_DELAY_CYCLES);}
}

static void WriteLCDInstruction(const uint8_t instructionData)
{
    SetRSPin(LOW);
    SetRWPin(LOW);

    Write74HC595(instructionData);
    SetEnablePin(HIGH);
    __delay_cycles(ENABLE_DELAY_CYCLES);
    SetEnablePin(LOW);

    __delay_cycles(LCD_WRITE_DELAY_CYCLES);
}

static void SetEnablePin(bool setEnablePin)
{
    if(setEnablePin)
    {
        P2OUT |= LCD_ENABLE;
    }
    else 
    {
        P2OUT &= ~LCD_ENABLE;
    }
}

static void SetRWPin(bool setRWPin)
{
    if(setRWPin)
    {
        P2OUT |= LCD_RW;
    }
    else 
    {
        P2OUT &= ~LCD_RW;
    }
}

static void SetRSPin(bool setRSPin)
{
    if(setRSPin)
    {
        P2OUT |= LCD_RS;
    }
    else 
    {
        P2OUT &= ~LCD_RS;
    }
}
