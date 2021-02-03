#include "msp430g2553.h"

void main (void) {

  WDTCTL = WDT_MDLY_0_064; // WDTPW + WDTTMSEL + WDTCNTCL + WDTIS1 + WDTIS0  /* 0.064ms" */
  IE1 |= WDTIE; // Interrupt Enable = Watchdog Interrupt Enable
  P1DIR |= BIT0; // P1.0 Output
  _BIS_SR(LPM0_bits + GIE); // Low Power Mode + General Interrupt

}

// Timer interrupt service routine
#pragma vector = WDT_VECTOR
__interrupt void WDT_TIMER (void) {

    P1OUT ^= BIT0; // P1.0 LED 0
}

/*
WDTPW       = Bit 15-8 Watchdog timer + password. Read as 069h, write as 06Ah or a PUC is generated
WDTTMSEL    = Watchdog timer+ mode select. 0 Watchdog mode, 1 interval timer mode.
WDTCNTCL    = Watchdog timer+ counter clear 0 no action, 1 Clear count to 0000h.
WDTISx      = Watchdog timer+ interval select. Bit select to set the WDTIFG flag and/or generate PUC.
    WDTIS0  = Watchdog clock source /32768  - (2^15)bit -
    WDTIS1  = Watchdog clock source /8192   - (2^13)bit
WDTCTL      = Watchdog Timer Control
WTDIFG      = Set on Watchdog timer overflow in watchdog mode or passkey violation. Reset on Vcc.
PUC         = Resets the watchdog timer to its default condition

Watchdog mode default reset time is
32768/800000 ~ 40 ms
The WDTISx bits give the interval in Hz, so to get a time base, you have to reverse the formula: 32768/Clock Frequency

If using a 32768 Hz crystal as your clock source for Watchdog (using SSEL bit) and a divider of 64 (using WDTISx bits)
the reset will happen every:
64/32768 = 1.9 ms
*/
