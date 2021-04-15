#ifndef MY_ACTUATOR_H
#define MY_ACTUATOR_H

#include <Arduino.h>
#include "Button.h"
#include "Motor.h"
#include "Lock.h"

class Actuator {

  private:
    Button maxSwitch;
    Button minSwitch;
    Motor motor;
    Lock lock;
    uint8_t state;

  public:
    Actuator();
    Actuator(Button maxSwitch, Button minSwitch, Motor actuatorMotor, Lock lock);

    void setActuator(Button maxSwitch, Button minSwitch, Motor actuatorMotor, Lock lock);

    int getState();
    void setState(uint8_t newState);

    int calibrate(uint8_t calibrationSwitch);
    int moveToMax();
    int moveToMin();
};

#endif
