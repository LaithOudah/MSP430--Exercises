// MSP430(2)

#include "msp430g2553.h"

#define RXLED BIT6
#define TXLED BIT0
#define TXD BIT2
#define RXD BIT1

void main(void) {

    WDTCTL = WDTPW + WDTHOLD; // Stop WDT
    DCOCTL = 0; // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ; // Set DCO
    DCOCTL = CALDCO_1MHZ; // Set DCO
    P2DIR = 0xFF; //Disable all p2.x outputs.
    P2OUT &=0x00;
    P1SEL |= RXD + TXD; // P1.1 = RXD, P1.2 = TXD
    P1SEL2 |= RXD + TXD; // P1.1 = RXD, P1.2 = TXD
    P1DIR |= RXLED + TXLED;
    P1OUT &= 0x00;

    UCA0CTL1 |= UCSSEL_2; // SMCLK

    UCA0BR0 = 0x34; // Baud rate 19200, calc: 1Mhz/x = 19200, x = 52 = 0x34
    UCA0BR1 = 0x00; // Baud rate, UCA0BR1 is the "overflow" of UCA0BR0

    UCA0MCTL = UCBRS2 + UCBRS0; //Modulation UCBRSx = 5  (what dis?) (probably want to keep it)
    UCA0CTL1 &= ~UCSWRST; // **initialize USCI state machine**
    UC0IE |= UCA0RXIE; //Enable USCI_A0 RX interrupt

    __bis_SR_register(GIE); //general interrupt.
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void) {

     // Skicka till MSP430(1)
    UCA0TXBUF = 0x72 ; // 'r' i ASCII
  }

// UART RX interrupt service routine
#pragma vector=USCIAB0RX_VECTOR
__interrupt void UART_Rx (void) {

   // om 'g' är fått värde från MSP430(1) så tänd gröna lampan
  if(UCA0RXBUF == 0x67) P1OUT ^= 0x40; // **TXLED?** Green LED toggle
}
