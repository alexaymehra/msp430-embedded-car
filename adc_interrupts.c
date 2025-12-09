//------------------------------------------------------------------------------
//  Description: This file contains the ADC interrupt configuration.
//
//  Alexay Mehra
//  Oct 2025
//  Built with Code Composer Studio 12.8.1
//------------------------------------------------------------------------------


// Includes
#include  "msp430.h"
#include  <string.h>
#include  "functions.h"
#include  "LCD.h"
#include  "macros.h"
#include  "ports.h"


// Globals
volatile unsigned int ADC_Channel;              // ADC channel tracker
volatile unsigned int ADC_Left_Detect;          // Corresponds to V_DETECT_R (physical left side)
volatile unsigned int ADC_Right_Detect;         // Corresponds to V_DETECT_L (physical right side)


// ADC interrupt --------------------------------------------------------------
#pragma vector = ADC_VECTOR
__interrupt void ADC_ISR(void) {
    switch(__even_in_range(ADCIV, ADCIV_ADCIFG)) {
        case ADCIV_NONE:                                        // No interrupt pending
            break;
        case ADCIV_ADCOVIFG:                                    // Conversion result overwritten before read
            break;
        case ADCIV_ADCTOVIFG:                                   // Conversion-time overflow
            break;
        case ADCIV_ADCHIIFG:                                    // Window comparator high threshold interrupt
            break;
        case ADCIV_ADCLOIFG:                                    // Window comparator low threshold interrupt
            break;
        case ADCIV_ADCINIFG:                                    // Window comparator inside window interrupt
            break;
        case ADCIV_ADCIFG:                                      // Conversion complete & ADCMEM0 has new value
            ADCCTL0 &= ~ADCENC;                                 // Disable ADC conversions
            switch(ADC_Channel++){
                case 0x00:                                      // Channel A2
                    ADC_Right_Detect = ADCMEM0;                 // Store conversion result (channel A2)
                    ADC_Right_Detect = ADC_Right_Detect >> 2;   // Divide result by 4 (reduce noise)
                    ADCMCTL0 &= ~ADCINCH_2;                     // Disable channel A2
                    ADCMCTL0 |= ADCINCH_3;                      // Set next channel to A3
                    ADCCTL0 |= ADCSC;                           // Start next sample
                    break;
                case 0x01:                                      // Channel A3
                    ADC_Left_Detect = ADCMEM0;                  // Store conversion result (channel A3)
                    ADC_Left_Detect = ADC_Left_Detect >> 2;     // Divide result by 4 (reduce noise)
                    ADCMCTL0 &= ~ADCINCH_3;                     // Disable channel A3
                    ADCMCTL0 |= ADCINCH_2;                      // Set next channel to A2
                    ADC_Channel = 0;                            // Reset channel tracker
                    break;
                default: break;
            }
            ADCCTL0 |= ADCENC;                                  // Enable ADC conversions
            break;
        default: break;                                         // Default: break
    }
}
//-----------------------------------------------------------------------------
