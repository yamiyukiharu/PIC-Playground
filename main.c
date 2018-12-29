#include "mcc_generated_files/mcc.h"
#include "lcd.h"
#include "HD44780.h"
/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    WDTCONbits.SWDTEN = 0;
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable(); 
    __delay_ms(150);
    HD44780_init();
    //LCD_Init(M_FourBitMode, 2, 16);
    LCD_DisplayChar('H');
    //LCD_DisplayString("Hello");
    while (1) {
        LATB7 = !PORTBbits.RB7;
        __delay_ms(100);
    }
}
/**
 End of File
*/