#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_PN532.h>

#define PN532_SCK 14
#define PN532_MOSI 13
#define PN532_SS 15
#define PN532_MISO 12
#define MIFARE_KEY_A 0
#define MIFARE_KEY_B 1


class NFCService {
public:
  NFCService();
  void init();
  void reset();
  bool waitForCard();
  void dumpCard();
  bool readBlock(uint8_t block);
  bool writeBlock(uint8_t block, uint8_t* data);
private:
  bool authenticateBlock(uint8_t block);
  Adafruit_PN532 nfc = Adafruit_PN532(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);
  uint8_t success;                          // Flag to check if there was an error with the PN532
  uint8_t uid[7] = { 0, 0, 0, 0, 0, 0, 0 }; // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  uint8_t data[16];                         // Array to store block data during reads
  uint8_t keyA[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // Keyb on NDEF and Mifare Classic should be the same
  uint8_t keyB[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }; // Keyb on NDEF and Mifare Classic should be the same

};
