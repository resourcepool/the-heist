#include "utils.h"

bool equals(char* str1, char* str2, uint8_t length) {
  for (uint8_t i = 0; i < length; i++) {
    if (str1[i] != str2[i]) {
      return false;
    }
  }
  return true;
}

uint32_t getTimestamp(uint16_t y, uint16_t m, uint16_t d, uint16_t hours, uint16_t mins, uint16_t secs) {
  uint32_t t;

  //January and February are counted as months 13 and 14 of the previous year
  if(m <= 2) {
     m += 12;
     y -= 1;
  }

  //Convert years to days
  t = (365 * y) + (y / 4) - (y / 100) + (y / 400);
  //Convert months to days
  t += (30 * m) + (3 * (m + 1) / 5) + d;
  //Unix time starts on January 1st, 1970
  t -= 719561;
  //Convert days to seconds
  t *= 86400;
  //Add hours, minutes and seconds
  t += (3600 * hours) + (60 * mins) + secs;

  //Return Unix time
  return t;
}

void getHexBytes(char* buffer, byte* bytes) {
  getHexBytes(buffer, bytes, 0, strlen(buffer));
}

void getHexBytes(char* buffer, byte* bytes, uint8_t len) {
  getHexBytes(buffer, bytes, 0, len);
}

void getHexBytes(char* buffer, byte* bytes, uint8_t offset, uint8_t len) {
  char c;
  bool startByte = false;
  uint8_t parsedBytes = 0;
  for (uint16_t i = 0; i < strlen(buffer); i++) {
    c = buffer[i];
    uint8_t hexValue = getHexValue(c);
    if (parsedBytes == len) {
      return;
    }
    if (hexValue < 16) {
      if (!startByte) {
        startByte = true;
        bytes[parsedBytes] = hexValue * 16;
      } else {
        bytes[parsedBytes] += hexValue;
        if (offset > 0) {
          offset--;
        } else {
          parsedBytes++;  
        }
        startByte = false;
      }
    }
  }
}

uint8_t getHexValue(char c) {
  // (0-ASCII)
  if (c < 48) {
    return -1;
  }
  // (9-ASCII)
  if (c <= 57) {
    return c - 48;
  }
  // (A-ASCII)
  if (c < 65) {
    return -1;
  }
  // (F-ASCII)
  if (c <= 70) {
    return c - 55;
  }
  // (a-ASCII)
  if (c < 97) {
    return -1;
  }
  if (c <= 102) {
    return c - 87;
  }
  return -1;
}
