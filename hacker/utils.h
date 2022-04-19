#include <Arduino.h>

bool equals(char* command, char* buffer, uint8_t length);
void getHexBytes(char* buffer, byte* bytes);
void getHexBytes(char* buffer, byte* bytes, uint8_t length);
void getHexBytes(char* buffer, byte* bytes, uint8_t offset, uint8_t length);
uint8_t getHexValue(char c);
uint32_t getTimestamp(uint16_t y, uint16_t m, uint16_t d, uint16_t hours, uint16_t mins, uint16_t secs);
