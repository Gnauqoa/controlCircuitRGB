#include "Mode2.h"

void MODE2::setup(VAREFFECT &varEffect, byte adrEEPROM, byte &pageFocus, LiquidCrystal_I2C & lcd){
  this->varEffect = &varEffect;
  this->adrEEPROM = adrEEPROM;
  pageMode.setup("MODE2",pageList,pageLine,adrEEPROM,pageFocus,lcd);
}
void MODE2::runEffect1(){
  unsigned long time = varEffect->speed*1000;
  FastLED.setBrightness(map(varEffect->brightness,100,0,255,0));
  if(varEffect->ss1 == 1){
  varEffect->ss1 = 0;
  if((varEffect->flag_run2 == 1) && (varEffect->flag_run1 == 0)){
    varEffect->flag_run12 = 1;
  }
  else{
    if(varEffect->flag_run1 == 0){
      varEffect->flag_off1 = 0;
      varEffect->flag_run1 = 1;
      varEffect->timer_run1 = millis();
      varEffect->num1 = varEffect->num;
      varEffect->count1 = 1;
    }
  }
  }
  if(varEffect->ss2 == 1){
  varEffect->ss2 = 0;
  if((varEffect->flag_run1 == 1) && (varEffect->flag_run2 == 0)){
    varEffect->flag_run12 = 1;
  }
  else{
    if(varEffect->flag_run2 == 0){
      varEffect->flag_off2 = 0;
      varEffect->flag_run2 = 1;
      varEffect->timer_run2 = millis();
      varEffect->num2 = 1;
      varEffect->count2 = varEffect->num;
    }
  }
  } 
  if(varEffect->flag_run12 == 1){
  if(varEffect->flag_run2 == 1){
    if(varEffect->flag_set == 0){ 
      if(varEffect->count2 <= varEffect->num/2){
        for(byte i = varEffect->num/2; i >= 1; --i){
          *(varEffect->adr + i-1) = varEffect->getColor(0);
        }
        varEffect->count2 = varEffect->num/2 +1;
        FastLED.show(); 
      }
      varEffect->num2 = varEffect->num/2;
      varEffect->flag_off2 = 0;
      
      varEffect->flag_off1 = 0;
      varEffect->flag_run1 = 1;
      varEffect->timer_run1 = millis();
      varEffect->num1 = varEffect->num/2;
      varEffect->count1 = 1;     
      varEffect->flag_set = 1;
    }
  }
  if(varEffect->flag_run1 == 1){
    if(varEffect->flag_set == 0){
    
      if(varEffect->count1 > varEffect->num/2){
        for(byte i = varEffect->num/2+1; i <= varEffect->count1; ++i){
          *(varEffect->adr + i-1) = varEffect->getColor(0);
          
        }
        varEffect->count1 = varEffect->num/2;
        FastLED.show(); 
      }
      varEffect->num1 = varEffect->num/2;
      varEffect->flag_off1 = 0;
      
      varEffect->flag_off2 = 0;
      varEffect->flag_run2 = 1;
      varEffect->timer_run2 = millis();
      varEffect->num2 = varEffect->num/2;
      varEffect->count2 = varEffect->num ;
      
      
      varEffect->flag_set = 1;
    }
  }
  if((varEffect->flag_done1 == 1) && (varEffect->flag_done2 == 1)){
      varEffect->flag_run12 = 0;
      varEffect->flag_set = 0;
      varEffect->flag_done1 = 0;
      varEffect->flag_done2 = 0;
  }
  }
  if(varEffect->flag_run1 == 1){
  if((varEffect->count1 <= varEffect->num1) && (varEffect->flag_off1 == 0))   
  if(millis() - varEffect->timer_run1 >= time){
    if(varEffect->count1 + step > varEffect->num1){
      for(byte i = varEffect->count1; i<= varEffect->num1; ++i)
        *(varEffect->adr + i - 1) = varEffect->getColor(varEffect->color);          
      varEffect->count1 = varEffect->num1 + 1;
    }
    else{
      for(byte i = 0; i < step;++i)
        *(varEffect->adr + varEffect->count1 + i - 1) = varEffect->getColor(varEffect->color);     
      varEffect->count1 += step;
    }
    varEffect->timer_run1 = millis();
    if(varEffect->count1 > varEffect->num1){
      varEffect->count1--;
      if(varEffect->flag_run12 == 1){
        varEffect->flag_done1 = 1;
      }
      else{
        varEffect->timer_Off1 = millis();
        varEffect->timer_Off2 = millis();
        varEffect->flag_off1 = 1;
        varEffect->flag_off2 = 1;
      }
    }
    FastLED.show();
  }
  if(varEffect->flag_run12 == 0)
  if((varEffect->count1 <= varEffect->num1) && (varEffect->flag_off1 == 1)){
    if(millis()- (varEffect->timer_Off1) >= (timeOff)*1000){
      if(varEffect->count1 >= 1){
        
        if(millis() - varEffect->timer_run1 >= time){
          varEffect->timer_run1 = millis();
          if(varEffect->count1 - step < 1){
            for(byte i = 0; i <= varEffect->count1; ++i)
              *(varEffect->adr + varEffect->num1 - i - 1) = varEffect->getColor(0); 
            varEffect->count1 = 0;
          }
          else{
            for(byte i = 0; i < step; ++i)
              *(varEffect->adr + varEffect->num1 - (varEffect->count1 - i) - 1) = varEffect->getColor(0);
            varEffect->count1 -= step;
          }
          FastLED.show();
          
        }
      }
      else{
        varEffect->flag_off1 = 0;
        varEffect->flag_run1 = 0;
     
        varEffect->count1 = 1;
      }
    }
  }
  }
  if(varEffect->flag_run2 == 1){
  if((varEffect->count2 > varEffect->num2) && (varEffect->flag_off2 == 0))   
  if(millis() - varEffect->timer_run2 >= time){ 
    if(varEffect->count2 - step < varEffect->num2){
      for(byte i = varEffect->num2; i <= varEffect->count2; ++i)
        *(varEffect->adr + i - 1) = varEffect->getColor(varEffect->color);
      varEffect->count2 = varEffect->num2;
  
    }
    else{
      for(byte i = 0; i < step; ++i)
        *(varEffect->adr +  varEffect->count2 - i - 1) = varEffect->getColor(varEffect->color);
      varEffect->count2 -= step;
   
    }
    varEffect->timer_run2 = millis();
    if(varEffect->count2 == varEffect->num2){
      if(varEffect->flag_run12 == 1){
        varEffect->flag_done2 = 1;
      }
      else{
        varEffect->timer_Off2 = millis();
        varEffect->timer_Off1 = millis();
        varEffect->flag_off2 = 1;
        varEffect->flag_off1 = 1;
      }
    }
    FastLED.show();
  }
  if(varEffect->flag_run12 == 0)
  if((varEffect->count2 >= varEffect->num2) && (varEffect->flag_off2 == 1)){
  
  
    if(millis()- (varEffect->timer_Off2) >= (timeOff)*1000){
  
      if(varEffect->count2 <= varEffect->num){
        
        if(millis() - varEffect->timer_run2 >= time){
   
          if(varEffect->count2 + step > varEffect->num){
            for(byte i = 0; i <= varEffect->num-varEffect->count2; ++i){
              *(varEffect->adr + varEffect->num-(varEffect->count2 + i)) = varEffect->getColor(0);
         
            }
            varEffect->count2 =  varEffect->num + 1;
       
          }
          else{
            for(byte i = 0; i < step; ++i)
              *(varEffect->adr + varEffect->num - (varEffect->count2 + i - varEffect->num2) - 1) = varEffect->getColor(0);
            varEffect->count2 += step;
        
          }
          varEffect->timer_run2 = millis();
          FastLED.show();
    
        }
      }
      else{
        varEffect->flag_off2 = 0;
     
        varEffect->flag_run2 = 0;
        varEffect->count2 = 0;
      }
    }
  }
  }
}
void MODE2::runEffect(){
  if(effect == 1)
    runEffect1();
}
