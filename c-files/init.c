//------------------------------------------------------------------------------
//  Description: This file initializes the display and enables interrupts.
//
//  Alexay Mehra
//  Sep 2025
//  Built with Code Composer Studio 12.8.1
//------------------------------------------------------------------------------


// Includes
#include  "msp430.h"
#include  "functions.h"
#include  "LCD.h"
#include  "macros.h"
#include  "ports.h"


// Global Variables
extern char display_line[4][11];                        // LCD display
extern char *display[4];                                // LCD display
extern volatile unsigned char update_display;           // Update display
extern volatile unsigned int disp_update_counter;       // Update display counter

extern volatile unsigned int time_counter;              // Time counter

extern char color_to_measure;                           // Color to calibrate
extern volatile unsigned int calibrate_counter;         // Calibration counter
extern unsigned char detect_state;                      // Detection state machine variable
extern unsigned char follow_state;                      // Following state machine variable
extern volatile unsigned int ADC_Channel;               // ADC channel tracker

extern volatile unsigned char sw1_pressed;              // Indicate if SW1 pressed
extern volatile unsigned char sw2_pressed;              // Indicate if SW2 pressed

extern char init_seq_state;                             // Initial commands state machine variable
extern char can_exec_command;                           // Indicate if commands can be executed

extern volatile unsigned int ping_counter;              // Counter for pinging google


// Initialize Conditions -------------------------------------------------------
void Init_Conditions(void){
  unsigned int i;                       // Perform resets for LCD
  for(i = 11; i > 0; i--){              // Loop through all chars in display
    display_line[0][i-1] = RESET_STATE; // Set all line 1 chars to reset state
    display_line[1][i-1] = RESET_STATE; // Set all line 2 chars to reset state
    display_line[2][i-1] = RESET_STATE; // Set all line 3 chars to reset state
    display_line[3][i-1] = RESET_STATE; // Set all line 4 chars to reset state
  }
  display_line[0][10] = 0;              // Null terminate line 1
  display_line[1][10] = 0;              // Null terminate line 2
  display_line[2][10] = 0;              // Null terminate line 3
  display_line[3][10] = 0;              // Null terminate line 4

  display[0] = &display_line[0][0];     // display[0] points to display_line[0][0]
  display[1] = &display_line[1][0];     // display[1] points to display_line[1][0]
  display[2] = &display_line[2][0];     // display[2] points to display_line[2][0]
  display[3] = &display_line[3][0];     // display[3] points to display_line[3][0]
  update_display = 0;                   // Don't update display yet

  P4IFG &= ~SW1;                        // Ensure interrupt flag cleared
  P2IFG &= ~SW2;                        // Ensure interrupt flag cleared

  enable_interrupts();                  // Enable interrupts
}
//------------------------------------------------------------------------------


// Initialize Variables --------------------------------------------------------
void Init_Vars(void){
    time_counter = 0;                   // Set time_counter to 0
    disp_update_counter = 0;            // Set the update display counter to 0
    calibrate_counter = 0;              // Set calibration counter to 0

    sw1_pressed = FALSE;                // Set SW1 not pressed
    sw2_pressed = FALSE;                // Set SW2 not pressed

    detect_state = IDLE;                // Set detection state to idle
    follow_state = IDLE;                // Set follow state to idle

    ADC_Channel = 0;                    // Set ADC channel to 0
    color_to_measure = WHITE;           // Set color to be measured to white

    init_seq_state = WAITING;           // Sent initial command sequence state
    can_exec_command = CAN_EXECUTE;     // Set variable to allow commands to execute

    ping_counter = 0;                   // Reset ping counter
}
//------------------------------------------------------------------------------


