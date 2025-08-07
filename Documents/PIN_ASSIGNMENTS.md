# Pin Assignments

## 16x2 LCD:

### Control
1) **Enable** = 2.0
2) **RW** = 2.1
3) **RS** = 2.2

### Shift Register
1) **SER** = 1.2 (UCA0SIMO)
2) **OE** = pulldown
3) **RCLK** = 2.4 (UCA0CLK)
4) **SRCLK** = 1.4 (UCA0CLK)
5) **SRCLR** = pullup

### MCP23017 IO Expander
1) **SCK** = 1.6 
2) **SDA** = 1.7
3) **A0, A1, A2** = pulldown