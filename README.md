# MSP430-UART-FSM-With-Peripheries-Lab-4

Welcome to this GitHub repository showcasing a sophisticated embedded system project for MSP430x2xx microcontrollers, programmed in C to leverage a finite state machine (FSM) for managing peripherals with remote control using PC instruction and keyboard interactions. This project is ideally structured for intricate hardware control and is perfect for educational purposes and advanced embedded development, enhancing the advantages of the UART.

# Features

Modular Design: Code is organized into Application (APP), Board Support Package (BSP), Hardware Abstraction Layer (HAL), and Application Programming Interface (API) layers, enhancing both maintainability and scalability.

Finite State Machine (FSM): Manages system states and transitions for effective control of operational modes, ensuring a robust and responsive system.

Peripheral Management : Utilizes the UART for efficient data transfer from the PC to the MCU, making the system work in remote environment.

Low Power Management: Implements various low-power modes to optimize power consumption, vital for battery-operated and energy-efficient applications.

# FSM States and Operations

The FSM in this project manages different aspects of system functionality through these states and functions:

state1 : Blink the RGB LED color by color with delay of X.

state2: Count up onto the LCD screen with delay of X.

state3: Circular tone series via Buzzer with delay of X.

state4: Get new delay time X from the User.

state5: Displaying the LDR voltage onto the LCD screen.

state6: Clear the LCD screen.

state7: Show Menu.

state8: Sleep mode. 

#  Key Peripheral Utilization

UART 

GPIOs

LEDs

LCD

Keypad

Interrupts

Timers

# Project Structure

api.h & api.c: Define and implement interactions with peripherals.

app.h: Declares FSM states, modes, and global variables.

bsp.h & bsp.c: Include hardware-specific configurations and initializations.

halGPIO.h & halGPIO.c: Provide lower-level hardware management functions.

main.c: Initializes the system and manages the operational loop.
