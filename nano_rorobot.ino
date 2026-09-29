#define MOTOR1_A 7
#define MOTOR1_B 6

#define MOTOR2_A 8
#define MOTOR2_B 9

#define TRIG_PIN A1
#define ECHO_PIN A2

#define FLAME_SENSOR 11

long duration;
float distance;

void setup() {

  pinMode(MOTOR1_A, OUTPUT);
  pinMode(MOTOR1_B, OUTPUT);

  pinMode(MOTOR2_A, OUTPUT);
  pinMode(MOTOR2_B, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(FLAME_SENSOR, INPUT);

  Serial.begin(9600);
}

// ---------- MOVE FORWARD ----------
void forward() {

  digitalWrite(MOTOR1_A, HIGH);
  digitalWrite(MOTOR1_B, LOW);

  digitalWrite(MOTOR2_A, HIGH);
  digitalWrite(MOTOR2_B, LOW);
}

// ---------- STOP ----------
void stopRobot() {

  digitalWrite(MOTOR1_A, LOW);
  digitalWrite(MOTOR1_B, LOW);

  digitalWrite(MOTOR2_A, LOW);
  digitalWrite(MOTOR2_B, LOW);
}

// ---------- TURN RIGHT ----------
void turnRight() {

  digitalWrite(MOTOR1_A, HIGH);
  digitalWrite(MOTOR1_B, LOW);

  digitalWrite(MOTOR2_A, LOW);
  digitalWrite(MOTOR2_B, HIGH);

  delay(500);

  stopRobot();
}

// ---------- GET DISTANCE ----------
float getDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  if (duration == 0) {
    return 999;
  }

  return duration * 0.0343 / 2;
}

void loop() {

  distance = getDistance();

  // ---------- FLAME SENSOR ----------

  if (digitalRead(FLAME_SENSOR) == LOW) {

    // Flame detected
    Serial.println("ON");

  } else {

    // No flame
    Serial.println("OFF");
  }


  // ---------- ULTRASONIC ----------

  if (distance < 10) {

    // Object detected
    stopRobot();

    // Stop for 5 seconds
    delay(5000);

    // Turn right
    turnRight();

  } else {

    // No object
    forward();
  }

  delay(100);
}