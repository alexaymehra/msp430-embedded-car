//------------------------------------------------------------------------------
//  Description: This file contains the initial command sequence functions.
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
extern char init_seq_state;                             // Variable for initial commands state machine
extern char can_exec_command;                           // Indicate if commands can be executed

volatile char transmit_buffer[TRANSMIT_BUFFER_SIZE];    // Buffer for transmission

extern char process_buffer[PROCESS_BUFFER_SIZE];        // Buffer for processing incoming data

extern char display_line[4][11];                        // LCD display
extern char *display[4];                                // LCD display
extern volatile unsigned char display_changed;          // LCD display changed

extern volatile unsigned int ping_counter;              // Counter for pinging google


// Initial Command Sequence ----------------------------------------------------
void Initial_Command_Sequence(void){
    switch (init_seq_state){                                    // Initial command state machine
        case ATSYSSTORE0:                                       // ATSYSSTORE0:
            if (can_exec_command == CAN_EXECUTE){               // If commands can be executed
                unsigned int i;                                 // Helper variable (looping)
                char command[15] = "AT+SYSSTORE=0\r\n";         // Store command to be sent
                for (i = 15; i > 0; i--){                       // Loop through the command
                    transmit_buffer[i - 1] = command[i - 1];    // Put command in transmit buffer
                }
                can_exec_command = DONT_EXECUTE;                // Commands cannot be executed
                USCI_A0_Transmit();                             // Transmit the command
            }
            break;
        case ATCIPMUX1:                                         // ATCIPMUX1:
            if (can_exec_command == CAN_EXECUTE){               // If commands can be executed
                unsigned int i;                                 // Helper variable (looping)
                char command[13] = "AT+CIPMUX=1\r\n";           // Store command to be sent
                for (i = 13; i > 0; i--){                       // Loop through the command
                    transmit_buffer[i - 1] = command[i - 1];    // Put command in transmit buffer
                }
                can_exec_command = DONT_EXECUTE;                // Commands cannot be executed
                USCI_A0_Transmit();                             // Transmit the command
            }
            break;
        case ATCIPSERVER1:                                      // ATCIPSERVER1:
            if (can_exec_command == CAN_EXECUTE){               // If commands can be executed
                unsigned int i;                                 // Helper variable (looping)
                char command[21] = "AT+CIPSERVER=1,3067\r\n";   // Store command to be sent
                for (i = 21; i > 0; i--){                       // Loop through the command
                    transmit_buffer[i - 1] = command[i - 1];    // Put command in transmit buffer
                }
                can_exec_command = DONT_EXECUTE;                // Commands cannot be executed
                USCI_A0_Transmit();                             // Transmit the command
            }
            break;
        case ATCIFSR:                                           // ATCIFSR:
            if (can_exec_command == CAN_EXECUTE){               // If commands can be executed
                unsigned int i;                                 // Helper variable (looping)
                char command[10] = "AT+CIFSR\r\n";              // Store command to be sent
                for (i = 10; i > 0; i--){                       // Loop through the command
                    transmit_buffer[i - 1] = command[i - 1];    // Put command in transmit buffer
                }
                can_exec_command = DONT_EXECUTE;                // Commands cannot be executed
                USCI_A0_Transmit();                             // Transmit the command
            }
            break;
        case END:                                               // END:
            if (ping_counter >= 250){                           // Execute every 5s
                ping_counter = 0;                               // Reset ping counter
                unsigned int i;                                 // Helper variable (looping)
                char command[19] = "AT+PING=\"8.8.8.8\"\r\n";   // Store command to be sent
                for (i = 19; i > 0; i--){                       // Loop through the command
                    transmit_buffer[i - 1] = command[i - 1];    // Put command in transmit buffer
                }
                USCI_A0_Transmit();                             // Transmit the command
            }
            break;
        default: break;                                         // DEFAULT: do nothing
    }
}
//------------------------------------------------------------------------------


