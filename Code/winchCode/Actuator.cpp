#include "Actuator.h"

enum State_enum {CALIBRATE, WAIT, MOVE, HOLD, ADJUST};
enum Switch_enum {MIN, MAX};

Actuator::Actuator() {}
//TODO: Make lock do something special when at the top
Actuator::Actuator(Button maxSwitch, Button minSwitch, Motor actuatorMotor, Lock lock) {
  this->maxSwitch = maxSwitch;
  this->minSwitch = minSwitch;
  this->motor = actuatorMotor;
  this->lock = lock;
  this->state = WAIT;
}

void Actuator::setActuator(Button maxSwitch, Button minSwitch, Motor actuatorMotor, Lock lock) {
  this->maxSwitch = maxSwitch;
  this->minSwitch = minSwitch;
  this->motor = actuatorMotor;
  this->lock = lock;
  this->state = WAIT;
}

int Actuator::getState() {
  return state;
}

void Actuator::setState(uint8_t newState) {
  this->state = newState;
}

int Actuator::calibrate(uint8_t calibrationSwitchEnum) {
  state = CALIBRATE;
  Button calibrationSwitch = (calibrationSwitchEnum == MIN) ? minSwitch : maxSwitch;
  switch (state) {
    case CALIBRATE:
      if (calibrationSwitch.isPressed()) {
        motor.up();
        break;
      }
      else state = WAIT;

    case WAIT:
      motor.hold();
      if (calibrationSwitch.isPressed()) state = CALIBRATE;

      break;
  }
}

int Actuator::moveToMax() {
  state = MOVE;
  switch (state) {
    case MOVE:
      if (!maxSwitch.isPressed()) {
        motor.up();
        break;
      }
      else state = HOLD;

    case HOLD:
      if (maxSwitch.isPressed()) {
        motor.hold();
        break;
      }
      else state = ADJUST;

    case ADJUST:
      motor.up();
      if (maxSwitch.isPressed()) state = HOLD;

      break;
  }
  return state;
}

int Actuator::moveToMin() {
  state = MOVE;
  switch (state) {
    case MOVE:
      if (!minSwitch.isPressed()) {
        motor.down();
        break;
      }
      else state = HOLD;

    case HOLD:
      motor.hold();

      break;
  }
  return state;
}
