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

// Yellow
#define WH_TOP A3
#define WH_BOTTOM A2
// Green
#define DH_TOP 9
#define DH_BOTTOM 8
// Red
#define WF_TOP A5
#define WF_BOTTOM A4
// White
#define DF_TOP A1
#define DF_BOTTOM A0

#define NORMALLY_CLOSED true
#define NORMALLY_OPEN false

Motor wh_motor(H_IN1, H_IN2, WH_ENA);
Motor dh_motor(H_IN1, H_IN2, DH_ENA);
Motor wf_motor(F_IN1, F_IN2, WF_ENA);
Motor df_motor(F_IN1, F_IN2, DF_ENA);

Button upButton(UP_PIN, NORMALLY_CLOSED);
Button dnButton(DN_PIN, NORMALLY_CLOSED);

Button wh_button_min(WH_BOTTOM, NORMALLY_CLOSED);
Button wh_button_max(WH_TOP, NORMALLY_CLOSED);
Button dh_button_min(DH_BOTTOM, NORMALLY_CLOSED);
Button dh_button_max(DH_TOP, NORMALLY_CLOSED);
Button wf_button_min(WF_BOTTOM, NORMALLY_CLOSED);
Button wf_button_max(WF_TOP, NORMALLY_CLOSED);
Button df_button_min(DF_BOTTOM, NORMALLY_CLOSED);
Button df_button_max(DF_TOP, NORMALLY_CLOSED);

Lock lock(upButton, dnButton);

Actuator wh_actuator(wh_button_max, wh_button_min, wh_motor, lock);
Actuator dh_actuator(dh_button_max, dh_button_min, dh_motor, lock);
Actuator wf_actuator(wf_button_max, wf_button_min, wf_motor, lock);
Actuator df_actuator(df_button_max, df_button_min, df_motor, lock);

bool goingUp;
bool atTop;
bool atBottom;

void setup() {
  Serial.begin(9600);
  goingUp = false;
  atTop = false;
  atBottom = false;
}

void loop() {
  lock.update();
  //    wh_motor.moveAtSpeed(1);
  //    dh_motor.moveAtSpeed(1);
  //    wf_motor.moveAtSpeed(1);
  //    df_motor.moveAtSpeed(1);
  if (upButton.isPressed() && !dnButton.isPressed() && !lock.isLocked()) {
    Serial.println("up");
    if (atBottom) {
      Serial.println("At bottom");
      int actuatorCounter = 0;
      if (wh_actuator.calibrate(MIN) == WAIT) actuatorCounter++;
      if (dh_actuator.calibrate(MIN) == WAIT) actuatorCounter++;
      if (wf_actuator.calibrate(MIN) == WAIT) actuatorCounter++;
      if (df_actuator.calibrate(MIN) == WAIT) actuatorCounter++;

      if (actuatorCounter >= 4) {
        Serial.println("Calibration complete");
        atBottom = false;
      }
    } else if (!atTop){
      Serial.println("Moving up");
      int actuatorCounter = 0;
      if (wh_actuator.moveToMax() == WAIT) actuatorCounter++;
      if (dh_actuator.moveToMax() == WAIT) actuatorCounter++;
      if (wf_actuator.moveToMax() == WAIT) actuatorCounter++;
      if (df_actuator.moveToMax() == WAIT) actuatorCounter++;

      if (actuatorCounter >= 4) {
        Serial.println("Reached top");
        atTop = true;
      }
    } else if (atTop) {
      Serial.println("At top");
      wh_actuator.hold();
      dh_actuator.hold();
      wf_actuator.hold();
      df_actuator.hold();
    }

    if (!wh_button_max.isPressed() || !dh_button_max.isPressed() || !wf_button_max.isPressed() || !df_button_max.isPressed()) {
      atTop = false; 
    }

    goingUp = true;
  } else if (!upButton.isPressed() && dnButton.isPressed() && !lock.isLocked()) {
    Serial.println("down");
    if (!atBottom) {
      Serial.println("Not at bottom");
      int actuatorCounter = 0;
      if (wh_actuator.moveToMin() == WAIT) actuatorCounter++;
      if (dh_actuator.moveToMin() == WAIT) actuatorCounter++;
      if (wf_actuator.moveToMin() == WAIT) actuatorCounter++;
      if (df_actuator.moveToMin() == WAIT) actuatorCounter++;

      if (actuatorCounter >= 4 ) {
        Serial.print("Reached bottom");
        atBottom = true;
      }
    } else {
      Serial.print("At bottom");
      wh_actuator.hold();
      dh_actuator.hold();
      wf_actuator.hold();
      df_actuator.hold();
    }

    goingUp = false;
    atTop = false;
  } else {
    Serial.println("hold");
    wh_motor.hold();
    dh_motor.hold();
    wf_motor.hold();
    df_motor.hold();

    goingUp = false;
  }
  delay(10);
}
