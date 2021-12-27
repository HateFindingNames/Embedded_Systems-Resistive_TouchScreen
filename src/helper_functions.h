#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif
#include "defines.h"

void setTOCM(bool set);
uint16_t getADC();
int readX(void);
int readY(void);
bool isFingered(void);