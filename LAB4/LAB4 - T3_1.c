// MSP430(1)

#include "msp430g2553.h"

#define RXLED BIT6
#define TXLED BIT0
#define TXD BIT2
#define RXD BIT1

void main(void) {

    // Configuration
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT
    DCOCTL = 0; // Select lowest DCOx and MODx settings   <-**| (Calibrate internal oscilator at 1 Mhz)
    BCSCTL1 = CALBC1_1MHZ; // Set DCO                     <-**| (Master Clock (SMCLK) used by UART)
    DCOCTL = CALDCO_1MHZ; // Set DCO                      <-**|
    P2DIR = 0xFF;// Disable all p2.x outputs.
    P2OUT &=0x00; //
    P1SEL |= RXD + TXD; // P1.1 = RXD, P1.2 = TXD         <-**| (p1.1 and p1.2 set to UART mode)
    P1SEL2 |= RXD + TXD; // P1.1 = RXD, P1.2 = TXD        <-**|
    P1DIR |= RXLED + TXLED; // LED setup
    P1OUT &= 0x00; //LED setup

    UCA0CTL1 |= UCSSEL_2; // SMCLK set as clock source
    // Could have used UCSSEL_1 to select an external crystal (ACLK) as clock source.
    UCA0BR0 = 0x34; // Baud rate 19200, calc: 1Mhz/x = 19200, x = 52 = 0x34
    UCA0BR1 = 0x00; // Baud rate, UCA0BR1 is the "overflow" of UCA0BR0

    UCA0MCTL = UCBRS2 + UCBRS0; // Modulation UCBRSx = 5  (what dis?) (probably want to keep it)
    UCA0CTL1 &= ~UCSWRST; // **initialize USCI state machine**  <-**| Enable UART module for the recieve event.
    UC0IE |= UCA0RXIE; // Enable USCI_A0 RX interrupt            <-**|

    TACCR0 |= CCIE;

    __bis_SR_register(GIE); // general interrupt.
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void) {

     // skicka till  MSP430(2)
    UCA0TXBUF = 0x67 ; // 'g' i ASCII  - Kan skriva 'g'
  }

// UART RX interrupt service routine
#pragma vector=USCIAB0RX_VECTOR
__interrupt void UART_Rx (void) {

   // om 'r' är fått från MSP430(2) tänd röda lampan
  if(UCA0RXBUF == 0x72) P1OUT ^= 0x01; //**RXLED??** Red LED toggle
}
