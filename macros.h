//------------------------------------------------------------------------------
//  Description: This file gives symbolic names to values.
//
//  Alexay Mehra
//  Sep 2025
//  Built with Code Composer Studio 12.8.1
//------------------------------------------------------------------------------


// MISC =========================================================================
#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define TRUE                    (0x01)
#define FALSE                   (0x00)
#define P4PUPD                  (P4OUT)
#define P2PUPD                  (P2OUT)
// ==============================================================================


// TIMERS =======================================================================
#define TIMER_B0_CCR0_VECTOR        TIMER0_B0_VECTOR
#define TIMER_B0_CCR1_2_OV_VECTOR   TIMER0_B1_VECTOR

#define TIMER_B1_CCR0_VECTOR        TIMER1_B0_VECTOR
#define TIMER_B1_CCR1_2_OV_VECTOR   TIMER1_B1_VECTOR

#define TIMER_B2_CCR0_VECTOR        TIMER2_B0_VECTOR
#define TIMER_B2_CCR1_2_OV_VECTOR   TIMER2_B1_VECTOR

#define TIMER_B3_CCR0_VECTOR        TIMER3_B0_VECTOR
#define TIMER_B3_CCR1_2_OV_VECTOR   TIMER3_B1_VECTOR

#define TB0CCR0_INTERVAL        (2500)      // 8,000,000 / 8 / 8 / (1 / 20msec)
#define TB0CCR1_INTERVAL        (31250)     // 8,000,000 / 8 / 8 / (1 / 250msec)
#define TB0CCR2_INTERVAL        (31250)     // 8,000,000 / 8 / 8 / (1 / 250msec)
// ==============================================================================


// PWM ==========================================================================
#define PWM_PERIOD              (TB3CCR0)
#define LEFT_FORWARD_SPEED      (TB3CCR1)
#define RIGHT_FORWARD_SPEED     (TB3CCR2)
#define LEFT_REVERSE_SPEED      (TB3CCR3)
#define RIGHT_REVERSE_SPEED     (TB3CCR4)
#define LCD_BACKLITE_DIMMING    (TB3CCR5)

#define WHEEL_PERIOD            (50005)
#define WHEEL_OFF               (0)
#define RIGHT_SLOW              (29005)
#define LEFT_SLOW               (25005)
#define RIGHT_MED               (39005)
#define LEFT_MED                (35005)
#define RIGHT_FAST              (50000)
#define LEFT_FAST               (46000)

#define PERCENT_100             (50000)
#define PERCENT_80              (45000)
#define OFF                     (0)
// ==============================================================================


// Movement State Machine =======================================================
#define IDLE                    ('I')
#define PREPARE                 ('P')
#define RUN                     ('R')
#define STOP                    ('S')

#define WHITE_DETECT            ('W')
#define DELAY1                  ('1')
#define DELAY2                  ('2')
#define TURN                    ('T')
// ==============================================================================


// Black Line Detection & Following =============================================
#define BLACK                   ('B')
#define WHITE                   ('W')
#define NOCOLOR                 ('N')

#define FORWARD                 ('F')
#define TURN_LEFT               ('L')
#define TURN_RIGHT              ('R')

#define FOLLOW                  (0x01)
#define DONT_FOLLOW             (0x00)
// ==============================================================================


// Serial Communication =========================================================
#define SMALL_RING_SIZE         (20)
#define PROCESS_BUFFER_SIZE     (70)
#define TRANSMIT_BUFFER_SIZE    (25)

#define BUFFER1                 ('O')
#define BUFFER2                 ('T')

#define SPEED_115200            ('S')
#define SPEED_460800            ('F')

#define CR                      (0x0D)
#define LF                      (0x0A)

#define COMPLETED               (0x01)
#define INCOMPLETE              (0x00)

#define VALID                   (0x01)
#define INVALID                 (0x00)

#define CAN_EXECUTE             (0x01)
#define DONT_EXECUTE            (0x00)

#define READY                   (0x01)
#define NOT_READY               (0x00)
#define NO_RUNNING              (0x02)

#define WAITING                 ('W')
#define ATSYSSTORE0             ('A')
#define ATCIPMUX1               ('B')
#define ATCIPSERVER1            ('C')
#define ATCIFSR                 ('D')
#define END                     ('E')

#define NUM_COMMANDS            (4)
#define COMMAND_LENGTH          (15)
// ==============================================================================


// DAC ==========================================================================
#define DAC_Begin               (2725)  // 2.00 V
#define DAC_Limit               (1500)  // 4.02 V
#define DAC_Adjust              (1505)  // 4.00 V
// ==============================================================================

