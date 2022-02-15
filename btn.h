#ifndef btn_h
#define btn_h

  #include <Arduino.h>
  
  const bool staPress = 0;
  const int time_btn = 500;
  const int time_wait = 500;
  const int time_press = 900;
  const int time_re = 100;
  
  struct btn{
    btn(byte);
    bool checkStatusSensor();
    bool checkStatusBtn();

    byte pin;
    bool flag_btn = 0;  
    bool flag_press = 0;  
    unsigned long timer_btn = 0;
    unsigned long timer_press = 0;
    unsigned long timer_re = 0;
    
  };
  struct btnDouble{
    btnDouble(byte);
    byte checkStatusBtn();

    byte pin;
    byte flag = 0;
    bool flag_btn = 0;  
    bool flag_press = 0;  
    unsigned long timer_btn = 0;
    unsigned long timer_wait = 0;
    unsigned long timer_press = 0;
    unsigned long timer_re = 0;
  };
#endif
