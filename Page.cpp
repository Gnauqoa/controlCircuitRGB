#include "Page.h"

void PAGE::setup(const char * pageName, PAGECOMPONENT * pageList,byte numLine, byte &adrEEPROM, byte &pageFocus, LiquidCrystal_I2C &lcd){
  strcpy(this->pageName,pageName);
  this->pageList = pageList;
  this->numLine = numLine;
  this->pageFocus = &pageFocus;
  this->adrEEPROM = &adrEEPROM;
  this->lcd = &lcd;
  int adr = *this->adrEEPROM;
  for(int i = 0; i < numLine; ++i){
    pageList[i].readEEPROM(adr);
    adr += pageList[i].sizeOf();
  }
}
void PAGE::controlBtn(byte &val){
  if((val != 1) && (val != 2))
    save = 1;
  switch(val){
    case 1:{
      if(line != 1) --line;
      break;
    }
    case 2:{
      if(line != numLine) ++line;
      break;
    }
    case 3:{
      ++pageList[line];
      break;
    }
     case 4:{
      --pageList[line];
      break;
    }
    case 9:{
      *pageFocus = 0;
      if(save == 1){
        save = 0;
        int adr = *adrEEPROM;
        for(int i = 0; i < numLine; ++i){
            pageList[i].writeEEPROM(adr);
            adr += pageList[i].sizeOf();
        }
      }
    }
  }
}
void PAGE::controlBtn(byte & buff, byte &val){
  *pageFocus = val;
}
void PAGE::showPage(){
  char text[21] = "";
  strcpy(text,pageName);
  makeCenter(text);
  print_LCD(0,text);
  if(line <= 3){
    for(byte i = 1; i <= 3; ++i){
      if(i == line) getLineFocus(text,i);
      else getLine(text,i);
      print_LCD(i,text);
    }
  }
  else{
    for(int i = 1; i <= 2; ++i){
      getLine(text,line-i);  
      print_LCD(3-i,text);     
    }          
    getLineFocus(text,line);       
    print_LCD(3,text);     
  }
}
void PAGE::getLine(char *s, byte line){
  strcpy(s,pageList[line]);
  makeCenter(s);
}
void PAGE::getLineFocus(char *s, byte line) {
  getLine(s,line);
  s[0] = '<';
  s[19] = '>';
}
void PAGE::makeCenter(char *s) {
  char buff[20] = "";
  byte leg = (20 - (strlen(s))) / 2;
  strcpy(buff,s);
  strcpy(s,"");
  for (byte i = 0; i < leg; ++i) 
    s[i] = ' ';
  strcat(s,buff);
}
void PAGE::print_LCD(byte loc, const char *s){
  lcd->setCursor(0,loc);
  lcd->print(s);
}
