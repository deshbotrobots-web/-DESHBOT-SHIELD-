#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Buttons
#define MOVE_BUTTON 10
#define HIT_BUTTON  12

// Mole position
int mole = 0;

// Player cursor
int cursor = 0;

// Score
int score = 0;

// Game time
unsigned long startTime;
const int gameTime = 20;

// Button states
bool lastMove = HIGH;
bool lastHit = HIGH;

void newMole() {

  int oldMole = mole;

  // Make sure the new mole is different
  do {
    mole = random(0, 4);
  } while (mole == oldMole);
}

void drawGame() {

  display.clearDisplay();

  // Title
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(2, 0);
  display.print("WHACK-A-MOLE");

  // Score
  display.setCursor(90, 0);
  display.print(score);

  // Mole positions
  int x[4] = {25, 90, 25, 90};
  int y[4] = {23, 23, 48, 48};

  // Draw four holes
  for (int i = 0; i < 4; i++) {

    display.drawCircle(x[i], y[i], 8, SSD1306_WHITE);

    // Draw mole
    if (i == mole) {
      display.fillCircle(x[i], y[i], 5, SSD1306_WHITE);
    }
  }

  // Cursor around selected position
  display.drawRect(
    x[cursor] - 11,
    y[cursor] - 11,
    22,
    22,
    SSD1306_WHITE
  );

  // Time remaining
  int elapsed = (millis() - startTime) / 1000;
  int remaining = gameTime - elapsed;

  display.setCursor(2, 57);
  display.print("TIME:");
  display.print(remaining);

  display.display();
}

void gameOver() {

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(20, 15);
  display.print("GAME");

  display.setCursor(20, 35);
  display.print("OVER");

  display.setTextSize(1);

  display.setCursor(82, 25);
  display.print("SCORE");

  display.setCursor(95, 40);
  display.print(score);

  display.display();

  delay(3000);
}

void setup() {

  pinMode(MOVE_BUTTON, INPUT_PULLUP);
  pinMode(HIT_BUTTON, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }

  randomSeed(analogRead(A0));

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(15, 20);
  display.print("READY!");

  display.display();

  delay(1500);

  newMole();

  startTime = millis();
}

void loop() {

  // ---------------- TIME ----------------

  int elapsed = (millis() - startTime) / 1000;

  if (elapsed >= gameTime) {

    gameOver();

    // Restart game
    score = 0;
    cursor = 0;

    newMole();

    startTime = millis();

    return;
  }


  // ---------------- MOVE BUTTON ----------------

  bool moveState = digitalRead(MOVE_BUTTON);

  if (moveState == LOW && lastMove == HIGH) {

    cursor++;

    if (cursor >= 4) {
      cursor = 0;
    }

    delay(100);
  }

  lastMove = moveState;


  // ---------------- HIT BUTTON ----------------

  bool hitState = digitalRead(HIT_BUTTON);

  if (hitState == LOW && lastHit == HIGH) {

    if (cursor == mole) {

      // Correct!
      score++;

      newMole();

    } else {

      // Wrong hit
      if (score > 0) {
        score--;
      }
    }

    delay(150);
  }

  lastHit = hitState;


  // ---------------- DISPLAY ----------------

  drawGame();

  delay(20);
}
