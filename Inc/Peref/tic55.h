#ifndef _TICC55_H_
#define _TICC55_H_

void tic_control_off();
void tic_control_on();
void tic_set_char(unsigned char Data, unsigned char Pos, char dot, char set); 
void tic_print_num (unsigned int Num, unsigned char Pos, char dot, char set);
void tic_clear(void);
void tic_send(void);
void tic_print_char(unsigned char Char, unsigned char Pos, char dot, char set);
void tic_print_symbol(int Data, unsigned char Pos);
void tic_print_numful (unsigned int Num, unsigned char Pos);

void tic_print_time (void);
void tic_print_date (RTC_DateTypeDef *);

extern unsigned int code[];

#endif