// Initial Command Checks ------------------------------------------------------
void Initial_Command_Checks(void){

    unsigned int i;                                                                         // Helper variable

    // Checks in initial command sequence -------------------------
    switch (init_seq_state){                                                                // Initial command check state machine
        case WAITING:                                                                       // WAITING:
            i = 0;                                                                          // Set i = 0
            while ((i < PROCESS_BUFFER_SIZE) && (process_buffer[i] != 'G')) i++;            // Look for the index of 'G'
            if (i < PROCESS_BUFFER_SIZE - 2){                                               // Prevent out of bounds checking
                if ((process_buffer[i+1] == 'O')                                            // If index + 1 is 'O'
                && (process_buffer[i+2] == 'T')){                                           // If index + 2 is 'T'
                    init_seq_state = ATSYSSTORE0;                                           // Set init_seq_state to ATSYSSTORE0
                    can_exec_command = CAN_EXECUTE;                                         // Commands can be executed
                }
            }
            break;

        case ATSYSSTORE0:                                                                   // ATSYSSTORE0:
            i = 0;                                                                          // Set i = 0
            while ((i < PROCESS_BUFFER_SIZE) && (process_buffer[i] != 'O')) i++;            // Look for the index of 'O'
            if (i < PROCESS_BUFFER_SIZE - 1){                                               // Prevent out of bounds checking
                if (process_buffer[i+1] == 'K'){                                            // If index + 1 is 'K'
                    init_seq_state = ATCIPMUX1;                                             // Set init_seq_state to ATCIPMUX1
                    can_exec_command = CAN_EXECUTE;                                         // Commands can be executed
                }
            }
            break;

        case ATCIPMUX1:                                                                     // ATCIPMUX1:
            i = 0;                                                                          // Set i = 0
            while ((i < PROCESS_BUFFER_SIZE) && (process_buffer[i] != 'O')) i++;            // Look for the index of 'O'
            if (i < PROCESS_BUFFER_SIZE - 1){                                               // Prevent out of bounds checking
                if (process_buffer[i+1] == 'K'){                                            // If index + 1 is 'K'
                    init_seq_state = ATCIPSERVER1;                                          // Set init_seq_state to ATCIPSERVER1
                    can_exec_command = CAN_EXECUTE;                                         // Commands can be executed
                }
            }
            break;

        case ATCIPSERVER1:                                                                  // ATCIPSERVER1:
            i = 0;                                                                          // Set i = 0
            while ((i < PROCESS_BUFFER_SIZE) && (process_buffer[i] != 'O')) i++;            // Look for the index of 'O'
            if (i < PROCESS_BUFFER_SIZE - 1){                                               // Prevent out of bounds checking
                if (process_buffer[i+1] == 'K'){                                            // If index + 1 is 'K'
                    init_seq_state = ATCIFSR;                                               // Set init_seq_state to ATCIFSR
                    can_exec_command = CAN_EXECUTE;                                         // Commands can be executed
                }
            }
            break;

        case ATCIFSR: {                                                                     // ATCIFSR:
            unsigned int start_index;                                                       // Helper variable (indexing)
            unsigned int end_index;                                                         // Helper variable (indexing)
            unsigned int length;                                                            // Helper variable (looping)
            unsigned int j;                                                                 // Helper variable (looping)
            unsigned int k;                                                                 // Helper variable (indexing)

            k = 0;                                                                          // Set k = 0
            j = 0;                                                                          // Set j = 0
            while ((k < PROCESS_BUFFER_SIZE) && (process_buffer[k] != '"')) k++;            // Find index of '"'

            if (k < PROCESS_BUFFER_SIZE - 1){                                               // If k is not at the end of process buffer
                start_index = k + 1;                                                        // Start of IP address is k + 1

                k = start_index;                                                            // Set k to start index
                while ((k < PROCESS_BUFFER_SIZE) && (process_buffer[k] != '"')) k++;        // Find index of second '"'

                if (k < PROCESS_BUFFER_SIZE){                                               // If second '"' found
                    end_index = k - 1;                                                      // End of IP address is k - 1
                    if (start_index <= end_index){                                          // If start index is <= end index
                        length = end_index - start_index + 1;                               // Length of IP address
                        if (length > 20) length = 20;                                       // Limit IP address length
                        char ip_address[20] = {0};                                          // Character array to hold IP address
                        for (j = 0; j < length; j++){                                       // Loop through IP address found
                            ip_address[j] = process_buffer[start_index + j];                // Store IP address in ip_address array
                        }
                        for (j = 0; j < 6; j++) display_line[2][j+2] = ip_address[j];       // Display first 6 IP chars on line 3
                        for (j = 6; j < length; j++) display_line[3][j-4] = ip_address[j];  // Display the rest of the IP chars on line 4
                        display_changed = TRUE;                                             // Display changed
                        init_seq_state = END;                                               // Set init_seq_state to END
                        can_exec_command = CAN_EXECUTE;                                     // Commands can be executed
                    }
                }
            }
            break;
        }
        default: break;                                                                     // DEFAULT: do nothing
    }
    //-------------------------------------------------------------
}
//------------------------------------------------------------------------------
