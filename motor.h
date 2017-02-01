#ifndef KUGLE_MOTOR_H
#define KUGLE_MOTOR_H

class Motor
{
private:
  // Motor pins
  int pwm_pin, enable_a_pin, enable_b_pin;
  // Encoder pins
  int encoder_a_pin, encoder_b_pin;
  // Encoder position
  int pos = 0;

public:
  enum mode {RUN, BRAKE, FREE};

  Motor(int pwm, int enable_a, int enable_b, int encoder_a, int encoder_b);

  void onEncoderChangeA();
  void onEncoderChangeB();

  void setVoltage(double v);
  void setMode(mode m);

  int getPosition();
};

#endif
