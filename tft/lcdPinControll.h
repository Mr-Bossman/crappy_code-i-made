#include <Arduino.h>
#include <stdint.h>


class lcdPin {

  public:

  uint8_t bus[8];
  uint8_t RD;
  uint8_t WR;
  uint8_t DC;
  uint8_t RTS;

  lcdPin(const uint8_t bus[8], uint8_t RD,uint8_t WR, uint8_t DC,uint8_t RTS);

  void reset();
  void writeLCD(uint8_t data);
  uint8_t readLCD();
  void commandLCD(uint8_t data);
  uint8_t statusLCD();

  private:

  void writeBus(uint8_t data);
  uint8_t readBus();
  void stateBus(int state);
};
