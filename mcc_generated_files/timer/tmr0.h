/**
 * TMR0 Generated Driver API Header File
 * 
 * @file tmr0.h
 * 
 * @defgroup  tmr0 TMR0
 * 
 * @brief This file contains API prototypes and other data types for the Timer0 (TMR0) driver
 *
 * @version TMR0 Driver Version 2.0.0
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

#ifndef TMR0_H
#define TMR0_H

#include "timer_interface.h"
#include <stdbool.h>
#include <stdint.h>


/**
 * @ingroup tmr0
 * @struct TMR_INTERFACE
 * @brief  This is an instance of TMR_INTERFACE for the Timer0 module.
 */
extern const struct TMR_INTERFACE Timer0;

/**
 * @ingroup tmr0
 * @brief Initializes the Timer0 module.
 *        This routine is called once, before any other Timer0 routine.
 * @param None.
 * @return None.
 */ 
void Timer0_Initialize(void);

/**
 * @ingroup tmr0
 * @brief Reads the 8-bit value from the Timer0 register.
 * @pre Initialize Timer0 with Timer0_Initialize() before calling this API.
 * @param None.
 * @return 8-bit data from the Timer0 register
 */
uint8_t Timer0_Read(void);

/**
 * @ingroup tmr0
 * @brief Writes an 8-bit value to the Timer0 register.
 *        Initialize Timer0 with Timer0_Initialize() before calling this API.
 * @param timerVal - 8-bit value to be written to the Timer0 register
 * @return None.
 */
void Timer0_Write(size_t timerVal);

/**
 * @ingroup tmr0
 * @brief Loads an 8-bit value to the Timer0 register.
 * @pre Initialize Timer0 with Timer0_Initialize() before calling this API.
 * @param None.
 * @return None.
 */
void Timer0_Reload(void);

/**
 * @ingroup tmr0
 * @brief Loads the 8-bit value to the timer0ReloadVal variable.
 * @param periodVal - 8-bit value 
 * @return None.
 */
void Timer0_PeriodCountSet(size_t periodVal);

/**
 * @ingroup tmr0
 * @brief Setter function for the Timer0 overflow callback.
 * @param CallbackHandler - Pointer to custom callback
 * @return None.
 */
 void Timer0_OverflowCallbackRegister(void (* CallbackHandler)(void));

/**
 * @ingroup tmr0
 * @brief Performs tasks to be executed on timer overflow event.
 * @param None.
 * @return None.
 */
void Timer0_Tasks(void);

/**
 * @}
 */
#endif //TMR0_H