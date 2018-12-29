#include <xc.h> // include processor files - each processor file is guarded.  
#include "mcc_generated_files/device_config.h"
#include <stdbool.h>

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

// 8 X 1 settings at the moment
void HD44780_init();