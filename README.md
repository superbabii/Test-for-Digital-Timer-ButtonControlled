# Test-for-Digital-Timer-ButtonControlled

This repository contains a test project for a button-controlled digital timer using a PIC microcontroller. The timer's time can be adjusted using physical buttons, with the countdown displayed on a multiplexed 7-segment display.

## Features

- **Time Adjustment**: 
  - **S1 Button (RA0)**: Increases time by minutes.
  - **S2 Button (RA1)**: Decreases time by minutes.
  - **S3 Button (RA2)**: Starts the timer countdown.

- **Timer0-Based Countdown**: 
  - The countdown starts in seconds after pressing the start button (S3) and continues until it reaches 00:00.

- **Multiplexed 7-Segment Display**: 
  - The current countdown time is displayed using a 4-digit 7-segment display, with multiplexing handled in the main loop.

## Project Structure

- **main.c**: Core logic for countdown timekeeping, button handling, and display multiplexing.
- **mcc_generated_files/**: Auto-generated files by MPLAB Code Configurator (MCC) for PIC initialization.

## Getting Started

1. Clone the repository:
    ```bash
    git clone https://github.com/superbabii/Test-for-Digital-Timer-ButtonControlled.git
    ```
2. Open the project in MPLAB X IDE.
3. Compile and upload the code to the PIC microcontroller.

## Hardware Requirements

- PIC Microcontroller (e.g., PIC16F1518)
- Buttons connected to RA0, RA1, and RA2
- 7-segment display
- Pull-up or pull-down resistors as needed
- Power supply

## Usage

- **Increment Time**: Press the S1 button to increase the time by one minute.
- **Decrement Time**: Press the S2 button to decrease the time by one minute.
- **Start Countdown**: Press the S3 button to start the countdown timer.

## Contributing

This project is a test for a final purpose. Fixes and improvements may be made based on testing results. Contributions and suggestions are welcome.

## License

This project is licensed under the MIT License.
