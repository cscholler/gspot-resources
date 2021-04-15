#ifndef MY_LOCK_H
#define MY_LOCK_H

#include <Arduino.h>
#include "Button.h"

class Lock {
  
  private:
    Button button1;
    Button button2;
    bool locked; // true is locked, false is unlocked
    
   public:
    Lock();
    Lock(Button first_button, Button second_button);
    
    void setLock(Button first_button, Button second_button);
    void update();
    
    bool isLocked();
};

#endif
