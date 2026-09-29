#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------------- PINS ----------------

#define IR_SENSOR 9

#define TRIG_PIN A0
#define ECHO_PIN 13

// ---------------- VARIABLES ----------------

float distanceCM = 0;
float speedKMH = 0;

unsigned long lastIRTime = 0;

// Distance between two IR detection points
// Change this according to your setup
float IR_DISTANCE_CM = 20.0;

// ---------------- SETUP ----------------

void setup() {

  pinMode(IR_SENSOR, INPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(20, 10);
  display.println("SPEED");
  display.setCursor(20, 35);
  display.println("METER");

  display.display();

  delay(2000);
}

// ---------------- LOOP ----------------

void loop() {

  // =================================================
  // ULTRASONIC DISTANCE
  // =================================================

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration > 0) {

    distanceCM = duration * 0.0343 / 2;

  }


  // =================================================
  // IR SPEED
  // =================================================

  if (digitalRead(IR_SENSOR) == LOW) {

    unsigned long currentTime = millis();

    if (lastIRTime != 0) {

      unsigned long timeDifference =
        currentTime - lastIRTime;

      if (timeDifference > 50) {

        float timeSeconds =
          timeDifference / 1000.0;

        // Speed = distance / time
        float speedCMs =
          IR_DISTANCE_CM / timeSeconds;

        // cm/s → km/h
        speedKMH =
          speedCMs * 0.036;
      }
    }

    lastIRTime = currentTime;

    delay(100);
  }


  // =================================================
  // OLED DISPLAY
  // =================================================

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  // Distance
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("ULTRASONIC DIST");

  display.setTextSize(2);
  display.setCursor(0, 12);
  display.print(distanceCM, 1);
  display.println(" cm");


  // Speed
  display.setTextSize(1);
  display.setCursor(0, 38);
  display.println("IR SPEED");

  display.setTextSize(2);
  display.setCursor(0, 48);
  display.print(speedKMH, 1);
  display.print(" km/h");

  display.display();


  // =================================================
  // SERIAL MONITOR
  // =================================================

  Serial.print("Distance: ");
  Serial.print(distanceCM, 1);

  Serial.print(" cm   |   IR Speed: ");

  Serial.print(speedKMH, 1);

  Serial.println(" km/h");


  delay(50);
}