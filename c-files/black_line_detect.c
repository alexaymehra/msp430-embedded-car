//------------------------------------------------------------------------------
//  Description: This file contains the code for black line detection.
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
unsigned char detect_state;                     // Detection state machine variable
extern volatile unsigned int time_counter;      // Time counter (incremented every 20ms)
extern char display_line[4][11];                // LCD display
extern char *display[4];                        // LCD display
extern volatile unsigned char display_changed;  // LCD display changed
extern volatile unsigned int ADC_Left_Detect;   // Corresponds to V_DETECT_R (physical left side)
extern volatile unsigned int ADC_Right_Detect;  // Corresponds to V_DETECT_L (physical right side)
extern unsigned int white_value;                // Calibrated white value
extern unsigned int black_value;                // Calibrated black value
extern unsigned char follow_state;              // Black line following state machine variable


// Timed movement state machine ------------------------------------------------
void black_line_machine(void){
    switch (detect_state){                  // Detection State Machine
        case IDLE: break;                   // IDLE: do nothing
        case PREPARE:                       // PREPARE:
            prepare_case();                 // Make preparations
            break;
        case WHITE_DETECT:                  // WHITE DETECT:
            white_detect_case();            // Find the white board
            break;
        case DELAY1:                        // DELAY1:
            delay_case_1();                 // 10s delay
            break;
        case RUN:                           // RUN:
            run_case();                     // Find the black line
            break;
        case DELAY2:                        // DELAY2:
            delay_case_2();                 // 10s delay
            break;
        case TURN:                          // TURN:
            turn_case();                    // Turn onto the black line
            break;
        case STOP:                          // STOP:
            stop_case();                    // 10s delay, then start black line following
            break;
        default: break;                     // DEFAULT: do nothing
    }
}
//------------------------------------------------------------------------------


// Prepare for movement --------------------------------------------------------
void prepare_case(void){
    P2OUT |= IR_LED;                            // IR LED ON
    All_Movement_Off();                         // Movement OFF
    Forward_Med();                              // Forward MED
    detect_state = WHITE_DETECT;                // Detect state WHITE_DETECT
}
//------------------------------------------------------------------------------


// Run detection for white line ------------------------------------------------
void white_detect_case(void){
    if ((ADC_Left_Detect <= (white_value + 5))      // If white found
    && (ADC_Left_Detect >= (white_value - 5))){
        All_Movement_Off();                         // Movement OFF
        time_counter = 0;                           // Reset time counter
        detect_state = DELAY1;                      // Detect state DELAY1
        strcpy(display_line[0], " BL Start ");      // Display BL Start
        display_changed = TRUE;                     // Display changed
        LCD_BACKLITE_DIMMING = PERCENT_80;          // LCD light ON
    }
}
//------------------------------------------------------------------------------


// Delay case 1 ----------------------------------------------------------------
void delay_case_1(void){
    if (time_counter > 500){                        // 10s delay
        detect_state = RUN;                         // Detect state RUN
        LCD_BACKLITE_DIMMING = OFF;                 // LCD light OFF
        Forward_Med();                              // Forward MED
    }
}
//------------------------------------------------------------------------------


// Run the detection -----------------------------------------------------------
void run_case(void){
    if ((ADC_Left_Detect >= black_value)            // If black found
    && (ADC_Right_Detect >= black_value)){
        All_Movement_Off();                         // Movement OFF
        strcpy(display_line[0], "Intercept ");      // Display Intercept
        display_changed = TRUE;                     // Display changed
        LCD_BACKLITE_DIMMING = PERCENT_80;          // LCD light ON
        detect_state = DELAY2;                      // Detect state DLEAY2
        time_counter = 0;                           // Reset time counter
    }
}
//------------------------------------------------------------------------------


// Delay case 2 ----------------------------------------------------------------
void delay_case_2(void){
    if (time_counter > 500){                        // 10s delay
        strcpy(display_line[0], " BL Turn  ");      // Display BL Turn
        display_changed = TRUE;                     // Display changed
        detect_state = TURN;                        // Detect state TURN
        Left_Slow();                                // Left Slow
    }
}
//------------------------------------------------------------------------------


// Turn case -------------------------------------------------------------------
void turn_case(void){
    if (ADC_Right_Detect >= black_value){           // If right finds black
        All_Movement_Off();                         // Movement OFF
        detect_state = STOP;                        // Detect state STOP
        time_counter = 0;                           // Rest time counter
    }
}
//------------------------------------------------------------------------------


// Ensure all movement stopped & reset to idle state ---------------------------
void stop_case(void){
    if (time_counter > 500){                        // 10s delay
        detect_state = IDLE;                        // Detect state IDLE
        follow_state = PREPARE;                     // Initiate black line following
    }
}
//------------------------------------------------------------------------------

