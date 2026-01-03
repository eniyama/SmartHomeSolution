# Smart Home Automation – Microcontroller (MC)

## Overview
This directory contains the **Microcontroller firmware** for the Smart Home Automation system.  
The firmware is developed using **STM32CubeIDE** with **HAL drivers** and **FreeRTOS**.

The microcontroller handles:
- Communication with the Wireless Communication Module (WCM)
- Relay control (Lights, Fan, AC, etc.)
- Sensor data acquisition (DHT11)
- Task management using FreeRTOS

---

## Folder Contents
This directory contains **source files only**. No build or binary files are included.

|      File Name         |         Description         |
|------------------------|------------|
| `main.c`               | Application entry point and system initialization |
| `main.h`               | Global definitions and pin configurations |
| `freertos.c`           | FreeRTOS task creation and scheduler setup |
| `FreeRTOSConfig.h`     | FreeRTOS kernel configuration |
| `relay_control.c`      | Relay control logic |
| `relay_control.h`      | Relay control APIs |
| `dht11_driver.c`       | DHT11 sensor driver implementation |
| `dht11_driver.h`       | DHT11 driver declarations |
| `structure.h`          | Communication data structures |
| `Smart_Home.ioc`       | STM32CubeMX configuration file |

---

## Software Requirements
- **STM32CubeIDE**
- Supported STM32 microcontroller
- ST-Link debugger/programmer

---

## Important Note
This repository **does not contain build files** such as:
- `Debug/` or `Release/` folders
- `.elf`, `.hex`, or `.bin` files

Users must generate build files locally using STM32CubeIDE.

---

## How to Import and Build the Project

### Step 1: Clone or Download the Repository
```bash
git clone https://github.com/<your-username>/smart_home_automation.git

### Step 2: Open STM32CubeIDE
1. Launch **STM32CubeIDE**
2. Select or create a workspace directory
3. Click **Launch**

---

### Step 3: Import the Project
1. Go to **File → Open Projects from File System**
2. Click **Directory**
3. Select the **MC** folder
4. Click **Finish**

---

### Step 4: Load CubeMX Configuration
1. Open `Smart_Home.ioc`
2. STM32CubeIDE will automatically load:
   - Pin configuration  
   - Clock settings  
   - Peripheral configuration  
3. If prompted, click **Generate Code**

---

### Step 5: Build the Project
1. Right-click the project → **Build Project**  
   **OR**
2. Click the **Build (hammer) icon** in the toolbar
