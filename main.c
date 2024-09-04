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

const uint8_t SEGMENT_MAP[10] = {
    0b11000000, // 0 
    0b11111001, // 1 
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000  // 9
};

// Variables for timekeeping
uint8_t minutes = 0;
uint8_t seconds = 0;
uint8_t digit[4];
bool timer_running = false;

// Timer0 Preload Value for 1ms Timing
//#define TMR0_PRELOAD 120

// Function to update the 7-segment display values
void displayDigits(uint8_t minutes, uint8_t seconds) {
    uint8_t digit[4];
    digit[0] = minutes / 10;
    digit[1] = minutes % 10;
    digit[2] = seconds / 10;
    digit[3] = seconds % 10;

    for (int i = 0; i < 4; i++) {
        LATC = SEGMENT_MAP[digit[i]];
        LATB = (1 << i);
        __delay_ms(1);
        LATB = 0;
    }
}

// Timer0 Overflow Callback Function
void Timer0_OverflowCallback(void) {
    static unsigned int ms_count = 0;

//    // Reload Timer0 to maintain 1ms interval
//    Timer0_Write(TMR0_PRELOAD);

    if (timer_running) {
        ms_count++;
        if (ms_count >= 1000) { // 1 second
            ms_count = 0;
            if (seconds == 0) {
                if (minutes == 0) {
                    timer_running = false; // Stop the timer when it reaches 00:00
                } else {
                    minutes--;
                    seconds = 59;
                }
            } else {
                seconds--;
            }
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

    // Register the Timer0 Overflow Callback function
    Timer0_OverflowCallbackRegister(Timer0_OverflowCallback);

    while(1) {
        if (PORTAbits.RA0 == 0 && !timer_running) {  // + Button
            __delay_ms(20); // Debounce delay
            if (PORTAbits.RA0 == 0) {
                minutes++;
                if (minutes > 99) {
                    minutes = 99;  // Limit to 99 minutes
                }
            }
        }

        if (PORTAbits.RA1 == 0 && !timer_running) {  // - Button
            __delay_ms(20); // Debounce delay
            if (PORTAbits.RA1 == 0) {
                if (minutes > 0) {
                    minutes--;
                }
            }
        }

        if (PORTAbits.RA2 == 0) {  // Start Button (S3)
            __delay_ms(20); // Debounce delay
            if (PORTAbits.RA2 == 0 && !timer_running) {
                timer_running = true;
                while (PORTAbits.RA2 == 0); // Wait until the button is released
            }
        }
        
        // Display the time
        displayDigits(minutes, seconds);
    }    
}