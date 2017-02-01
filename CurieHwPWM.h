/*
	CurieHwPWM.h - Library for generating PWM signals using the hardware PWM counters.
	Created by Lee Johnston, March 26, 2016.
	Released into the public domain.
*/

#ifndef CurieHwPWM_h
#define CurieHwPWM_h

#include "Arduino.h"
#include "variant.h"
#include "pins_arduino.h"
#include "scss_registers.h"

#define SOC_PWM 3

typedef enum {
  UNRESERVED = 0,
  UNCONFIGURED,
  RUNNING,
  STOPPED
} CurieHwPWMStateType;

class CurieHwPWM {
	PinDescription *p = NULL;
	uint32_t period = 32000000/490;
	uint32_t low = 0;
	uint32_t high = 0;

  public:
    CurieHwPWM(uint8_t pin);
    ~CurieHwPWM();
	void reserve();
    void dutyCycle(double dc);
    void start();
    void stop();
    void release();
    void setRate(double f);
};

#endif