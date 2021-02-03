#include "msp430g2553.h"

int a = 0;

void main(void) {

  P1DIR |= BIT0; // P1.0 output
  TACCTL0 = CCIE; // TACCR0 interrupt enabled
  TACCR0 = 50000;
  TACTL = TASSEL_2 + MC_1; // SMCLK, up mode

  for (;;) {
    _BIS_SR(GIE);

    // WDT Password. Read as 069h, written as 05Ah. + Counter Clear, sets value to 0000h, Auto reset
    WDTCTL = WDTPW + WDTCNTCL;
  }
}

// Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void) {
    // Blink LED P1.0
  if (a == 10) {
    P1OUT ^= BIT0;
    a = 0;
  } else {
    a++;
  }
}


