#include "msp430g2553.h"

void main(void) {

  WDTCTL = WDTPW + WDTHOLD; // Stop WDT
  P1DIR |= 0x01; // P1.0 output
  TACTL = TASSEL_2 + MC_2 + TAIE + ID0 + ID1; // SMCLK, continuous mode, interrupt, divided by 8
//  TACCR1 = 0x7FFF; // TACCR1 L�ggstill samt tar v�rdet av 0xFFFFF och dividerar p� h�lften.
//  TACCR1 = 0xFFFF/2;
  TACCR1 = 0xFFFF>>1;

  TACCTL1 = CCIE; // TACCR1 interupt enabled
  _BIS_SR(LPM0_bits + GIE); // Enter LPM0 w/ interrupt
}

// Timer_A3 Interrupt Vector (TAIV) handler
#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer_A(void) {
  switch (TAIV) {
  case 2: {
    P1OUT ^= 0x01; // CCR1 anv�nds
    break;
  }
  case 4: {
    break;
  } // TACCR2 not used
  case 10: {
    P1OUT ^= 0x01; // Timer overflow
    break;
   }
  }
}


























