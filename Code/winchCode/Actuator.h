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
    uint8_t state;

  public:
    Actuator();
    Actuator(Button maxSwitch, Button minSwitch, Motor actuatorMotor);

    void setActuator(Button maxSwitch, Button minSwitch, Motor actuatorMotor);

    uint8_t getState();
    void setState(uint8_t newState);

    uint8_t calibrate(uint8_t calibrationSwitch);
    uint8_t moveToMax();
    uint8_t moveToMin();
    void hold();
};

#endif
