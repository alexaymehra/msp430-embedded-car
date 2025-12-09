//------------------------------------------------------------------------------
//  Description: This file contains the UART interrupts.
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
extern volatile char IOT_Ring_Rx[SMALL_RING_SIZE];              // IOT ring buffer
extern volatile unsigned int iot_ring_wr;                       // IOT ring buffer write index

volatile char transmit_buffer[TRANSMIT_BUFFER_SIZE];            // Transmit buffer
volatile unsigned int transmit_index;                           // Transmit buffer index


// eUSCI_A1 interrupt ----------------------------------------------------------
#pragma vector = EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){

    char usb_value;                                             // Hold char from PC

    switch(__even_in_range(UCA1IV, 0x08)){
        case 0:                                                 // No interrupt
            break;
        case 2:                                                 // RXIFG (receiving)
            usb_value = UCA1RXBUF;                              // Store received char
            UCA0TXBUF = usb_value;                              // Send received char to IOT
            break;
        case 4:                                                 // TXIFG (transmission)
            break;
        default: break;                                         // DEFAULT: do nothing
    }
}
//------------------------------------------------------------------------------


// eUSCI_A0 interrupt ----------------------------------------------------------
#pragma vector = EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){

    char iot_value;                                                 // Hold char from IOT

    switch(__even_in_range(UCA0IV, 0x08)){
        case 0:                                                     // No interrupt
            break;

        case 2:                                                     // RXIFG (receiving)
            iot_value = UCA0RXBUF;                                  // Store received char
            UCA1TXBUF = iot_value;                                  // Send received char to PC
            IOT_Ring_Rx[iot_ring_wr++] = iot_value;                 // Store received char in ring buffer
            if (iot_ring_wr >= SMALL_RING_SIZE) iot_ring_wr = 0;    // Wrap around ring buffer write index
            break;

        case 4:                                                     // TXIFG (transmission)
            UCA0TXBUF = transmit_buffer[transmit_index];            // Transmit char in transmit buffer
            if ((transmit_index > 0) &&                             // If transmit_index > 0
            (transmit_buffer[transmit_index] == LF) &&              // And char transmitted was LF
            (transmit_buffer[transmit_index - 1] == CR)){           // And previous char was CR
                UCA0IE &= ~UCTXIE;                                  // Disable TX interrupt
            }
            else{                                                   // If not at end of message
                transmit_index++;                                   // Increment transmit index
            }
            break;

        default: break;                                             // DEFAULT: do nothing
    }
}
//------------------------------------------------------------------------------


