//------------------------------------------------------------------------------
//  Description: This file contains the UART configuration and basic functions.
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
volatile char IOT_Ring_Rx[SMALL_RING_SIZE];                     // IOT ring buffer
volatile unsigned int iot_ring_wr;                              // IOT ring buffer write index
unsigned int iot_ring_rd;                                       // IOT ring buffer read index

char process_buffer[PROCESS_BUFFER_SIZE];                       // Process buffer
unsigned int pb_index;                                          // Process buffer index

extern volatile char transmit_buffer[TRANSMIT_BUFFER_SIZE];     // Transmit buffer
volatile unsigned int transmit_index;                           // Transmit buffer index

extern char command_queue[NUM_COMMANDS][COMMAND_LENGTH];        // Command queue
extern unsigned int command_num;                                // Command index for storing
extern unsigned int command_to_run;                             // Command index for running
extern char ready_to_run_command;                               // Indicate if commands can be run


//                                                          TX error    RX error
//  BRCLK       Baudrate    UCOS16  UCBRx   UCFx    UCSx    neg   pos   neg  pos
//  8000000     4800        1       104     2       0xD6    -0.08 0.04  -0.10 0.14
//  8000000     9600        1       52      1       0x49    -0.08 0.04  -0.10 0.14
//  8000000     19200       1       26      0       0xB6    -0.08 0.16  -0.28 0.20
//  8000000     57600       1       8       10      0xF7    -0.32 0.32  -1.00 0.36
//  8000000     115200      1       4       5       0x55    -0.80 0.64  -1.12 1.76
//  8000000     460800      0       17      0       0x4A    -2.72 2.56  -3.76 7.28


// UART main configuration function --------------------------------------------
void Init_UART(char speed){
    Init_Serial_UCA0(speed);                        // Initialize UCA0
    Init_Serial_UCA1(speed);                        // Initialize UCA1

    iot_ring_wr = 0;                                // Reset iot_ring_wr
    iot_ring_rd = 0;                                // Reset iot_ring_rd
    pb_index = 0;                                   // Reset pb_index

    command_num = 0;                                // Reset command number
    command_to_run = 0;                             // Rest command to run
    ready_to_run_command = READY;                   // Ready to run commands

    unsigned int i;                                 // Helper variable (looping)
    for (i = PROCESS_BUFFER_SIZE; i > 0; i--){      // Loop through process buffer
        process_buffer[i - 1] = 0x00;               // Null out process buffer
    }

    for (i = TRANSMIT_BUFFER_SIZE; i > 0; i--){     // Loop through transmit buffer
        transmit_buffer[i - 1] = 0x00;              // Null out transmit buffer
    }

    unsigned int j;                                 // Helper variable (looping)
    for (i = NUM_COMMANDS; i > 0; i--){             // Loop through the queue
        for (j = COMMAND_LENGTH; j > 0; j--){       // Loop through the commands
            command_queue[i - 1][j - 1] = 0x00;     // Null out command queue
        }
    }
}
//------------------------------------------------------------------------------


// eUSCI_A0 configuration ------------------------------------------------------
void Init_Serial_UCA0(char speed){
    UCA0CTLW0 = 0;                          // Clear
    UCA0CTLW0 |=  UCSWRST;                  // Put eUSCI in reset
    UCA0CTLW0 |=  UCSSEL__SMCLK;            // Set SMCLK as fBRCLK
    UCA0CTLW0 &= ~UCMSB;                    // LSB first in data
    UCA0CTLW0 &= ~UCSPB;                    // Choose only 1 stop bit
    UCA0CTLW0 &= ~UCPEN;                    // No parity
    UCA0CTLW0 &= ~UCSYNC;                   // Select UART mode
    UCA0CTLW0 &= ~UC7BIT;                   // 8 bits of data
    UCA0CTLW0 |=  UCMODE_0;                 // Select UART operational mode

    if (speed == SPEED_115200){             // If speed is to be 115,200 baud
        UCA0BRW = 4;                        // 115,200 baud
        UCA0MCTLW = 0x5551;                 // 115,200 baud
    }
    else{                                   // If speed is to be 460,800 baud
        UCA0BRW = 17;                       // 460,800 baud
        UCA0MCTLW = 0x4A00;                 // 460,800 baud
    }

    UCA0CTLW0 &= ~UCSWRST;                  // release from reset
    UCA0TXBUF = 0x00;                       // Prime the Pump ("wake up" the UART transmit hardware)
    UCA0IE |= UCRXIE;                       // Enable RX interrupt
}
//------------------------------------------------------------------------------


// eUSCI_A1 configuration ------------------------------------------------------
void Init_Serial_UCA1(char speed){
    UCA1CTLW0 = 0;                          // Clear
    UCA1CTLW0 |=  UCSWRST;                  // Put eUSCI in reset
    UCA1CTLW0 |=  UCSSEL__SMCLK;            // Set SMCLK as fBRCLK
    UCA1CTLW0 &= ~UCMSB;                    // LSB first in data
    UCA1CTLW0 &= ~UCSPB;                    // Choose only 1 stop bit
    UCA1CTLW0 &= ~UCPEN;                    // No parity
    UCA1CTLW0 &= ~UCSYNC;                   // Select UART mode
    UCA1CTLW0 &= ~UC7BIT;                   // 8 bits of data
    UCA1CTLW0 |=  UCMODE_0;                 // Select UART operational mode

    if (speed == SPEED_115200){             // If speed is to be 115,200 baud
        UCA1BRW = 4;                        // 115,200 baud
        UCA1MCTLW = 0x5551;                 // 115,200 baud
    }
    else{                                   // If speed is to be 460,800 baud
        UCA1BRW = 17;                       // 460,800 baud
        UCA1MCTLW = 0x4A00;                 // 460,800 baud
    }

    UCA1CTLW0 &= ~UCSWRST;                  // release from reset
    UCA1TXBUF = 0x00;                       // Prime the Pump ("wake up" the UART transmit hardware)
    UCA1IE |=  UCRXIE;                      // Enable RX interrupt
}
//------------------------------------------------------------------------------


// Transmit out A0 -------------------------------------------------------------
void USCI_A0_Transmit(void){
    transmit_index = 0;                     // Reset transmit index
    UCA0IE |= UCTXIE;                       // Enable UCA0 TX interrupt
}
//------------------------------------------------------------------------------
