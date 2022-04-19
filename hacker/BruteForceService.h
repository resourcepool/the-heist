#include <Arduino.h>

#define ROW0 5
#define ROW1 18
#define ROW2 19
#define ROW3 21
#define COL0 27
#define COL1 26
#define COL2 25

#define SUCCESS_PIN 23

class BruteForceService {

public:

BruteForceService();

// for step 2, must call sendTouch(1); sendTouch(10); in a loop
// for step 3, must start a loop, trying every possible password, until you find the good one.
// don't forget to implement a way to find when the password is the correct one,
// if you simulate another keystroke after the briefcase is open, it will lock itself again.
void startBruteforce();

void enterKey(uint8_t key);
void setupPinForBruteforce();
void setupPinForNeutralAction();

private:
void fastDigitalWrite(uint8_t row, bool high);
bool isBrowsingColumn(uint8_t col);
void blockWhileColumnIdle(uint8_t col);
void blockWhileColumnActive(uint8_t col);
void releaseFinger();
void simulateButtonPressed(uint8_t col, uint8_t row);
void simulateEmptyColumn(uint8_t col);
void enterPIN(int code);

};
