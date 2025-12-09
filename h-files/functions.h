//------------------------------------------------------------------------------
//  Description: This file contains the function prototypes.
//
//  Alexay Mehra
//  Oct 2025
//  Built with Code Composer Studio 12.8.1
//------------------------------------------------------------------------------


// Main ------------------------------------------------------------------------
void main(void);
//------------------------------------------------------------------------------


// Initialization --------------------------------------------------------------
void Init_Conditions(void);
void Init_Vars(void);
//------------------------------------------------------------------------------


// Interrupts ------------------------------------------------------------------
void enable_interrupts(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void switch_interrupt(void);
//------------------------------------------------------------------------------


// Analog to Digital Converter -------------------------------------------------
void Init_ADC(void);
void HEXtoBCD(unsigned int hex_value);
void adc_line(char line, char location);

void disp_bat(unsigned int raw_value);
//------------------------------------------------------------------------------


// Clocks ----------------------------------------------------------------------
void Init_Clocks(void);
//------------------------------------------------------------------------------


// LED Configurations ----------------------------------------------------------
void Init_LEDs(void);
void IR_LED_control(char selection);
void Backlite_control(char selection);
//------------------------------------------------------------------------------


// LCD -------------------------------------------------------------------------
void Display_Process(void);
void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4);
void enable_display_update(void);
void update_string(char *string_data, int string);
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);

void lcd_power_on(void);
void lcd_write_line1(void);
void lcd_write_line2(void);
//void lcd_draw_time_page(void);
//void lcd_power_off(void);
void lcd_enter_sleep(void);
void lcd_exit_sleep(void);
//void lcd_write(unsigned char c);
//void out_lcd(unsigned char c);

void Write_LCD_Ins(char instruction);
void Write_LCD_Data(char data);
void ClrDisplay(void);
void ClrDisplay_Buffer_0(void);
void ClrDisplay_Buffer_1(void);
void ClrDisplay_Buffer_2(void);
void ClrDisplay_Buffer_3(void);

void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_BIG_bot(void);
void lcd_120(void);

void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void lcd_rotate(char view);

//void lcd_write(char data, char command);
void lcd_write(unsigned char c);
void lcd_write_line1(void);
void lcd_write_line2(void);
void lcd_write_line3(void);

void lcd_command( char data);
void LCD_test(void);
void LCD_iot_meassage_print(int nema_index);
//------------------------------------------------------------------------------


// Menu ------------------------------------------------------------------------
//void Menu_Process(void);
//------------------------------------------------------------------------------


// Ports -----------------------------------------------------------------------
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);
//------------------------------------------------------------------------------


// SPI -------------------------------------------------------------------------
void Init_SPI_B1(void);
void SPI_B1_write(char byte);
void spi_rs_data(void);
void spi_rs_command(void);
void spi_LCD_idle(void);
void spi_LCD_active(void);
void SPI_test(void);
void WriteIns(char instruction);
void WriteData(char data);
//------------------------------------------------------------------------------


// Switches --------------------------------------------------------------------
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);
void Init_Switch(void);
void Switch_Process(void);
void Switch1_Process(void);
void Switch2_Process(void);
//void menu_act(void);
//void menu_select(void);
//------------------------------------------------------------------------------


// Timers ----------------------------------------------------------------------
void Init_Timers(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void Init_Timer_B3(void);

void usleep(unsigned int usec);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int msec);
void measure_delay(void);
void out_control_words(void);
//------------------------------------------------------------------------------


// Movement --------------------------------------------------------------------
void All_Movement_Off(void);
void Check_Rev_Fwd(void);

void Forward_Slow(void);
void Forward_Med(void);
void Forward_Fast(void);

void Reverse_Fast(void);

void Right_Slow(void);

void Left_Slow(void);
//------------------------------------------------------------------------------


// Black line detection & following --------------------------------------------
void calibrate_color(const char color);

void black_line_machine(void);
void prepare_case(void);
void run_case(void);
void stop_case(void);

void white_detect_case(void);
void delay_case_1(void);
void delay_case_2(void);
void turn_case(void);

void line_follow_machine(void);
void follow_prepare_case(void);
void follow_run_case(void);
void follow_stop_case(void);

void follow_delay_case_1(void);
void follow_delay_case_2(void);
//------------------------------------------------------------------------------


// UART / IOT ------------------------------------------------------------------
void Init_UART(char speed);
void Init_Serial_UCA0(char speed);
void Init_Serial_UCA1(char speed);

void USCI_A0_Transmit(void);

void IOT_Receive(void);

void Initial_Command_Sequence(void);
void Initial_Command_Checks(void);

void Store_Commands(void);
void Run_Commands(void);

unsigned int CHARtoINT(char c_array[4]);
//------------------------------------------------------------------------------


// DAC -------------------------------------------------------------------------
void Init_DAC(void);
//------------------------------------------------------------------------------

