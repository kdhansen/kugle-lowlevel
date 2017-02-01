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
    long pos = 0;
    long old_pos = 0;
    unsigned int encoder_resolution = 1920;
    double velocity = 0.;

    // Velocity controller stuff
    // P gain
    double k_p = 0.01;
    // Velocity setpoint
    double ref_velocity = 0;

public:
    enum mode {CW, CCW, BRAKE, FREE};

    Motor(int pwm, int enable_a, int enable_b, int encoder_a, int encoder_b);

    void onEncoderChangeA();
    void onEncoderChangeB();

    void setVoltage(double v);
    void setMode(mode m);

    int getPosition();

    double getVelocity();
    void setVelocity(double v);

    void update(double d_t);
    void setPGain(double p);
};

#endif
