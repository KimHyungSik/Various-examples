/*
 * myUtil.c
 *
 * Created: 2020-10-27 오후 3:31:54
 *  Author: IT학교
 */ 
#include "myUtil.h"
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

void fnd_display_set(int index, int data){
	switch(index){
		case 1: //0x01 일
		PORTG = 1;
		break;
		case 2: //0bxxxx 0010 십
		PORTG = 2;
		break;
		case 3: //0bxxxx 0100 백
		PORTG = 4;
		break;
		case 4: //0bxxxx 1000 천
		PORTG = 8;
		break;
		
	}
	fnd_display(data);
}

void fnd_displayAll(int data)
{
	fnd_display_set(1,data/1000);
	_delay_ms(2);
	fnd_display_set(2,(data%1000)/100);
	_delay_ms(3);
	fnd_display_set(3,data%100/10);
	_delay_ms(2);
	fnd_display_set(4,data%10);
	_delay_ms(5);
}
