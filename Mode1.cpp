#include "Mode1.h"

void MODE1::setup(VAREFFECT &varEffect, byte adrEEPROM, byte &pageFocus, LiquidCrystal_I2C & lcd){
  this->varEffect = &varEffect;
  this->adrEEPROM = adrEEPROM;
  pageMode.setup("MODE1",pageList,pageLine,adrEEPROM,pageFocus,lcd);
}
void MODE1::runEffect(){
  if((varEffect->ss1 == 1) || (varEffect->ss2 == 1)){
    varEffect->ss1 = 0;
    varEffect->ss2 = 0;
    if(varEffect->flag_run1 == 0){
      Serial.println("strart");
      Serial.println(timeOff);
      varEffect->flag_run1 = 1;
      varEffect->count = 0;
      varEffect->timer_Off1 = millis();
    }
  }
  if(varEffect->flag_run1 == 1){
    switch(effect){
      case 1:{runEffect1();break;}   
      case 2:{runEffect2();break;}    
      case 3:{runEffect3();break;}   
      case 4:{runEffect4();break;}   
      default:{runEffect5();break;}   
    }
    if(millis() - varEffect->timer_Off1 > (timeOff*1000)){
      Serial.println("off");
      varEffect->flag_run1 = 0;
      varEffect->ss1 = 0;
      varEffect->ss2 = 0;
      FastLED.clear();
      FastLED.show();
    }
  }
}
void MODE1::runEffect1(){
  if(millis() - varEffect->timer_run1 >= varEffect->speed*1000){
    fadeToBlackBy( varEffect->adr, varEffect->num, 30);
    int pos = beatsin16( 13, 0, varEffect->num-1 );
    *(varEffect->adr + pos) += varEffect->getColor();
    varEffect->timer_run1 = millis();
    FastLED.show(); 
  }
}
void MODE1::runEffect2(){//confetti
  if(millis() - varEffect->timer_run1 >= varEffect->speed*1000){
    fadeToBlackBy(varEffect->adr, varEffect->num, 40);
    int pos = random(0,varEffect->num);
    *(varEffect->adr + pos) += varEffect->getColor();
    varEffect->timer_run1 = millis();  
    FastLED.show();
  }
}
void MODE1::runEffect3(){
  if(millis()- varEffect->timer_run1 >= varEffect->speed*1000){
    fadeToBlackBy(varEffect->adr, varEffect->num,60);
    *(varEffect->adr + varEffect->count) = varEffect->getColor();
    for(int i = varEffect->num/2; i <varEffect->num;++i)
      *(varEffect->adr + i) = *(varEffect->adr - 1 + varEffect->num/2-(i - varEffect->num/2));
    FastLED.show();
    varEffect->count++;
    if(varEffect->count >= varEffect->num/2) varEffect->count = 0;
    varEffect->timer_run1 = millis();
  }
}
void MODE1::runEffect4(){
  if(millis()- varEffect->timer_run1 >= varEffect->speed*1000){
    if(varEffect->count < varEffect->num){
      *(varEffect->adr + varEffect->count) = varEffect->getColor();
      FastLED.show();
      varEffect->count++;
    }
    varEffect->timer_run1 = millis();
  }
}
void MODE1::runEffect5(){
  if(millis()- varEffect->timer_run1 >= varEffect->speed*1000){
    if(varEffect->count < varEffect->num){
      *(varEffect->adr + varEffect->count) = varEffect->getColor();
      FastLED.show();
      varEffect->count++;
    }
    else{
      fadeToBlackBy(varEffect->adr, varEffect->num,40);
      uint32_t t = *(varEffect->adr);
      if(t == 0)
        varEffect->count = 0;
      FastLED.show();
    }
    varEffect->timer_run1 = millis();
  }
}
