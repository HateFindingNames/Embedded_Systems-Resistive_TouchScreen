#ifdef NEWSTUFF
#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include <Arduino.h>
#include "defines.h"

class FourWireRTP() {
	public:
		void setTOCM(bool set);
		uint16_t getADC();
		int readX(void);
		int readY(void);
		bool isFingered(void);
		float doSomeMedianFiltering(int *p, int n, int clamp);
	private:
		int _xvals[OVERSAMPLING] {0};
		int _yvals[OVERSAMPLING] {0};
		int *_p;
};

#endif
#endif