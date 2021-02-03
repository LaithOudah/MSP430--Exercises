#include "msp430g2553.h"


void main(void) {
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT
    P1DIR |= 0x01; // P1.0 output
    TACCTL1 = CCIE; // TACCR1 interrupt enabled
    TACCR1 = 50000; //TACCR1 initial value
    TACCTL0 = CCIE; // TACCR0 interrupt enabled     ------------- NYTT
    TACCR0 = 25000; // TACCR0 initial value         ------------- NYTT
    TACTL = TASSEL_2 + MC_2; // SMCLK, Continuous mode
    _BIS_SR(LPM0_bits + GIE); // Enter LPM0 w/ interrupt
  }


// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR //                  ------------- NYTT
__interrupt void Timer_A0 (void) {
  P1OUT ^= 0x01; // Toggle P1.0
  TACCR0 += 50000; // Add Offset to CCR0
}

  // Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{
    switch (TAIV) {
    case 2: { // TACCR1 interrupt
      P1OUT ^= 0x01; // Toggle P1.0
      TACCR1 += 50000; // Add Offset to TACCR1
    }
    break;
    case 4:
      break; // TACCR2 not used
    case 10:
      break; // Timer overflow not used
    }
  }


















