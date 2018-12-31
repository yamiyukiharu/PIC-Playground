#include <xc.h>
#include "HD44780.h"

#define DELAY_MULTIPLIER 2

//configuration macros
#define HD44780_CURSOR_MOVE_WHEN_DISPLAY_SHIFT
#define HD44780_CURSOR_MOVE_RIGHT
#define HD44780_LINE_NUMBER_2 

//constants 
#define HD44780_4_BIT_INTERFACE		0x02
#define HD44780_DISPLAY_OFF         0x08
#define HD44780_DISPLAY_CLEAR       0x01
#define HD44780_RETURN_HOME         0x02
#define HD44780_CURSOR_ON_NO_BLINK  0x0E
#define HD44780_CURSOR_ON_BLINK     0x0F
#define HD44780_CURSOR_SHIFT_LEFT   0x10
#define HD44780_CURSOR_SHIFT_RIGHT  0x14
#define HD44780_DISPLAY_SHIFT_LEFT  0x18
#define HD44780_DISPLAY_SHIFT_RIGHT 0x1C


#ifdef HD44780_LINE_NUMBER_2
    #define HD44780_FUNCTION_SET    0xFF
#else
    #define HD44780_FUNCTION_SET    0x0B
#endif

#ifdef HD44780_CURSOR_MOVE_RIGHT
    #ifdef HD44780_CURSOR_MOVE_WHEN_DISPLAY_SHIFT
        #define HD44780_ENTRY_MODE  0x06
    #endif
#else
    #ifdef HD44780_CURSOR_MOVE_WHEN_DISPLAY_SHIFT
        #define HD44780_ENTRY_MODE  0x07
    #else
        #define HD44780_ENTRY_MODE  0x04
    #endif
#endif

void write_mode_on(void);
void read_mode_on(void);
void select_instruction_register(void);
void select_data_register(void);
void enable_pulse(void);
void writeNibble(uint8_t value);
void writeByte(uint8_t value);


void HD44780_init(void) {
    //Init sequence as specified by datasheet
    delay_ms(100*DELAY_MULTIPLIER);
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
    writeNibble(HD44780_4_BIT_INTERFACE);
    writeNibble(HD44780_FUNCTION_SET);
    
    HD44780_writeCommand(HD44780_CURSOR_ON_BLINK);
    HD44780_writeCommand(HD44780_ENTRY_MODE);
    delay_us(500);
}

void HD44780_writeString(char* value) {
    while((*value)!=0)
		HD44780_writeData(*value++); // Loop through the string and display char by char
}

void HD44780_setDisplayAddress(uint8_t value) {
    HD44780_writeCommand(0b10000000 | value);
}

void HD44780_clearDisplay() {
    HD44780_writeCommand(HD44780_DISPLAY_CLEAR);
    delay_ms(2*DELAY_MULTIPLIER);
}

void HD44780_returnHome() {
    HD44780_writeCommand(HD44780_RETURN_HOME);
    delay_ms(2*DELAY_MULTIPLIER);
}

void HD44780_shiftCursorLeft() {
    HD44780_writeCommand(HD44780_CURSOR_SHIFT_LEFT);
}
void HD44780_shiftCursorRight() {
    HD44780_writeCommand(HD44780_CURSOR_SHIFT_RIGHT);
}
void HD44780_shiftDisplayLeft() {
    HD44780_writeCommand(HD44780_DISPLAY_SHIFT_LEFT);
}
void HD44780_shiftDisplayRight() {
    HD44780_writeCommand(HD44780_DISPLAY_SHIFT_RIGHT);
}

void HD44780_writeCommand(uint8_t value) {
    select_instruction_register();
    write_mode_on();
    writeByte(value);
}

void HD44780_writeData(uint8_t value) {
    select_data_register();
    write_mode_on();
    writeByte(value);
}

void writeNibble(uint8_t value) {
	digitalWrite_DB7((value >> 3) & 0b1);
    digitalWrite_DB6((value >> 2) & 0b1);
    digitalWrite_DB5((value >> 1) & 0b1);
    digitalWrite_DB4(value & 0b1);
    enable_pulse();
    delay_us(40*DELAY_MULTIPLIER);
}

void writeByte(uint8_t value) {
	writeNibble(value >> 4);
    writeNibble(value);
}

void write_mode_on(void) {
    digitalWrite_RW(LOW);
}

void read_mode_on(void) {
    digitalWrite_RW(HIGH);
}

void select_instruction_register(void) {
    digitalWrite_RS(LOW);
}

void select_data_register(void) {
    digitalWrite_RS(HIGH);
}

void enable_pulse(void) {
    digitalWrite_EN(HIGH);
    delay_us(1*DELAY_MULTIPLIER);
    digitalWrite_EN(LOW);
}
