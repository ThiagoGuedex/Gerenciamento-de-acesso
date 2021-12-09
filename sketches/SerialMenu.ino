int Op;
bool View;
bool Menu;

void setup() {
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
    Op = verify();
    switch(Op){
    case 1:
    Serial.println("1\n");
    reset();
    break;
    case 2:
    Serial.println("2\n");
    reset();
    break;
    case 3:
    Serial.println("3\n");
    reset();
    break;
    case 4:
    Serial.println("4\n");
    reset();
    break;
    case 5:
    Serial.println("5\n");
    reset();
    break;
    default:
    Serial.println("Erro: Escolha uma opção deve ser um número de 1 a 5\n");
    reset();
    break;
    }
  }
}

void reset(){
  Menu = false;
  Op = 0;
  while(Serial.available() > 0){Serial.read();}
}

int verify(){
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
