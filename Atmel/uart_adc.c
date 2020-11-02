#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

void init(){
	//단일 6번 채널, free running, polling, 128
	//ad converter
	  ADMUX = (1<<REFS1) | (1<<REFS0) | 6;
	  ADCSRA = (1<<ADEN) | (1<<ADFR) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	 
	 ADCW = 0x00;
	
	//uart
	UDR0 = 0x00;
	UCSR0A = 0x00;
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	UBRR0H = 0x00;
	UBRR0L = 103;
	
	DDRE = 0x02;
	sei();
}

void sendNumder(unsigned int num){
	int i = 0;
	char tempChar [20];
	itoa(num, (unsigned char*)tempChar, 10);
	transmit('\r');
	while(tempChar[i] != '\0'){
		transmit(tempChar[i++]);
	}
	transmit('\n');
}

void transmit(unsigned char data)
{
	while(!(UCSR0A & (1<<UDRE0)))
	{
		;
	}
	UDR0 = data;
}

int main(void)
{
	init();
	
	ADCSRA |= (1<<ADSC);
	
    while (1) 
    {
		sendNumder(ADCW);
		_delay_ms(1000);
    }
}

