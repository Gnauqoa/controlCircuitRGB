#ifndef Page_h
#define Page_h

  #include <Arduino.h>
  #include <LiquidCrystal_I2C.h> 
  #include <EEPROM.h>
  #include <String.h>
  #include "PageComponent.h"
  
  struct PAGE {
    void setup(const char *, PAGECOMPONENT *, byte , byte&, byte&, LiquidCrystal_I2C&);
    void controlBtn(byte&);
    void controlBtn(byte& , byte &);
    void showPage();
    void getLine(char *, byte);
    void getLineFocus(char *, byte);
    void makeCenter(char *);
    void print_LCD(byte , const char *);
    
    PAGECOMPONENT *pageList;
    LiquidCrystal_I2C *lcd;

    bool save = 0;
    char pageName[21] = "";
    byte *adrEEPROM = NULL;
    byte *pageFocus = NULL;
    byte line = 1;
    byte numLine = 0;
  };

#endif
