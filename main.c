#include "mcc_generated_files/system/system.h"

// Segment map for 7-segment display (0-9)
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

// Constants
#define ONE_SECOND_TICKS 123
#define MAX_MINUTES 99
#define DEBOUNCE_DELAY 100

// Variables for timekeeping
uint8_t minutes = 0;
uint8_t seconds = 0;
bool timer_running = false;
bool sleep_mode = false;

// Function prototypes
void displayDigits(uint8_t minutes, uint8_t seconds);
void decreaseTime(void);
void handleSleepMode(void);
void checkButtons(void);
void controlLED(void);
bool debounceButton(uint8_t portPin);

void displayDigits(uint8_t minutes, uint8_t seconds) {
    uint8_t digit[4];
    digit[0] = minutes / 10;
    digit[1] = minutes % 10;
    digit[2] = seconds / 10;
    digit[3] = seconds % 10;

    for (int i = 0; i < 4; i++) {
        LATC = SEGMENT_MAP[digit[i]];
        LATB = (unsigned char)(1 << i);
        __delay_ms(1); // Brief delay for display multiplexing
        LATB = 0;
    }
}

void decreaseTime(void) {
    static unsigned int ms_count = 0;

    if (timer_running) {
        ms_count++;
        if (ms_count >= ONE_SECOND_TICKS) {
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

void handleSleepMode(void) {
    if (PORTAbits.RA4 == 0) {  
//      WDTCONbits.SWDTEN = 1;
        LATAbits.LATA5 = 0;
        SLEEP();
        sleep_mode = true;
    } else  {
        CLRWDT();      
        sleep_mode = false;
        if(timer_running)
            LATAbits.LATA5 = 1;
    }
}

void controlLED(void) {
    LATAbits.LATA5 = timer_running ? 1 : 0; // LED on when running
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
    
    while(1) {
        handleSleepMode();  // Manage sleep mode and watchdog timer
        
        if (PORTAbits.RA0 == 0 && !timer_running) {  // + Button
            __delay_ms(100); // Debounce delay
            if (PORTAbits.RA0 == 0) {
                minutes++;
                if (minutes > 99) {
                    minutes = 99;  // Limit to 99 minutes
                }
            }
        }

        if (PORTAbits.RA1 == 0 && !timer_running) {  // - Button
            __delay_ms(100); // Debounce delay
            if (PORTAbits.RA1 == 0) {
                if (minutes > 0) {
                    minutes--;
                }
            }
        }

        if (PORTAbits.RA2 == 0) {  // Start Button (S3)
            __delay_ms(100); // Debounce delay
            if (PORTAbits.RA2 == 0 && !timer_running) {
                timer_running = true;
                while (PORTAbits.RA2 == 0); // Wait until the button is released
            }
        }
        
        controlLED();       // Control the LED based on timer state

        // Decrease time and update display
        decreaseTime();
        if(sleep_mode == false)
            displayDigits(minutes, seconds);
    }    
}
