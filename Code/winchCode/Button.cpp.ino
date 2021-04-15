#include "Button.h"

Button::Button(){}

Button::Button(byte pin, bool normallyClosed) {
      this->pin = pin;
      this->normallyClosed = normallyClosed;
      lastReading = LOW;
      init();
    }

void Button::setButton(byte pin, bool normallyClosed) {
      this->pin = pin;
      this->normallyClosed = normallyClosed;
      lastReading = LOW;
      init();
    }

void Button::init() {
      pinMode(pin, INPUT);
      update();
    }

void Button::update() {
      byte newReading = digitalRead(pin);
      
      if (newReading != lastReading) {
        lastDebounceTime = millis();
      }
      if (millis() - lastDebounceTime > debounceDelay) {
        state = newReading;
      }
      lastReading = newReading;
    }
    
byte Button::getState() {
      update();
      return state;
    }
    
bool Button::isPressed() {
      return (normallyClosed ? getState() == LOW : getState() == HIGH);
    }
