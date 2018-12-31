#include "mcc_generated_files/mcc.h"
#include "lcd.h"
#include "HD44780.h"
/*
                         Main application
 */
void WDT_LED_Timer_ISR(void) {
    CLRWDT();
    LATB7 = !PORTBbits.RB7;
}

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    WDTCONbits.SWDTEN = 1;
    TMR0_SetInterruptHandler(&WDT_LED_Timer_ISR);
    TMR0_StartTimer();
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable(); 
    HD44780_init();
    HD44780_writeString("Hello World!");
//    HD44780_writeString("Hello World!");
//    HD44780_shiftDisplayLeft();
//    HD44780_shiftDisplayLeft();
    HD44780_setDisplayAddress(0x40);
    HD44780_writeData('C');
    while (1) {
        
    }
}
/**
 End of File
*/