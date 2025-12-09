//------------------------------------------------------------------------------
//
//  Description: This file sets up the switch interrupts.
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
volatile unsigned char sw1_pressed;         // Indicate if SW1 pressed
volatile unsigned char sw2_pressed;         // Indicate if SW2 pressed


// SW1 Interrupt - DeBounce Time is 250ms -------------------------------------
#pragma vector = PORT4_VECTOR
__interrupt void switch1_interrupt(void) {
    if (P4IFG & SW1) {                      // Check if interrupt is for SW1
        P4IE &= ~SW1;                       // 1. Disable Switch 1
        P4IFG &= ~SW1;                      // 2. Clear Switch 1 Flag
        TB0CCTL1 &= ~CCIFG;                 // 3. Clear TimerB0 Interrupt Flag for CCR1
        TB0CCR1 = TB0R + TB0CCR1_INTERVAL;  // 4. Add Interval to TB0R for TB0CCR1
        TB0CCTL1 |= CCIE;                   // 5. Enable TimerB0_1
        sw1_pressed = TRUE;                 // Set variable to identify switch pressed
    }
}
//-----------------------------------------------------------------------------


// SW2 Interrupt - DeBounce Time is 250ms -------------------------------------
#pragma vector = PORT2_VECTOR
__interrupt void switch2_interrupt(void) {
    if (P2IFG & SW2) {                      // Check if interrupt is for SW2
        P2IE &= ~SW2;                       // 1. Disable Switch 2
        P2IFG &= ~SW2;                      // 2. Clear Switch 2 Flag
        TB0CCTL2 &= ~CCIFG;                 // 3. Clear TimerB0 Interrupt Flag for CCR2
        TB0CCR2 = TB0R + TB0CCR2_INTERVAL;  // 4. Add Interval to TB0R for TB0CCR2
        TB0CCTL2 |= CCIE;                   // 5. Enable TimerB0_2
        sw2_pressed = TRUE;                 // Set variable to identify switch pressed
    }
}
//-----------------------------------------------------------------------------
