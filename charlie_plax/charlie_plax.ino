struct the {
  unsigned ddrx : 3;
  unsigned portx : 3;
};
the a[6] = {0b001,0b100,0b001,0b010 ,0b010,0b100 ,0b010,0b001 ,0b100,0b010 ,0b100,0b001 };
void ledSet(uint8_t in){
  DDRB = 0;
  PORTB = 0;
  DDRB = (~a[in].ddrx);
  PORTB = a[in].portx | 1<<4;
}
void setArray(uint8_t in){
  for(uint8_t b = 0;in;b++,in>>=1){
    if(in&1){
      DDRB = 0;
      PORTB = 0;
      DDRB = (~a[b].ddrx);
      PORTB = a[b].portx | 1<<4;
    }
  }
}

volatile uint8_t thing = 0;
int i = 0;
uint8_t x = 0;
volatile uint8_t prog = 0;
volatile uint8_t letters[][5] = {{0b00000000,0b00100001,0b00111111,0b00100001,0b00000000},{0b00011100,0b00111110,0b00011111,0b00111110,0b00011100},{0b00111111,0b00010000,0b00001000,0b00010000,0b00111111},{0b00000000,0b00100001,0b00111111,0b00100001,0b00000000},{0b00111111,0b00001100,0b00010010,0b00100001},{0b00111111,0b00000001,0b00000001,0b00000001,0b00111111}};//{0b00011111,0b00100100,0b00100100,0b00011111};
inline void tunedDelay(uint16_t delay) { 
  uint8_t tmp=0;

  asm volatile("sbiw    %0, 0x01 \n\t"
    "ldi %1, 0xFF \n\t"
    "cpi %A0, 0xFF \n\t"
    "cpc %B0, %1 \n\t"
    "brne .-10 \n\t"
    : "+r" (delay), "+a" (tmp)
    : "0" (delay)
    );
}
uint8_t rx_pin_read()
{
  return *((uint8_t*)0x29) & 0b00000001;
}
uint8_t recv()
{
  uint8_t d = 0;
  tunedDelay(114);
  for (uint8_t i=0x1; i; i <<= 1)
  {
    tunedDelay(236);
    uint8_t noti = ~i;
    if (!PINB&16)
      d |= i;
    else
      d &= noti;
  }
  tunedDelay(236);
  return d;
}
void setup() {  
  DDRB = 0;
  PORTB |= 1<<4; 
  uint8_t i  =0;
  while(1){
    if(!(PINB&16)){
      uint8_t x = recv();
      if(x){
      }
      _delay_loop_2(0);
      _delay_loop_2(0);
      _delay_loop_2(0);
      for(uint8_t set = 0; set < 6; set++){//witch letter am i on
        for(uint8_t col=0;col<5;col++){ // select columb of the letter
         uint8_t timedelay = 120; //set wis=dth delay
          while(timedelay--){             
           setArray(letters[set][col]);//set the array to the columb of the specified letter
          }
        }
        DDRB = 0; //clear
        _delay_loop_2(10000);// white space between the letters
      }
      PORTB |= 1<<4;// turn on pull up if not on
    } 
  }
  /*uint8_t on;
  uint8_t c;
  while(1){
    if(prog){
      int t = 0;
      if(PINB&8 == 0){
        t = millis();
        while(PINB&8 == 0);
        t = millis()-t;
       }
       if(t >100){
        if(t > 400){
          letters[on]=c;
  
          on++;
          c=0;
        }else{
          c++;
          }
       }
    }else{
       on = 0;
       c = 0;*/

  //}
}

/*ISR(PCINT0_vect){
  int t = i;
  i=millis()-t;
  if(t != 0){
    if(i >2000)prog ^= 1,i =0;
    else i =0;
  }
}*/

// check if there is more than 20 letters
void loop() {
}

