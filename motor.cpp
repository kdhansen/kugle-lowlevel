#include "motor.h"
#include "arduino.h"

Motor::Motor(int pwm, int enable_a, int enable_b, int encoder_a, int encoder_b):
hw_pwm(pwm)
{
    // Hardware PWM through CurieHwPWM lib.
    pwm_pin = pwm;
    hw_pwm.setRate(10e3);
    hw_pwm.dutyCycle(0.0);
    hw_pwm.start();

    // Enable pins A and B on the motor driver
    enable_a_pin = enable_a;
    pinMode(enable_a_pin, OUTPUT);
    enable_b_pin = enable_b;
    pinMode(enable_b_pin, OUTPUT);

    // Encoder inputs from the motor
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
// Set a voltage between -1 and 1 (unitless).
{
    // Negative rotation is clockwise.
    if (v < 0)
    {
        setMode(mode::CW);
        v = -v;
    }
    else
    {
        setMode(mode::CCW);
    }
    // CurieHwPWM uses 0 to 100 in duty cycle.
    v = 100. * v;
    // Clamp the duty cycle to 100.
    if (v > 100.)
    {
        v = 100.;
    }
    hw_pwm.dutyCycle(v);
}


void Motor::setMode(Motor::mode m)
{
    if (mode::CCW == m)
    {
        digitalWrite(enable_a_pin, LOW);
        digitalWrite(enable_b_pin, HIGH);
    }
    else if (mode::CW == m)
    {
        digitalWrite(enable_a_pin, HIGH);
        digitalWrite(enable_b_pin, LOW);
    }
    else
    {
        digitalWrite(enable_a_pin, LOW);
        digitalWrite(enable_b_pin, LOW);
    }
}

int Motor::getPosition()
{
    return pos;
}

void Motor::setPwmRate(double r)
// Set the PWM rate for the motor driver.
{
    hw_pwm.setRate(r);
}
