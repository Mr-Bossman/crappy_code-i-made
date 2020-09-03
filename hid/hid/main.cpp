#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
uint16_t _tx_delay;
ISR(USB_GEN_vect){
	if(UDINT&(1<<EORSTI)){	
	  //disables all endpoints except 0
	  for (uint8_t i = 1; i <= 6; i++) {
		UENUM = (UENUM & 0xF8) | i; // selects endpoints
	    UECONX &= ~(1 << EPEN); // disables selected endpoint
	  }
	  UENUM &= (~7);  // selects endpoint 0
	  UECONX |= (1<<EPEN); // enables selected end point
      UECFG0X = 0;   // endpoint 0 is a control endpoint
      UECFG1X = (1 << EPSIZE1) | (1 << EPSIZE0) | (1 << ALLOC);
	  if (!(UESTA0X & (1 << CFGOK))) {
		  //error
	  }
	  UENUM &= (~7); // selects endpoint 0
	  UDINT &= ~(1 << EORSTI); // clears usb reset bit
	  UDADDR |= 0b10000000; // enables usb addressing
	}
}
void Send (uint8_t b) {
	uint8_t mask = 0b10000000;
	uint8_t imask = ~mask;
	uint8_t oSREG = SREG;
	cli();
	PORTC &= imask;
	_delay_loop_2(_tx_delay);
	for (uint8_t i = 8; i > 0; --i) {
		if (b & 1)
		PORTC |= mask;
		else
		PORTC &= imask;
		_delay_loop_2(_tx_delay);
		b >>= 1;
	}
	PORTC |= mask;
	SREG = oSREG;
	_delay_loop_2(_tx_delay);
	sei();
}

int main (void) {
	_tx_delay = 0;
	uint16_t bit_delay = (F_CPU / 9600) / 4;
	if (bit_delay > 15 / 4)
	_tx_delay = bit_delay - (15 / 4);
	else
	_tx_delay = 1;
	PORTC = 0b10000000;
	DDRC = 0b10000000;
	cli();
	USBCON &= 0b11111110; // disables VBUS transition interrupt
	UDIEN &= 0b10000010; //disables some interrupts
	UEIENX &= 0b00100000; //disables some more interrupts
	sei();
	
   //prescaler setup
	PLLCSR = 0;
	PLLCSR |= (1 << PINDIV);
	PLLFRQ = 0;
	PLLFRQ |= (1 << PLLUSB) | (1 << PDIV3) | (1 << PDIV1) | (1 << PLLTM0);
	PLLCSR |= (1 << PLLE);
	while (!(PLLCSR & (1 << PLOCK)));
	
	UHWCON |= (1 << UVREGE); //sets usb pad regulator enable
	USBCON |= (1 << USBE) | (1<<OTGPADE); // enables usb pad and usb controller
	UDCON &= ~(1 << LSM); // sets full speed usb
	USBCON &= ~(1 << FRZCLK); // unfreezes clock to usb controller
	while (!(USBSTA & (1 << VBUS))); // waits till usb is detected
	UDCON &= ~(1 << DETACH); // set pull up on usb pins
	UDIEN |= (1<<EORSTE); // enables usb reset interrupt
	while (!(UEINTX & (1 << RXSTPI))); // waits for usb setup packet
	UEINTX &= ~(1 << RXSTPI); // clears usb setup packet received bit
	while (1) {
		UEINTX &= ~(1 << TXINI); 
		while (!(UEINTX & (1 << TXINI))); 
		UEDATX = 65;
        UEINTX &= ~(1 << TXINI); 
	}
}

