class Motor {
  private:
    byte IN1;
    byte IN2;
    byte ENA;
    int defaultSpeed = 255;
   public:
    Motor(byte IN1, byte IN2, byte ENA) {
      this->IN1 = IN1;
      this->IN2 = IN2;
      this->ENA = ENA;
      init();
    }
    void init() {
      pinMode(IN1, OUTPUT);
      pinMode(IN2, OUTPUT);
      pinMode(ENA, OUTPUT);
    }
    void up() {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, defaultSpeed);
    }
    void down() {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(ENA, defaultSpeed);
    }
    void idle() {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
    }
    void hold() {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
    }
    void moveAtSpeed(int moveSpeed) {
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
};

class Button {
  private:
    byte pin;
    byte state;
    byte lastReading;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;
  public:
    Button() {
      
    }
    Button(byte pin) {
      this->pin = pin;
      lastReading = LOW;
      init();
    }
    void init() {
      pinMode(pin, INPUT);
      update();
    }
    void update() {
      byte newReading = digitalRead(pin);
      
      if (newReading != lastReading) {
        lastDebounceTime = millis();
      }
      if (millis() - lastDebounceTime > debounceDelay) {
        state = newReading;
      }
      lastReading = newReading;
    }
    byte getState() {
      update();
      return state;
    }
    bool isPressed() {
      return (getState() == HIGH);
    }
}; 

class Lock {
  private:
    Button button1;
    Button button2;
    bool locked; // true is locked, false is unlocked
  public:
    Lock(Button button1, Button button2) {
      this->button1 = button1;
      this->button2 = button2;
      locked = false;
      update();
    }
  void update() {
    if (button1.isPressed() && button2.isPressed()) {
      locked = true;
    } else if (!button1.isPressed() && !button2.isPressed()) {
      locked = false;
    }
  }
  bool isLocked() {
    update();
    return locked;
  }
};

Motor windowHead(4, 2, 5);
Motor doorHead(4, 2, 3);
Motor windowFoot(12, 13, 10);
Motor doorFoot(12, 13, 11);
Button upButton(6); // Yellow
Button downButton(7); //Blue
Lock lock(upButton, downButton);

bool goingUp = false;

void setup() {}

void loop() {
  lock.update();
  if (upButton.isPressed() && !downButton.isPressed() && !lock.isLocked()) {
      allUp();
      goingUp = true;
  } else if (!upButton.isPressed() && downButton.isPressed() && !lock.isLocked()) {
      allDown();
      goingUp = false;
  } else if (!upButton.isPressed() && !downButton.isPressed() && goingUp){
      allMove(100);
  } else if (!upButton.isPressed() && !downButton.isPressed() && !goingUp) {
      allIdle();
  } else {
      allHold();
      goingUp = false;
  }
  delay(10);
}

void allUp() {
  windowHead.up();
  doorHead.up();
  windowFoot.up();
  doorFoot.up();
}
void allDown() {
  windowHead.down();
  doorHead.down();
  windowFoot.down();
  doorFoot.down();
}
void allIdle() {
  windowHead.idle();
  doorHead.idle();
  windowFoot.idle();
  doorFoot.idle();
}
void allHold() {
  windowHead.hold();
  doorHead.hold();
  windowFoot.hold();
  doorFoot.hold();
}
void allMove(int moveSpeed) {
  windowHead.moveAtSpeed(moveSpeed);
  doorHead.moveAtSpeed(moveSpeed);
  windowFoot.moveAtSpeed(moveSpeed);
  doorFoot.moveAtSpeed(moveSpeed);
}
