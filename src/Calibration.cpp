#ifdef NEWSTUFF
#include <Arduino.h>
#include "calibration.h"
#include "helper_functions.h"

// Constructor - flash LED_L 3 times
Calibration::Calibration() {
	for (int i = 0; i < 3; i++) {
		PORTC |= (1<<LED_L);                                    // LED_L on
		delay(250);
		PORTC &= ~(1<<LED_L);                                   // LED_L off
		delay(250);
	}
};

int Calibration::getLowerX() {
	Serial.println("Calibrating X MIN:");
	Serial.println("Move stylus to the far left until LED flashes ...");

	while (isFingered()) {
		for (int i = 0; i < OVERSAMPLING; i++) {
			_vals[i] = FourWireRTP.readX();
		}
		_buffer = FourWireRTP.doSomeMedianFiltering(_vals, OVERSAMPLING, CLAMP);
		if (_buffer < _xmin) {
			_xmin = _buffer;
		}
	}

	PORTC |= (1<<LED_L);                                    // LED_L on
	delay(500);
	PORTC &= ~(1<<LED_L);                                   // LED_L off
	return _xmin;
}

int Calibration::getUpperX() {
	Serial.println("Calibrating X MAX:");
	Serial.println("Move stylus to the far right until LED flashes ...");

	while (isFingered()) {
		for (int i = 0; i < OVERSAMPLING; i++) {
			_vals[i] = FourWireRTP.readX();
		}
		_buffer = FourWireRTP.doSomeMedianFiltering(_vals, OVERSAMPLING, CLAMP);
		if (_buffer > _xmax) {
			_xmax = _buffer;
		}
	}

	PORTC |= (1<<LED_L);                                    // LED_L on
	delay(500);
	PORTC &= ~(1<<LED_L);                                   // LED_L off
	return _xmax;
}

int Calibration::getLowerY() {
	Serial.println("Calibrating Y MIN:");
	Serial.println("Move stylus to the bottom until LED flashes ...");

	while (isFingered()) {
		for (int i = 0; i < OVERSAMPLING; i++) {
			_vals[i] = FourWireRTP.readX();
		}
		_buffer = FourWireRTP.doSomeMedianFiltering(_vals, OVERSAMPLING, CLAMP);
		if (_buffer < _xmin) {
			_ymin = _buffer;
		}
	}

	PORTC |= (1<<LED_L);                                    // LED_L on
	delay(500);
	PORTC &= ~(1<<LED_L);                                   // LED_L off
	return _ymin;
}

int Calibration::getUpperX() {
	Serial.println("Calibrating Y MAX:");
	Serial.println("Move stylus to the top until LED flashes ...");

	while (isFingered()) {
		for (int i = 0; i < OVERSAMPLING; i++) {
			_vals[i] = FourWireRTP.readX();
		}
		_buffer = FourWireRTP.doSomeMedianFiltering(_vals, OVERSAMPLING, CLAMP);
		if (_buffer > _ymax) {
			_ymax = _buffer;
		}
	}

	PORTC |= (1<<LED_L);                                    // LED_L on
	delay(500);
	PORTC &= ~(1<<LED_L);                                   // LED_L off
	return _ymax;
}

#endif