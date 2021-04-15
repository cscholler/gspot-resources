#include "Button.h"
#include "Motor.h"
#include "Lock.h"
#include "Actuator.h"

// DoorHead & WindowHead
#define H_IN1 4
#define H_IN2 2
#define WH_ENA 5
#define DH_ENA 3

// DoorFoot & WindowFoot
#define F_IN1 12
#define F_IN2 13
#define WF_ENA 10
#define DF_ENA 11

#define UP_PIN 6  // Yellow
#define DN_PIN 7  // Blue
#define NORMALLY_CLOSED false
#define NORMALLY_OPEN true

Motor windowHead(H_IN1, H_IN2, WH_ENA);
Motor doorHead(H_IN1, H_IN2, DH_ENA);
Motor windowFoot(F_IN1, F_IN2, WF_ENA);
Motor doorFoot(F_IN1, F_IN2, DF_ENA);

Button upButton(UP_PIN, NORMALLY_OPEN);
Button downButton(DN_PIN, NORMALLY_OPEN);

Lock lock(upButton, downButton);

bool goingUp;

void setup() {
  goingUp = false;
}

void loop() {
  lock.update();
  if (upButton.isPressed() && !downButton.isPressed() && !lock.isLocked()) {
      //Up
      goingUp = true;
  } else if (!upButton.isPressed() && downButton.isPressed() && !lock.isLocked()) {
      //Down
      goingUp = false;
  } else {
      //Hold
      goingUp = false;
  }
  delay(10);
}
