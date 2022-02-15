#include "Mode3.h"

void MODE3::setup(VAREFFECT &varEffect, byte adrEEPROM, byte &pageFocus, LiquidCrystal_I2C & lcd){
  this->varEffect = &varEffect;
  this->adrEEPROM = adrEEPROM;
  pageMode.setup("MODE3",pageList,pageLine,adrEEPROM,pageFocus,lcd);
}
void MODE3::runEffect(){
  if(effect == 1)
    runEffect1();
  if(effect == 2)
    runEffect2();
  if(effect == 3)
    runEffect3();
}
void MODE3::runEffect1(){
  FastLED.setBrightness(map(varEffect->brightness,100,0,255,0));
  unsigned long time = varEffect->speed*1000;
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
    }
    if((varEffect->flag_done1 == 1) && (varEffect->flag_done2 == 1)){
      varEffect->flag_run12 = 0;
      varEffect->flag_set = 0;
      varEffect->flag_done1 = 0;
      varEffect->flag_done2 = 0;
    }
    if(varEffect->flag_run1 == 1){
      if((varEffect->count1 <= varEffect->num1) && (varEffect->flag_off1 == 0))   
      if(millis() - varEffect->timer_run1 >= time){
          
          *(varEffect->adr + varEffect->count1-1) = varEffect->getColor();
          varEffect->count1++;
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
              *(varEffect->adr + varEffect->num1 - varEffect->count1) = varEffect->getColor(0);
              FastLED.show();
              --varEffect->count1;
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
          *(varEffect->adr +  varEffect->count2-1) = varEffect->getColor();
          --varEffect->count2;
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
              varEffect->timer_run2 = millis();
              *(varEffect->adr + varEffect->num - (varEffect->count2 - varEffect->num2)) = varEffect->getColor(0);
              FastLED.show();
              ++varEffect->count2;
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
void MODE3::runEffect2(){
  FastLED.setBrightness(map(varEffect->brightness,100,0,255,0));
  unsigned long time = varEffect->speed*1000;
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
          varEffect->num1 = LedStep * numStep;
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
          varEffect->num2 = 0;
          varEffect->count2 = LedStep * numStep;

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
          varEffect->count2 = LedStep * numStep ;
          varEffect->flag_set = 1;
        }
      }
    }
    if((varEffect->flag_done1 == 1) && (varEffect->flag_done2 == 1)){
      varEffect->flag_run12 = 0;
      varEffect->flag_set = 0;
      varEffect->flag_done1 = 0;
      varEffect->flag_done2 = 0;
    }
    if(varEffect->flag_run1 == 1){
      if((varEffect->count1 <= varEffect->num1) && (varEffect->flag_off1 == 0))   
      if(millis() - varEffect->timer_run1 >= time){
        
          byte t = (varEffect->count1-1)/LedStep;
          byte t1 = t*LedStep;
          byte t2 =  (t+1)*LedStep;
          if(t2 > varEffect->num1)
            t2 = varEffect->num1;

          *(varEffect->adr + map(varEffect->count1,t1,t2,t2,t1)-1) = varEffect->getColor();
          varEffect->count1++;
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
              byte t = (varEffect->count1-1)/LedStep;
              byte t1 = t*LedStep;
              byte t2 =  (t+1)*LedStep;
              *(varEffect->adr + map(varEffect->count1,t1,t2,t2,t1)-1) = varEffect->getColor(0);
              FastLED.show();
              --varEffect->count1;
              varEffect->timer_run1 = millis();
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
          byte t = (varEffect->count2-1)/LedStep;
          byte t1 = t*LedStep;
          byte t2 =  (t+1)*LedStep;
          if(t1 < varEffect->num2){
 
            t1 = varEffect->num2;  
          }       
      
         
            *(varEffect->adr + map(varEffect->count2,t1,t2,t2,t1)-1) = varEffect->getColor();
          --varEffect->count2;   
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
              varEffect->timer_run2 = millis();
              byte t = (varEffect->count2-1)/LedStep;
              byte t1 = t*LedStep;
              byte t2 =  (t+1)*LedStep;
              *(varEffect->adr + map(varEffect->count2,t1,t2,t2,t1)-1) = varEffect->getColor(0);
              FastLED.show();
              ++varEffect->count2;
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
void MODE3::runEffect3(){
  FastLED.setBrightness(map(varEffect->brightness,100,0,255,0));
  unsigned long time = varEffect->speed*1000;
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
          varEffect->num1 = LedStep * numStep;
          if(LedStep%2 == 0)
            varEffect->count1 = LedStep / 2;
          else
            varEffect->count1 = LedStep / 2 + 1;
          varEffect->cen = varEffect->count1;
          varEffect->t = (varEffect->count1)/LedStep;
          varEffect->t1 = (varEffect->t)*LedStep+1;
          varEffect->t2 =  (varEffect->t+1)*LedStep;
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
          varEffect->num2 = 0;
          varEffect->count2 = LedStep * numStep - LedStep/2;
          varEffect->_cen = varEffect->count2;
          varEffect->_t = (varEffect->count2)/LedStep;
          varEffect->_t1 = varEffect->_t*LedStep+1;
          varEffect->_t2 =  (varEffect->_t+1)*LedStep;
        }
      }
    }
    if(varEffect->flag_run12 == 1){
      if(varEffect->flag_run2 == 1){
        if(varEffect->flag_set == 0){
          varEffect->flag_off2 = 0;
          varEffect->flag_off1 = 0;
          varEffect->flag_run1 = 1;
          varEffect->flag_set = 1;   
             
          if(LedStep%2 == 0)
            varEffect->count1 = LedStep / 2;         
          else
            varEffect->count1 = LedStep / 2 + 1;                 
          
          FastLED.show(); 
          if(numStep %2 == 0){
            varEffect->num1 = numStep/2*LedStep;             
            varEffect->num2 = numStep/2*LedStep;             
          }       
          else{
            varEffect->num1 = (numStep/2+1)*LedStep;            
            varEffect->num2 = (numStep/2 + 1)*LedStep;
          }
          for(byte i = varEffect->num2; i >= 1; --i){
            *(varEffect->adr + i-1) = varEffect->getColor(0);
          }
          if(varEffect->count2 < varEffect->num2) varEffect->count2 = varEffect->num2+1;   
          Serial.println(varEffect->num1);
          Serial.println(varEffect->num2);
          varEffect->cen = varEffect->count1;
          varEffect->t = (varEffect->count1)/LedStep;
          varEffect->t1 = (varEffect->t)*LedStep+1;
          varEffect->t2 =  (varEffect->t+1)*LedStep;
          varEffect->timer_run1 = millis();
        }
      }
      if(varEffect->flag_run1 == 1){
        if(varEffect->flag_set == 0){
          varEffect->flag_off1 = 0;
          varEffect->flag_off2 = 0;
          varEffect->flag_run2 = 1;
          varEffect->flag_set = 1;
          if(numStep %2 == 0){
            varEffect->num1 = numStep/2*LedStep;             
            varEffect->num2 = numStep/2*LedStep;             
          }       
          else{
            varEffect->num1 = (numStep/2 + 1)*LedStep;            
            varEffect->num2 = (numStep/2 + 1)*LedStep;
          }
          
          
          varEffect->count2 = LedStep * numStep - LedStep/2; 
          varEffect->_cen = varEffect->count2;
          varEffect->_t = (varEffect->count2)/LedStep;
          varEffect->_t1 = (varEffect->_t)*LedStep+1;
          varEffect->_t2 =  (varEffect->_t+1)*LedStep;
       
          for(byte i = varEffect->num1+1; i <= varEffect->count1; ++i){
            *(varEffect->adr + i-1) = varEffect->getColor(0);
          }
          if(varEffect->count1 > varEffect->num1) varEffect->count1 = varEffect->num1;
          FastLED.show(); 
          varEffect->timer_run2 = millis();
        }
      }
    }
    if((varEffect->flag_done1 == 1) && (varEffect->flag_done2 == 1)){
      varEffect->flag_run12 = 0;
      varEffect->flag_set = 0;
      varEffect->flag_done1 = 0;
      varEffect->flag_done2 = 0;
    }
    if(varEffect->flag_run1 == 1){
      if((varEffect->count1 <= varEffect->num1) && (varEffect->flag_off1 == 0))   
      if(millis() - varEffect->timer_run1 >= time){
          *(varEffect->adr + varEffect->count1 - 1) = varEffect->getColor();
          if(LedStep%2 == 0)
            *(varEffect->adr + map(varEffect->count1,varEffect->t2,varEffect->cen+1,varEffect->t1,varEffect->cen) - 1) = varEffect->getColor();         
          else
            *(varEffect->adr + map(varEffect->count1,varEffect->t2,varEffect->cen,varEffect->t1,varEffect->cen) - 1) = varEffect->getColor();         
          if(varEffect->count1 % LedStep == 0){
            if(LedStep%2 == 0)
              varEffect->count1 += LedStep / 2;
            else
              varEffect->count1 += LedStep / 2 + 1;
            varEffect->t = (varEffect->count1)/LedStep;
            varEffect->t1 = varEffect->t*LedStep+1;
            varEffect->t2 =  (varEffect->t+1)*LedStep;
            varEffect->cen = varEffect->count1;
          }
          else
            varEffect->count1++;
          varEffect->timer_run1 = millis();
          if(varEffect->count1 > varEffect->num1){
            varEffect->count1 = varEffect->num1 - LedStep/2;
            varEffect->t = (varEffect->count1)/LedStep;
            varEffect->t1 = varEffect->t*LedStep+1;
            varEffect->t2 =  (varEffect->t+1)*LedStep;
            varEffect->cen = varEffect->count1;
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
              if(varEffect->count1 >= varEffect->t1){
                *(varEffect->adr + varEffect->count1 - 1) = varEffect->getColor(0);
                if(LedStep%2 == 0)
                  *(varEffect->adr + map(varEffect->count1,varEffect->t2,varEffect->cen+1,varEffect->t1,varEffect->cen) - 1) = varEffect->getColor(0);               
                else
                  *(varEffect->adr + map(varEffect->count1,varEffect->t2,varEffect->cen,varEffect->t1,varEffect->cen) - 1) = varEffect->getColor(0);               
              }
              if(varEffect->count1 % LedStep == 0){
                varEffect->count1 -= LedStep / 2;
                varEffect->t = (varEffect->count1)/LedStep;
                varEffect->t1 = varEffect->t*LedStep+1;
                varEffect->t2 =  (varEffect->t+1)*LedStep;
                varEffect->cen = varEffect->count1;
              }
              else
                varEffect->count1--;
              FastLED.show();
              varEffect->timer_run1 = millis();
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
        if(varEffect->count2 >= varEffect->_t1){
          *(varEffect->adr + varEffect->count2 - 1) = varEffect->getColor();
          if(LedStep%2 == 0){
            *(varEffect->adr + map(varEffect->count2,varEffect->_t2,varEffect->_cen+1,varEffect->_t1,varEffect->_cen) - 1) = varEffect->getColor();    
          }     
          else{
            *(varEffect->adr + map(varEffect->count2,varEffect->_t2,varEffect->_cen,varEffect->_t1,varEffect->_cen) - 1) = varEffect->getColor();   
          }
        }
        if(varEffect->count2 % LedStep == 0){
          varEffect->count2 -= LedStep / 2;
          varEffect->_t = (varEffect->count2)/LedStep;
          varEffect->_t1 = varEffect->_t*LedStep+1;
          varEffect->_t2 =  (varEffect->_t+1)*LedStep;
          varEffect->_cen = varEffect->count2;
        }
        else
          --varEffect->count2;   
        FastLED.show();
        varEffect->timer_run2 = millis();    
        if(varEffect->count2 <= varEffect->num2){
          varEffect->count2 += LedStep/2 + 1;
          
          varEffect->_t = (varEffect->count2)/LedStep;
          varEffect->_t1 = varEffect->_t*LedStep+1;
          varEffect->_t2 =  (varEffect->_t+1)*LedStep;
          varEffect->_cen = varEffect->count2;
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
        
      }
      if(varEffect->flag_run12 == 0)
      if((varEffect->count2 >= varEffect->num2) && (varEffect->flag_off2 == 1)){
        if(millis()- (varEffect->timer_Off2) >= (timeOff)*1000){
          if(varEffect->count2 <= LedStep * numStep){
            if(millis() - varEffect->timer_run2 >= time){ 
              if(varEffect->count2 <= varEffect->_t2){
                *(varEffect->adr + varEffect->count2 - 1) = varEffect->getColor();
                if(LedStep%2 == 0){
                  *(varEffect->adr + map(varEffect->count2,varEffect->_t2,varEffect->_cen,varEffect->_t1,varEffect->_cen-1) - 1) = varEffect->getColor(0);    
                }     
                else{
                  *(varEffect->adr + map(varEffect->count2,varEffect->_t2,varEffect->_cen,varEffect->_t1,varEffect->_cen) - 1) = varEffect->getColor(0);   
                }
              }
              FastLED.show();
              if(varEffect->count2 % LedStep == 0){
                varEffect->count2 += LedStep / 2+1;
                varEffect->_t = (varEffect->count2)/LedStep;
                varEffect->_t1 = varEffect->_t*LedStep+1;
                varEffect->_t2 =  (varEffect->_t+1)*LedStep;
                varEffect->_cen = varEffect->count2;
              }
              else
                ++varEffect->count2;
              varEffect->timer_run2 = millis();
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
