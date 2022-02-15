#ifndef Mode2_h
#define Mode2_h
  #include <Arduino.h>  
  #include "VarEffect.h"
  #include "Page.h"
  #include "Mode.h"
  #undef numEffect
  #undef pageLine
  #define numEffect 1
  #define pageLine 3
  
  struct MODE2:MODE{ 
    void setup(VAREFFECT &, byte, byte&, LiquidCrystal_I2C&);
    void runEffect();
    void runEffect1();
    
    PAGECOMPONENT pageList[pageLine] = {
      PAGECOMPONENT(effect,"Effect: ",1,numEffect),
      PAGECOMPONENT(timeOff,"Time Off: ",1,maxTimeOff),
      PAGECOMPONENT(step,"Step: ",1,getMaxStep())
    };

    
    int step = 0;
  };

#endif
