#include "Motor.h"

Motor::Motor(){}

Motor::Motor(byte IN1, byte IN2, byte ENA) {
      this->IN1 = IN1;
      this->IN2 = IN2;
      this->ENA = ENA;
      init();
    }

void Motor::setMotor(byte IN1, byte IN2, byte ENA) {
      this->IN1 = IN1;
      this->IN2 = IN2;
      this->ENA = ENA;
      init();
    }

void Motor::init() {
      pinMode(IN1, OUTPUT);
      pinMode(IN2, OUTPUT);
      pinMode(ENA, OUTPUT);
    }

void Motor::up() {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, defaultSpeed);
    }

void Motor::down() {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(ENA, defaultSpeed);
    }

void Motor::idle() {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
    }

void Motor::hold() {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
    }

void Motor::moveAtSpeed(int moveSpeed) {
      if (moveSpeed > 0) {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(ENA, moveSpeed);
      } else if (moveSpeed < 0) {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        analogWrite(ENA, abs(moveSpeed));
      }
    }
