#ifndef _I2C_H_
#define _I2C_H_

#include <stdint.h>

/*PORT 2*/
#define I2CSCL BIT6
#define I2CSDA BIT7

#define MCP23017_DEVICE_ADDRESS (0x20U)

void InitI2C(void);
bool WriteMCP23017(uint8_t registerAddress, uint8_t data);
uint8_t ReadMCP23017(uint8_t registerAddress);
void InitMCP23017(void);

#endif 
