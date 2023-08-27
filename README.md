# Temperature-Controlled-Fan
The Fan turns on or off depending on the temperature using a Raspberry Pi
# Introduction:
In the final project for the ECE471 class, a Raspberry Pi 4 was utilized to develop a temperature-controlled fan system. The objective of this project was to maintain a specific temperature by controlling a fan while providing visual feedback through an i2c LED display. A 1-wire temperature sensor was employed to measure temperature, and when it exceeded a predefined threshold, the fan would turn on or off accordingly. The LED display would indicate "FAN ON" or "FAN OFF."

# Hardware Design:
The Raspberry Pi 4 was chosen due to its accessibility and robust specifications, including 4GB RAM and a Quad-core Cortex-A72 64-bit CPU. To power a 12V DC fan from the Pi's 3.3V output, an IRFD110 MOSFET, a 2N3904 BJT transistor, and a 12V power source were employed. Pull-up resistors (1k and 10k Ohms) were incorporated to prevent current from flowing back into the Pi. The DSB18B20 1-wire temperature sensor, capable of measuring temperatures from -55°C to 125°C, was connected to the Pi's GPIO pins.

# Output Components:
The 12V DC fan was originally designed for a PC and was controlled through its wires (red for power, black for ground, yellow for PWM speed control). To simplify the project, PWM was not used, and the fan was directly controlled by sending a 3.3V signal to a BJT gate terminal. Additionally, a 4x7 LED display was utilized via i2c communication to provide visual feedback.

# Software and OS:
C was selected as the programming language due to its low-level control capabilities, efficiency, and extensive online resources. The Raspberry Pi ran Linux 2.1 as the operating system, providing a stable and cost-effective solution. Linux's open-source nature and support for resource-constrained environments like the Pi were advantageous.

# Real-time Considerations:
This temperature-controlled fan operates as a soft real-time system, where occasional delays do not significantly impact performance. Temperature changes are gradual, so brief software delays do not pose a critical issue.

# Security Measures:
There are currently no major security concerns, as the project is not connected to the internet. However, physical security considerations include potential unplugging of components, which could disrupt operations. Welding the connections could enhance hardware security.

# Code Density and Optimization:
Given the Raspberry Pi's 4GB RAM, code density was not a concern. The project's code and operations ran smoothly without memory-related issues.

# Related Work:
Research revealed various approaches to connecting a 12V DC fan to a Raspberry Pi. While some used PWM for fan control, this project focused on direct GPIO control for simplicity. Comparatively, variations in source code and methodologies were found.

# Conclusion:
Working independently, this project was completed in approximately 8 hours. Challenges included researching fan connections and resolving software and hardware issues. Future improvements could involve adding a cooling fan for the Raspberry Pi's CPU. Overall, this project exemplifies the successful integration of hardware and software on a Raspberry Pi to create a practical temperature control system.
Research revealed various approaches to connecting a 12V DC fan to a Raspberry Pi. While some used PWM for fan control, this project focused on direct GPIO control for simplicity. Comparatively, variations in source code and methodologies were found.

Conclusion:
Working independently, this project was completed in approximately 8 hours. Challenges included researching fan connections and resolving software and hardware issues. Future improvements could involve adding a cooling fan for the Raspberry Pi's CPU. Overall, this project exemplifies the successful integration of hardware and software on a Raspberry Pi to create a practical temperature control system.
