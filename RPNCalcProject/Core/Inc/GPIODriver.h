#ifndef _GPIO_DRIVER_H_
#define _GPIO_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>

void GPIOSetup(void);
void SetEnablePin(bool setEnablePin);
void SetRWPin(bool setRWPin);
void SetRSPin(bool setRSPin);
void SetLCDDataPins(uint8_t data);
void ClearLCDDataPins(void);

#endif
