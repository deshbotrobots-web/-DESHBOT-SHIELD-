#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Ultrasonic
#define TRIG_PIN A0
#define ECHO_PIN 13

// Buzzer
#define BUZZER 11

float distance;
long duration;

void setup() {

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(15, 5);
  display.println("PARKING");

  display.setCursor(20, 30);
  display.println("ASSIST");

  display.display();

  delay(2000);
}

void loop() {

  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  // Read echo
  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    distance = 999;
  }
  else {
    distance = duration * 0.0343 / 2;
  }

  display.clearDisplay();

  // Title
  display.setTextSize(1);
  display.setCursor(25, 0);
  display.println("PARKING ASSIST");

  // Distance
  display.setTextSize(2);
  display.setCursor(10, 18);

  if (distance >= 100) {
    display.print("---");
  }
  else {
    display.print(distance, 1);
  }

  display.print(" cm");

  // Status
  display.setTextSize(1);
  display.setCursor(10, 45);

  if (distance <= 10) {

    display.println("!!! STOP !!!");

    tone(BUZZER, 2000);

  }
  else if (distance <= 20) {

    display.println("VERY CLOSE");

    tone(BUZZER, 1600, 100);
    delay(120);

  }
  else if (distance <= 40) {

    display.println("CAUTION");

    tone(BUZZER, 1000, 100);
    delay(350);

  }
  else {

    display.println("SAFE");

    noTone(BUZZER);
  }

  display.display();

  delay(50);
}