//------------------------------------------------------------------------------
//  Description: This file contains the ADC configuration and display functions.
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
extern char display_line[4][11];                    // LCD display
extern char *display[4];                            // LCD display
extern volatile unsigned char display_changed;      // LCD display changed
char adc_char[4];                                   // ADC value display


// ADC configuration ----------------------------------------------------------
void Init_ADC(void){
    // ADCCTL0 - ADC Control Register 0
    ADCCTL0 = 0;                    // Reset
    ADCCTL0 |= ADCSHT_2;            // Sample-and-hold time = 16 cycles from ADC clock source (divided)
    ADCCTL0 |= ADCMSC;              // Multiple Sample Conversion (has no effect in our case)
    ADCCTL0 |= ADCON;               // Turn on ADC

    // ADCCTL1 - ADC Control Register 1
    // ADCCTL1 & ADCBUSY identifies a conversion is in process
    ADCCTL1 = 0;                    // Reset
    ADCCTL1 |= ADCSHS_0;            // Trigger source for ADC conversion process: software (ADCSC bit)
    ADCCTL1 |= ADCSHP;              // Use internal sampling timer to generate sample pulse (uses duration set earlier, 16 cycles)
    ADCCTL1 &= ~ADCISSH;            // No signal inversion on sample-and-hold control line (ADC samples when line is high)
    ADCCTL1 |= ADCDIV_0;            // Divide clock source by additional 1
    ADCCTL1 |= ADCSSEL_0;           // Clock source: MODCLK
    ADCCTL1 |= ADCCONSEQ_0;         // Conversion mode: Single-channel single-conversion

    // ADCCTL2 - ADC Control Register 2
    ADCCTL2 = 0;                    // Reset
    ADCCTL2 |= ADCPDIV0;            // Divide clock source by 1
    ADCCTL2 |= ADCRES_1;            // 10-bit resolution
    ADCCTL2 &= ~ADCDF;              // output format: unsigned integer
    ADCCTL2 &= ~ADCSR;              // Use normal sampling rate (<= 200k samples per second)

    // ADCMCTL0 - ADC Memory Control Register 0
    ADCMCTL0 |= ADCSREF_0;          // Reference Levels:  VR+ = AVCC  and  VR– = AVSS (the microcontroller's VCC and GND rails)
    ADCMCTL0 |= ADCINCH_2;          // Select First Input Channel to be Read upon ADC Interrupt (V_BAT)

    // Interrupts and Conversion Start
    ADCIE   |= ADCIE0;              // Enable ADC to generate interrupts upon completion of a conversion
    ADCCTL0 |= ADCENC;              // Enable ADC conversions
}
//-----------------------------------------------------------------------------


// Hex to BCD conversion -------------------------------------------------------
void HEXtoBCD(unsigned int hex_value){
    int value = 0;                          // Helper variable (placeholder)
    unsigned int i;                         // Helper variable (looping)
    for (i = 0; i < 4; i++){                // Loop through adc_char
        adc_char[i] = '0';                  // Set adc_char to all zeros
    }

    while (hex_value > 999){                // While hex_value > 999
        hex_value = hex_value - 1000;       // Subtract 1000
        value = value + 1;                  // Add 1 to value
    }
    adc_char[0] = 0x30 + value;             // Thousands place

    value = 0;                              // Reset value
    while (hex_value > 99){                 // While hex_value > 99
        hex_value = hex_value - 100;        // Subtract 100
        value = value + 1;                  // Add 1 to value
    }
    adc_char[1] = 0x30 + value;             // Hundreds place

    value = 0;                              // Reset value
    while (hex_value > 9){                  // While hex_value > 9
        hex_value = hex_value - 10;         // Subtract 10
        value = value + 1;                  // Add 1 to value
    }
    adc_char[2] = 0x30 + value;             // Tens place

    adc_char[3] = 0x30 + hex_value;         // Ones place
}

//------------------------------------------------------------------------------


// ADC line insert -------------------------------------------------------------
void adc_line(char line, char location){
    unsigned int real_line;                                     // Real line
    real_line = line - 1;                                       // Line - 1
    unsigned int i;                                             // Helper variable
    for (i = 0; i < 4; i++){                                    // Loop through adc_char
        display_line[real_line][i+location] = adc_char[i];      // Display adc_char
    }
    display_changed = TRUE;                                     // Display changed
}
//------------------------------------------------------------------------------
