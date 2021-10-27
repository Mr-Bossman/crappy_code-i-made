
#include <iostream>
using namespace std;


void bitsA(uint8_t val,char out[]){ // msb
	for(uint8_t i = 0; i < 8; i++) {
		out[i] = (val&128)?'1':'0';
		val <<= 1;
	}
}
void bitsB(uint8_t val,char out[]){ // lsb
	for(uint8_t i = 0; i < 8; i++) {
		out[i] = (val&1)?'1':'0';
		val >>= 1;
	}
}

uint8_t rotateR(uint8_t val, uint8_t count){
	for(uint8_t i = 0; i < count;i++){
		val = (val << 7) | (val >> 1);
	}
	return val;
}
uint8_t rotateL(uint8_t val, uint8_t count){
	for(uint8_t i = 0; i < count;i++){
		val = (val >> 7) | (val << 1);
	}
	return val;
}
uint8_t flip(uint8_t val){
	uint8_t ret = (val&1);
	for(uint8_t i = 0; i < 7; i++) {
		val >>= 1;
		ret <<= 1;
		ret  |= (val&1);
	}
	return ret;
}

#define ogseed 6203
uint16_t x = 0, w = 0;
inline static uint16_t randn() {
	x *= x;
	x += (w += ogseed);
	return x = (x>>8) | (x<<8);
}

int main() {
	char bit[9] = {0};
	bitsA(flip(128),bit);
	std::cout << randn();
	return 0;
}

/*
 * #define F_CPU 3330000UL // ????
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
volatile uint16_t _tx_delay = 0;
void initSerial(){
	_tx_delay = 0;
	uint16_t bit_delay = (F_CPU / 1200) / 4;
	if (bit_delay > 15 / 4)
		_tx_delay = bit_delay - (15 / 4);
	else
		_tx_delay = 1;
}
uint8_t readSerial(){
	cli();
	uint8_t ret = 0;
	_delay_loop_2(_tx_delay>>1);
	_delay_loop_2(_tx_delay);
	for (uint8_t w = 0; w < 8;w++) {
		ret >>= 1;
		ret |= state_AC()?128:0;
		_delay_loop_2(_tx_delay);
	}
	sei();
	return ret;
}
void Send (uint8_t b) {
	uint8_t mask = 1<<3;
	uint8_t imask = ~mask;
	cli();
	PORTB.OUT &= imask;
	_delay_loop_2(_tx_delay);
	for (uint8_t i = 8; i > 0; --i) {
		if (b & 1)
		PORTB.OUT |= mask;
		else
		PORTB.OUT &= imask;
		_delay_loop_2(_tx_delay);
		b >>= 1;
	}
	PORTB.OUT |= mask;
	_delay_loop_2(_tx_delay);
	sei();
}*/
