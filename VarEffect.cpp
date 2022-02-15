#include "VarEffect.h"

void VAREFFECT::setup(CRGB *LED){
  adr = LED;
}
CRGB VAREFFECT::getColor(byte n){
  byte check = n != 10 ? n : color;
  switch(check){
    case 0: return CRGB::Black;
    case 1: return CRGB::Red;   
    case 2: return CRGB::Green;
    case 3: return CRGB::Blue;
    case 4: return CRGB::Yellow;
    case 5: return CRGB(255,20,147);
    case 6: return CRGB(255,165,0);
    case 7: return CRGB::White;
    default: return getColor(random(0,8));     
  }
}
