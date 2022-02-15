#ifndef Mode3_h
#define Mode3_h

  #include <Arduino.h>  
  #include "VarEffect.h"
  #include "Page.h"
  #include "Mode.h"
  #undef numEffect
  #undef pageLine
  #define numEffect 3
  #define pageLine 7
  
  struct MODE3:MODE{ 
    void setup(VAREFFECT &, byte, byte&, LiquidCrystal_I2C&);
    void runEffect();
    void runEffect1();
    void runEffect2();
    void runEffect3();
    
    PAGECOMPONENT pageList[pageLine] = {
      PAGECOMPONENT(effect,"Effect: ",1,numEffect),
      PAGECOMPONENT(timeOff,"Time Off: ",1,maxTimeOff),
      PAGECOMPONENT(LedStep,"Led Step: ",1,getMaxStep()),
      PAGECOMPONENT(numStep,"Num Step: ",1,getMaxStep()),
      PAGECOMPONENT(speed_led,"Speed Led: ",minSPEED,maxSPEED,speedStep),
      PAGECOMPONENT(speed_step,"Speed Step: ",minSPEED,maxSPEED,speedStep),
      PAGECOMPONENT(runMode,"Run Mode: ",0,1)
    };
    
    
    int LedStep = 0;
    int numStep = 0;
    float speed_led = 0;
    float speed_step = 0;
    byte runMode = 0;
  };

#endif
