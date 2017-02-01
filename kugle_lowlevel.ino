#include "motor.h"
#include "velocity_controller.h"
#include "imu.h"


// Motor 0 Connections
const int pin_pwm_m0 = 3;
const int pin_enable_a_m0 = A0;
const int pin_enable_b_m0 = A1;
const int pin_encoder_a_m0 = 2;
const int pin_encoder_b_m0 = 7;

// Motor 1 Connections
const int pin_pwm_m1 = 5;
const int pin_enable_a_m1 = A2;
const int pin_enable_b_m1 = A3;
const int pin_encoder_a_m1 = 8;
const int pin_encoder_b_m1 = 10;

// Motor 2 Connections
const int pin_pwm_m2 = 6;
const int pin_enable_a_m2 = A4;
const int pin_enable_b_m2 = A5;
const int pin_encoder_a_m2 = 11;
const int pin_encoder_b_m2 = 12;

// Create an array of motor controllers with the
// above pin assignments.
Motor motors[3] = {
    {pin_pwm_m0, pin_enable_a_m0, pin_enable_b_m0, pin_encoder_a_m0, pin_encoder_b_m0},
    {pin_pwm_m1, pin_enable_a_m1, pin_enable_b_m1, pin_encoder_a_m1, pin_encoder_b_m1},
    {pin_pwm_m2, pin_enable_a_m2, pin_enable_b_m2, pin_encoder_a_m2, pin_encoder_b_m2}
};

// Interrupt service routines for the encoders.
// The Arduino IDE does not let us set class members
// as ISRs, so we wrap them here.
void enc_isr0A() {motors[0].onEncoderChangeA();}
void enc_isr0B() {motors[0].onEncoderChangeB();}
void enc_isr1A() {motors[1].onEncoderChangeA();}
void enc_isr1B() {motors[1].onEncoderChangeB();}
void enc_isr2A() {motors[2].onEncoderChangeA();}
void enc_isr2B() {motors[2].onEncoderChangeB();}

// Create an array of velocity controllers for
// the motors.
VelocityController vel_controllers[3] = {
    {motors[0]}, {motors[1]}, {motors[2]}
};

// Loop rate pacing
const int loop_rate = 25;
const unsigned long microsPerReading = 1000000 / loop_rate;
unsigned long microsPrevious;

// IMU
const int accelerometer_range = 2;
const int gyro_range = 250;
IMU imu(loop_rate, accelerometer_range, gyro_range);

void setup()
{
    // Setup interrupts on encoders
    attachInterrupt(pin_encoder_a_m0, enc_isr0A, CHANGE);
    attachInterrupt(pin_encoder_b_m0, enc_isr0B, CHANGE);
    attachInterrupt(pin_encoder_a_m1, enc_isr1A, CHANGE);
    attachInterrupt(pin_encoder_b_m1, enc_isr1B, CHANGE);
    attachInterrupt(pin_encoder_a_m2, enc_isr2A, CHANGE);
    attachInterrupt(pin_encoder_b_m2, enc_isr2B, CHANGE);

    // Setup the serial connection
    Serial.begin(9600);

    // Initialize variables to pace updates to correct rate
    microsPrevious = micros();
}

void loop() {

    // Check if it's time to update the loop
    unsigned long microsNow = micros();
    if (microsNow - microsPrevious >= microsPerReading) {

        imu.update();

        // print the heading, pitch and roll
        Serial.print("Orientation: ");
        Serial.print(imu.getRoll());
        Serial.print(" ");
        Serial.print(imu.getPitch());
        Serial.print(" ");
        Serial.println(imu.getYaw());
    }
}
