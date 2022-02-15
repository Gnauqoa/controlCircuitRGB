#ifndef Mode_h
#define Mode_h

  #include <Arduino.h>
  
  #define minSPEED  0.01
  #define maxSPEED  10
  #define minLED  100
  #define maxLED  100
  #define maxTimeOff  600
  #define speedStep 0.01

  struct MODE{
    int getMaxStep(){
      return varEffect->num/2;
    }
    void controlBtn(byte val){
      pageMode.controlBtn(val);
    }
    void showPage(){
      pageMode.showPage();
    }
    
    VAREFFECT *varEffect;
    PAGE pageMode;
    
    byte effect = 1;
    int timeOff = 0;
    byte adrEEPROM = 0; 
  };

#endif
