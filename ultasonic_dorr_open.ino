// -------- PINS --------

#define TRIG_PIN A3
#define ECHO_PIN A4

#define MOTOR_A 6
#define MOTOR_B 7

#define LED 11


// -------- SETTINGS --------

#define DETECT_DISTANCE 20

// Motor running time
#define MOTOR_TIME 1500

// Gate stays open for 3 seconds
#define OPEN_TIME 3000


// -------- DISTANCE FUNCTION --------

int getDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return 999;
  }

  int distance = duration * 0.034 / 2;

  return distance;
}


// -------- MOTOR OPEN --------

void gateOpen() {

  digitalWrite(MOTOR_A, HIGH);
  digitalWrite(MOTOR_B, LOW);

  digitalWrite(LED, HIGH);

  delay(MOTOR_TIME);

  // Stop motor
  digitalWrite(MOTOR_A, LOW);
  digitalWrite(MOTOR_B, LOW);
}


// -------- MOTOR CLOSE --------

void gateClose() {

  digitalWrite(MOTOR_A, LOW);
  digitalWrite(MOTOR_B, HIGH);

  delay(MOTOR_TIME);

  // Stop motor
  digitalWrite(MOTOR_A, LOW);
  digitalWrite(MOTOR_B, LOW);

  digitalWrite(LED, LOW);
}


// -------- SETUP --------

void setup() {

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(MOTOR_A, OUTPUT);
  pinMode(MOTOR_B, OUTPUT);

  pinMode(LED, OUTPUT);

  digitalWrite(MOTOR_A, LOW);
  digitalWrite(MOTOR_B, LOW);
  digitalWrite(LED, LOW);

  Serial.begin(9600);
}


// -------- LOOP --------

void loop() {

  int distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  // Object detected
  if (distance <= DETECT_DISTANCE) {

    // OPEN
    gateOpen();

    // Keep gate open
    delay(OPEN_TIME);

    // CLOSE / RETURN
    gateClose();


    // Wait until object moves away
    while (getDistance() <= DETECT_DISTANCE) {
      delay(100);
    }

    // Small delay before allowing another detection
    delay(500);
  }


  delay(100);
}