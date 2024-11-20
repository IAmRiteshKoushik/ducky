## 1. Abstract
A USB Rubber Ducky is a malicious device disguised as a harmless USB flash drive. When plugged into a computer, it emulates a human-interface device like a mouse or a keyboard and starts injecting keystrokes to execute malicious commands. Our project aims to build a custom USB Rubber Ducky using the STM32 Black Pill microcontroller, providing a platform for both learning and ethical hacking.

## 2. Hardware Components
**STM32 Black Pill Microcontroller:** The core of the project, providing the processing power and USB capabilities. (ARM Cortex-M3, 64kB flash, 20kB SRAM, 16MHz Clock)
USB Connector: For power and data transfer to the host computer.
**Jumpers:** To construct the mouth of the bad-USB with a USB-head.
**USB-UART Converter:** To facilitate serial communication between the computer and the microcontroller for debugging and configuration.
**ST-LINK Debugger:** For programming, flashing and debugging the STM32 Black Pill microcontroller.

## 3. Software Tools and Libraries
**CLion IDE by JetBrains:** An integrated development environment (IDE) for C/C++ used for code development, and debugging packaging code with minimal setup steps.
**Platform.io:** An open-source IDE extension for developing embedded systems, around C/C++ or Rust with support for 1000s of different microcontrollers and embedded frameworks like CMSIS, Arduino, RTOS, HAL, etc.
**PuTTY:** Acts as a serial-monitor and shows the keys which behave in malformed ways. 

## 4. Schematic Diagram of STM32 Black Pill Rubber Ducky
![diagram-1](./schematic-diagram.jpeg)

## 5. Project Implementation

### 5.1 Hardware Setup
Connect the components: Assemble the components on the Black Pill Development Kit, ensuring proper connections between the microcontroller, USB host shield,USB-UART connector  ST-Link V2 and power supply. The above mentioned schematic diagram gives a 100 feet view of how the connections are to be made. 
Configure the microcontroller: Use the CLion IDE with Platform.io to configure the microcontroller's clock speed, USB peripherals, and GPIO pins through embedded-C code.
Flash the firmware: Use ST-Link V2 to flash the compiled firmware onto the microcontroller.

### 5.2 Malware Development
**Initialize the USB host:** Configure the USB host shield to communicate with the host computer's USB port.
**Emulate a USB mass storage device:** Implement the MSC library to allow the device to appear as a USB drive. This can be used to store payload files or configuration data.
Implement keyboard emulation: Use the keyboard emulation library to simulate keystrokes. The firmware can be programmed to execute specific commands, such as opening malicious files, downloading malware, or remapping one key to another so as to cause anxiety and chaos to the victim’s system.
**Delay and timing:** Incorporate delays to control the rate of keystroke injection, either making it less detectable or executing things quickly before getting scanned by Windows defender or other Anti-Virus software. Keystrokes can operate at 1000 WPM. 

## 6. Security Considerations and Ethical Use
**Physical Security:** Protect the device to prevent unauthorized access and misuse.
**Firmware Security:** Implement measures to protect the firmware from reverse engineering and modification.
**Ethical Use:** Use this technology responsibly and for legitimate purposes, such as security testing and research.

## 7. Future Enhancements
**Wireless Capabilities:** Introduce a Wi-Fi or Bluetooth module to enable remote control and data transfer to attackers in the form of key-logging.
**Advanced Payload Delivery:** Implement techniques to bypass security measures and deliver payloads effectively by means of multi-threading. 
Stealth Mode: Features to minimize detection, such as delayed activation or low-profile operation would be great additions to the project
**Dynamic Payload Embedding:** Currently, a hardcoded payload is being executed but in the future versions a payload file can be embedded in the binaries that are flashed into STM32 and the instructions from the file can be read and executed. 

## 8. Conclusion
The USB Rubber Ducky project provides a valuable platform for learning about microcontroller programming, USB protocols, and security vulnerabilities. By understanding the principles behind this device, individuals can enhance their security awareness and develop countermeasures to protect against such threats. It is crucial to use this knowledge responsibly and ethically to contribute to a safer digital environment.
