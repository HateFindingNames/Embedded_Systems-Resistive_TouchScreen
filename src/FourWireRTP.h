#ifndef FOURWIRERTP_H
#define FOURWIRERTP_H
#include <Arduino.h>
#include "defines.h"

class FourWireRTP_ {
	public:
		FourWireRTP_();
		int readX(void);
		int readY(void);
		bool isFingered(void);
		int doSomeMedianFiltering(int *p, int n, int clamp);
	private:
		void setTOCM(bool set);
		uint16_t getADC();
};

extern FourWireRTP_ FourWireRTP;
#endif