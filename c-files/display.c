//------------------------------------------------------------------------------
//  Description: This file contains the process to update/change the LCD display.
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


// Global Variables
extern volatile unsigned char display_changed;      // Display changed
extern volatile unsigned char update_display;       // Update display (every 200ms)


// Update Display and Indicate if Changed --------------------------------------
void Display_Process(void){
  if(update_display){               // If display to be updated
    update_display = 0;             // Set update_display to 0
    if(display_changed){            // If display has been changed
      display_changed = 0;          // Set display_changed to 0
      Display_Update(0,0,0,0);      // Update the display
    }
  }
}
//------------------------------------------------------------------------------
