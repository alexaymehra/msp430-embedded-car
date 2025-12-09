//------------------------------------------------------------------------------
//
//  Description: This file contains the System Configurations
//
//  Jim Carlson
//  Jan 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------


// Includes
#include  "msp430.h"
#include  <string.h>
#include  "functions.h"
#include  "LCD.h"
#include  "macros.h"
#include  "ports.h"


// Globals
volatile char slow_input_down;
extern char display_line[4][11];
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;

unsigned int wheel_move;
char forward;


//------------------------------------------------------------------------------
// System Configurations -------------------------------------------------------

// Tells the compiler to provide the value in reg as an input to an
// inline assembly block.  Even though the block contains no instructions,
// the compiler may not optimize it away, and is told that the value
// may change and should not be relied upon.

//inline void READ_AND_DISCARD(unsigned int reg) __attribute__((always_inline));
//void READ_AND_DISCARD(unsigned int reg){
//  asm volatile ("" : "=m" (reg) : "r" (reg));
//}

//inline void enable_interrupts(void) __attribute__((always_inline));
void enable_interrupts(void){
  __bis_SR_register(GIE);     // enable interrupts
//  asm volatile ("eint \n");
}

//inline void disable_interrupts(void) __attribute__((always_inline));
//void disable_interrupts(void){
//  asm volatile ("dint \n");
//}
