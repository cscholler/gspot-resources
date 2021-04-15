#include "Actuator.h"

enum State_enum {CALIBRATE, WAIT, MOVE, HOLD, ADJUST};

Actuator::Actuator(){}

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
    
int Actuator::moveToMax() {
      switch(state) {
        case CALIBRATE:
          if (minSwitch.isPressed()) motor.up();
          else state = WAIT;
          
          break;
        case WAIT:
          motor.hold();
          if (minSwitch.isPressed()) state = CALIBRATE;

          break;
        case MOVE:
          if (!maxSwitch.isPressed()) motor.up();
          else state = HOLD;

          break;
        case HOLD:
          motor.hold();
          if (!maxSwitch.isPressed()) state = ADJUST;

          break;
        case ADJUST:
          motor.up();
          if (maxSwitch.isPressed()) state = HOLD;

          break;
      }
    }

int Actuator::moveToMin() {
  
}
