//------------------------------------------------------------------------------
//
//  Description: The file contains functions to initialize timers.
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


// Initial Configurations for All Timers --------------------------------------
void Init_Timers(void){
    Init_Timer_B0();                        // Initialize timer B0
    //Init_Timer_B1();
    //Init_Timer_B2();
    Init_Timer_B3();                        // Initialize timer B1
}
//-----------------------------------------------------------------------------


// Initialize Timer B0 --------------------------------------------------------
void Init_Timer_B0(void) {
    TB0CTL = TBSSEL__SMCLK;                 // Set CLK source (SMCLK, ACLK, external)
    TB0CTL |= MC__CONTINOUS;                // Continuous operating mode
    TB0CTL |= TBCLR;                        // Resets: TB0R, clock divider, count direction
    TB0CTL |= ID__8;                        // Divide clock speed by 8
    TB0EX0 = TBIDEX__8;                     // Divide clock speed by additional 8

    TB0CCR0 = TB0CCR0_INTERVAL;             // CCR0 set 1st interrupt time
    TB0CCTL0 &= ~CCIFG;                     // Clear possible pending interrupt
    TB0CCTL0 |= CCIE;                       // CCR0 enable interrupt

    TB0CCR1 = TB0CCR1_INTERVAL;             // CCR1 set 1st interrupt time
    TB0CCTL1 &= ~CCIFG;                     // Clear possible pending interrupt
    TB0CCTL1 |= CCIE;                       // CCR1 enable interrupt

    TB0CCR2 = TB0CCR2_INTERVAL;             // CCR2 set 1st interrupt time
    TB0CCTL2 &= ~CCIFG;                     // Clear possible pending interrupt
    TB0CCTL2 |= CCIE;                       // CCR2 enable interrupt

    TB0CTL &= ~TBIE;                        // Disable Overflow Interrupt
    TB0CTL &= ~TBIFG;                       // Clear Overflow Interrupt flag
}
//-----------------------------------------------------------------------------


// Initialize Timer B3 --------------------------------------------------------
void Init_Timer_B3(void) {
    TB3CTL = TBSSEL__SMCLK;                 // Set CLK source (SMCLK, ACLK, external)
    TB3CTL |= MC__UP;                       // Up operating mode
    TB3CTL |= TBCLR;                        // Resets: TB3R, clock divider, count direction

    PWM_PERIOD = WHEEL_PERIOD;              // PWM Period (Set to 50005)

    TB3CCTL1 = OUTMOD_7;                    // CCR1 reset/set
    LEFT_FORWARD_SPEED = WHEEL_OFF;         // Left forward PWM duty cycle

    TB3CCTL2 = OUTMOD_7;                    // CCR2 reset/set
    RIGHT_FORWARD_SPEED = WHEEL_OFF;        // Right forward PWM duty cycle

    TB3CCTL3 = OUTMOD_7;                    // CCR3 reset/set
    LEFT_REVERSE_SPEED = WHEEL_OFF;         // Left reverse PWM duty cycle

    TB3CCTL4 = OUTMOD_7;                    // CCR4 reset/set
    RIGHT_REVERSE_SPEED = WHEEL_OFF;        // Right reverse PWM duty cycle

    TB3CCTL5 = OUTMOD_7;                    // CCR5 reset/set
    LCD_BACKLITE_DIMMING = OFF;             // LCD BackLight PWM duty cycle
}
//-----------------------------------------------------------------------------

