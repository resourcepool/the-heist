# The Heist: Crack the safe

Welcome to the handson workshop **The Heist**.

Before you get to the workshop, please follow the following guidelines.

## Requirements
 * Compatible with Windows 8+ / Mac OSX / Linux
 * 1 USB Port available
 * Internet connection

## Setup

### Install Arduino
Make sure Arduino is installed on your computer [https://www.arduino.cc/en/main/software](https://www.arduino.cc/en/main/software)

### Install ESP32 Espressif using Arduino IDE Boards Manager

Stable release link: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`   

- Start Arduino and open Preferences window.
- Enter one of the release links above into *Additional Board Manager URLs* field. You can add multiple URLs, separating them with commas.
- Open Boards Manager from Tools > Board menu and install *esp32* platform (and don't forget to select your ESP32 board from Tools > Board menu after installation).
- Restart Arduino

### Clone this repository
`git clone https://github.com/resourcepool/the-heist`

### Add Arduino libraries

Copy the content of the **libraries** directory to your **Arduino/libraries** folder.
* Windows: should be in `My Documents/Arduino/libraries`
* Linux: should be in the `libraries` subfolder of wherever you placed arduino
* Mac OS: should be in the `Documents/Arduino/libraries` folder

Restart Arduino IDE.

### Linux

Additionally, if you are on Linux you need to follow theses extra steps :
* install pyserial with pip & python3 :
    * if pip is not installed : `sudo apt install python-is-python3`
    * installez pyserial `pip install pyserial`
* enter the following command and reboot your computer:
  `sudo usermod -aG dialout $USER`


## Game guide

The game step-by-step guide will be available here as soon as the game starts:  
[https://resourcepool.github.io/the-heist/index.html](https://resourcepool.github.io/the-heist/index.html)

That's it! See you soon!
