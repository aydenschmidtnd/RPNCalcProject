#include <msp430.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "ShiftRegisterDriver.h"
#include "IoExpanderDriver.h"
#include "LcdDriver.h"
#include "Timer.h"
#include "Main.h"

static void InitClockTo16MHz(void);

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; //Stop Watchdog Timer
    
    InitClockTo16MHz();
    /*Init Peripherals*/
    InitLcdPeripherals();
    Init74HC595Peripherals();
    InitMCP23017Peripherals();
    /*Init Devices*/
    InitMCP23017();
    InitLCD();

    InitTimer();

    bool writeInstruction = true;
    uint8_t buttonCheck = 100;

    uint64_t currentTime = 0;
    uint64_t pastTime = 0;

    bool flagOne = false;
    bool flagTwo = false;
    bool flagThree = false;
    bool flagFour = false;
    char LCD_Buffer[MAX_LCD_BUFFER] = "                ";
    uint8_t index = 0;
    while(true)
    {
        WriteMCP23017(0x12, ~0x01);  //Turn COL 1 on
        __delay_cycles(100000);
        buttonCheck = ReadMCP23017(0x13);
        switch(buttonCheck)
        {
            case 1:
                if(flagOne == false)
                {
                    LCD_Buffer[index++] = '1';
                    flagOne = true;
                }
                break;
            case 2: 
                if(flagTwo == false)
                {
                    LCD_Buffer[index++] = '3';
                    flagTwo = true;
                }
                break;
            default:
                break;
        }
        __delay_cycles(100000);
        if(ReadMCP23017(0x13) == 0)
        {
            flagOne = false;
            flagTwo = false;
        } 
        if(index == 16){index = 0;}
        WriteMCP23017(0x12, 0x01);
        __delay_cycles(100000);

        WriteMCP23017(0x12, ~0x02);
        __delay_cycles(100000);
        buttonCheck = ReadMCP23017(0x13);
        switch(buttonCheck)
        {
            case 1:
                if(flagThree == false)
                {
                    LCD_Buffer[index++] = '2';
                    flagThree = true;
                }
                break;
            case 2: 
                if(flagFour == false)
                {
                    LCD_Buffer[index++] = '4';
                    flagFour = true;
                }
                break;
            default:
                break;
        }
        __delay_cycles(100000);
        if(ReadMCP23017(0x13) == 0)
        {
            flagThree = false;
            flagFour = false;
        }
        if(index == 16){index = 0;}
        
        WriteMCP23017(0x12, 0x02);
        __delay_cycles(100000);

        WriteLCDString(LCD_LINE_ONE, 0, LCD_Buffer);
    }
}

static void InitClockTo16MHz()
{
    if (CALBC1_16MHZ==0xFF)                  // If calibration constant erased
    {
        while(1);                            // do not load, trap CPU!!
    }
    DCOCTL = 0;                              // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_16MHZ;                  // Set DCO
    DCOCTL = CALDCO_16MHZ;                   
}
