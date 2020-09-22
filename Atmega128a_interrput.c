/*
 * 3.c
 *
 * Created: 2020-09-22 오후 2:46:23
 * Author : IT학교
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int swflag = 0;
unsigned int temp = 0, i =0;

ISR(INT5_vect){
	temp = ~(1<<i);
	i++;
	if(i >8) i = 0;
	PORTC = temp;
	_delay_ms(100);
}

void led_init(){
	DDRC = 0xFF;
	PORTC = 0xFF;
}

void swInterrupt_init(){
	DDRE = (0<<PE5);
	EIMSK= (1<<INT5);
	EICRB = (0<<ISC51) | (0<<ISC50);
	EIFR = (0<<INTF5);
}

int main(void){
	led_init();
    swInterrupt_init();
	sei();
	
    while (1) 
    {
		PORTC = temp;
    }
}

