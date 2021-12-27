#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif
#include "helper_functions.h"

void setTOCM(bool set){
	cli();
	if (set){
		TIMSK0 |= (1<<OCIE0A);
		TCNT0 = 0;
	} else {
		TIMSK0 &= ~(1<<OCIE0A);
	}
	sei();
}

bool isFingered(void){
	/*
	PF7  x_le    LOW
	PF6  x_ri    Hi Z
	PF5  y_up    ADC
	PF4  y_lo    Hi Z
	*/

	DDRF = 0x80;											// Set PF7 as output, others as input
	PORTF = 0x00;
	ADMUX &= ~(1<<MUX1);									// Connect ADC5
	ADCSRA |= (1<<ADSC) | (1<<ADEN);
	setTOCM(true);
	if (getADC() < 100) {
		return true;
	} else {
		return false;
	}
}

uint16_t getADC(){
	setTOCM(true);											// Enable Timer Output Compare Match interrupt
	while ((ADCSRA & (1<<ADSC))){							// Wait for Conversion to complete (about 13 ADC cycles/104us)
		// do nothing
	}
	uint16_t val = ADCL;									// Read ADCL ...
	val |= (ADCH<<8);										// and ADCH left shifted by 8 bit
	return val;
}

int readX() {
	/*
	Reading X             | Reading Y
	------------------------------------------
	ADC7  x_le    HIGH    | ADC7  x_le    ADC
	ADC6  x_ri    LOW     | ADC6  x_ri    Hi Z
	ADC5  y_up    ADC     | ADC5  y_up    HIGH
	ADC4  y_lo    Hi Z    | ADC4  y_lo    LOW
	*/

	setTOCM(false);											// Disable TOCM interrupt
	// Setting up pin modes
	DDRF = 0xC0;											// Setting PF7 and PF6 as output
	PORTF = 0x80;											// Setting PF7 HIGH
	ADMUX &= ~(1<<MUX1);									// Making sure ADC5 is connected to ADC
	// Enable ADC and start conversion
	ADCSRA |= (1<<ADSC) | (1<<ADEN);
	return getADC();
}

int readY() {
	/*
	Reading X             | Reading Y
	------------------------------------------
	ADC7  x_le    HIGH    | ADC7  x_le    ADC
	ADC6  x_ri    LOW     | ADC6  x_ri    Hi Z
	ADC5  y_up    ADC     | ADC5  y_up    HIGH
	ADC4  y_lo    Hi Z    | ADC4  y_lo    LOW
	*/

	setTOCM(false);											// Disable TOCM interrupt
	// Setting up pin modes
	DDRF = 0x30;											// Setting PF5 and PF4 as output
	PORTF = 0x20;											// Setting PF5 HIGH
	ADMUX |= (1<<MUX1);										// Connecting ADC7 to ADC
	// Enable ADC and start conversion
	ADCSRA |= (1<<ADSC) | (1<<ADEN);
	return getADC();
}