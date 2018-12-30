#include <xc.h>
#include "HD44780.h"

#define DELAY_MULTIPLIER 2

#define HD44780_4_BIT_INTERFACE		0x2

void write_mode_on();
void read_mode_on();
void select_instruction_register();
void select_data_register();
void enable_pulse();
void writeNibble(uint8_t value);
void writeByte(uint8_t value);

void HD44780_init() {
    delay_ms(16*DELAY_MULTIPLIER);
    digitalWrite_DB7(LOW);
    digitalWrite_DB6(LOW);
    digitalWrite_DB5(HIGH);
    digitalWrite_DB4(HIGH);
    select_instruction_register();
    write_mode_on();
    delay_us(1*DELAY_MULTIPLIER);
    enable_pulse();
    delay_ms(5*DELAY_MULTIPLIER);
    enable_pulse();
    delay_us(110*DELAY_MULTIPLIER);
    enable_pulse();
    delay_us(40*DELAY_MULTIPLIER);

    //set 4 bit interface
    writeNibble(HD44780_4_BIT_INTERFACE);
    
    //specify display lines & font
    digitalWrite_DB7(LOW);
    digitalWrite_DB6(LOW);
    digitalWrite_DB5(HIGH);
    digitalWrite_DB4(LOW);
    enable_pulse();
    delay_us(40*DELAY_MULTIPLIER);
    digitalWrite_DB7(HIGH);
    digitalWrite_DB6(LOW);
    digitalWrite_DB5(LOW);
    digitalWrite_DB4(LOW);
    enable_pulse();
    delay_us(40*DELAY_MULTIPLIER);
    
    //Display Off
    digitalWrite_DB7(LOW);
    digitalWrite_DB6(LOW);
    digitalWrite_DB5(LOW);
    digitalWrite_DB4(LOW);
    enable_pulse();
    delay_us(40*DELAY_MULTIPLIER);
    digitalWrite_DB7(HIGH);
    digitalWrite_DB6(LOW);
    digitalWrite_DB5(LOW);
    digitalWrite_DB4(LOW);
    enable_pulse();
    delay_us(40*DELAY_MULTIPLIER);
    
    //Display Clear
    digitalWrite_DB7(LOW);
    digitalWrite_DB6(LOW);
    digitalWrite_DB5(LOW);
    digitalWrite_DB4(LOW);
    enable_pulse();
    delay_us(40*DELAY_MULTIPLIER);
    digitalWrite_DB7(HIGH);
    digitalWrite_DB6(HIGH);
    digitalWrite_DB5(HIGH);
    digitalWrite_DB4(LOW);
    enable_pulse();
    delay_us(40*DELAY_MULTIPLIER);
}

void writeNibble(uint8_t value) {
	digitalWrite_DB7(value >> 3 | 0b1);
    digitalWrite_DB6(value >> 2 | 0b1);
    digitalWrite_DB5(value >> 1 | 0b1);
    digitalWrite_DB4(value | 0b1);
    enable_pulse();
    delay_us(40*DELAY_MULTIPLIER);
}

void writeByte(uint8_t value) {
	writeNibble(value >> 4);
    writeNibble(value);
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
    delay_us(1*DELAY_MULTIPLIER);
    digitalWrite_EN(LOW);
}
