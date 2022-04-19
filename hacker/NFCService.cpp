#include "NFCService.h"

NFCService::NFCService() {

}

void NFCService::init() {
  #ifndef ESP8266
    while (!Serial); // for Leonardo/Micro/Zero
  #endif
  Serial.println("Looking for PN532 Chip...");
  nfc.begin();
  uint32_t versiondata = 0;
  uint8_t attempts = 0;
  do {
    nfc.begin();
    versiondata = nfc.getFirmwareVersion();
    attempts++;
    if (!versiondata) {
      Serial.println("Didn't find PN53x board. Reboot device please!");
      delay(500);
    }
  } while (!versiondata && attempts < 3);
  if (!versiondata) {
    Serial.println("Will continue with NFC Disabled");
  } else {
    Serial.print("Found chip PN5");
    Serial.println((versiondata>>24) & 0xFF, HEX);
    Serial.print("Firmware ver. ");
    Serial.print((versiondata>>16) & 0xFF, DEC);
    Serial.print('.');
    Serial.println((versiondata>>8) & 0xFF, DEC);
    // configure board to read RFID tags
    nfc.SAMConfig();
  }
}

bool NFCService::waitForCard() {
  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  return nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
}


void NFCService::dumpCard() {
  Serial.println("Waiting for a NFC card on the reader...");
  waitForCard();
  // Display some basic information about the card
  Serial.println("Found an ISO14443A card");
  Serial.print("  UID Length: ");
  Serial.print(uidLength, DEC);
  Serial.println(" bytes");
  Serial.print("  UID Value: ");
  nfc.PrintHex(uid, uidLength);
  Serial.println("");
  if (uidLength != 4) {
    Serial.println("Ooops ... this doesn't seem to be a Mifare Classic card!");
    return;
  }
  Serial.println("Seems to be a Mifare Classic card (4 byte UID)");

  // Now we try to go through all 16 sectors (each having 4 blocks)
  // authenticating each sector, and then dumping the blocks
  uint8_t block = 0;
  bool blockRead = true;
  for (block = 0; block < 64; block++) {
    if (block % 4 == 0) {
      Serial.print("------------------------Sector ");
      Serial.print(block / 4, DEC);
      Serial.println("-------------------------");
    }
    blockRead = readBlock(block);
    if (!blockRead) {
      return;
    }
  }
}

bool NFCService::readBlock(uint8_t block) {
  if (!authenticateBlock(block)) {
    return false;
  }
  // Authenticated ... we should be able to read the block now
  // Dump the data into the 'data' array
  success = nfc.mifareclassic_ReadDataBlock(block, data);
  if (success) {
    // Read successful
    Serial.print("Block ");
    Serial.print(block, DEC);
    if (block < 10) {
      Serial.print("  ");
    } else {
      Serial.print(" ");
    }
    // Dump the raw data
    nfc.PrintHexChar(data, 16);
  } else {
    // Oops ... something happened
    Serial.print("Block ");
    Serial.print(block, DEC);
    Serial.println(" unable to read this block");
  }
  return success;
}

bool NFCService::authenticateBlock(uint8_t block) {
  bool authenticated = false;
  // Attempt to authenticate with both keys
  authenticated = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, block, MIFARE_KEY_A, keyB);
  if (!authenticated) {
    authenticated = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, block, MIFARE_KEY_A, keyA);
  }
  if (!authenticated) {
    authenticated = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, block, MIFARE_KEY_B, keyB);
  }
  if (!authenticated) {
    authenticated = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, block, MIFARE_KEY_B, keyA);
  }
  if (!authenticated) {
    Serial.print("Block ");
    Serial.print(block, DEC);
    Serial.println(" unable to authenticate");
    return false;
  }
  return true;
}

bool NFCService::writeBlock(uint8_t block, uint8_t* data) {
  if (!authenticateBlock(block)) {
    return false;
  }
  // Authenticated ... we should be able to write the block now
  bool success = nfc.mifareclassic_WriteDataBlock(block, data);
  if (!success) {
    // Oops ... something happened
    Serial.print("Block ");
    Serial.print(block, DEC);
    Serial.println(" unable to write this block");
  }
  return success;
}
