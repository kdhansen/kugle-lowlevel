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

void Motor::onEncoderChange()
{
    pos += 1;
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