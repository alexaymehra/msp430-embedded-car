//------------------------------------------------------------------------------
//  Description: This file contains for black & while calibration.
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
extern char display_line[4][11];                    // LCD display
extern char *display[4];                            // LCD display
extern volatile unsigned char display_changed;      // LCD display changed
extern volatile unsigned int calibrate_counter;     // Counter for calibration delay
unsigned int white_value;                           // Calibrated white value
unsigned int black_value;                           // Calibrated black value
extern volatile unsigned int ADC_Left_Detect;       // IR reading from physical left side


// Color calibration function --------------------------------------------------
void calibrate_color(const char color){
    if (color == WHITE){                            // If color is WHITE
        strcpy(display_line[0], "WHITE:    ");      // Display WHITE:
    }
    if (color == BLACK){                            // If color is BLACK
        strcpy(display_line[0], "BLACK:    ");      // Display BLACK:
    }
    display_changed = TRUE;                         // Display changed

    calibrate_counter = 0;                          // Reset calibrate counter
    while (calibrate_counter < 40);                 // Do nothing for 800ms

    if (color == WHITE){                            // If color is WHITE
        white_value = ADC_Left_Detect;              // Set IR reading to white value
        HEXtoBCD(white_value);                      // Convert white value to BCD
        adc_line(1, 6);                             // Display white value
    }
    if (color == BLACK){                            // If color is BLACK
        black_value = ADC_Left_Detect;              // Set IR reading to black value
        HEXtoBCD(black_value);                      // Convert black value to BCD
        adc_line(1,6);                              // Display black value
        black_value -= 10;                          // Subtract 10 to deal with noise
    }
}
//------------------------------------------------------------------------------

