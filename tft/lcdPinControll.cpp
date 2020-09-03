// CS must be low 
// RTS is reset
//RS is DC
// default state after each function is HIGH for RTS, RD , WR and  DC and bus output
// there is an imaginary delay between each instruction its there irl but not in code
#include "lcdPinControll.h"

  lcdPin::lcdPin(const uint8_t bus[8], uint8_t RD,uint8_t WR, uint8_t DC,uint8_t RTS) {
    this->RD = RD;
    this->WR = WR;
    this->DC = DC;
    this->RTS = RTS;
    memcpy(this->bus,bus,8);
    stateBus(OUTPUT);
    pinMode(RTS,OUTPUT);
    digitalWrite(RTS,LOW);
    
    pinMode(WR,OUTPUT);
    digitalWrite(WR,HIGH);

    pinMode(DC,OUTPUT);
    digitalWrite(DC,HIGH);

    pinMode(RD,OUTPUT);
    digitalWrite(RD,HIGH);
    delay(100);
    
    digitalWrite(RTS,HIGH);

    delay(120);
    
  }
  void lcdPin::reset(){
    digitalWrite(RTS,LOW);
    delay(100);
    digitalWrite(RTS,HIGH);
    delay(120);
  }
  
  void lcdPin::writeLCD(uint8_t data){
    writeBus(data);
    digitalWrite(WR,LOW);
    digitalWrite(WR,HIGH);
  }
  uint8_t lcdPin::readLCD(){
    uint8_t tmp;
    stateBus(INPUT);
    digitalWrite(RD,LOW);
    digitalWrite(RD,HIGH);
    tmp = readBus();
    stateBus(OUTPUT);
    return tmp;
  }
  void lcdPin::commandLCD(uint8_t data){
    writeBus(data);
    digitalWrite(DC,LOW);
    digitalWrite(WR,LOW);
    digitalWrite(WR,HIGH);
    digitalWrite(DC,HIGH);

  }
  uint8_t lcdPin::statusLCD(){
    return readLCD();
  }
 void lcdPin::writeBus(uint8_t data){
    for(uint8_t i = 0; i < 8; i++){
      digitalWrite(bus[i],(data&1));
      data >>= 1;
    }
  }
  uint8_t lcdPin::readBus(){
    uint8_t data;
    for(uint8_t i = 0; i < 8; i++){
      data += (digitalRead(lcdPin::bus[i]))?128:0;
      data >>= 1;
    }
    return data;
  }
  void lcdPin::stateBus(int state){
    for(uint8_t i = 0; i < 8; i++){
      pinMode(bus[i],state);
    }
  }

