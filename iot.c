//------------------------------------------------------------------------------
//  Description: This file contains the IOT processing functions.
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
char init_seq_state;                                    // Initial commands state machine variable
char can_exec_command;                                  // Indicate whether commands can be executed

extern volatile char IOT_Ring_Rx[SMALL_RING_SIZE];      // IOT ring buffer
extern volatile unsigned int iot_ring_wr;               // IOT ring buffer write index
extern unsigned int iot_ring_rd;                        // IOT ring buffer read index

extern char process_buffer[PROCESS_BUFFER_SIZE];        // Process buffer
extern unsigned int pb_index;                           // Process buffer index

char command_queue[NUM_COMMANDS][COMMAND_LENGTH];       // Command queue
unsigned int command_num;                               // Index for storing commands
unsigned int command_to_run;                            // Index for running commands
char ready_to_run_command;                              // Indicate whether incoming commands can be run

unsigned int delay_time;                                // Delay time after command is run

extern volatile unsigned int move_counter;              // Counter for movement

extern char display_line[4][11];                        // LCD display
extern char *display[4];                                // LCD display
extern volatile unsigned char display_changed;          // LCD display changed

extern unsigned char detect_state;                      // Detection state

extern char follow_or_not;                              // Continute black line following or not


// Receive messages from the ESP32 ---------------------------------------------
void IOT_Receive(void){
    if (iot_ring_wr != iot_ring_rd){                                                // If read and write index different
        char reception_complete = INCOMPLETE;                                       // Set reception to incomplete

        process_buffer[pb_index] = IOT_Ring_Rx[iot_ring_rd++];                      // Store new char in process buffer

        if ((pb_index > 0) && (process_buffer[pb_index] == LF)                      // If pb_index > 0 and current char is LF
        && (process_buffer[pb_index - 1] == CR)){                                   // And previous char is CR
            reception_complete = COMPLETED;                                         // Set reception to completed
        }

        if (iot_ring_rd >= SMALL_RING_SIZE) iot_ring_rd = 0;                        // Wrap around ring buffer read index

        if (reception_complete == INCOMPLETE){                                      // If reception is incomplete
            pb_index++;                                                             // Increment pb_index
            if (pb_index >= PROCESS_BUFFER_SIZE){                                   // If pb_index is out of bounds
               strcpy(display_line[2], " OVERFLOW ");                               // Display OVERFLOW
               display_changed = TRUE;                                              // Display changed
           }
        }

        if (reception_complete == COMPLETED){                                       // If reception is completed

            unsigned int i;                                                         // Helper variable (looping)

            if (init_seq_state != END) Initial_Command_Checks();                    // If init_seq_state not at end do initial command checks
            else Store_Commands();                                                  // Otherwise store the command received

            // Reset variables and clear process buffer -------------------
            pb_index = 0;                                                           // Reset pb_idnex

            for (i = PROCESS_BUFFER_SIZE; i > 0; i--){                              // Loop through process buffer
                process_buffer[i - 1] = 0x00;                                       // Null out process buffer
            }
            //-------------------------------------------------------------
        }
    }
}
//------------------------------------------------------------------------------


// Store Commands ------------------------------------------------------------
void Store_Commands(void){
    unsigned int i = 0;                                                             // Helper variable (looping)
    unsigned int j;                                                                 // Helper variable (looping)
    while ((i < PROCESS_BUFFER_SIZE) && (process_buffer[i] != 0x00)){               // Loop through process buffer content
        if (process_buffer[i] == '^'){                                              // If '^' is found
            j = i;                                                                  // Set j to i
            while ((j < PROCESS_BUFFER_SIZE - 1)                                    // While j isn't at process buffer end
            && !(process_buffer[j] == CR && process_buffer[j+1] == LF)){            // And CR LF hasn't been found
                command_queue[command_num][j - i] = process_buffer[j];              // Store command character
                j++;                                                                // Increment j
            }
            command_queue[command_num][j - i] = CR;                                 // Append CR to command
            command_queue[command_num][j - i + 1] = LF;                             // Append LF to command
            command_num++;                                                          // Increment command number to store
            if (command_num >= NUM_COMMANDS) command_num = 0;                       // Wrap around command storing
        }
        i++;                                                                        // Increment i
    }
}
//------------------------------------------------------------------------------


