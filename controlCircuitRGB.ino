#include <LiquidCrystal_I2C.h> //https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c
#include <EEPROM.h>
#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>
#include <FastLED.h>
#include "Port.h"
#include "btn.h"

const int num_LEDs = 200;
const int pin_Port1 = 19;// day led 1
const int pin_Port2 = 1;// day led 2
const int pin_Port3 = 1;// day led 3

const int pin_btn1 = 12;// nut 1
const int pin_btn2 = 14;// nut 2
const int pin_btn3 = 27;// nut 3
const int pin_btn4 = 26;// nut 4
const int pin_btn5 = 25;// nut 5

const int pin_voice = 33;// am thanh
const int pin_ss1 = 13;// cam bien 1
const int pin_ss2 = 15;// cam bien2 

CRGB LED1[num_LEDs];
SoftwareSerial mySoftwareSerial(16, 17); // RX, TX
LiquidCrystal_I2C lcd(0x3F, 20, 4);
DFRobotDFPlayerMini myDFPlayer;

btnDouble btn1(pin_btn1);
btnDouble btn2(pin_btn2);
btn btn3(pin_btn3);
btn btn4(pin_btn4);
btn btn5(pin_btn5);
btn ss1(pin_ss1);
btn ss2(pin_ss2);

PORT port1;

byte getStatusBtn();
void configLCD();
void controlLED();
void controlLCD();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(pin_btn1,INPUT);
  pinMode(pin_btn2,INPUT);
  pinMode(pin_btn3,INPUT);
  pinMode(pin_btn4,INPUT);
  pinMode(pin_btn5,INPUT);
  pinMode(pin_ss1,INPUT);
  pinMode(pin_ss2,INPUT);

  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial);
  myDFPlayer.volume(15);  

  FastLED.addLeds<WS2812, pin_Port1, GRB>(LED1, num_LEDs).setCorrection( TypicalLEDStrip );
  FastLED.clear();
  port1.setup(0,lcd,LED1);
  configLCD();
}

void loop() {
  controlBtn();
  controlLED();
}
void controlBtn(){
  port1.controlBtn(getStatusBtn());
  controlLCD();
}
void controlLED(){
  port1.runEffect();
}
void controlLCD(){
  port1.showPage();
}
byte getStatusBtn(){
  if (Serial.available() > 0) {
    const String s = Serial.readString();
    Serial_println("Serial: " + s);
    if (s.indexOf("btn1") != -1)
      return 1;
    if (s.indexOf("btn2") != -1)
      return 2;
    if (s.indexOf("btn3") != -1)
      return 3;
    if (s.indexOf("btn4") != -1)
      return 4;
    if (s.indexOf("btn5") != -1)
      return 5;
    if (s.indexOf("btn6") != -1)
      return 6;
    if (s.indexOf("btn7") != -1)
      return 7;
    if (s.indexOf("btn8") != -1)
      return 8;
    if (s.indexOf("btn9") != -1)
      return 9;
    if (s.indexOf("btn10") != -1)
      return 10;
  }
  switch(btn1.checkStatusBtn()){
    case 1: return 1;
    case 2: return 8;
  }
  switch(btn2.checkStatusBtn()){
    case 1: return 2;
    case 2: return 9;
  }
  if(btn3.checkStatusBtn())
    return 3;
  if(btn4.checkStatusBtn())
    return 4;
  if(btn5.checkStatusBtn())
    return 5;
  if(ss1.checkStatusSensor())
    return 6;
  if(ss2.checkStatusSensor())
    return 7;
  return 0;
}
void configLCD(){
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
}
void Serial_println(const String s){
  Serial.println(s);
}
void Serial_print(const String s){
  Serial.print(s);
}
