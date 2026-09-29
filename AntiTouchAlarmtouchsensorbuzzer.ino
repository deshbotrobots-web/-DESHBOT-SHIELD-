// ---------------- PINS ----------------

#define TOUCH_SENSOR 9
#define BUZZER 11


void setup() {

  pinMode(TOUCH_SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(BUZZER, LOW);
}


void loop() {

  int touch = digitalRead(TOUCH_SENSOR);

  if (touch == HIGH) {

    // Touch detected
    digitalWrite(BUZZER, HIGH);

  } 
  else {

    // No touch
    digitalWrite(BUZZER, LOW);
  }
}