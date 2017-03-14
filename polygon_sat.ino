#define STEP_PIN 10
#define DIR_PIN 16
#define POWER_ENABLE_PIN 14
#define END_SWITCH1 2
#define END_SWITCH2 3

#define LEFT_DIR 1
#define RIGHT_DIR 0

#define STEP_IN_ROTATION 200

int dir, rotation;
long steps, i;


void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(POWER_ENABLE_PIN, OUTPUT);

  digitalWrite(POWER_ENABLE_PIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial1.available() > 0) {

    // max int 31072
    rotation = Serial1.readStringUntil('\n').toInt();

    if (rotation > 0) {
      move(RIGHT_DIR, rotation);
    }

    if (rotation < 0) {
      move(LEFT_DIR, abs(rotation));
    }

  }
}

void move(int dir, unsigned int rotation) {

  digitalWrite(POWER_ENABLE_PIN, LOW);
  digitalWrite(DIR_PIN, dir);

  steps = rotation * STEP_IN_ROTATION;

  doSteps(steps);

  digitalWrite(POWER_ENABLE_PIN, HIGH);

}

boolean isEndSwitch() {

  if (digitalRead(END_SWITCH1) == 1) {
    Serial1.println("END_SWITCH1");
    rollBack(RIGHT_DIR);
    return true;
  }

  if (digitalRead(END_SWITCH2) == 1) {
    Serial1.println("END_SWITCH2");
    rollBack(LEFT_DIR);
    return true;
  }

  return false;
}

boolean isStopInSerial() {

  if (Serial1.available() > 0) {
    if (Serial1.readStringUntil('\n').toInt() == 0) {
      return true;
    }
  }

  return false;

}

void rollBack(int dir) {

  digitalWrite(DIR_PIN, dir);
  for (i = 0; i <= 100; i++) {
    doStep();
  }
}

void doSteps(long steps) {

  for (i = 0; i <= steps; i++) {

    if (isEndSwitch()) {
      return;
    }

    if (isStopInSerial()) {
      return;
    }

    doStep();

  }

  Serial1.println("STOP");

}

void doStep() {

  digitalWrite(STEP_PIN, HIGH);
  delay(1);
  digitalWrite(STEP_PIN, LOW);
  delay(1);

}

