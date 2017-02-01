#ifndef KUGLE_IMU_H
#define KUGLE_IMU_H
#include <MadgwickAHRS.h>

class IMU
{
private:
    int _rate;
    int _acc_range;
    int _gyro_range;

    Madgwick _filter;

    float convertRawAcceleration(int aRaw);
    float convertRawGyro(int gRaw);

public:
    // Constructor
    // rate - supported values: 25, 50, 100, 200, 400, 800, 1600 (Hz)
    // accelerometer range supported values: 2, 4, 8, 16 (G)
    // gyroscope range - supported values: 125, 250, 500, 1000, 2000 (degrees/second)
    IMU(int rate, int accelerometer_range, int gyro_range);

    void update();
    float getRoll();
    float getPitch();
    float getYaw();
};

#endif