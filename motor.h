#ifndef KUGLE_MOTOR_H
#define KUGLE_MOTOR_H

#include "CurieHwPWM.h"

class Motor
{
private:
  // Motor pins
  int pwm_pin, enable_a_pin, enable_b_pin;
  // Encoder pins
  int encoder_a_pin, encoder_b_pin;
  // Encoder position
  int pos = 0;
  // PWM object
  CurieHwPWM hw_pwm;

public:
  enum mode {CW, CCW, BRAKE, FREE};

  Motor(int pwm, int enable_a, int enable_b, int encoder_a, int encoder_b);

  void onEncoderChangeA();
  void onEncoderChangeB();

  void setVoltage(double v);
  void setMode(mode m);

  int getPosition();

  void setPwmRate(double r);
};

#endif
