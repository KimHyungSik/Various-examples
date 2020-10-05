#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int swflag = 0;
unsigned int temp = 0, i =0;

unsigned char FND_DATA[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f};
	
void fnd_init(){
	DDRG = 0x0f;
	DDRD = 0xf0;
	DDRB = 0xf0;
}

void fnd_display(int data){
	PORTD = (FND_DATA[data] & 0x0F) << 4;
	PORTB = (FND_DATA[data] & 0xF0);
}

ISR(INT7_vect){
	i++;
	if(i >9) i = 0;
}


void swInterrupt_init(){
	DDRE = (0<<PE7);
	EIMSK= (1<<INT7);
	EICRB = (1<<ISC71) | (1<<ISC70);
	EIFR = (0<<INTF7);
}

int main(void){
    swInterrupt_init();
	sei();
    while (1) 
    {
		PORTG =0x02;
		fnd_display(i);
		_delay_ms(100);
    }
}

