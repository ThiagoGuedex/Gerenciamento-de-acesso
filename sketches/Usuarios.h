#ifndef Usuarios_h
#include <Arduino.h>
#include "LerFlash.h"
#include "SalvarFlash.h"

void Usuarios(){
  int eepromOffset = 0;

  // Writing
  String str1 = "Thiago";
  String str2 = "Guedes";
  String str3 = "Tui.083029";
  
  // Criar um offset a partir 
  int str1AddrOffset = writeStringToEEPROM(eepromOffset, str1);
  int str2AddrOffset = writeStringToEEPROM(str1AddrOffset, str2);
  writeStringToEEPROM(str2AddrOffset, str3);

  // Reading
  String newStr1;
  String newStr2;
  String newStr3;

  int newStr1AddrOffset = readStringFromEEPROM(eepromOffset, &newStr1);
  int newStr2AddrOffset = readStringFromEEPROM(newStr1AddrOffset, &newStr2);
  readStringFromEEPROM(newStr2AddrOffset, &newStr3);
  
  Serial.println(newStr1);
  Serial.println(newStr2);
  Serial.println(newStr3); 
  Serial.println("");
}

#endif
