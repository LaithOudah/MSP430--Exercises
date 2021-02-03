#include "msp430g2553.h"

void main(void) {

  WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
  P1DIR |= 0x01 + 0x04 + 0x40; // Set P1.0, P1.2 and P1.6 to output direction
  P1IE |= 0x20; // P1.5 Interrupt enabled
  P1IES &= ~0x20; // P1.5 rising edge

  //P1OUT &= 0xFD; // 1111 1101 // Pull low
  P1IFG &= ~0x20; // P1.5 IFG cleared
  _BIS_SR(GIE); // Global Interrupt Enabled

  while (1) {

   int a,b ; // Counters
    for (a = 0 ;a < 10000; a++) {
      for (b = 0; b < 10000; b++) {
        _NOP(); // No operation
      }
    }
    P1OUT ^= 0x04; //0000 0100
    P1OUT ^= 0x40; //0100 0000
  }
}

// Port 1 interrupt service routine
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void) {
  P1OUT ^= 0x01; // P1.0 = toggle LED
  P1IFG &= ~0x20; // P1.5 IFG cleared
}
