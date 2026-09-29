#define PUMP_A 6
#define PUMP_B 7

void setup() {
  pinMode(PUMP_A, OUTPUT);
  pinMode(PUMP_B, OUTPUT);

  digitalWrite(PUMP_A, LOW);
  digitalWrite(PUMP_B, LOW);

  Serial.begin(9600);
}

void loop() {

  if (Serial.available()) {

    String signal = Serial.readStringUntil('\n');
    signal.trim();

    if (signal == "ON") {
      digitalWrite(PUMP_A, HIGH);
      digitalWrite(PUMP_B, LOW);
    }

    else if (signal == "OFF") {
      digitalWrite(PUMP_A, LOW);
      digitalWrite(PUMP_B, LOW);
    }
  }
}