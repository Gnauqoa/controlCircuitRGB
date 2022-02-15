#ifndef Port_h
#define Port_h
  #include <Arduino.h>
  #include <LiquidCrystal_I2C.h> 
  #include "VarEffect.h"
  #include "Page.h"
  #include "Mode1.h"
  #include "Mode2.h"
  #include "Mode3.h"
  
  #undef numEffect
  #undef pageLine
  
  const byte pageLine = 6;
  const byte numMode = 3;
  const byte minBrightness = 0;
  const byte maxBrightness = 255;
  const byte minColor = 0;
  const byte maxColor = 7;
  
  struct PORT {
    void setup(byte, LiquidCrystal_I2C&, CRGB*);
    void runEffect();
    void showPage();
    void controlBtn(byte);
    
    VAREFFECT varEffect;
    PAGECOMPONENT pageList[pageLine] = {
      PAGECOMPONENT(varEffect.on,"Active: ",0,1),
      PAGECOMPONENT(varEffect.brightness,"Brightness: ",minBrightness,maxBrightness),
      PAGECOMPONENT(mode,"Mode: ",1,numMode),
      PAGECOMPONENT(varEffect.num,"Number led: ",minLED,maxLED),
      PAGECOMPONENT(varEffect.color,"Color: ",minColor,maxColor),
      PAGECOMPONENT(varEffect.speed,"Speed: ",minSPEED,maxSPEED,speedStep)
    };
    MODE1 mode1;
    MODE2 mode2;
    MODE3 mode3;
    PAGE pagePort;

    byte pageFocus = 0;
    byte mode = 0;
    int add = 1;
    byte ID = 0;
    byte adrEEPROM = 0;
  };
#endif
