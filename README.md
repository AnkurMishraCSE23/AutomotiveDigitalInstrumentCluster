# Automotive Digital Instrument Cluster Firmware

STM32-based automotive instrument cluster firmware developed in Embedded C using STM32CubeIDE and the STM32 HAL.

The project focuses on peripheral configuration, interrupt-driven event handling, CAN communication, vehicle-state management, and UART telemetry.

## Overview

The firmware represents the embedded software layer of a simplified automotive digital instrument cluster.

Vehicle parameters are received through CAN, decoded into an internal `VehicleState` model, and periodically transmitted over UART for monitoring and debugging.

The project was developed without physical automotive hardware, with the embedded firmware and communication architecture being the primary focus.

## Features

- CAN communication at 500 kbit/s
- CAN hardware acceptance filtering
- Interrupt-driven CAN reception using RX FIFO0
- CAN vehicle-state frame decoding
- Centralized vehicle-state management
- GPIO input handling using external interrupts
- GPIO output control for cluster indicators
- ADC peripheral configuration for analog sensor input
- UART-based vehicle-state telemetry
- Modular application-level peripheral managers
- STM32 HAL-based peripheral abstraction

## System Architecture

                    STM32F407
                       │
        ┌──────────────┼──────────────┐
        │              │              │
       CAN            GPIO           ADC
        │              │              │
        ▼              ▼              ▼
  CanManager     InputManager    SensorManager
        │              │
        ▼              ▼
   VehicleState    GPIO Events
        │
        ▼
  ClusterComm
        │
        ▼
      UART

## CAN Communication

CAN1 is configured for **500 kbit/s** communication.

The firmware uses a hardware acceptance filter to accept vehicle-state messages with standard CAN ID:

    0x100

### Vehicle-State CAN Frame

The current application-level frame format is:

| Byte | Data |
|------|------|
| 0–1 | Speed (`uint16`, little-endian) |
| 2–3 | RPM (`uint16`, little-endian) |
| 4 | Fuel percentage |
| 5–6 | Temperature (`int16`, little-endian) |
| 7 | Reserved |

Example:

    CAN ID: 0x100
    DLC: 8

Received frames are handled through the CAN RX FIFO0 interrupt and decoded by the CAN manager before updating the centralized vehicle state.

## Vehicle State

The firmware maintains the following vehicle parameters:

    typedef struct
    {
        uint16_t speed_kmh;
        uint16_t rpm;
        uint8_t  fuel_percent;
        int16_t  temperature_c;

    } VehicleState;

The CAN manager updates this state through:

    VehicleState_SetFromCAN(...)

This keeps vehicle-state management separate from the underlying communication mechanism.

## UART Telemetry

The current vehicle state is transmitted through USART2 every 200 ms.

Example output:

    SPEED=80,RPM=2400,FUEL=74,TEMP=82

This provides a simple way to observe the firmware's processed vehicle data from a serial terminal.

## GPIO and Interrupt Handling

The project demonstrates GPIO configuration for:

- Push-pull output
- Pull-up input
- External interrupt input

The turn-signal input is configured using an external interrupt. The interrupt callback records the event, while the main application loop processes the event and controls the corresponding cluster indicator.

## ADC

ADC1 is configured for analog input and provides the foundation for sensor-oriented input handling.

The ADC infrastructure is kept modular through the `SensorManager` component.

## Project Structure

    AutomotiveDigitalInstrumentCluster/
    │
    ├── Core/
    │   ├── Inc/
    │   │   ├── can_manager.h
    │   │   ├── cluster_comm.h
    │   │   ├── input_manager.h
    │   │   ├── sensor_manager.h
    │   │   ├── vehicle_state.h
    │   │   └── ...
    │   │
    │   ├── Src/
    │   │   ├── can_manager.c
    │   │   ├── cluster_comm.c
    │   │   ├── input_manager.c
    │   │   ├── sensor_manager.c
    │   │   ├── vehicle_state.c
    │   │   └── ...
    │   │
    │   └── Startup/
    │
    ├── Drivers/
    │   ├── CMSIS/
    │   └── STM32F4xx_HAL_Driver/
    │
    ├── AutomotiveDigitalInstrumentCluster.ioc
    ├── STM32F407VGTX_FLASH.ld
    ├── STM32F407VGTX_RAM.ld
    └── README.md

## Development Environment

### Microcontroller

- STM32F407VGT6 / STM32F407VGTx family

### Software

- STM32CubeIDE
- STM32 HAL
- CMSIS
- ARM GCC toolchain

### Peripherals

- CAN1
- USART2
- GPIO
- ADC1
- EXTI / NVIC

## Building the Project

1. Clone the repository.
2. Import the project into STM32CubeIDE.
3. Open the `.ioc` configuration file if CubeMX configuration needs to be inspected.
4. Build the project using STM32CubeIDE.

The project was developed and verified to compile successfully in STM32CubeIDE.

## Project Scope

This repository represents the **embedded firmware implementation** of the instrument cluster project.

The current version focuses on the embedded communication and peripheral architecture rather than a graphical dashboard or physical vehicle integration.

## Tech Stack

- **Language:** Embedded C
- **Microcontroller:** STM32F407VGT6
- **IDE:** STM32CubeIDE
- **Framework / Libraries:** STM32 HAL, CMSIS
- **Communication:** CAN, UART
- **Peripherals:** GPIO, ADC, EXTI, NVIC
- **Toolchain:** ARM GCC

## Author

**Ankur Mishra**

B.Tech Computer Science & Engineering

### Technologies Used

`Embedded C` · `STM32F407VGT6` · `STM32CubeIDE` · `STM32 HAL` · `CMSIS` · `CAN` · `UART` · `GPIO` · `ADC` · `EXTI` · `NVIC` · `ARM GCC`