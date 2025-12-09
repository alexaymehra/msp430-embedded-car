# MSP430 Embedded Car

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

<!-- Optional: You can add build/status badges here if you have CI or tests -->

---

## Table of Contents
* [Overview](#overview)
* [Features](#features)
* [Repository Structure](#repository-structure)
* [Hardware & Software Requirements](#hardware--software-requirements)
* [Build & Flash Instructions](#build--flash-instructions)
* [Usage](#usage)
* [Project Status & Limitations](#project-status--limitations)
* [License](#license)
* [Contact](#contact)

---

## Overview
This project uses the MSP430FR2355 microcontroller and other peripherals such as a FET board, motors, an LCD Dispaly, IR emitters, an IR detector, an ESP32, and a DAC board to allow the car to execute remote-controlled movements and autonomously detect and follow a black line (e.g. black tape).


---

## Features

* Line detection and line‑following logic based on analog/digital sensor inputs
* Sensor calibration routines for improved detection accuracy
* Real‑time, interrupt‑driven sensor reading (ADC / timers / ports)
* Motor and wheel control abstractions for driving / steering
* Modular code organization (sensors, wheels, initialization, communication, etc.) for easy customization
* Optional IoT / Wi‑Fi / communication module support (depending on hardware)
* Minimal dependencies — designed for bare‑metal microcontroller development

---

## Hardware & Software Requirements

Before building or deploying this project, ensure you have the following:

* **Microcontroller:** MSP430FR2355TPT (or other compatible MSP430 variant)
* **Development board or custom PCB** wired for sensors, motors, power supply
* **Sensors:** For line detection (e.g. IR reflectance sensors, photodiodes / phototransistors, or similar)
* **Motors + motor driver circuits** for wheel control (motors, H‑bridge or driver board, power supply)
* **Power supply** (batteries or regulated power that meets MCU + motor requirements)
* **Toolchain:** A working MSP430 compiler (e.g. MSP430‑ELF GCC toolchain), or TI Code Composer Studio (CCS), or other compatible toolchain for MSP430
* **(Optional) Peripheral modules**: Wi‑Fi module (if you plan to use IoT code), display or serial interface for debugging or telemetry

---

## Build & Flash Instructions

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

## Usage

1. Wire up the sensors, motors, power supply, and any optional peripherals (Wi‑Fi module, display, etc.) according to your hardware setup.
2. Calibrate sensors if needed (e.g. using calibration routines in code).
3. Build and flash the firmware onto the MSP430 microcontroller.
4. Power the board — the car should attempt line detection and follow along the line if present.
5. (Optional) Use Wi‑Fi / IoT features for remote control, telemetry, configuration, or monitoring (depending on hardware).

> 💡 For more advanced usage: consider extending with PID-based motion control, obstacle detection, or feedback mechanisms for smoother navigation / better reliability.

---

## License

This project is released under the **MIT License**. See the [LICENSE](LICENSE) file for full text.

---

## 📬 Contact

Created and maintained by **Alexay Mehra**.

