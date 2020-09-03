uint8_t ADCLAST;
uint8_t PINLAST;
uint8_t PIN;
boolean Print = true;
void setup() {
  PORTB = (1<<PB0) | (1<<PB1) | (1<<PB2);
  DDRB = 0b00010000;
  ADCSRA |= (0 << ADPS2) | (0 << ADPS1) | (0 << ADPS0); 
  ADMUX |= (0 << REFS0) | (0 << REFS1);
  ADMUX |= (1 << ADLAR);  
  ADMUX |= (0 << MUX3) | (0 << MUX2) | (1 << MUX1) | (1 << MUX0);
  ADCSRA |= (1 << ADEN);
  ADCSRA |= (1 << ADSC); 
  ADCSRA |= (1 << ADATE);
  Serial.begin(115200);
  while(1) {
    if((ADCH & 252) != (ADCLAST & 252)){
      Print = true;
      ADCLAST = ADCH;
    }
    if ((PIN = PINB & 7) != (PINLAST & 7)) {
      Print = true;
    }
    PINLAST = PIN;
    if(Print == true) {
      for (int b = 15; b >= 0; b--) {
        Serial.print(bitRead(paritise((ADCLAST << 3) + (PINLAST & 7)), b));
      }  
      Serial.println();
      Print = false;
    }
    
  }
}

void loop() {
}

uint16_t paritise(uint16_t n) {
  uint16_t c = 0;
  uint16_t o = (n << 1);
  while (n) {
    c += n & 1;
    n = (n >> 1);
  }
  o += c & 1;
  return o;
}

void Send(uint16_t s) {
  for (int n = 16; n > 0; n--) {
    if ( n & 1 == 1){
      s1();
    }
    if ( n & 1 == 0){
      s0();
    }
    s = (s >> 1);
  }
}
void s1() {
   PORTB |= (1 << PB4);  
   PORTB &= ~(1 << PB4);  
}

void s0() {
   PORTB |= (1 << PB4);  
   PORTB &= ~(1 << PB4);
}




