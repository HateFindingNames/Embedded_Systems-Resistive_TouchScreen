#ifdef NEWSTUFF
#pragma once
#ifndef CALIBRATION_H
#define CALIBRATION_H
#include <Arduino.h>
#include "defines.h"

class Calibration {
	public:
		Calibration(void);
		int getLowerX(void);
		int getUpperX(void);
		int getLowerY(void);
		int getUpperY(void);
	private:
		int _xmin;
		int _xmax;
		int _ymin;
		int _ymax;
		int _vals[OVERSAMPLING] {0};
		int _buffer;
};

#endif
#endif