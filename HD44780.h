#include <xc.h> // include processor files - each processor file is guarded.  
#include "mcc_generated_files/device_config.h"
#include <stdbool.h>
#include <stdint.h>

#define HIGH    1
#define LOW     0

/*  Need to implement these functions to map the IO to target hardware
    Supports 4 bit mode only
*/
#define digitalWrite_DB4(state)     LATC5 = state;
#define digitalWrite_DB5(state)     LATC4 = state;
#define digitalWrite_DB6(state)     LATC3 = state;
#define digitalWrite_DB7(state)     LATC6 = state;

#define digitalWrite_RS(state)     LATB4 = state;
#define digitalWrite_RW(state)     LATB5 = state;
#define digitalWrite_EN(state)     LATB6 = state;

#define delay_us(time)                   __delay_us(time);
#define delay_ms(time)                   __delay_ms(time);

// 8 X 1 settings at the moment
void HD44780_init(void);
void HD44780_writeCommand(uint8_t value);
void HD44780_writeData(uint8_t value);
void HD44780_clearDisplay();
void HD44780_returnHome();
void HD44780_writeString(char* value);
void HD44780_shiftCursorLeft();
void HD44780_shiftCursorRight();
void HD44780_shiftDisplayLeft();
void HD44780_shiftDisplayRight();
void HD44780_setDisplayAddress(uint8_t value);