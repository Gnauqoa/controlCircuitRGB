#ifndef Mode1_h
#define Mode1_h

  #include <Arduino.h>  
  #include "VarEffect.h"
  #include "Page.h"
  #include "Mode.h"
  #undef numEffect
  #undef pageLine
  #define numEffect 5
  #define pageLine 2

  struct MODE1:MODE{ 
      void setup(VAREFFECT &, byte, byte&, LiquidCrystal_I2C&);
      void runEffect();
      void runEffect1();
      void runEffect2();
      void runEffect3();
      void runEffect4();
      void runEffect5();
      
      PAGECOMPONENT pageList[pageLine] = {
        PAGECOMPONENT(effect,"Effect: ",1,numEffect),
        PAGECOMPONENT(timeOff,"Time Off: ",1,maxTimeOff)
      };


  };

#endif
