#include <LiquidCrystal.h>

// ---------------- LCD ----------------
// RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(A4, A3, A2, A1, A0, 13);

// ---------------- IR SENSOR ----------------
#define IR_SENSOR 9

// Wheel circumference in meters
float wheelCircumference = 0.20;

unsigned long lastTime = 0;
unsigned long revolutionCount = 0;

void setup() {

  pinMode(IR_SENSOR, INPUT);

  lcd.begin(16, 2);

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("SPEED METER");

  lcd.setCursor(4, 1);
  lcd.print("READY");

  delay(2000);

  lcd.clear();
}

void loop() {

  static bool lastState = HIGH;

  bool currentState = digitalRead(IR_SENSOR);

  // Detect IR sensor trigger
  if (lastState == HIGH && currentState == LOW) {

    unsigned long currentTime = millis();

    if (lastTime != 0) {

      unsigned long timeDifference = currentTime - lastTime;

      // Speed in m/s
      float speedMS = wheelCircumference /
                      (timeDifference / 1000.0);

      // Convert to km/h
      float speedKMH = speedMS * 3.6;

      revolutionCount++;

      // -------- LCD --------
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Speed:");

      lcd.setCursor(7, 0);
      lcd.print(speedKMH, 1);
      lcd.print(" km/h");

      lcd.setCursor(0, 1);
      lcd.print("REV:");
      lcd.print(revolutionCount);

    }

    lastTime = currentTime;
  }

  lastState = currentState;
}