// Run Commands ----------------------------------------------------------------
void Run_Commands(void){
    if ((ready_to_run_command == NO_RUNNING)                                        // If ready_to_run_command is NO_RUNNING
    && (command_queue[command_to_run][0] == '^')){                                  // And '^' is found (command starter)
        if ((command_queue[command_to_run][1] == '6')                               // Password check
        && (command_queue[command_to_run][2] == '6')                                // Password check
        && (command_queue[command_to_run][3] == '7')                                // Password check
        && (command_queue[command_to_run][4] == '9')){                              // Password check
            if (command_queue[command_to_run][5] == 'E'){                           // If command is 'E'
                follow_or_not = DONT_FOLLOW;                                        // Stop black line following
            }
        }

        // Clear current command & prepare to run next command --------
        unsigned int i;                                                             // Helper variable (looping)
        for (i = COMMAND_LENGTH; i > 0; i--){                                       // Loop through command
            command_queue[command_to_run][i - 1] = 0x00;                            // Null out command
        }
        command_to_run++;                                                           // Set next command to be run
        if (command_to_run >= NUM_COMMANDS) command_to_run = 0;                     // Loop around command to run
        //-------------------------------------------------------------
    }

    if (ready_to_run_command == NOT_READY){                                         // If ready_to_run_command is NOT_READY
        if (move_counter >= delay_time){                                            // If movement counter >= delay time
            All_Movement_Off();                                                     // Movement off
            if (move_counter >= delay_time + 25) ready_to_run_command = READY;      // 0.5s delay before running next command
        }
    }

    if ((ready_to_run_command == READY)                                             // If ready_to_run_command is READY
    && (command_queue[command_to_run][0] == '^')){                                  // And '^' is found (command starter)
        // Command Processing -----------------------------------------
        if ((command_queue[command_to_run][1] == '6')                               // Password Check
        && (command_queue[command_to_run][2] == '6')                                // Password Check
        && (command_queue[command_to_run][3] == '7')                                // Password Check
        && (command_queue[command_to_run][4] == '9')){                              // Password Check
            // Move forward
            if (command_queue[command_to_run][5] == 'F'){                           // If command is 'F'
                ready_to_run_command = NOT_READY;                                   // Set commands not ready to run
                strcpy(display_line[3], "F         ");                              // Display 'F'

                char to_convert[4];                                                 // Array for delay time characters
                unsigned int i;                                                     // Helper variable (looping)
                for (i = 4; i > 0; i--){                                            // Loop through delay time number
                    to_convert[i - 1] = command_queue[command_to_run][i + 5];       // Store delay time characters
                    display_line[3][i] = command_queue[command_to_run][i + 5];      // Display delay time characters
                }
                delay_time = CHARtoINT(to_convert);                                 // Convert delay time to unsigned integer

                display_changed = TRUE;                                             // Display changed

                move_counter = 0;                                                   // Reset move counter
                Forward_Fast();                                                     // Forward FAST
            }

            // Move backwards
            else if (command_queue[command_to_run][5] == 'B'){                      // If command is 'B'
                ready_to_run_command = NOT_READY;                                   // Set commands not ready to run
                strcpy(display_line[3], "B         ");                              // Display 'B'

                char to_convert[4];                                                 // Array for delay time characters
                unsigned int i;                                                     // Helper variable (looping)
                for (i = 4; i > 0; i--){                                            // Loop through delay time number
                    to_convert[i - 1] = command_queue[command_to_run][i + 5];       // Store delay time characters
                    display_line[3][i] = command_queue[command_to_run][i + 5];      // Display delay time characters
                }
                delay_time = CHARtoINT(to_convert);                                 // Convert delay time to unsigned integer

                display_changed = TRUE;                                             // Display changed

                move_counter = 0;                                                   // Reset move counter
                Reverse_Fast();                                                     // Reverse FAST
            }

            // Turn right
            else if (command_queue[command_to_run][5] == 'L'){                      // If command is 'L'
                ready_to_run_command = NOT_READY;                                   // Set commands not ready to run
                strcpy(display_line[3], "L         ");                              // Display 'L'

                char to_convert[4];                                                 // Array for delay time characters
                unsigned int i;                                                     // Helper variable (looping)
                for (i = 4; i > 0; i--){                                            // Loop through delay time number
                    to_convert[i - 1] = command_queue[command_to_run][i + 5];       // Store delay time characters
                    display_line[3][i] = command_queue[command_to_run][i + 5];      // Display delay time characters
                }
                delay_time = CHARtoINT(to_convert);                                 // Convert delay time to unsigned integer

                display_changed = TRUE;                                             // Display changed

                move_counter = 0;                                                   // Reset move counter
                Left_Slow();                                                        // Left SLOW
            }

            // Turn left
            else if (command_queue[command_to_run][5] == 'R'){                      // If command is 'R'
                ready_to_run_command = NOT_READY;                                   // Set commands ready to run
                strcpy(display_line[3], "R         ");                              // Display 'R'

                char to_convert[4];                                                 // Array for delay time characters
                unsigned int i;                                                     // Helper variable (looping)
                for (i = 4; i > 0; i--){                                            // Loop through delay time number
                    to_convert[i - 1] = command_queue[command_to_run][i + 5];       // Store delay time characters
                    display_line[3][i] = command_queue[command_to_run][i + 5];      // Display delay time characters
                }
                delay_time = CHARtoINT(to_convert);                                 // Convert delay time to unsigned integer

                display_changed = TRUE;                                             // Display changed

                move_counter = 0;                                                   // Reset move counter
                Right_Slow();                                                       // Right SLOW
            }

            // Start the autonomous black line following
            else if (command_queue[command_to_run][5] == 'D'){                      // If command is 'D'
                detect_state = PREPARE;                                             // Set detection state to PREPARE
                ready_to_run_command = NO_RUNNING;                                  // Set ready_to_run_command to NO_RUNNING
            }

            // Display the pad that was touched
            else if (command_queue[command_to_run][5] == 'N'){                      // If command is 'N'
                if (strncmp(display_line[0], "Arrived", 7) == 0){                   // If "Arrived" is on display line 1
                    strcpy(display_line[0], "          ");                          // Clear display line 1
                    display_changed = TRUE;                                         // Display changed
                    LCD_BACKLITE_DIMMING = OFF;                                     // LCD light OFF
                }
                else{
                    strcpy(display_line[0], "Arrived 0 ");                          // Display "Arrived 0"
                    display_line[0][9] = command_queue[command_to_run][6];          // Display the number sent by command
                    display_changed = TRUE;                                         // Display changed
                    LCD_BACKLITE_DIMMING = PERCENT_80;                              // LCD light ON
                }
            }
        }

        //-------------------------------------------------------------

        // Clear current command & prepare to run next command --------
        unsigned int i;                                                             // Helper variable (looping)
        for (i = COMMAND_LENGTH; i > 0; i--){                                       // Loop through command
            command_queue[command_to_run][i - 1] = 0x00;                            // Null out command
        }
        command_to_run++;                                                           // Set next command to be run
        if (command_to_run >= NUM_COMMANDS) command_to_run = 0;                     // Wrap around command to be run
        //-------------------------------------------------------------
    }
}
//------------------------------------------------------------------------------


// Convert character array to unsigned int -------------------------------------
unsigned int CHARtoINT(char c_array[4]){
    unsigned int return_value = 0;                                                  // Integer return value

    return_value += 1000 * ((int) (c_array[0] - '0'));                              // Add the thousands
    return_value += 100 * ((int) (c_array[1] - '0'));                               // Add the hundreds
    return_value += 10 * ((int) (c_array[2] - '0'));                                // Add the tens
    return_value += ((int) (c_array[3] - '0'));                                     // Add the ones
    return return_value;                                                            // Return the integer value
}
//------------------------------------------------------------------------------

