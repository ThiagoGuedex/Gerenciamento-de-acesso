#ifndef Eventos_h
#include <Arduino.h>

void Eventos(){
 Serial.println("Faça o login");
 Serial.println("Usuário:");
 while(Serial.available()==0){}
 if(Serial.available()>0){
  String User = Serial.readStringUntil('n'); 
  if(User!=""){
    Serial.println("Senha:");
    while(Serial.available()==0){}
    String Pass = Serial.readStringUntil('\n');
    if(Pass!=""){
      String ops = "ADM";
      if(ops=="ADM"){
        if(true){
          Serial.println("A porta 1 está fechada");
          Serial.println("A porta 2 está aberta\n");
          }
        else if(false){
          Serial.println("A porta 1 está aberta");
          Serial.println("A porta 2 está fechada\n");
          }
        else if(false){
          Serial.println("As duas portas estão abertas\n");
          }
        else if(false){
          Serial.println("As duas portas estão fechadas\n");
          }
       }
       else{
        Serial.println("Apenas administradores\n");
        }
      }
      else{
        Serial.println("Senha inválida");
        }
    }
    else{
      Serial.println("Usuário inválido");
    }
  } 
}

#endif
