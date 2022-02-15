#ifndef PageComponent_h
#define PageComponent_h

  #include <Arduino.h>
  #include <String.h>
  #include <EEPROM.h>
  int EEPROM_readInt(int adr);
  float EEPROM_readFloat(int adr);
  struct PAGECOMPONENT {
    PAGECOMPONENT(byte &, const char *, float , float, float = 1);
    PAGECOMPONENT(float &, const char *, float , float, float = 1);
    PAGECOMPONENT(int&, const char *, float , float, float = 1);
    PAGECOMPONENT& operator++();
    PAGECOMPONENT& operator--();
    operator byte() const;
    operator float() const;
    operator char*();
    byte sizeOf();
    void writeEEPROM(byte);
    void readEEPROM(byte);
    int *val3 = NULL;
    float *val2 = NULL;
    byte *val1 = NULL;
    char text[21];
    float step;
    float max;
    float min;
  };

#endif
