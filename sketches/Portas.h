#ifndef Portas_h
#include <Arduino.h>

void PortaUm(){
  Serial.println("Faça o login");
  Serial.println("Usuário:");
  while(Serial.available()==0){}
  if(Serial.available()>0){
    String User = Serial.readStringUntil('\n');
    Serial.println("Senha:");
    String Pass = Serial.readStringUntil('\n');
    Serial.println("Porta-1 foi liberada");
    delay(5000);
    Serial.println("Porta-1 foi Trancada\n");
  }
}

void PortaDois(){
  Serial.println("Faça o login");
  Serial.println("Usuário:");
  while(Serial.available()==0){}
  if(Serial.available()>0){
    String User = Serial.readStringUntil('\n');
    Serial.println("Senha:");
    String Pass = Serial.readStringUntil('\n');
    Serial.println("Porta-2 foi liberada");
    delay(5000);
    Serial.println("Porta-2 foi Trancada\n");
  }
}

#endif
