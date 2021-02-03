#include "msp430g2553.h"

void main(void) {

 WDTCTL = WDTPW + WDTHOLD; // Stop WDT
 ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON + ADC10ON + ADC10IE + REF2_5V;// VREFpositiv + Referens ON + ADC On + ADC Interrupt enable + 2.5V
 ADC10CTL1 = INCH_1 + CONSEQ_2 + SHS_1; // Input A1(P1.1) + Repeat Mode + Sample&HoldSourceSelect
 ADC10AE0 |= BIT1; // ADC Analog Enable For P1.1
 P1DIR |= BIT0; // Set P1.0 to output direction

 TACCR0 = 2048-1;       // PWM Period
 TACCTL1 = OUTMOD_3;    // OutputMode3 Set/Reset
 TACCR1 = 1024-1;       // PWM Duty Cycle
 TACTL = TASSEL_2 + MC_1; // SMCLK + UpMode

 ADC10CTL0 |= ENC; // Enable Conversion

__bis_SR_register (GIE); // Low power mode

}

#pragma vector = ADC10_VECTOR; // Vadfan är du? Jag vet inte, den funkar.
__interrupt void ADC10_ISR(void) {
    if (ADC10MEM < 0x265) {  // A1 > (1.5 V * 1023)/2.5 = 613 => 0x265
        P1OUT &= ~0x01; // Clear P1.0 LED Off
    }
    else {
        P1OUT |= 0x01; // Set P1.0 LED On
    }
}

