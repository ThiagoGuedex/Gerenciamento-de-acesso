#include <ArduinoJson.h>
#include <EEPROM.h>

int Op;
bool Menu;
String Ports;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  serialMenu();
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
    Serial.println("Erro: Escolha uma opção. Deve ser um número de 1 a 5\n");
    reset();
    break;
    }
  }
}

void Cadastro(){
  Serial.println("Nome de usuário:");
  while (Serial.available()==0){}
  
  if(Serial.available()>0){
    while (Serial.available()==0){}
    String Username = Serial.readStringUntil('\n');
    Serial.println(Username);
    Serial.println("Senha:");
    
    if(Username!=""){
      while (Serial.available()==0){}
      String Password = Serial.readStringUntil('\n');
      Serial.println(Password);
      Serial.println("Escolha o tipo de conta:\n1. Administrador\n2. Comum");
      if(Password!=""){
        while (Serial.available()==0){}
        String Option = Serial.readStringUntil('\n');
        if(Option=="1"){
          String Users = Json(Username,Password,true);
          writeStringToEEPROM(0, Users);
          Serial.println();
        }
        else if(Option=="2"){
          String Users = Json(Username,Password,false);
          writeStringToEEPROM(0, Users);
          Serial.println();
        }
        else{
          Serial.println("Erro: Escolha uma opção. Deve ser 1 ou 2\n");
        }
      } 
    } 
  }
}

void Usuarios(){
  String Users = Usernames();
  Serial.println(Users);
  Serial.println("");
}

void Eventos(){
 Serial.println("Faça o login");
 Serial.println("Usuário:");
 while(Serial.available()==0){}

 if(Serial.available()>0){
  String Username = Serial.readStringUntil('\n'); 

  if(Username==Usernames()){
    Serial.println("Senha:");
    while(Serial.available()==0){}
    String Password = Serial.readStringUntil('\n');

    if(Password==Senhas()){
      if(Adms()){
        String EventA = readStringFromEEPROM(150);
        String EventB = readStringFromEEPROM(200);
        Serial.println(EventA);
        Serial.println(EventB);
        Serial.println("");
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

void PortaUm(){
  Serial.println("Faça o login");
  Serial.println("Usuário:");
  while(Serial.available()==0){}

  if(Serial.available()>0){
    String Username = Serial.readStringUntil('\n');
    Serial.println("Senha:");

    if(Username==Usernames()){
      while(Serial.available()==0){}
      String Password = Serial.readStringUntil('\n');

      if(Password==Senhas()){
        String PortA = "Porta 1 foi liberada";
        String PortB = "Porta 1 foi Trancada";
        writeStringToEEPROM(150, PortA);
        digitalWrite(2, HIGH);
        Serial.println(PortA);
        delay(5000);
        writeStringToEEPROM(200, PortB);
        digitalWrite(2, LOW);
        Serial.println(PortB);
        Serial.println("");
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

void PortaDois(){
  Serial.println("Faça o login");
  Serial.println("Usuário:");
  while(Serial.available()==0){}

  if(Serial.available()>0){
    String Username = Serial.readStringUntil('\n');
    Serial.println("Senha:");

    if(Username==Usernames()){
      while(Serial.available()==0){}
      String Password = Serial.readStringUntil('\n');

      if(Password==Senhas()){
        String PortA = "Porta 2 foi liberada";
        String PortB = "Porta 2 foi Trancada";
        writeStringToEEPROM(150, PortA);
        digitalWrite(3, HIGH);
        Serial.println(PortA);
        delay(5000);
        writeStringToEEPROM(200, PortB);
        digitalWrite(3, LOW);
        Serial.println(PortB);
        Serial.println("");
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

void reset(){
  Menu = false;
  Op = 0;
  while(Serial.available() > 0){Serial.read();}
}

int Verificar(){
   String Option = Serial.readStringUntil('\n');
    if(Option.length()!=1){
     return 0;
    }
    else {
      if(isAlpha(Option.charAt(0))){
        return 0;
      }
      else{
        if(isDigit(Option.charAt(0))){
          return Option.toInt(); 
        }
        else{
          return 0;
        }
      }
   }
}

int writeStringToEEPROM(int addrOffset, const String &strToWrite){
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);

  for (int i = 0; i < len; i++){
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }

  return addrOffset + 1 + len;
}

String readStringFromEEPROM(int addrOffset){
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++){
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0'; 
  return String(data);
}

String Json(String Username, String Password, bool Adm){
    String JsonDoc;
    String OldJsonDoc;
    String NewJsonDoc;
    StaticJsonDocument<200> doc;

    doc["User"] = Username;
    doc["Senha"] = Password;
    doc["Adm"] = Adm;

    OldJsonDoc = readStringFromEEPROM(0);
    serializeJson(doc, JsonDoc);
    NewJsonDoc = OldJsonDoc.concat(JsonDoc);
    Serial.println(NewJsonDoc);
    return JsonDoc;
}

String Usernames(){
    StaticJsonDocument<200> doc;
    String json = readStringFromEEPROM(0);

    DeserializationError error = deserializeJson(doc, json);
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
        }

    String Users = doc["User"];
    return Users;
}

String Senhas(){
    StaticJsonDocument<200> doc;
    String json = readStringFromEEPROM(0);

    DeserializationError error = deserializeJson(doc, json);
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
        }

    String Senhas = doc["Senha"];
    return Senhas;
}

bool Adms(){
    StaticJsonDocument<200> doc;
    String json = readStringFromEEPROM(0);

    DeserializationError error = deserializeJson(doc, json);
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
        }

    bool Adms = doc["Adm"];
    return Adms;
}
