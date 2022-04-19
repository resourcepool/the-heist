#include <Arduino.h>
#include "utils.h"

#define FIRST_NAME_FIRST_BLOCK 4
#define LAST_NAME_FIRST_BLOCK 8
#define EMPLOYEE_ID_BLOCK 12
#define DATES_BLOCK 13


class NFCService;
class BruteForceService;


class HeistController {
public:
  HeistController();
  void init();
  void tick();
private:
  NFCService* nfcService;
  BruteForceService* bruteForceService;
  uint8_t parsedBytes;
  uint8_t shownBytes;
  bool nfcInitialized = false;
  char cmdBuffer[200];
  void showHelp();
  void parseCommand();
  void processCommand();
  void bruteforce();
  void sendTouch(byte touch);
  void writeNFCBlock();
  void readNFCBlock();
  void resetNFCTag();
  void readTimestamp(uint16_t* date);
};
