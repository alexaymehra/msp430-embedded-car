//------------------------------------------------------------------------------
//  Description: This file contains the Main Routine - "While" Operating System.
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
extern char display_line[4][11];                // LCD display
extern char *display[4];                        // LCD display
unsigned char display_mode;                     // LCD display mode
extern volatile unsigned char display_changed;  // LCD display changed
extern volatile unsigned int time_counter;      // Time counter (updated in timer interrupt)


// Main Function ---------------------------------------------------------------
void main(void){

    Init_Ports();                           // Initialize Ports
    Init_Clocks();                          // Initialize Clock System
    Init_Timers();                          // Initialize Timers

    Init_Vars();                            // Initialize Variables
    Init_Conditions();                      // Initialize Display Values & Enable Interrupts

    while (time_counter < 50);              // Wait 1 sec

    Init_LCD();                             // Initialize LCD

    while (time_counter < 60);              // Wait 200 msec

    Init_ADC();                             // Initialize ADC

    while (time_counter < 70);              // Wait 200 msec

    Init_UART(SPEED_115200);                // Initialize UART

    while (time_counter < 80);              // Wait 200 msec

    P3OUT |= IOT_EN;                        // Enable IOT

    while (time_counter < 90);              // Wait 200msec

    Init_DAC();                             // Initialize DAC

    strcpy(display_line[0], " Waiting  ");  // Initial display
    strcpy(display_line[1], "for input ");  // Initial display
    strcpy(display_line[2], "          ");  // Initial display
    strcpy(display_line[3], "          ");  // Initial display
    display_changed = TRUE;                 // Display changed

    // Main Code that is Always Active ---------------------------------------------
    while(ALWAYS) {
        Switches_Process();                 // Check for switch state change
        Display_Process();                  // Update Display
        P3OUT ^= TEST_PROBE;                // Change State of TEST_PROBE

        Check_Rev_Fwd();                    // Ensure reverse & forward movement not on at same time

        IOT_Receive();                      // Receive and store commands
        Run_Commands();                     // Run commands
        Initial_Command_Sequence();         // Initial command sequence & pinging google

        black_line_machine();               // Black line detection state machine
        line_follow_machine();              // Black line following state machine
    }
    //------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------


