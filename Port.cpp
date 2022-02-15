#include "Port.h"

void PORT::setup(byte adrEEPROM, LiquidCrystal_I2C &lcd, CRGB* LED){
  this->adrEEPROM = adrEEPROM;
  varEffect.setup(LED);
  pagePort.setup("PORT",pageList,pageLine,adrEEPROM,pageFocus,lcd);
  mode1.setup(varEffect,adrEEPROM+8,pageFocus,lcd);
  mode2.setup(varEffect,adrEEPROM+11,pageFocus,lcd);
  mode3.setup(varEffect,adrEEPROM+16,pageFocus,lcd);
}
void PORT::runEffect(){
  if(!varEffect.on)return;
   switch(mode){
    case 1:{mode1.runEffect();break;}   
    case 2:{mode2.runEffect();break;}    
    case 3:{mode3.runEffect();break;}   
    default:{mode1.runEffect();break;}   
  }
}
void PORT::showPage(){
  switch(pageFocus){
    case 1:{mode1.showPage();break;}   
    case 2:{mode2.showPage();break;}    
    case 3:{mode3.showPage();break;}   
    default:{pagePort.showPage();break;}   
  }
}
void PORT::controlBtn(byte val){
   switch(pageFocus){
    case 1:{mode1.controlBtn(val);break;}   
    case 2:{mode2.controlBtn(val);break;}    
    case 3:{mode3.controlBtn(val);break;}   
    default:{pagePort.controlBtn(val,val);break;}   
  }
  
}
