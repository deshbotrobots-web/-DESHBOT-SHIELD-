#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Buttons
#define UP_BUTTON   10
#define DOWN_BUTTON 12

// Motor driver
#define MOTOR_A 6
#define MOTOR_B 7

// Buzzer
#define BUZZER 11

int currentFloor = 1;

void setup() {

  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);

  pinMode(MOTOR_A, OUTPUT);
  pinMode(MOTOR_B, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  stopMotor();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  showFloor();
}

void loop() {

  // UP
  if (digitalRead(UP_BUTTON) == LOW) {

    if (currentFloor < 4) {

      currentFloor++;

      moveUp();

      delay(1000);

      stopMotor();

      showFloor();
    }

    delay(300);
  }

  // DOWN
  if (digitalRead(DOWN_BUTTON) == LOW) {

    if (currentFloor > 1) {

      currentFloor--;

      moveDown();

      delay(1000);

      stopMotor();

      showFloor();
    }

    delay(300);
  }
}

// ---------------- MOTOR UP ----------------

void moveUp() {

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(15, 5);
  display.println("GOING UP");

  display.setCursor(45, 32);
  display.print("F");
  display.print(currentFloor);

  display.display();

  digitalWrite(MOTOR_A, HIGH);
  digitalWrite(MOTOR_B, LOW);

  tone(BUZZER, 1200, 150);
}

// ---------------- MOTOR DOWN ----------------

void moveDown() {

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(5, 5);
  display.println("GOING DOWN");

  display.setCursor(45, 32);
  display.print("F");
  display.print(currentFloor);

  display.display();

  digitalWrite(MOTOR_A, LOW);
  digitalWrite(MOTOR_B, HIGH);

  tone(BUZZER, 800, 150);
}

// ---------------- STOP MOTOR ----------------

void stopMotor() {

  digitalWrite(MOTOR_A, LOW);
  digitalWrite(MOTOR_B, LOW);
}

// ---------------- FLOOR DISPLAY ----------------

void showFloor() {

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(35, 0);
  display.println("ELEVATOR");

  display.setTextSize(2);
  display.setCursor(20, 20);
  display.print("FLOOR ");
  display.print(currentFloor);

  display.setTextSize(1);
  display.setCursor(42, 50);
  display.println("READY");

  display.display();
}