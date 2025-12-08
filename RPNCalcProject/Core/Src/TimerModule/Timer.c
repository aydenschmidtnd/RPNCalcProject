#include <msp430.h>
#include <stdint.h>

#include "Timer.h"

volatile uint64_t OneMsTick = 0;

void InitTimer(void)
{
    P2DIR |= BIT6;                            // Debug output, set P2.6 to output
    CCTL0 = CCIE;                             // CCR0 interrupt enabled
    CCR0 = 15999;                             // With SMCLK flag, is set every 1 ms
    TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode
    __bis_SR_register(GIE);                   // Enable interrupts
}

// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
    OneMsTick += 1;
}
