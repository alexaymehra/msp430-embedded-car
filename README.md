# MSP430 Embedded Car 🚗

> **Wi‑Fi‑enabled line‑following car built around the MSP430FR2355TPT microcontroller** — combining sensors, motor control, and optional IoT functionality for embedded robotics experimentation.

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

<!-- Optional: You can add build/status badges here if you have CI or tests -->

---

## 📄 Table of Contents

* [Overview](#overview)
* [Features](#features)
* [Repository Structure](#repository-structure)
* [Hardware & Software Requirements](#hardware--software-requirements)
* [Build & Flash Instructions](#build--flash-instructions)
* [Usage](#usage)
* [Project Status & Limitations](#project-status--limitations)
* [Contributing](#contributing)
* [License](#license)
* [Contact](#contact)

---

## 🔎 Overview

The MSP430 Embedded Car project implements a small autonomous / semi-autonomous car using the MSP430FR2355TPT microcontroller. The car is capable of detecting a line on the ground (e.g. black tape), following the line automatically using sensor input and wheel control logic, and optionally supporting Wi‑Fi / IoT communication for remote control, telemetry, or configuration.

This repo serves as a **reference / proof‑of‑concept** for anyone interested in MSP430‑based embedded robotics and can be extended, modified, or repurposed for custom embedded‑systems applications (e.g. robotics, automation, educational experiments).

---

## 🚀 Features

* Line detection and line‑following logic based on analog/digital sensor inputs
* Sensor calibration routines for improved detection accuracy
* Real‑time, interrupt‑driven sensor reading (ADC / timers / ports)
* Motor and wheel control abstractions for driving / steering
* Modular code organization (sensors, wheels, initialization, communication, etc.) for easy customization
* Optional IoT / Wi‑Fi / communication module support (depending on hardware)
* Minimal dependencies — designed for bare‑metal microcontroller development

---

## 📁 Repository Structure

```
/  (root)
│   main.c                      — Program entry point  
│   init.c / init_cmds.c        — Initialization and startup routines  
│   clocks.c                    — MCU clock / oscillator setup  
│   ports.c / ports.h           — Port and pin definitions / configuration  
│   timers.c / timer_interrupts.c   — Timer setup and interrupt handlers  
│   adc.c / adc_interrupts.c         — ADC routines & sensor interrupt‑based reading  
│   black_line_detect.c / black_line_follow.c — Line detection and line‑following logic  
│   wheels.c                    — Wheel / motor control logic  
│   iot.c                       — Optional Wi‑Fi / IoT / communication related code  
│   display.c / LCD.h           — (Optional) debugging / display / feedback routines  
│   functions.h / macros.h      — Utility macros and helper functions  
│   LICENSE                    — Project license (MIT)  
│   README.md                  — This file  
```

> You can reorganize or extend modules as needed (e.g. add obstacle detection, PID steering, different sensor types, etc.).

---

## 🧰 Hardware & Software Requirements

Before building or deploying this project, ensure you have the following:

* **Microcontroller:** MSP430FR2355TPT (or other compatible MSP430 variant)
* **Development board or custom PCB** wired for sensors, motors, power supply
* **Sensors:** For line detection (e.g. IR reflectance sensors, photodiodes / phototransistors, or similar)
* **Motors + motor driver circuits** for wheel control (motors, H‑bridge or driver board, power supply)
* **Power supply** (batteries or regulated power that meets MCU + motor requirements)
* **Toolchain:** A working MSP430 compiler (e.g. MSP430‑ELF GCC toolchain), or TI Code Composer Studio (CCS), or other compatible toolchain for MSP430
* **(Optional) Peripheral modules**: Wi‑Fi module (if you plan to use IoT code), display or serial interface for debugging or telemetry

---

## 🛠️ Build & Flash Instructions

Below is an example using the `msp430‑elf‑gcc` toolchain. Adjust based on your setup / toolchain / MCU variant:

```bash
# Example compile command
msp430-elf-gcc -mmcu=msp430fr2355 -O2 -o car_firmware \
  main.c init.c clocks.c ports.c \
  timers.c adc.c black_line_detect.c \
  black_line_follow.c wheels.c iot.c display.c

# Flash to MCU (example using a generic MSP430 programmer)
# Replace with the programmer/command relevant to your platform
mspdebug rf2500 "prog car_firmware"
```

> ⚠️ Ensure that all `.c` files your build depends on are included. If you add new modules or dependencies, update the command accordingly.

---

## 🚗 Usage

1. Wire up the sensors, motors, power supply, and any optional peripherals (Wi‑Fi module, display, etc.) according to your hardware setup.
2. Calibrate sensors if needed (e.g. using calibration routines in code).
3. Build and flash the firmware onto the MSP430 microcontroller.
4. Power the board — the car should attempt line detection and follow along the line if present.
5. (Optional) Use Wi‑Fi / IoT features for remote control, telemetry, configuration, or monitoring (depending on hardware).

> 💡 For more advanced usage: consider extending with PID-based motion control, obstacle detection, or feedback mechanisms for smoother navigation / better reliability.

---

## ⚠️ Project Status & Limitations

* This project is primarily a **proof-of-concept / learning / educational** repo — not a polished, production-ready robotics platform.
* **Safety mechanisms** (e.g. obstacle detection, emergency stop) are **not included by default**. If you plan to run this car in a real environment, implement safety checks before use.
* **Hardware dependencies**: behavior depends heavily on correct wiring, sensor calibration, and motor/hardware reliability.
* **Limited error-handling and robustness**: the code may not handle hardware faults, misreads, power dropouts, or unexpected conditions gracefully.

---

## 🤝 Contributing

Contributions are more than welcome! Here are a few ideas:

* Bug reports or issues (e.g. unexpected behavior, sensor logic edge cases, motor control bugs)
* Feature enhancements:

  * Obstacle detection (e.g. using ultrasonic / IR distance sensors)
  * PID control for smoother and more stable line-following
  * Support for different sensors or motor configurations
  * Telemetry, logging, and calibration/debug interfaces
* Improved documentation, wiring diagrams, schematics, or hardware setup guides
* Porting the project to other MSP430 variants or different microcontrollers / platforms

If you want to contribute — open an issue, start a discussion, or submit a pull request. Please follow consistent code style, add documentation for any new module or feature, and test thoroughly before changing core logic.

---

## 📜 License

This project is released under the **MIT License**. See the [LICENSE](LICENSE) file for full text.

---

## 📬 Contact

Created and maintained by **Alexay Mehra**.
Feel free to reach out with questions, suggestions, or collaboration ideas — e.g. via GitHub Issues or pull requests.
