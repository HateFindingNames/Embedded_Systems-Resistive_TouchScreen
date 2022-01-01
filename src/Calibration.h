#pragma once
#ifndef CALIBRATION_H
#define CALIBRATION_H
#include <Arduino.h>
#include "defines.h"

class Calibration_ {
	public:
		Calibration_(void);
		int getLowerX(int samples, int clamp);
		int getUpperX(int samples, int clamp);
		int getLowerY(int samples, int clamp);
		int getUpperY(int samples, int clamp);
	private:
		int _xmin;
		int _xmax;
		int _ymin;
		int _ymax;
		int _vals[OVERSAMPLING] {0};
		int _buffer;
};

extern Calibration_ Calibration;

#endif