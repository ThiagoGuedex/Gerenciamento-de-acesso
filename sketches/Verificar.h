#ifndef Verificar_h
#include <Arduino.h>

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

#endif
