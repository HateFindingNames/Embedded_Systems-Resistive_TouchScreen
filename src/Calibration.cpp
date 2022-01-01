#include <Arduino.h>
#include "Calibration.h"
#include "FourWireRTP.h"

// FourWireRTP fwrtp;

// Constructor - flash LED_L 3 times
Calibration_::Calibration_() {
	for (int i = 0; i < 3; i++) {
		PORTC |= (1<<LED_L);                                    // LED_L on
		delay(250);
		PORTC &= ~(1<<LED_L);                                   // LED_L off
		delay(250);
	}
}

int Calibration_::getLowerX(int samples, int clamp) {
	Serial.println("Calibrating X MIN:");
	Serial.println("Move stylus to the far left until LED flashes ...");

	while (FourWireRTP.isFingered()) {
		for (int i = 0; i < samples; i++) {
			_vals[i] = FourWireRTP.readX();
		}
		_buffer = FourWireRTP.doSomeMedianFiltering(_vals, samples, clamp);
		if (_buffer < _xmin) {
			_xmin = _buffer;
		}
	}

	PORTC |= (1<<LED_L);                                    // LED_L on
	delay(500);
	PORTC &= ~(1<<LED_L);                                   // LED_L off
	return _xmin;
}

int Calibration_::getUpperX(int samples, int clamp) {
	Serial.println("Calibrating X MAX:");
	Serial.println("Move stylus to the far right until LED flashes ...");

	while (FourWireRTP.isFingered()) {
		for (int i = 0; i < samples; i++) {
			_vals[i] = FourWireRTP.readX();
		}
		_buffer = FourWireRTP.doSomeMedianFiltering(_vals, samples, clamp);
		if (_buffer > _xmax) {
			_xmax = _buffer;
		}
	}

	PORTC |= (1<<LED_L);                                    // LED_L on
	delay(500);
	PORTC &= ~(1<<LED_L);                                   // LED_L off
	return _xmax;
}

int Calibration_::getLowerY(int samples, int clamp) {
	Serial.println("Calibrating Y MIN:");
	Serial.println("Move stylus to the bottom until LED flashes ...");

	while (FourWireRTP.isFingered()) {
		for (int i = 0; i < samples; i++) {
			_vals[i] = FourWireRTP.readX();
		}
		_buffer = FourWireRTP.doSomeMedianFiltering(_vals, samples, clamp);
		if (_buffer < _xmin) {
			_ymin = _buffer;
		}
	}

	PORTC |= (1<<LED_L);                                    // LED_L on
	delay(500);
	PORTC &= ~(1<<LED_L);                                   // LED_L off
	return _ymin;
}

int Calibration_::getUpperY(int samples, int clamp) {
	Serial.println("Calibrating Y MAX:");
	Serial.println("Move stylus to the top until LED flashes ...");

	while (FourWireRTP.isFingered()) {
		for (int i = 0; i < samples; i++) {
			_vals[i] = FourWireRTP.readX();
		}
		_buffer = FourWireRTP.doSomeMedianFiltering(_vals, samples, clamp);
		if (_buffer > _ymax) {
			_ymax = _buffer;
		}
	}

	PORTC |= (1<<LED_L);                                    // LED_L on
	delay(500);
	PORTC &= ~(1<<LED_L);                                   // LED_L off
	return _ymax;
}

Calibration_ Calibration;