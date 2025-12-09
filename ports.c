//------------------------------------------------------------------------------
//
//  Description: This file sets the default configurations of all port pins.
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


// Initialize All Ports --------------------------------------------------------
void Init_Ports(void){
    Init_Port1();               // Initialize port 1
    Init_Port2();               // Initialize port 2
    Init_Port3();               // Initialize port 3
    Init_Port4();               // Initialize port 4
    Init_Port5();               // Initialize port 5
    Init_Port6();               // Initialize port 6
}
//------------------------------------------------------------------------------


// Configure Port 1 ------------------------------------------------------------
void Init_Port1(void) {
    P1OUT = 0x00;               // P1 set Low
    P1DIR = 0x00;               // Set P1 direction to input

    P1SEL0 &= ~RED_LED;         // RED_LED GPIO operation
    P1SEL1 &= ~RED_LED;         // RED_LED GPIO operation
    P1OUT  &= ~RED_LED;         // Initial Value = Low / Off
    P1DIR  |=  RED_LED;         // Direction = output

    P1SEL0 &= ~A1_SEEED;        // A1_SEEED GPIO operation
    P1SEL1 &= ~A1_SEEED;        // A1_SEED GPIO operation
    P1OUT  &= ~A1_SEEED;        // Initial Value = Low / Off
    P1DIR  |=  A1_SEEED;        // Direction = output

    P1SELC |=  V_DETECT_L;      // ADC input for V_DETECT_L

    P1SELC |=  V_DETECT_R;      // ADC input for V_DETECT_R

    P1SEL0 &= ~A4_SEEED;        // A4_SEED GPIO operation
    P1SEL1 &= ~A4_SEEED;        // A4_SEED GPIO operation
    P1OUT  &= ~A4_SEEED;        // Initial Value = Low / Off
    P1DIR  |=  A4_SEEED;        // Direction = output

    P1SELC |=  V_THUMB;         // ADC input for V_THUMB

    P1SEL0 |=  UCA0RXD;         // UCA0RXD UART operation
    P1SEL1 &= ~UCA0RXD;         // UCA0RXD UART operation

    P1SEL0 |=  UCA0TXD;         // UCA0TXD UART operation
    P1SEL1 &= ~UCA0TXD;         // UCA0TXD UART operation
}
//------------------------------------------------------------------------------


// Configure Port 2 ------------------------------------------------------------
void Init_Port2(void) {
    P2OUT = 0x00;               // P2 set Low
    P2DIR = 0x00;               // Set P2 direction to output

    P2SEL0 &= ~SLOW_CLK;        // SLOW_CLK GPIO operation
    P2SEL1 &= ~SLOW_CLK;        // SLOW_CLK GPIO operation
    P2OUT  &= ~SLOW_CLK;        // Initial Value = Low / Off
    P2DIR  |=  SLOW_CLK;        // Direction = output

    P2SEL0 &= ~CHECK_BAT;       // CHECK_BAT GPIO operation
    P2SEL1 &= ~CHECK_BAT;       // CHECK_BAT GPIO operation
    P2OUT  &= ~CHECK_BAT;       // Initial Value = Low / Off
    P2DIR  |=  CHECK_BAT;       // Direction = output

    P2SEL0 &= ~IR_LED;          // IR_LED GPIO operation
    P2SEL1 &= ~IR_LED;          // IR_LED GPIO operation
    P2OUT  &= ~IR_LED;          // Initial Value = Low / Off
    P2DIR  |=  IR_LED;          // Direction = output

    P2SEL0 &= ~SW2;             // SW2 GPIO Operation
    P2SEL1 &= ~SW2;             // SW2 GPIO Operation
    P2PUPD |=  SW2;             // Configure pull-up resistor
    P2DIR  &= ~SW2;             // Direction = input
    P2REN  |=  SW2;             // Enable pull-up resistor
    P2IES  |=  SW2;             // SW2 Hi/Lo edge interrupt
    P2IFG  &= ~SW2;             // IFG SW2 cleared
    P2IE   |=  SW2;             // SW2 interrupt enabled

    P2SEL0 &= ~IOT_RUN_RED;     // IOT_RUN_RED GPIO operation
    P2SEL1 &= ~IOT_RUN_RED;     // IOT_RUN_RED GPIO operation
    P2OUT  &= ~IOT_RUN_RED;     // Initial Value = Low / Off
    P2DIR  |=  IOT_RUN_RED;     // Direction = output

    P2SEL0 &= ~DAC_ENB;         // DAC_ENB GPIO operation
    P2SEL1 &= ~DAC_ENB;         // DAC_ENB GPIO operation
    P2OUT  &= ~DAC_ENB;         // Initial Value = High
    P2DIR  |=  DAC_ENB;         // Direction = output

    P2SEL0 &= ~LFXOUT;          // LFXOUT Clock operation
    P2SEL1 |=  LFXOUT;          // LFXOUT Clock operation

    P2SEL0 &= ~LFXIN;           // LFXIN Clock operation
    P2SEL1 |=  LFXIN;           // LFXIN Clock operation
}
//------------------------------------------------------------------------------


