#ifndef MY_MOTOR_H
#define MY_MOTOR_H

#include <Arduino.h>

class Motor {
  
  private:
    byte IN1;
    byte IN2;
    byte ENA;
    int defaultSpeed = 255;
    
   public:
    Motor();
    Motor(byte IN1, byte IN2, byte ENA);
    
    void setMotor(byte IN1, byte IN2, byte ENA);
    void init();
    
    void up();
    void down();
    void idle();
    void hold();
    void moveAtSpeed(int moveSpeed);
};

#endif
