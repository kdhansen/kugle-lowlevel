#ifndef KUGLE_VELOCITY_CONTROLLER_H
#define KUGLE_VELOCITY_CONTROLLER_H

#include "motor.h"

class VelocityController
{
private:
    const Motor& motor;

public:
    VelocityController(const Motor& m);
};

#endif
