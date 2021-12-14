#ifndef Cadastro_h
#include <Arduino.h>
#include <ArduinoJson.h>
//#include "SalvarFlash.h"

void Cadastro(){
  Serial.println("Nome de usuário:");
  while (Serial.available()==0){}
  if(Serial.available()>0){
    while (Serial.available()==0){}
    String Username = Serial.readStringUntil('\n');
    //writeStringToEEPROM(0, Username);
    Serial.println("Senha:");
    
    if(Username!=""){
      while (Serial.available()==0){}
      String Password = Serial.readStringUntil('\n');
      //writeStringToEEPROM(2, Password);
      Serial.println("Escolha o tipo de conta:\n1. Administrador\n2. Comum\n");
      
      if(Password!=""){
        while (Serial.available()==0){}
        String cont = Serial.readStringUntil('\n');
        
        if(cont=="1"){
          String ops = "ADM";
          //writeStringToEEPROM(2, ops);
        }
        
        else if(cont=="2"){
          String ops = "Normal";
          //writeStringToEEPROM(2, ops);
        }
      } 
    } 
  }
}

#endif
