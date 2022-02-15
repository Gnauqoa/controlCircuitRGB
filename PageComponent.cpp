#include "PageComponent.h"

PAGECOMPONENT::PAGECOMPONENT(byte & val, const char *text, float min, float max, float step ){
  val1 = &val;
  sprintf(this->text,"%s: %i",text,val);
  this->min = min;
  this->max = max;
  this->step = step;
}
PAGECOMPONENT::PAGECOMPONENT(float & val, const char *text, float min, float max, float step ){
  val2 = &val;
  sprintf(this->text,"%s: %f",text,val);
  this->min = min;
  this->max = max;
  this->step = step;
}
PAGECOMPONENT::PAGECOMPONENT(int & val, const char * text, float min, float max, float step ){
  val3 = &val;
  sprintf(this->text,"%s: %i",text,val);
  this->min = min;
  this->max = max;
  this->step = step;
}
PAGECOMPONENT::operator char*(){
  return text;
}

PAGECOMPONENT::operator byte() const{
  return *(val1);
}

PAGECOMPONENT::operator float() const{
  return *(val2);
}
PAGECOMPONENT& PAGECOMPONENT::operator++(){
  if(val1 != NULL)
    if(*val1 == max)
      *val1 = min; 
    else
    *val1 += step;
  else
  if(val2 != NULL)
    if(*val2 == max)
      *val2 = min; 
    else    
    *val2 += step;
  else
  if(*val3 == max)
    *val3 = min; 
  else
  *val3 += step;
}
PAGECOMPONENT& PAGECOMPONENT::operator--(){
  if(val1 != NULL){
    if(*val1 == min)
      *val1 = max; 
    else
    *val1 -= step;
  }
  else
  if(val2 != NULL)
    if(*val2 == min)
      *val2 = max; 
    
    else
    *val2 -= step;
  
  else
  if(*val3 == min)
    *val3 = max; 
  else
  *val3 -= step;
}
byte PAGECOMPONENT::sizeOf(){
  if(val1 != NULL) return 1;
  return 2;
}
void PAGECOMPONENT::writeEEPROM(byte adr){
  if(val1 != NULL){
    EEPROM.write(adr,*val1);
    EEPROM.commit();
    return;
  }
  int a;
  if(val2 != NULL) a = *val2*100;
  else a = *val3;
  byte cao_8 = ((a >> 8) & 0xFF);
  EEPROM.write(adr, cao_8);
  byte thap_8 = (a & 0xFF);
  EEPROM.write(adr + 1, thap_8);
  EEPROM.commit();
}
void PAGECOMPONENT::readEEPROM(byte adr){
  if(val1 != NULL){
    *val1 = EEPROM.read(*val1);
    return;
  }
  if(val2 != NULL){
    *val2 = EEPROM_readFloat(adr);
    return;
  }
  *val3 = EEPROM_readInt(adr);
}
float EEPROM_readFloat(int adr){
  byte doc_cao_8, doc_thap_8;
  doc_cao_8 = EEPROM.read(adr); 
  doc_thap_8 = EEPROM.read(adr + 1); 
  int doc_a; 
  doc_a = (doc_cao_8 << 8); 
  doc_a = doc_a | doc_thap_8; 
  return (float)doc_a/100;
}
int EEPROM_readInt(int adr){
  byte doc_cao_8, doc_thap_8;
  doc_cao_8 = EEPROM.read(adr); 
  doc_thap_8 = EEPROM.read(adr + 1); 
  int doc_a; 
  doc_a = (doc_cao_8 << 8); 
  doc_a = doc_a | doc_thap_8; 
  return doc_a;
}
