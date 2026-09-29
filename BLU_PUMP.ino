#include <SoftwareSerial.h>

#define PUMP_A 6
#define PUMP_B 7

SoftwareSerial bluetooth(0, 1);

void setup() {

  pinMode(PUMP_A, OUTPUT);
  pinMode(PUMP_B, OUTPUT);

  digitalWrite(PUMP_A, LOW);
  digitalWrite(PUMP_B, LOW);

  bluetooth.begin(9600);
}

void loop() {

  if (bluetooth.available()) {

    String command = bluetooth.readStringUntil('\n');
    command.trim();

    if (command == "ON") {
      digitalWrite(PUMP_A, HIGH);
      digitalWrite(PUMP_B, LOW);
    }

    if (command == "OFF") {
      digitalWrite(PUMP_A, LOW);
      digitalWrite(PUMP_B, LOW);
    }
  }
}