 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/tmr0.h"

unsigned char seconds = 0;
unsigned char minutes = 0;
unsigned char digit[4];

// Timer0 Preload Value for 1ms Timing
#define TMR0_PRELOAD 120

// Function to update the 7-segment display values
void update_display() {
    digit[0] = minutes / 10;
    digit[1] = minutes % 10;
    digit[2] = seconds / 10;
    digit[3] = seconds % 10;
}

// Timer0 Overflow Callback Function
void Timer0_OverflowCallback(void) {
    static unsigned int ms_count = 0;

    // Reload Timer0 to maintain 1ms interval
    Timer0_Write(TMR0_PRELOAD);

    ms_count++;
    if (ms_count >= 1000) { // 1 second
        ms_count = 0;
        seconds++;
        if (seconds >= 60) {
            seconds = 0;
            minutes++;
            if (minutes >= 60) {
                minutes = 0;
            }
        }
    }
}

// Function to handle button presses
void handle_buttons(void) {
    if (PORTAbits.RA0 == 0) {  // + Button
        __delay_ms(20); // Debounce delay
        if (PORTAbits.RA0 == 0) {
            minutes++;
            if (minutes >= 60) {
                minutes = 0;
            }
            while (PORTAbits.RA0 == 0); // Wait until the button is released
        }
    }

    if (PORTAbits.RA1 == 0) {  // - Button
        __delay_ms(20); // Debounce delay
        if (PORTAbits.RA1 == 0) {
            if (minutes == 0) {
                minutes = 59;
            } else {
                minutes--;
            }
            while (PORTAbits.RA1 == 0); // Wait until the button is released
        }
    }

    if (PORTAbits.RA2 == 0) {  // Reset Button
        __delay_ms(20); // Debounce delay
        if (PORTAbits.RA2 == 0) {
            minutes = 0;
            seconds = 0;
            while (PORTAbits.RA2 == 0); // Wait until the button is released
        }
    }
}

/*
    Main application
*/

int main(void) {
    SYSTEM_Initialize();

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 

    // Set the initial preload value for Timer0
    Timer0_Write(TMR0_PRELOAD);

    // Register the Timer0 Overflow Callback function
    Timer0_OverflowCallbackRegister(Timer0_OverflowCallback);

    while(1) {
        update_display();
        handle_buttons();

        // Multiplex displays
        LATBbits.LATB0 = 1; LATC = digit[0]; __delay_ms(1); LATBbits.LATB0 = 0;
        LATBbits.LATB1 = 1; LATC = digit[1]; __delay_ms(1); LATBbits.LATB1 = 0;
        LATBbits.LATB2 = 1; LATC = digit[2]; __delay_ms(1); LATBbits.LATB2 = 0;
        LATBbits.LATB3 = 1; LATC = digit[3]; __delay_ms(1); LATBbits.LATB3 = 0;
    }    
}