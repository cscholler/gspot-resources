#include "Lock.h"

Lock::Lock() {}

Lock::Lock(Button first_button, Button second_button) {
  this->button1 = first_button;
  this->button2 = second_button;
  locked = false;
  update();
}

void Lock::setLock(Button first_button, Button second_button) {
  this->button1 = first_button;
  this->button2 = second_button;
  locked = false;
  update();
}

void Lock::update() {
  if (button1.isPressed() && button2.isPressed()) {
    locked = true;
  } else if (!button1.isPressed() && !button2.isPressed()) {
    locked = false;
  }
}

bool Lock::isLocked() {
  update();
  return locked;
}
