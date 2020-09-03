#define F_CPU 16000000UL
#define SREG    _SFR_IO8(0x3f)
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t PIN = 0;
uint16_t _tx_delay;
bool Print = true;
uint8_t ADCn;
uint8_t ADCo;
uint8_t SDA = PB1;
uint8_t SCL = PB2;
/*uint16_t paritise (uint16_t n) {
	uint16_t c = 0;
	uint16_t o = (n << 1);
	while (n) {
		c += n & 1;
		n = (n >> 1);
	}
	o += c & 1;
	return o;
}
	  uint8_t buffer[8];
	  uint8_t b = PIN;
	  for(uint8_t i = 0; i < 8;i++){
		  if (b & 1) buffer[i] = 49;
		  else buffer[i] = 48;
		  b >>= 1;
	  }
	  for (uint8_t *addr = (uint8_t*)(&buffer); addr < (uint8_t*)(&buffer) + (uint8_t)sizeof(buffer); addr++) {
		  Send(*addr);
	  }*/

void I2cInit () {
  PORTB &= ~(1 << SDA);
  PORTB &= ~(1 << SCL);
  DDRB &= ~(1 << SDA);
  DDRB &= ~(1 << SCL);
  _delay_loop_2(1000);
}

void I2copar () {
  _delay_loop_2(2000);
  if (( ~((DDRB >> SCL) | (DDRB >> SDA)) & 1)) {
    DDRB |= (1 << SDA);
	_delay_loop_2(500);
    DDRB |= (1 << SCL);
  } else {
    DDRB &= ~(1 << SCL);
    _delay_loop_2(500);
    DDRB &= ~(1 << SDA);
  }
  _delay_loop_2(500);
}

bool I2cSend (uint8_t& data) {
  bool ret = true;
  uint8_t len = 9;
  while (len--) {
	if (data & 1 || len == 1) DDRB &= ~(1 << SDA);
	else DDRB |= (1 << SDA);
	_delay_loop_2(500);
    DDRB &= ~(1 << SCL);
	while ( !(PINB & (1 << SCL)) && len == 1);
	if (PINB & (1 << SDA)) {
	  if (len == 1) {
		ret = false;
	  } else {
		data += 128;
	  }
	}
    _delay_loop_2(1000);
	DDRB |= (1 << SCL);
	if(len != 1) data >>= 1;
	_delay_loop_2(500);
  }
  return ret;
}
//void I2cMid () {
  
//}
void Send (uint8_t b) {
	uint8_t mask = 0b00010000;
	uint8_t imask = ~mask;
	uint8_t oSREG = SREG;
	cli();
	PORTB &= imask;
	_delay_loop_2(_tx_delay);
	for (uint8_t i = 8; i > 0; --i) {
		if (b & 1)
		PORTB |= mask;
		else
		PORTB &= imask;
		_delay_loop_2(_tx_delay);
		b >>= 1;
	}
	PORTB |= mask;
	SREG = oSREG;
	_delay_loop_2(_tx_delay);
	sei();
}

int main(void) {	
  _tx_delay = 0;
  uint16_t bit_delay = (F_CPU / 9600) / 4;
  if (bit_delay > 15 / 4)
  _tx_delay = bit_delay - (15 / 4);
  else
  _tx_delay = 1;
  
  PORTB =(1<<PB0) | (1<<PB1) | (1<<PB2) | (1<<PB4); // pull up on 012 and turn on 4
  DDRB = 0b00010101; // input on 012 and out put on 4
  GIMSK |= 0b00100000;    // turns on pin change interrupts
  PCMSK = 0b00000111;    // turn on interrupts on pins PB0, PB1,PB2
  ADCSRA &= ~((1 << ADPS2) | (1 << ADPS0) | (1 << ADPS1));
  //ADCSRA |=  ;
  ADMUX &= ~((1 << REFS0) | (1 << REFS1));
  ADMUX |= (1 << ADLAR) | (1 << MUX1) | (1 << MUX0);
  ADMUX &= ~((1 << MUX3) | (1 << MUX2)) ;
  ADCSRA |= (1 << ADEN);
  ADCSRA |= (1 << ADSC);
  ADCSRA |= (1 << ADATE);
  DIDR0 &= ~(1 << ADC0D);
  sei();
  I2cInit();
  _delay_loop_2(0);
  //uint8_t i;
  while(1){
	  Send(0);
	  //I2copar();
	  //i = 188;
	  //I2cSend(i);
	  //_delay_loop_2(2000);
	  //i = 255;
	  //I2cSend(i);
	  //DDRB |= (1 << SDA);
	  //_delay_loop_2(500);
	  //I2copar();
	  ADCn = ADCH;
	  if(ADCn != ADCo){
		ADCo = ADCn;
		Print = true;
	  }
	  
    if(Print){
	  Send(ADCo);
	  Print = false;

	  Send(10); 
	}
  }
}

ISR(PCINT0_vect)
{
  if (PIN != PINB) {
    PIN = PINB;
    Print = true;
  }
}

	
	
	//ADCSRA &= ~((0 << ADPS2) | !(0 << ADPS0));
	//ADCSRA |=  (1 << ADPS1);
	//ADMUX &= ~((0 << REFS0) | !(0 << REFS1));
	//ADMUX |= (1 << ADLAR) | (1 << MUX1) | (1 << MUX0);
	//ADMUX &= ~((0 << MUX3) | (0 << MUX2)) ;
	//ADCSRA |= (1 << ADIE)
	//ADCSRA |= (1 << ADEN);
	//ADCSRA |= (1 << ADSC);
	//ADCSRA |= (1 << ADATE);
	//while(1) {
		//start:
		//if(ADCH != ADCLAST){
			//Print = true;
			//ADCLAST = ADCH;
		//}
		//
		//if ((PIN = PINB & 7) != (PINLAST & 7)) {
			//Print = true;
		//}
		//
		//if ((PINLAST & 7) == 0) {
			//Print = false;
		//}
		//
		//PINLAST = PIN;
		//if(Print == true) {
			//if ((PINLAST & 7) == 0) {
				//nid();
				//Print = false;
				//goto start;
			//}
//
			//Send((paritise((ADCLAST << 3) + (PINLAST & 7)) >> 8) & 0b11111111);
			//Send(paritise((ADCLAST << 3) + (PINLAST & 7)) & 0b11111111);
			//
			//Print = false;
		//}
	//}
