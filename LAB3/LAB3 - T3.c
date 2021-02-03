#include "msp430g2553.h"

/*
 *
 * Create a result buffer.
 *
 * The number of element is same as the number of ADC reading using DTC
 *
 * Flag resets when interrput request is served
 *
 */

int a[16] = {0};
int i, average, sum = 0;

void main(void) {

        // ska det vara WDTPW | WDTHOLD eller + mellan?
  WDTCTL = WDTPW + WDTHOLD; // Stop Watchdog Timer
  // RefV is 2.5 V with REF2_5V

  /// FRÅGA SAMUEL OM |=
  ADC10CTL0 |= SREF_1 + ADC10SHT_2 + REFON + ADC10ON + REF2_5V + MSC + ADC10IE; // MSC (multi sample conversion),  Interrupt enabled
  ADC10CTL1 |= INCH_1 + CONSEQ_2; // input A1, CONSEQ_2 - repeat single channel mode

  // Varför |= nedan?
  ADC10AE0 = 0x01; // P1.1 ADC option select
  ADC10DTC1 = 0x10; // 16 transfers per block

 //Set the address of the ADC buffer  with the address of the Array
  ADC10SA = (unsigned short) a; //  Set DTC sample location to where the physical memory array a is located
  ADC10CTL0 |= ENC + ADC10SC; // Enable and start conversion

  __bis_SR_register (GIE); // General interrup

 }

#pragma vector = ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
  // Calculate average of the ADC reading in the defined array
  for (i = 0; i < 16; i++) {
    sum = sum + a[i];
  }
  average = sum / 16;
  sum = 0;
  ADC10SA = (unsigned short) a; //  Set DTC sample location to where the physical memory array a is located
}

