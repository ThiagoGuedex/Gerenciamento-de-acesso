#ifndef SalvarFlash_h
#include <Arduino.h>
#include <EEPROM.h>

int writeStringToEEPROM(int addrOffset, const String &strToWrite){
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);

  for (int i = 0; i < len; i++){
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }

  return addrOffset + 1 + len;
}

#endif
