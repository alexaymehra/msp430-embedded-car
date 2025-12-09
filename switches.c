//------------------------------------------------------------------------------
//
//  Description: This file contains the functions for when a switch is pressed.
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
#include  <string.h>


// Globals
extern volatile unsigned char sw1_pressed;          // Indicate if SW1 pressed
extern volatile unsigned char sw2_pressed;          // Indicate if SW2 pressed

char color_to_measure;                              // Color to calibrate

extern char display_line[4][11];                    // LCD display
extern char *display[4];                            // LCD display
extern volatile unsigned char display_changed;      // LCD display changed


// Call both Switch Functions ----------------------------------------------------
void Switches_Process(void){
    Switch1_Process();                              // SW1 function
    Switch2_Process();                              // SW2 function
}
// -------------------------------------------------------------------------------


// Switch 1 Function -------------------------------------------------------------
void Switch1_Process(void){
    if (sw1_pressed == TRUE){                       // If SW1 pressed

        sw1_pressed = FALSE;                        // Reset button pressed state

        P2OUT |= IR_LED;                            // IR LED on for calibration

        if (color_to_measure == WHITE){             // If WHITE to be calibrated
            calibrate_color(WHITE);                 // Calibrate WHITE
            color_to_measure = BLACK;               // Set BLACK to be calibrated
        }
        else if (color_to_measure == BLACK){        // If BLACK to be calibrated
            calibrate_color(BLACK);                 // Calibrate BLACK
            color_to_measure = NOCOLOR;             // Set NOCOLOR to be calibrated
        }
        else{                                       // If NOCOLOR to be calibrated
            strcpy(display_line[0], " Waiting  ");  // Display Waiting
            display_changed = TRUE;                 // Display changed
            color_to_measure = WHITE;               // Set WHITE to be calibrated
        }

        P2OUT &= ~IR_LED;                           // IR LED off for power

    }
}
// -------------------------------------------------------------------------------


// Switch 2 Function -------------------------------------------------------------
void Switch2_Process(void){
    if (sw2_pressed == TRUE){                       // If SW2 pressed
        sw2_pressed = FALSE;                        // Reset button pressed state

        strcpy(display_line[0], "          ");      // Move IP address on display
        strcpy(display_line[1], display_line[2]);   // Move IP address on display
        strcpy(display_line[2], display_line[3]);   // Move IP address on display
        strcpy(display_line[3], "          ");      // Move IP address on display
        display_changed = TRUE;                     // Display changed
    }
}
// -------------------------------------------------------------------------------

