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

uint8_t Actuator::getState() {
  return state;
}

void Actuator::setState(uint8_t newState) {
  this->state = newState;
}

uint8_t Actuator::calibrate(uint8_t calibrationSwitchEnum) {
  state = CALIBRATE;
  Button calibrationSwitch = (calibrationSwitchEnum == MIN) ? minSwitch : maxSwitch;
  switch (state) {
    case CALIBRATE:
      if (calibrationSwitch.isPressed()) {
        calibrationSwitchEnum == MIN ? motor.up() : motor.down();
        break;
      }
      else state = WAIT;

    case WAIT:
      motor.moveAtSpeed(1);
      if (calibrationSwitch.isPressed()) state = CALIBRATE;

      break;
  }
  return state;
}

uint8_t Actuator::moveToMax() {
  state = MOVE;
  switch (state) {
    case MOVE:
      if (!maxSwitch.isPressed()) {
        Serial.println("State: MOVE");
        motor.up();
        break;
      }
      else {
        state = WAIT;
      }

    case WAIT:
    Serial.println("State: WAIT");
      motor.moveAtSpeed(1);
      break;
  }
  return state;
}

uint8_t Actuator::moveToMin() {
  state = MOVE;
  switch (state) {
    case MOVE:
      if (!minSwitch.isPressed()) {
        motor.down();
        break;
      }
      else {
        state = WAIT;
      }

    case WAIT:
      motor.moveAtSpeed(-1);
      break;
  }
  return state;
}

void Actuator::hold() {
  motor.hold();
}
