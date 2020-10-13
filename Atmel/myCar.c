#include <avr/io.h>
#include <util/delay.h>

void stop(){
		PORTE &= (0<<PE3);
		PORTH &= (0<<PH3);
}

void R_forword(){
		DDRG |= (1<<PG5);
		PORTG|= (1<<PG5);
		PORTE |= (1<<PE3);
}

void L_forword(){
		DDRH &= (0<<PH4);
		PORTH |= (1<<PH3);
}

void R_backword(){
		PORTG &= (0<<PG5);
		PORTE |= (1<<PE3);
}

void L_backword(){
		DDRH |= (1<<PH4);
		PORTH |= (1<<PH4);
		PORTH |= (1<<PH3);
}

//==========================
void forword(){
	L_forword();
	R_forword();
}

void backword(){
	L_backword();
	R_backword();
}

void Right(){
	L_forword();
	R_backword();
}

void Left(){
	R_forword();
	L_backword();
}

//==============================
int main(void)
{
	
	DDRK = 0xFF;
	PORTK = 0xFF;
    
    while (1) 
    {
		Right();
    }
}