// Configure Port 3 ------------------------------------------------------------
void Init_Port3(void) {
    P3OUT = 0x00;               // P3 set Low
    P3DIR = 0x00;               // Set P3 direction to output

    P3SEL0 &= ~TEST_PROBE;      // TEST_PROBE GPIO operation
    P3SEL1 &= ~TEST_PROBE;      // TEST_PROBE GPIO operation
    P3OUT  &= ~TEST_PROBE;      // Initial Value = Low / Off
    P3DIR  |=  TEST_PROBE;      // Direction = output

    P3SEL0 &= ~DAC_CNTL_2;      // DAC_CNTL_2 GPIO operation
    P3SEL1 &= ~DAC_CNTL_2;      // DAC_CNTL_2 GPIO operation
    P3OUT  &= ~DAC_CNTL_2;      // Initial Value = Low / Off
    P3DIR  |=  DAC_CNTL_2;      // Direction = output

    P3SEL0 &= ~OA2N;            // OA2N GPIO operation
    P3SEL1 &= ~OA2N;            // OA2N GPIO operation
    P3OUT  &= ~OA2N;            // Initial Value = Low / Off
    P3DIR  |=  OA2N;            // Direction = output

    P3SEL0 &= ~OA2P;            // OA2P GPIO operation
    P3SEL1 &= ~OA2P;            // OA2P GPIO operation
    P3OUT  &= ~OA2P;            // Initial Value = Low / Off
    P3DIR  |=  OA2P;            // Direction = output

    P3SEL0 &= ~SMCLK;           // SMCLK GPIO operation
    P3SEL1 &= ~SMCLK;           // SMCLK GPIO operation
    P3OUT  &= ~SMCLK;           // Initial Value = Low / Off
    P3DIR  |=  SMCLK;           // Direction = output

    P3SELC |=  DAC_CNTL_3;      // DAC_CNTL_3 DAC operation

    P3SEL0 &= ~IOT_LINK_GRN;    // IOT_LINK_GRN GPIO operation
    P3SEL1 &= ~IOT_LINK_GRN;    // IOT_LINK_GRN GPIO operation
    P3OUT  &= ~IOT_LINK_GRN;    // Initial Value = Low / Off
    P3DIR  |=  IOT_LINK_GRN;    // Direction = output

    P3SEL0 &= ~IOT_EN;          // IOT_EN GPIO operation
    P3SEL1 &= ~IOT_EN;          // IOT_EN GPIO operation
    P3OUT  &= ~IOT_EN;          // Initial Value = Low / Off
    P3DIR  |=  IOT_EN;          // Direction = output
}
//------------------------------------------------------------------------------


// Configure Port 4 ------------------------------------------------------------
void Init_Port4(void) {
    P4OUT = 0x00;               // P4 set Low
    P4DIR = 0x00;               // Set P4 direction to output

    P4SEL0 &= ~RESET_LCD;       // RESET_LCD GPIO operation
    P4SEL1 &= ~RESET_LCD;       // RESET_LCD GPIO operation
    P4OUT  &= ~RESET_LCD;       // Initial Value = Low / Off
    P4DIR  |=  RESET_LCD;       // Direction = output

    P4SEL0 &= ~SW1;             // SW1 GPIO operation
    P4SEL1 &= ~SW1;             // SW1 GPIO operation
    P4PUPD  |=  SW1;            // Configure pull-up resistor
    P4DIR  &= ~SW1;             // Direction = input
    P4REN  |=  SW1;             // Enable pull-up resistor
    P4IES  |=  SW1;             // SW1 Hi/Lo edge interrupt
    P4IFG  &= ~SW1;             // IFG SW1 cleared
    P4IE   |=  SW1;             // SW1 interrupt enabled

    P4SEL0 |= UCA1TXD;          // UCA1TXD UART operation
    P4SEL1 &= ~UCA1TXD;         // UCA1TXD UART operation

    P4SEL0 |= UCA1RXD;          // UCA1RXD UART operation
    P4SEL1 &= ~UCA1RXD;         // UCA1RXD UART operation

    P4SEL0 &= ~UCB1_CS_LCD;     // UCB1_CS_LCD GPIO operation
    P4SEL1 &= ~UCB1_CS_LCD;     // UCB1_CS_LCD GPIO operation
    P4OUT  |=  UCB1_CS_LCD;     // Set SPI_CS_LCD off [High]
    P4DIR  |=  UCB1_CS_LCD;     // Set SPI_CS_LCD direction to output

    P4SEL0 |= UCB1CLK;          // UCB1CLK SPI BUS operation
    P4SEL1 &= ~UCB1CLK;         // UCB1CLK SPI BUS operation

    P4SEL0 |= UCB1SIMO;         // UCB1SIMO SPI BUS operation
    P4SEL1 &= ~UCB1SIMO;        // UCB1SIMO SPI BUS operation

    P4SEL0 |= UCB1SOMI;         // UCB1SOMI SPI BUS operation
    P4SEL1 &= ~UCB1SOMI;        // UCB1SOMI SPI BUS operation
}
//------------------------------------------------------------------------------


