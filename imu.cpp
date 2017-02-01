#include "imu.h"
#include <CurieIMU.h>


IMU::IMU(int rate, int accelerometer_range, int gyro_range)
{
    _rate = rate;
    _acc_range = accelerometer_range;
    _gyro_range = gyro_range;

    // Start the IMU and filter
    CurieIMU.begin();
    CurieIMU.setGyroRate(_rate);
    CurieIMU.setAccelerometerRate(_rate);
    _filter.begin(_rate);
    // Set the accelerometer range to 2G
    CurieIMU.setAccelerometerRange(_acc_range);
    // Set the gyroscope range to 250 degrees/second
    CurieIMU.setGyroRange(_gyro_range);
}

void IMU::update()
{
    int aix, aiy, aiz;
    int gix, giy, giz;
    float ax, ay, az;
    float gx, gy, gz;

    CurieIMU.readMotionSensor(aix, aiy, aiz, gix, giy, giz);

    // convert from raw data to gravity and degrees/second units
    ax = convertRawAcceleration(aix);
    ay = convertRawAcceleration(aiy);
    az = convertRawAcceleration(aiz);
    gx = convertRawGyro(gix);
    gy = convertRawGyro(giy);
    gz = convertRawGyro(giz);

    // update the filter, which computes orientation
    _filter.updateIMU(gx, gy, gz, ax, ay, az);
}

float IMU::convertRawAcceleration(int aRaw) {
  float a = (aRaw * _acc_range) / 32768.0;
  return a;
}

float IMU::convertRawGyro(int gRaw) {
  float g = (gRaw * _gyro_range) / 32768.0;
  return g;
}

float IMU::getRoll()
{
    return _filter.getRoll();
}

float IMU::getPitch()
{
    return _filter.getPitch();
}

float IMU::getYaw()
{
    return _filter.getYaw();
}