# Test-for-DigitalClock-ButtonControlled

This repository contains a test project for a button-controlled digital clock using a PIC microcontroller. The clock's time can be adjusted using physical buttons, with the time displayed on a multiplexed 7-segment display.

## Features

- **Time Adjustment**: 
  - **S1 Button (RA0)**: Increases time by minutes.
  - **S2 Button (RA1)**: Decreases time by minutes.
  - **S3 Button (RA2)**: Resets time to 00:00.

- **Timer0-Based Timekeeping**: 
  - The time is incremented every second using a Timer0 overflow interrupt.

- **Multiplexed 7-Segment Display**: 
  - The current time is displayed using a 4-digit 7-segment display, with multiplexing handled in the main loop.

## Project Structure

- **main.c**: Core logic for timekeeping, button handling, and display multiplexing.
- **mcc_generated_files/**: Auto-generated files by MPLAB Code Configurator (MCC) for PIC initialization.

## Getting Started

1. Clone the repository:
    ```bash
    git clone https://github.com/superbabii/Test-for-DigitalClock-ButtonControlled.git
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
- **Reset Time**: Press the S3 button to reset the time to 00:00.

## Contributing

This project is a test for a final purpose. Fixes and improvements may be made based on testing results. Contributions and suggestions are welcome.

## License

This project is licensed under the MIT License.
