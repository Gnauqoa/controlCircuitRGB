#ifndef VarEffect_h
#define VarEffect_h

  #include <Arduino.h>
  #include <FastLED.h>
  
  struct VAREFFECT{    
    void setup(CRGB *);
    CRGB getColor(byte n = 10);
    
    float speed = 0;//led/s
    int count;
    CRGB *adr;
    bool flag_makeLED = 0;
    bool flag_setting = 0;
    bool flag_off1 = 0;
    bool flag_off2 = 0;
    bool flag_done1 = 0;
    bool flag_done2 = 0;
    bool flag_set = 0;
    bool flag_page = 0;
    bool ss1 = 0;
    bool ss2 = 0;
    bool flag_run1 = 0;
    bool flag_run2 = 0;
    bool flag_run12 = 0;
    
    byte on = 1;
    byte cen = 0;
    byte _cen = 0;
    byte count1 = 0;
    byte count2 = 0;
    byte brightness = 0;
    byte num1 = 0;
    byte num2 = 0;
    byte num = 0;
    byte color = 1;
    byte t = 0;
    byte t1 = 0;
    byte t2 = 0;
    byte _t = 0;
    byte _t1 = 0;
    byte _t2 = 0;
    
    unsigned long timer_run1 = 0;
    unsigned long timer_run2 = 0;
    unsigned long timer_Off1 = 0;
    unsigned long timer_Off2 = 0;
    unsigned long timer_updateLED = 0;
  };
  
#endif
