#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


// ---------------- BUTTONS ----------------

#define BUTTON_1 10
#define BUTTON_2 12


// ---------------- PASSWORD ----------------

// 1 = Button 1
// 2 = Button 2

int password[] = {1, 2, 1, 1};

const int passwordLength = 4;

int position = 0;


// ---------------- DISPLAY ----------------

void showPassword() {

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);

  display.setCursor(35, 0);
  display.print("SECRET LOCK");

  display.setCursor(20, 20);

  for (int i = 0; i < passwordLength; i++) {

    if (i < position) {
      display.print("* ");
    }
    else {
      display.print("_ ");
    }
  }

  display.setCursor(10, 45);
  display.print("D10     D12");

  display.display();
}


// ---------------- ACCESS GRANTED ----------------

void accessGranted() {

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);

  display.setCursor(32, 10);
  display.print("ACCESS");

  display.setTextSize(2);

  display.setCursor(18, 28);
  display.print("GRANTED!");

  display.display();

  delay(3000);
}


// ---------------- WRONG PASSWORD ----------------

void wrongPassword() {

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);

  display.setCursor(25, 15);
  display.print("WRONG!");

  display.setTextSize(1);

  display.setCursor(30, 42);
  display.print("TRY AGAIN");

  display.display();

  delay(1500);

  position = 0;
}


// ---------------- CHECK BUTTON ----------------

void checkButton(int buttonNumber) {

  // Correct button
  if (buttonNumber == password[position]) {

    position++;

    // Complete password
    if (position == passwordLength) {

      accessGranted();

      position = 0;
    }
  }

  // Wrong button
  else {

    wrongPassword();
  }

  showPassword();
}


// ---------------- SETUP ----------------

void setup() {

  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);


  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {

    while (1);
  }


  showPassword();
}


// ---------------- LOOP ----------------

void loop() {

  // Button 1
  if (digitalRead(BUTTON_1) == LOW) {

    delay(50);

    if (digitalRead(BUTTON_1) == LOW) {

      checkButton(1);

      while (digitalRead(BUTTON_1) == LOW);
    }
  }


  // Button 2
  if (digitalRead(BUTTON_2) == LOW) {

    delay(50);

    if (digitalRead(BUTTON_2) == LOW) {

      checkButton(2);

      while (digitalRead(BUTTON_2) == LOW);
    }
  }
}