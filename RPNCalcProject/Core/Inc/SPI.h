#ifndef _SPI_H_
#define _SPI_H_

/*PORT 1*/
#define SHIFT_REGISTER_SER BIT2
#define SHIFT_REGISTER_SRCLK BIT4
/*PORT 2*/
#define SHIFT_REGISTER_RCLK BIT4

void InitSPI(void);
void Write74HC595(uint8_t data);

#endif
