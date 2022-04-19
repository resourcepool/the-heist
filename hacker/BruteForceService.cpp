#include "BruteForceService.h"

BruteForceService::BruteForceService() {
}


/**
 * TODO STEP 1 you need to implement this method
 * You can test your code by using the hacker "send-key" command.
 * If you succeed, the command will call the simulateButtonPressed method with the digit you provide.
 */
void BruteForceService::simulateButtonPressed(uint8_t col, uint8_t row) {
        // TODO STEP 1 you need to implement this method
        // we want to copy the state of the column 'col' to the row 'row' in real time.
        // so while column col is HIGH (idle), we wait...
        // as soon as column 'col' is LOW, we set the row 'row' to LOW state
        // then we wait while column 'col' is still LOW
        // as soon as column 'col' is HIGH, we set back the row 'row' to HIGH state
        // and the cycle will be complete
        // last thing but not least, simulate the fact that you have released your finger from the key.
}

/**
 * TODO STEP 2 You need to implement this method
 * This method is the bruteforce algorithm.
 * Remember: we want to perform a bruteforce attack, and we also have high assumptions that the first digit is a 3.
 */
void BruteForceService::startBruteforce() {
        Serial.println("Bruteforce started");
        // TODO STEP 2 create your algorithm here!
        Serial.println("Bruteforce finished");
}



/**
 * Nothing to change here!
 */
void BruteForceService::releaseFinger() {
    simulateEmptyColumn(COL0);
    simulateEmptyColumn(COL1);
    simulateEmptyColumn(COL2);
}


/*
 * Nothing to change here!
 */
void BruteForceService::setupPinForNeutralAction() {
        pinMode(ROW0, INPUT_PULLUP);
        pinMode(ROW1, INPUT_PULLUP);
        pinMode(ROW2, INPUT_PULLUP);
        pinMode(ROW3, INPUT_PULLUP);
        pinMode(COL0, INPUT_PULLUP);
        pinMode(COL1, INPUT_PULLUP);
        pinMode(COL2, INPUT_PULLUP);
}

/*
 * Nothing to change here!
 */
void BruteForceService::setupPinForBruteforce() {
        // configure the esp32 to read on column pins and write on ROWe pins.
        // a few hints:
        // there are 3 kinds of state for a pin : OUTPUT, INPUT and INPUT_PULLUP.
        // OUTPUT is straight forward.
        // INPUT and INPUT_PULLUP can be a bit trickier. To keep it simple: use INPUT_PULLUP.
        // for example if I want to set up the digital pin mapped to ROWE 0 to be an input (something that will be able to read), the code would be:
        // pinMode(ROW0, INPUT_PULLUP)
        // you can find the mapping of the pins in BruteForceService.h
        // By the way, the briefcase expects each line to be in a HIGH state by default when no key is pressed. A wise use of digitalWrite function should be made.
        pinMode(SUCCESS_PIN, INPUT_PULLUP);

        // INPUT_PULLUP to avoid electrical issues
        pinMode(COL0, INPUT_PULLUP);
        pinMode(COL1, INPUT_PULLUP);
        pinMode(COL2, INPUT_PULLUP);

        pinMode(ROW0, OUTPUT);
        pinMode(ROW1, OUTPUT);
        pinMode(ROW2, OUTPUT);
        pinMode(ROW3, OUTPUT);

        // The default state of a line is HIGH.
        digitalWrite(ROW0, HIGH);
        digitalWrite(ROW1, HIGH);
        digitalWrite(ROW2, HIGH);
        digitalWrite(ROW3, HIGH);

}

/**
 * Nothing to change here!
 * Returns true if briefcase is currently reading all the rows for the provided column, false otherwise.
 */
bool BruteForceService::isBrowsingColumn(uint8_t col) {
    return GPIO.in >> col & 0x1;
}

/**
 * Nothing to change here!
 * This method will wait for a column input to become idle (<=> to be set to HIGH)
 */
void BruteForceService::blockWhileColumnIdle(uint8_t col) {
    while (isBrowsingColumn(col)) {}
}

/**
 * Nothing to change here!
 * This method will wait for a column input to become active (<=> to be set to LOW)
 */
void BruteForceService::blockWhileColumnActive(uint8_t col) {
    while (!isBrowsingColumn(col)) {}
}

/**
 * Nothing to change here!
 * Set Digital Output GPIO to high or low
 * @param row the target row PIN
 * @param high true if high, false if low
 * Note: this uses registers to make the process faster.
 * Usually, people would use digitalWrite(PIN, HIGH|LOW); instead
 */
void BruteForceService::fastDigitalWrite(uint8_t row, bool high) {
    if (high) {
        GPIO.out_w1ts = ((uint32_t)1 << row);
    } else {
        GPIO.out_w1tc = ((uint32_t)1 << row);
    }
}


/**
 * Nothing to change here!
 * Browse column with all rows inactive (<=> not pressed)
 */
void BruteForceService::simulateEmptyColumn(uint8_t col) {
    blockWhileColumnIdle(col);
    blockWhileColumnActive(col);
}


/**
 * Nothing to change here!
 * This method maps keys (0 to 9 as digits, 10 as "*" and 11 as "#") to rows and columns.
 */
void BruteForceService::enterKey(uint8_t key) {
        // quite an easy one, just map the requested key to the correct parameters for simulateButtonPress function.
        // a switch case should be enough
        // reminder: if key = 0, it means button 0. same thing for 1 to 9. if key = 10 it's for * key. You don't need to map the # key.

        switch (key) {
        case 0: // button 0 -> col1 lin3
                simulateButtonPressed(COL1, ROW3);
                break;
        case 1: // button 1
                simulateButtonPressed(COL0, ROW0);
                break;
        case 2: // button 2
                simulateButtonPressed(COL1, ROW0);
                break;
        case 3: // button 3
                simulateButtonPressed(COL2, ROW0);
                break;
        case 4: // button 4
                simulateButtonPressed(COL0, ROW1);
                break;
        case 5: // button 5
                simulateButtonPressed(COL1, ROW1);
                break;
        case 6: // button 6
                simulateButtonPressed(COL2, ROW1);
                break;
        case 7: // button 7
                simulateButtonPressed(COL0, ROW2);
                break;
        case 8: // button 8
                simulateButtonPressed(COL1, ROW2);
                break;
        case 9: // button 9
                simulateButtonPressed(COL2, ROW2);
                break;
        case 10: // button *
                simulateButtonPressed(COL0, ROW3);
                break;
        case 11: // button #
                simulateButtonPressed(COL2, ROW3);
                break;
        }
}

/**
 * Nothing to change here!
 * This method will enter each digit of the provided PIN.
 * Implementation is recursive to make things easier.
 * if code is 1234, must simulate 1-2-3-4
 */
void BruteForceService::enterPIN(int pin) {
        if (pin >= 10) {
            enterPIN(pin / 10);
        }
        int digit = pin % 10;
        enterKey(digit);
}
