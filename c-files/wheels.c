//------------------------------------------------------------------------------
//
//  Description: This file contains the functions for basic movement.
//
//  Alexay Mehra
//  Oct 2025
//  Built with Code Composer Studio 12.8.1
//------------------------------------------------------------------------------


// Includes
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"
#include  "ports.h"


// Turn off all movement -------------------------------------------------------
void All_Movement_Off(void){
    LEFT_FORWARD_SPEED = WHEEL_OFF;         // Wheel Off
    RIGHT_FORWARD_SPEED = WHEEL_OFF;        // Wheel Off
    LEFT_REVERSE_SPEED = WHEEL_OFF;         // Wheel Off
    RIGHT_REVERSE_SPEED = WHEEL_OFF;        // Wheel Off
}
//------------------------------------------------------------------------------


// Ensure reverse and forward movement is not on at the same time --------------
void Check_Rev_Fwd(void){
    if ((LEFT_FORWARD_SPEED != WHEEL_OFF)   // If left forward not OFF
    && (LEFT_REVERSE_SPEED != WHEEL_OFF)){  // And left reverse not OFF
        All_Movement_Off();                 // Movement Off
        P1OUT |= RED_LED;                   // RED LED ON
        P6OUT  &= ~GRN_LED;                 // GREEN LED OFF
    }
    if ((RIGHT_FORWARD_SPEED != WHEEL_OFF)  // If right forward not OFF
    && (RIGHT_REVERSE_SPEED != WHEEL_OFF)){ // And right reverse not OFF
        All_Movement_Off();                 // Movement Off
        P1OUT |= RED_LED;                   // RED LED ON
        P6OUT  &= ~GRN_LED;                 // GREEN LED OFF
    }
}
//------------------------------------------------------------------------------


// Move forward at slow speed --------------------------------------------------
void Forward_Slow(void){
    LEFT_FORWARD_SPEED = LEFT_SLOW;             // Wheel Slow
    RIGHT_FORWARD_SPEED = RIGHT_SLOW;           // Wheel Slow
}
//------------------------------------------------------------------------------


// Move forward at med speed ---------------------------------------------------
void Forward_Med(void){
    LEFT_FORWARD_SPEED = LEFT_MED;              // Wheel Med
    RIGHT_FORWARD_SPEED = RIGHT_MED;            // Wheel Med
}
//------------------------------------------------------------------------------


// Move forward at fat speed --------------------------------------------------
void Forward_Fast(void){
    LEFT_FORWARD_SPEED = LEFT_FAST;             // Wheel Fast
    RIGHT_FORWARD_SPEED = RIGHT_FAST;           // Wheel Fast
}
//------------------------------------------------------------------------------


// Move reverse at fast speed --------------------------------------------------
void Reverse_Fast(void){
    LEFT_REVERSE_SPEED = LEFT_FAST;             // Wheel Fast
    RIGHT_REVERSE_SPEED = RIGHT_FAST;           // Wheel Fast
}
//------------------------------------------------------------------------------


// Spin in place clockwise -----------------------------------------------------
void Right_Slow(void){
    LEFT_FORWARD_SPEED = LEFT_SLOW;             // Wheel Slow
    RIGHT_REVERSE_SPEED = RIGHT_SLOW;           // Wheel Slow
}
//------------------------------------------------------------------------------


// Spin in place counterclockwise ----------------------------------------------
void Left_Slow(void){
    LEFT_REVERSE_SPEED = LEFT_SLOW;             // Wheel Slow
    RIGHT_FORWARD_SPEED = RIGHT_SLOW;           // Wheel Slow
}
//------------------------------------------------------------------------------
