# Edward's hacking Device: Getting Started

## About the device
This device will allow you to:
 - perform hardware bruteforce attacks on GPIO pins
 - read / write Mifare NFC cards

## Chapter 1. Bruteforce wiring
To perform bruteforce attacks on any GPIO keypad, you need to spoof the keypad.

Keypads are usually wired this way:  
![Keypad wiring](imgs/default-pinout.png)

 - Columns are set to high or low by the keypad controller
 - Rows are read by the keypad controller

Most of the time, keypad controllers also render a direct feedback to tell if key-combination was right or wrong.
This can either be software or hardware (i.e. a green or red LED), this means you have to physically connect to the LED, to read its value.

Therefore, a target wiring may look like this:

![Microcontroller wiring](imgs/pinout-chapter1.jpg)

As of "where should I connect the pins", the developer must have put it somewhere in the code... Maybe in **BruteForceService.h**?

## Chapter 2. NFC-wiring
In order to use NFC devices, the hacking microcontroller has to be wired to the NFC board using a SPI connection.

SPI Connections should be wired to all slaves with 3 main bus:
 - **CLOCK**: to sync all slave devices. Can also be named SCK, CLK or SCLK (Serial Clock)
 - **MISO** (Master Input Slave Output)
 - **MOSI** (Master Output Slave Input)

Additionnally, each slave should be connected to a specific GPIO output on the microcontroller, for **SS** (Slave Select), also called **CS** (Cable Select).
All slave selectors should be indexed, using 0-based indices. For instance, your first slave cable select output should be named **CS0**.

Most of the time, on ESP32 microcontrollers, SPI connections are using pins 12, 13 and 14, with the first CS0 on pin 15.

Beware, your NFC board needs to be wired to "speak" the SPI Standard.

![Microcontroller wiring](imgs/pinout-chapter2.jpg)

**Warning**: In order for your NFC-Board to work, it also has to be powered on. You can use the VIN of your microcontroller (5V) and your GND to make sure it has the necessary power to work properly.
