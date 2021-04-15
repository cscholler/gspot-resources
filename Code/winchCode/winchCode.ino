#include "Button.h"
#include "Motor.h"
#include "Lock.h"
#include "Actuator.h"

enum State_enum {CALIBRATE, WAIT, MOVE, HOLD, ADJUST};
enum Switch_enum {MIN, MAX};

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

#define WH_TOP 1
#define WH_BOTTOM 1
#define DH_TOP 1
#define DH_BOTTOM 1
#define WF_TOP 1
#define WF_BOTTOM 1
#define DF_TOP 1
#define DF_BOTTOM 1

#define NORMALLY_CLOSED false
#define NORMALLY_OPEN true

Motor wh_motor(H_IN1, H_IN2, WH_ENA);
Motor dh_motor(H_IN1, H_IN2, DH_ENA);
Motor wf_motor(F_IN1, F_IN2, WF_ENA);
Motor df_motor(F_IN1, F_IN2, DF_ENA);

Button upButton(UP_PIN, NORMALLY_OPEN);
Button dnButton(DN_PIN, NORMALLY_OPEN);

Button wh_button_min(WH_BOTTOM, NORMALLY_CLOSED);
Button wh_button_max(WH_TOP, NORMALLY_CLOSED);
Button dh_button_min(DH_BOTTOM, NORMALLY_CLOSED);
Button dh_button_max(DH_TOP, NORMALLY_CLOSED);
Button wf_button_min(WF_BOTTOM, NORMALLY_CLOSED);
Button wf_button_max(WF_TOP, NORMALLY_CLOSED);
Button df_button_min(DF_BOTTOM, NORMALLY_CLOSED);
Button df_button_max(WF_TOP, NORMALLY_CLOSED);

Lock lock(upButton, dnButton);

Actuator wh_actuator(wh_button_min, wh_button_max, wh_motor, lock);
Actuator dh_actuator(dh_button_min, dh_button_max, dh_motor, lock);
Actuator wf_actuator(wf_button_min, wf_button_max, wf_motor, lock);
Actuator df_actuator(df_button_min, df_button_max, df_motor, lock);

bool goingUp;
bool atTop;
Actuator bed[4] = {wh_actuator, dh_actuator, wf_actuator, df_actuator};

void setup() {
  goingUp = false;
  atTop = false;
}

void loop() {
  lock.update();
  if (upButton.isPressed() && !dnButton.isPressed() && !lock.isLocked()) {
    int checkState[4] = {0, 0, 0, 0};
    for (int i = 0; i < sizeof(bed); i++) {
      if (checkState[0] == 1 && checkState[1] == 1 && checkState[2] == 1 && checkState[3] == 1) {
        for (int j = 0; i < sizeof(bed); i++) 
          if (bed[i].moveToMax() == HOLD) atTop = true;
      } else {
        if (bed[i].calibrate(MAX) == WAIT) checkState[i] = 1;
      }
    }
    goingUp = true;
  } else if (!upButton.isPressed() && dnButton.isPressed() && !lock.isLocked()) {
    for (int i = 0; i < sizeof(bed); i++) bed[i].moveToMin();
    goingUp = false;
    atTop = false;
  } else {
    if (atTop) {
      for (int i = 0; i < sizeof(bed); i++) bed[i].moveToMax();
    } else {
      wh_motor.hold();
      dh_motor.hold();
      wf_motor.hold();
      df_motor.hold();
    }
    goingUp = false;
  }
  delay(10);
}
