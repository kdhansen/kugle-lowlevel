#include "arduino.h"
#include "motor.h"

typedef void(*isrFnc_t)(void);

Motor::Motor(int pwm, int enable_a, int enable_b, int encoder_a, int encoder_b)
{
    pwm_pin = pwm;
    pinMode(pwm_pin, OUTPUT);
    enable_a_pin = enable_a;
    pinMode(enable_a_pin, OUTPUT);
    enable_b_pin = enable_b;
    pinMode(enable_b_pin, OUTPUT);
    encoder_a_pin = encoder_a;
    pinMode(encoder_a_pin, INPUT_PULLUP);
    encoder_b_pin = encoder_b;
    pinMode(encoder_b_pin, INPUT_PULLUP);
}

void Motor::onEncoderChangeA()
{
  // Look for low-to-high status of channel A
  if(digitalRead(encoder_a_pin) == HIGH) {
    // Check low/high status of channel B
    if(digitalRead(encoder_b_pin) == LOW) {
      pos += 1; // CW
    }
    else {
      pos -= 1; // CCW
    }
  }
  // Must be high-to-low on channel A 
  else {
    // Check channel B to get direction
    if(digitalRead(encoder_b_pin) == HIGH) {
      pos += 1; // CW
    }
    else {
      pos -= 1; // CCW
   }
  }
}

void Motor::onEncoderChangeB()
{
  // look for a low-to-high on channel B
  if (digitalRead(encoder_b_pin) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoder_a_pin) == HIGH) {  
      pos += 1;         // CW
    } 
    else {
      pos -= 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel A to see which way encoder is turning  
    if (digitalRead(encoder_a_pin) == LOW) {   
      pos += 1;          // CW
    } 
    else {
      pos -= 1;          // CCW
    }
  }
}

void Motor::setVoltage(double v)
{

}

void Motor::setMode(Motor::mode m)
{

}

int Motor::getPosition()
{
    return pos;
}
