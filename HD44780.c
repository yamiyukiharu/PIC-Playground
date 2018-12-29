#include <xc.h>
#include "HD44780.h"

#define DELAY_MULTIPLIER 2

void write_mode_on();
void read_mode_on();
void select_instruction_register();
void select_data_register();
void enable_pulse();

void HD44780_init() {
    __delay_ms(16*DELAY_MULTIPLIER);
    digitalWrite_DB7(LOW);
    digitalWrite_DB6(LOW);
    digitalWrite_DB5(HIGH);
    digitalWrite_DB4(HIGH);
    select_instruction_register();
    write_mode_on();
    __delay_us(1*DELAY_MULTIPLIER);
    enable_pulse();
    __delay_ms(5*DELAY_MULTIPLIER);
    enable_pulse();
    __delay_us(110*DELAY_MULTIPLIER);
    enable_pulse();
    
    __delay_us(40*DELAY_MULTIPLIER);
    //set 4 bit interface
    digitalWrite_DB7(LOW);
    digitalWrite_DB6(LOW);
    digitalWrite_DB5(HIGH);
    digitalWrite_DB4(LOW);
    enable_pulse();
    __delay_us(40*DELAY_MULTIPLIER);
    
    //specify display lines & font
    digitalWrite_DB7(LOW);
    digitalWrite_DB6(LOW);
    digitalWrite_DB5(HIGH);
    digitalWrite_DB4(LOW);
    enable_pulse();
    __delay_us(40*DELAY_MULTIPLIER);
    digitalWrite_DB7(HIGH);
    digitalWrite_DB6(LOW);
    digitalWrite_DB5(LOW);
    digitalWrite_DB4(LOW);
    enable_pulse();
    __delay_us(40*DELAY_MULTIPLIER);
    
    //Display Off
    digitalWrite_DB7(LOW);
    digitalWrite_DB6(LOW);
    digitalWrite_DB5(LOW);
    digitalWrite_DB4(LOW);
    enable_pulse();
    __delay_us(40*DELAY_MULTIPLIER);
    digitalWrite_DB7(HIGH);
    digitalWrite_DB6(LOW);
    digitalWrite_DB5(LOW);
    digitalWrite_DB4(LOW);
    enable_pulse();
    __delay_us(40*DELAY_MULTIPLIER);
    
    //Display Clear
    digitalWrite_DB7(LOW);
    digitalWrite_DB6(LOW);
    digitalWrite_DB5(LOW);
    digitalWrite_DB4(LOW);
    enable_pulse();
    __delay_us(40*DELAY_MULTIPLIER);
    digitalWrite_DB7(HIGH);
    digitalWrite_DB6(HIGH);
    digitalWrite_DB5(HIGH);
    digitalWrite_DB4(LOW);
    enable_pulse();
    __delay_us(40*DELAY_MULTIPLIER);
}

void write_mode_on() {
    digitalWrite_RW(LOW);
}

void read_mode_on() {
    digitalWrite_RW(HIGH);
}

void select_instruction_register() {
    digitalWrite_RS(LOW);
}

void select_data_register() {
    digitalWrite_RS(HIGH);
}

void enable_pulse() {
    digitalWrite_EN(HIGH);
    __delay_us(1*DELAY_MULTIPLIER);
    digitalWrite_EN(LOW);
}
