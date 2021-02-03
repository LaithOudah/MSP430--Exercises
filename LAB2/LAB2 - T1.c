#include "msp430g2553.h"

unsigned char counter = 0; // Counter Variable

void main(void) {
  WDTCTL = WDTPW + WDTHOLD; // Stop WDT
  P1DIR |= 0x01; // P1.0 output
  TACCTL0 = CCIE; // TA0 CCR0 control: TACCR0 interrupt enabled - Klockan kan interuppta
  TACCR0 = 50000; //TA0 capture/compare register - R�kna till 500
  TACTL = TASSEL_2 + MC_1; // SMCLK, up mode - V�ljer Vilken klocka, i detta fall submaine clock, r�knar upp�t pga +mc_1
  _BIS_SR(LPM0_bits + GIE); // Enter LPM0 w/ interrupt - G� in i lowpowermode. Enablar Global Interuppt
}
// Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR // Togglar lampan n�r den har r�knat till 500 i detta fall.
__interrupt void Timer_A(void) {

    // F�rdr�jning av 10Hz signalen
  if (counter == 100) {
    P1OUT ^= 0x01; // Toggle P1.0 - Lampan lyser just nu vid 1khz.
    counter = 0;
  } else {
    counter++;
  }
}

// T1.1 L�sning: �ndra v�rdet 500 till 50 000 ger alltså 10hz.

// T1.2 L�sning: S�tt r�knaren till 50 000 sedan l�gg en if sats som r�knar endast efter 100 steg,
// detta f�r att g�ra klockan l�ngsammare - Se ifsats #16
// Allts� att den togglar vid 0.1hz enligt �nskem�l.
































