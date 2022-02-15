#include "btn.h"

btn::btn(byte pin){
  this->pin = pin;
}
btnDouble::btnDouble(byte pin){
  this->pin = pin;
}
bool btn::checkStatusSensor(){
  if(flag_btn == 0)
  if (digitalRead(pin) == staPress){
    Serial.println("get1");
    if(flag_btn == 0){
      timer_btn = millis();
      flag_btn = 1;
    }
  }   
  if (flag_btn == 1){
    if (digitalRead(pin) != staPress){
      Serial.println("get2");
      if(millis() - timer_btn <= time_btn){
        Serial.println("Get3");
        flag_btn = 0;
        return 1;
        //flag_press = 1;
      }else{
        flag_btn = 0;
        return 0;
      }
    }
  }
  return 0;
}
bool btn::checkStatusBtn(){
  if(flag_press == 0){
    if(flag_btn == 0)
    if (digitalRead(pin) == staPress){
      Serial.println("get1");
      if(flag_btn == 0){
        timer_btn = millis();
        timer_press = millis();
        flag_btn = 1;
      }
    }   
    if (flag_btn == 1){
      if (digitalRead(pin) != staPress){
        Serial.println("get2");
        if(millis() - timer_btn <= time_btn){
          Serial.println("Get3");
          flag_btn = 0;
          return 1;
    
        }else{
          flag_btn = 0;
          return 0;
        }
      }
      if(digitalRead(pin) == staPress){
        if(millis() - timer_press >= time_press){
          Serial.println("press on");
          flag_press = 1;
        }
      }
    }
  }
  if(flag_press == 1){
    Serial.println("press mode");
    if(digitalRead(pin) == staPress){
      if(millis() - timer_re >= time_re){
        timer_re = millis();
        return 1;
      }
    }else{
      Serial.println("press off");
      flag_press = 0;
      flag_btn = 0;
    }
  }
  return 0;
}
byte btnDouble::checkStatusBtn(){
  if(flag_press == 0){
    if(flag_btn == 0)
    if (digitalRead(pin) == staPress){
      Serial.println("get1");
      if(flag_btn == 0){
        timer_btn = millis();
        timer_press = millis();
        flag_btn = 1;
      }
    }   
    if (flag_btn == 1){
      if(digitalRead(pin) != staPress){
        Serial.println("get2");
        if(millis() - timer_btn <= time_btn){
          Serial.println("Get3");
          flag_btn = 0;
          if(flag == 0){
            flag++;
            timer_wait = millis();
            Serial.println(flag);
          }else{
            flag++;
            Serial.println(flag);
          }
        }else{
          flag_btn = 0;
          Serial.println("return0");
          return 0;
        }
      }
      if(digitalRead(pin) == staPress){
        if(millis() - timer_press >= time_press){
          Serial.println("press on");
          flag_press = 1;
        }
      }
    }
    if(flag == 1)
    if(millis() - timer_wait >= time_wait){
      flag = 0;
      flag_btn = 0;Serial.println("return0");
      return 1;
    }
    if(flag == 2){
      Serial.println("return");
      flag = 0;
      flag_btn = 0;
      return 2;
    }
  
    return 0;
  }
  if(flag_press ==1){
    Serial.println("press mode");
    if(digitalRead(pin) == staPress){
      if(millis() - timer_re >= time_re){
        timer_re = millis();
        return 1;
      }
    }else{
      Serial.println("press off");
      flag_press = 0;
      flag_btn = 0;
    }
  }
}
