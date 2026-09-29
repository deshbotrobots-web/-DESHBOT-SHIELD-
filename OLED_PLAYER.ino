#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define P2_BUTTON 12

int p2Score = 0;
bool gameStarted = false;
bool goSignal = false;

unsigned long startTime = 0;

void setup() {

  pinMode(P2_BUTTON, INPUT_PULLUP);

  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  showMessage("PLAYER 2", "READY");
}

void loop() {

  // Receive data from Nano 1
  if (Serial.available()) {

    String data = Serial.readStringUntil('\n');
    data.trim();

    if (data == "START") {

      gameStarted = true;
      goSignal = false;

      showMessage("ROUND", "GET READY");
    }

    if (data == "GO") {

      goSignal = true;
      startTime = millis();

      showMessage("GO!!!", "PRESS!");
    }
  }

  // Player 2 presses button
  if (gameStarted && goSignal) {

    if (digitalRead(P2_BUTTON) == LOW) {

      unsigned long reactionTime =
        millis() - startTime;

      Serial.print("P2:");
      Serial.println(reactionTime);

      showReaction(reactionTime);

      goSignal = false;
      gameStarted = false;

      delay(1500);
    }
  }
}

void showMessage(String line1, String line2) {

  display.clearDisplay();

  display.setTextSize(2);

  display.setCursor(10, 10);
  display.println(line1);

  display.setCursor(10, 40);
  display.println(line2);

  display.display();
}

void showReaction(unsigned long time) {

  display.clearDisplay();

  display.setTextSize(2);

  display.setCursor(0, 5);
  display.println("PLAYER 2");

  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("TIME: ");

  display.print(time);
  display.println(" ms");

  display.display();
}