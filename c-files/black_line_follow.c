//------------------------------------------------------------------------------
//  Description: This contains the code for following the black line.
//
//  Alexay Mehra
//  Sep 2025
//  Built with Code Composer Studio 12.8.1
//------------------------------------------------------------------------------


// Includes
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"
#include  "ports.h"
#include  <string.h>


// Globals
unsigned char follow_state;                         // Black line following state machine variable
extern volatile unsigned int time_counter;          // Time counter (incremented every 20ms)
extern char display_line[4][11];                    // LCD display
extern char *display[4];                            // LCD display
extern volatile unsigned char display_changed;      // LCD display changed
unsigned char last_movement;                        // Last movement initiated
extern unsigned int black_value;                    // Calibrated black value
extern volatile unsigned int ADC_Left_Detect;       // Corresponds to V_DETECT_R (physical left side)
extern volatile unsigned int ADC_Right_Detect;      // Corresponds to V_DETECT_L (physical right side)
char follow_or_not;                                 // Continue following or not
extern char ready_to_run_command;                   // Indicate if commands can be run


// Timed movement state machine ------------------------------------------------
void line_follow_machine(void){
    switch (follow_state){
        case IDLE: break;               // IDLE: do nothing
        case PREPARE:                   // PREPARE:
            follow_prepare_case();      // Make preparations
            break;
        case DELAY1:                    // DELAY1:
            follow_delay_case_1();      // 10s delay
            break;
        case RUN:                       // RUN:
            follow_run_case();          // Black line following
            break;
        case DELAY2:                    // DELAY2:
            follow_delay_case_2();      // 10s delay
            break;
        case STOP:                      // STOP:
            follow_stop_case();         // 2.5s delay, then stop & let commands be run
            break;
        default: break;                 // DEFAULT: do nothing
    }
}
//------------------------------------------------------------------------------


// Prepare for movement --------------------------------------------------------
void follow_prepare_case(void){
    All_Movement_Off();                         // Movement off
    strcpy(display_line[0], " BL Travel");      // Display BL Travel
    display_changed = TRUE;                     // Display changed
    follow_state = DELAY1;                      // Follow state DELAY1
    follow_or_not = FOLLOW;                     // Continue following
    time_counter = 0;                           // Reset time counter
}
//------------------------------------------------------------------------------


// Follow delay case 1 ---------------------------------------------------------
void follow_delay_case_1(void){
    if (time_counter > 500){                        // 10s delay
        LCD_BACKLITE_DIMMING = OFF;                 // LCD light OFF
        follow_state = RUN;                         // Follow state RUN
        last_movement = FORWARD;                    // Last movement FORWARD
        Forward_Med();                              // Forward MED (kick start)
        time_counter = 0;                           // Reset time counter
    }
}
//------------------------------------------------------------------------------


// Run the following -----------------------------------------------------------
void follow_run_case(void){
    // Finish black line following ------------------------------------------
    if (follow_or_not == DONT_FOLLOW){          // If following to be stopped
        All_Movement_Off();                     // Turn off all movement
        P2OUT &= ~IR_LED;                       // Turn off IR LED for power
        strcpy(display_line[0], " BL Exit  ");  // Display BL Exit
        display_changed = TRUE;                 // Display changed
        LCD_BACKLITE_DIMMING = PERCENT_80;      // LCD light ON
        follow_state = DELAY2;                  // Follow state DELAY2
        time_counter = 0;                       // Reset time counter
    }
    //-----------------------------------------------------------------------

    // Continue black line following ----------------------------------------
    else {
        if ((time_counter >= 300) && (time_counter <= 800)){    // 6s-16s after following
            if (LCD_BACKLITE_DIMMING == OFF){                   // If LCD light OFF
                strcpy(display_line[0], " BL Circle");          // Display BL Circle
                display_changed = TRUE;                         // Display changed
                LCD_BACKLITE_DIMMING = PERCENT_80;              // LCD light ON
                All_Movement_Off();                             // Movement OFF
            }
        }
        else{                                           // If not between 6s-16s after following
            if (time_counter == 801){                   // Right after 16s
                LCD_BACKLITE_DIMMING = OFF;             // LCD light OFF
                Forward_Med();                          // Forward MED (kick start)
                last_movement = FORWARD;                // Last movement FORWARD
            }

            if ((ADC_Left_Detect < black_value)         // If only left white
            && !(ADC_Right_Detect < black_value)){
                if (last_movement != TURN_RIGHT){       // If last movement not right
                    All_Movement_Off();                 // Movement OFF
                    Right_Slow();                       // Right SLOW
                    last_movement = TURN_RIGHT;         // Last movement right
                }
            }

            else if (!(ADC_Left_Detect < black_value)   // If only right white
            && (ADC_Right_Detect < black_value)){
                if (last_movement != TURN_LEFT){        // If last movement not left
                    All_Movement_Off();                 // Movement OFF
                    Left_Slow();                        // Left SLOW
                    last_movement = TURN_LEFT;          // Last movement left
                }
            }

            else if (!(ADC_Left_Detect < black_value)   // If both detectors black
            && !(ADC_Right_Detect < black_value)){
                if (last_movement != FORWARD){          // If last movement not forward
                    All_Movement_Off();                 // Movement OFF
                    Forward_Slow();                     // Forward SLOW
                    last_movement = FORWARD;            // Last movement forward
                }
            }

            else{                                       // If both detectors white
                if ((last_movement == FORWARD)          // If last movement is forward
                && (last_movement != TURN_RIGHT)){      // And if last movement not right
                    All_Movement_Off();                 // Movement OFF
                    Right_Slow();                       // Right SLOW
                    last_movement = TURN_RIGHT;         // Last movement right
                }
            }
        }
    }
    //-----------------------------------------------------------------------
}
//------------------------------------------------------------------------------


// Follow delay case 2 ---------------------------------------------------------
void follow_delay_case_2(void){
    if (time_counter > 500){                    // 10s delay
        LCD_BACKLITE_DIMMING = OFF;             // LCD light OFF
        follow_state = STOP;                    // Follow state STOP
        Forward_Fast();                         // Forward FAST
        time_counter = 0;                       // Reset time counter
    }
}
//------------------------------------------------------------------------------


// Ensure all movement stopped & reset to idle state ---------------------------
void follow_stop_case(void){
    if (time_counter >= 125){                   // Delay of 2.5s
        All_Movement_Off();                     // All movement off
        strcpy(display_line[0], " BL Stop  ");  // Display BL Stop
        display_changed = TRUE;                 // Display changed
        follow_state = IDLE;                    // Reset to idle state
        ready_to_run_command = READY;           // Allow commands to be run
    }
}
//------------------------------------------------------------------------------

