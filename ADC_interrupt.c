#include "myUtil.h"
int adc_data = 0;

ISR(ADC_vect){
	adc_data = (int)ADCW;
}

void adc_init(){
	ADMUX = (1<<REFS1)|(1<<REFS0)|(6<<MUX0);
	ADCSRA = (1<<ADEN)|(7<<ADPS0)|(1<<ADFR)|(1<<ADIE);
	ADCW = 0x00;
}

int main(void)
{
    fnd_init();
	adc_init();
	sei();
	ADCSRA |= (1<<ADSC);
	
    while (1)
    {
		fnd_displayAll(adc_data);
    }
}

