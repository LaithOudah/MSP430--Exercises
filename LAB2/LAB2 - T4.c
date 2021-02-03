#include <msp430.h>

// Identiferar f�r chippen det som ska anv�ndas n�r var och hur.
void main(void) {
  WDTCTL = WDTPW + WDTHOLD; // Stop WDT
  P1DIR |= 0x01 + 0x02 + 0x04; // Output P1.0, P1.1 och P1.2
  P1SEL |= 0x02 + 0x04; // St�ller P1.1 och P1.2 till timer output
  TACCTL0 = CCIE + OUTMOD_4; // TACCR0 interrupt enabled - Olika Output modes, 4an ger att den togglar
  TACCTL1 = CCIE + OUTMOD_4; // TACCR1 interrupt enabled - Olika Output modes, 4an ger att den togglar
//  TACCR0 = 200; // TACCR0 initial value - Givet ~ 2500Hz -> Beh�vs ej
//  TACCR1 = 1000; //TACCR1 initial value - Givet ~ 500HZ -> Beh�vs ej
  TACTL = TASSEL_2 + MC_2 + TAIE; // SMCLK, continuous mode, TA interrupt
  _BIS_SR(LPM0_bits + GIE); // Enter LPM0 w/ interrupt
}

#pragma vector = TIMER0_A0_VECTOR // Interrupt f�r TACCR0 Vector handler
void TIMER_A0(void) {
  //  P1OUT ^= BIT1; // Togglar P1.1 -> Utkommenterad d� OUTMOD_4 Anv�nds
  TACCR0 += 200; // Add offset 200 - Hur m�nga cyklar per klockslag
}

#pragma vector = TIMER0_A1_VECTOR // Interrupt f�r TACCR1 Vector handler
void Timer_A1(void) {

  switch (TAIV) {
  case 2: { //TACCR1 interrupt // Case 2
    //   P1OUT ^= BIT2; // Toggle P1.2 -> Utkommenterad d� OUTMOD_4 Anv�nds
    TACCR1 += 1000; // Add offset to 1000
    break;
  }
  case 4: { // TCCR2 Anv�nds ej
    break;}
  case 10: { // Case 10
    P1OUT ^= BIT0; // Toggle P1.0
    break;
    }
  }
}
