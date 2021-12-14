#ifndef Menu_h
#include <Arduino.h>
#include "Verificar.h"
#include "Cadastro.h"
#include "Usuarios.h"
#include "Eventos.h"
#include "Portas.h"

int Op;
bool Menu;

void reset(){
  Menu = false;
  Op = 0;
  while(Serial.available() > 0){Serial.read();}
}

void topMenu(){
    if(!Menu){
      Serial.println("Escolha uma opção:");
      Serial.println("1. Cadastrar usuário\n2. Usuários cadastrados\n3. Eventos\n4. Liberar porta(1)\n5. Liberar porta(2)\n");
      Menu = !Menu;
      }
}

void serialMenu(){
  topMenu();
  if(Serial.available()>0){
    Op = Verificar();
    switch(Op){
    case 1:
    Cadastro();
    reset();
    break;
    case 2:
    Serial.println("Usuários cadastrados:");
    Usuarios();
    reset();
    break;
    case 3:
    Eventos();
    reset();
    break;
    case 4:
    PortaUm();
    reset();
    break;
    case 5:
    PortaDois();
    reset();
    break;
    default:
    Serial.println("Erro: Escolha uma opção deve ser um número de 1 a 5\n");
    reset();
    break;
    }
  }
}
#endif
