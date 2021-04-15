#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <Arduino.h>

class Button {
  
  private:
    byte pin;
    byte state;
    byte lastReading;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;
    bool normallyClosed;
    
  public:
    Button();
    Button(byte pin, bool normallyClosed);
    
    void setButton(byte pin, bool normallyClosed);
    void init();
    void update();

    byte getState();
    bool isPressed();
};

#endif
