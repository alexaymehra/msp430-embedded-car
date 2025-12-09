//------------------------------------------------------------------------------
//  Description: This file sets up the timer interrupts.
//
//  Alexay Mehra
//  Oct 2025
//  Built with Code Composer Studio 12.8.1
//------------------------------------------------------------------------------


// Includes
#include  "msp430.h"
#include  "functions.h"
#include  "LCD.h"
#include  "macros.h"
#include  "ports.h"


// Globals
extern volatile unsigned char update_display;   // Indicate if display to be updated
volatile unsigned int time_counter;             // Time counter
volatile unsigned int disp_update_counter;      // Update display counter
volatile unsigned int move_counter;             // Movement counter
volatile unsigned int calibrate_counter;        // Calibration counter
volatile unsigned int ping_counter;             // Ping counter

volatile unsigned int overflow_counter = 0;     // Overflow counter
extern unsigned int DAC_data;                   // DAC value holder


// TimerB0 CCR0 Interrupt handler for 20msec timer ----------------------------
#pragma vector = TIMER_B0_CCR0_VECTOR
__interrupt void Timer0_B0_ISR(void){
    disp_update_counter++;                  // Increment counter for updating display
    if (disp_update_counter >= 10){         // Every 200msec
        disp_update_counter = 0;            // Reset update display counter
        update_display = TRUE;              // Indicate display to be updated
    }

    time_counter++;                         // Increment time counter
    move_counter++;                         // Increment move counter
    calibrate_counter++;                    // Increment calibrate counter
    ping_counter++;                         // Increment ping counter

    ADCCTL0 |= ADCSC;                       // Start an ADC conversion

    TB0CCR0 += TB0CCR0_INTERVAL;            // Set next interrupt to 20msec later
}
// ----------------------------------------------------------------------------


// TimerB0 CCR1, CCR2, and Overflow Interrupt Vector (TBIV) handler -----------
#pragma vector = TIMER_B0_CCR1_2_OV_VECTOR
__interrupt void TIMER0_B1_ISR(void){
    switch(__even_in_range(TB0IV,14)){
        case  0: break;                     // Case: No interrupt
        case  2:                            // Case: CCR1 Used for SW1 DeBounce
            TB0CCTL1 &= ~CCIE;              // 1. Disable Timer B0 CCR1
            P4IFG &= ~SW1;                  // 2. Clear SW1 Interrupt Flag
            P4IE |= SW1;                    // 3. Enable SW1 Interrupt
            break;
        case 4:                             // Case: CCR2 Used for SW2 DeBounce
            TB0CCTL2 &= ~CCIE;              // 1. Disable Timer B0 CCR2
            P2IFG &= ~SW2;                  // 2. Clear SW2 Interrupt Flag
            P2IE |= SW2;                    // 3. Enable SW2 Interrupt
            break;
        case 14:                            // Case: Overflow
            overflow_counter++;             // Increment overflow counter
            if (overflow_counter == 3){     // Wait for 3 overflows
                P2OUT |= DAC_ENB;           // Enable DAC
            }
            if (overflow_counter > 3){      // Wait for more than 3 overflows
                DAC_data = DAC_data - 100;  // Ramp up DAC data value
                SAC3DAT = DAC_data;         // Set DAC data

                if (DAC_data <= DAC_Limit){ // If DAC data below the limit
                    DAC_data = DAC_Adjust;  // Set DAC data to chosen value
                    SAC3DAT = DAC_data;     // Set DAC data
                    TB0CTL &= ~TBIE;        // Disable overflow interrupt
                }
            }
            break;
        default: break;                     // DEFAULT: do nothing
    }
}
//-----------------------------------------------------------------------------