// Configure Port 5 ------------------------------------------------------------
void Init_Port5(void) {
    P5OUT = 0x00;               // P5 set Low
    P5DIR = 0x00;               // Set P5 direction to output

    P5SEL0 &= ~V_BAT;           // V_BAT GPIO operation
    P5SEL1 &= ~V_BAT;           // V_BAT GPIO operation
    P5OUT  &= ~V_BAT;           // Initial Value = Low / Off
    P5DIR  |=  V_BAT;           // Direction = output

    P5SEL0 &= ~V_5_0;           // V_5_0 GPIO operation
    P5SEL1 &= ~V_5_0;           // V_5_0 GPIO operation
    P5OUT  &= ~V_5_0;           // Initial Value = Low / Off
    P5DIR  |=  V_5_0;           // Direction = output

    P5SEL0 &= ~V_DAC;           // V_DAC GPIO operation
    P5SEL1 &= ~V_DAC;           // V_DAC GPIO operation
    P5OUT  &= ~V_DAC;           // Initial Value = Low / Off
    P5DIR  |=  V_DAC;           // Direction = output

    P5SEL0 &= ~V_3_3;           // V_3_3 GPIO operation
    P5SEL1 &= ~V_3_3;           // V_3_3 GPIO operation
    P5OUT  &= ~V_3_3;           // Initial Value = Low / Off
    P5DIR  |=  V_3_3;           // Direction = output

    P5SEL0 &= ~IOT_BOOT_CPU;    // IOT_BOOT_CPU GPIO operation
    P5SEL1 &= ~IOT_BOOT_CPU;    // IOT_BOOT_CPU GPIO operation
    P5OUT  |=  IOT_BOOT_CPU;    // Initial Value = Low / Off
    P5DIR  |=  IOT_BOOT_CPU;    // Direction = output
}
//------------------------------------------------------------------------------


// Configure Port 6 ------------------------------------------------------------
void Init_Port6(void) {
    P6OUT = 0x00;               // P6 set Low
    P6DIR = 0x00;               // Set P6 direction to output

    P6SEL0 |=  L_FORWARD;       // L_FORWARD TB3 operation
    P6SEL1 &= ~L_FORWARD;       // L_FORWARD TB3 operation
    P6DIR  |=  L_FORWARD;       // Direction = output

    P6SEL0 |=  R_FORWARD;       // R_FORWARD TB3 operation
    P6SEL1 &= ~R_FORWARD;       // R_FORWARD GPIO operation
    P6DIR  |=  R_FORWARD;       // Direction = output

    P6SEL0 |=  L_REVERSE;       // L_REVERSE TB3 operation
    P6SEL1 &= ~L_REVERSE;       // L_REVERSE TB3 operation
    P6DIR  |=  L_REVERSE;       // Direction = output

    P6SEL0 |=  R_REVERSE;       // R_REVERSE TB3 operation
    P6SEL1 &= ~R_REVERSE;       // R_REVERSE TB3 operation
    P6DIR  |=  R_REVERSE;       // Direction = output

    P6SEL0 |=  LCD_BACKLITE ;   // LCD_BACKLITE TB3 operation
    P6SEL1 &= ~LCD_BACKLITE ;   // LCD_BACKLITE TB3 operation
    P6DIR  |=  LCD_BACKLITE ;   // Direction = output

    P6SEL0 &= ~P6_5;            // P6_5 GPIO operation
    P6SEL1 &= ~P6_5;            // P6_5 GPIO operation
    P6OUT  &= ~P6_5;            // Initial Value = Low / Off
    P6DIR  |=  P6_5;            // Direction = output

    P6SEL0 &= ~GRN_LED;         // GRN_LED GPIO operation
    P6SEL1 &= ~GRN_LED;         // GRN_LED GPIO operation
    P6OUT  &= ~GRN_LED;         // Initial Value = Low / Off
    P6DIR  |=  GRN_LED;         // Direction = output
}
//------------------------------------------------------------------------------
