/**************************************************************************/
/*!
    @file     mifareclassic_memdump.pde
    @author   Adafruit Industries
  @license  BSD (see license.txt)
    This example attempts to dump the contents of a Mifare Classic 1K card
    Note that you need the baud rate to be 115200 because we need to print
  out the data and read from the card at the same time!
    This is an example sketch for the Adafruit PN532 NFC/RFID breakout boards
    This library works with the Adafruit NFC breakout
      ----> https://www.adafruit.com/products/364
    Check out the links above for our tutorials and wiring diagrams
    These chips use SPI or I2C to communicate
    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!
*/
/**************************************************************************/

#include "HeistController.h"
HeistController ctrl = HeistController();
void setup(void) {
  ctrl.init();
}

void loop(void) {
  ctrl.tick();
}
