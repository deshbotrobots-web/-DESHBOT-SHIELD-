#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ================= PINS =================

#define NEXT 10
#define SELECT 12
#define BUZZER 11

// ================= SCREENS =================

#define HOME     0
#define MENU     1
#define CLOCK    2
#define GAMES    3
#define TIMER    4
#define SETTINGS 5
#define PONG     6
#define SNAKE    7
#define REACTION 8

byte screen = HOME;

// ================= BUTTON =================

bool lastNext = HIGH;
bool lastSelect = HIGH;

// ================= MENU =================

byte menuIndex = 0;

const char *menuItems[] = {
  "Clock",
  "Games",
  "Timer",
  "Settings"
};

// ================= CLOCK =================

unsigned long clockMillis = 0;

int hourNow = 10;
int minuteNow = 0;
int secondNow = 0;

// ================= TIMER =================

int timerValue = 30;
bool timerRunning = false;
unsigned long timerStart;

// ================= GAME MENU =================

byte gameIndex = 0;

const char *games[] = {
  "Pong",
  "Snake",
  "Reaction",
  "Back"
};

// =================================================
// BEEP
// =================================================

void beep() {
  digitalWrite(BUZZER, HIGH);
  delay(40);
  digitalWrite(BUZZER, LOW);
}

// =================================================
// HOME
// =================================================

void homeScreen() {

  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(25, 5);
  display.print("UNO");

  display.setCursor(8, 28);
  display.print("MINI OS");

  display.setTextSize(1);
  display.setCursor(25, 53);
  display.print("D12 START");

  display.display();
}

// =================================================
// MENU
// =================================================

void menuScreen() {

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(48, 0);
  display.print("MENU");

  for (byte i = 0; i < 4; i++) {

    display.setCursor(20, 14 + i * 11);

    if (i == menuIndex)
      display.print("> ");
    else
      display.print("  ");

    display.print(menuItems[i]);
  }

  display.display();
}

// =================================================
// CLOCK
// =================================================

void updateClock() {

  if (millis() - clockMillis >= 1000) {

    clockMillis += 1000;

    secondNow++;

    if (secondNow >= 60) {
      secondNow = 0;
      minuteNow++;
    }

    if (minuteNow >= 60) {
      minuteNow = 0;
      hourNow++;
    }

    if (hourNow >= 24) {
      hourNow = 0;
    }
  }
}

void clockScreen() {

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(48, 0);
  display.print("CLOCK");

  display.setTextSize(2);

  display.setCursor(12, 23);

  if (hourNow < 10)
    display.print("0");

  display.print(hourNow);
  display.print(":");

  if (minuteNow < 10)
    display.print("0");

  display.print(minuteNow);
  display.print(":");

  if (secondNow < 10)
    display.print("0");

  display.print(secondNow);

  display.setTextSize(1);
  display.setCursor(35, 53);
  display.print("D12 BACK");

  display.display();
}

// =================================================
// GAMES MENU
// =================================================

void gamesScreen() {

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(45, 0);
  display.print("GAMES");

  for (byte i = 0; i < 4; i++) {

    display.setCursor(20, 13 + i * 11);

    if (i == gameIndex)
      display.print("> ");
    else
      display.print("  ");

    display.print(games[i]);
  }

  display.display();
}

// =================================================
// PONG
// =================================================

int paddleY;
int ballX;
int ballY;

int ballDX;
int ballDY;

int pongScore;

unsigned long pongUpdate;

void startPong() {

  paddleY = 22;

  ballX = 64;
  ballY = 32;

  ballDX = 2;
  ballDY = 1;

  pongScore = 0;

  pongUpdate = millis();

  beep();
}

void pongGame() {

  // D10 = move paddle upward
  if (digitalRead(NEXT) == LOW) {

    paddleY -= 2;

    if (paddleY < 10)
      paddleY = 10;
  }

  // Automatic paddle movement
  else {

    if (ballY > paddleY + 10)
      paddleY++;

    if (ballY < paddleY + 10)
      paddleY--;

    if (paddleY < 10)
      paddleY = 10;

    if (paddleY > 42)
      paddleY = 42;
  }

  // Ball movement
  if (millis() - pongUpdate >= 35) {

    pongUpdate = millis();

    ballX += ballDX;
    ballY += ballDY;

    // Top/bottom
    if (ballY <= 11 || ballY >= 61) {
      ballDY = -ballDY;
    }

    // Right wall
    if (ballX >= 124) {
      ballDX = -ballDX;
    }

    // Paddle
    if (ballX <= 8 &&
        ballY >= paddleY &&
        ballY <= paddleY + 20) {

      ballDX = 2;

      pongScore++;

      beep();
    }

    // Miss
    if (ballX <= 0) {

      ballX = 64;
      ballY = 32;

      ballDX = 2;
      ballDY = 1;

      pongScore = 0;
    }
  }

  // Draw
  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(2, 0);
  display.print("PONG");

  display.setCursor(95, 0);
  display.print(pongScore);

  // Middle line
  for (int y = 10; y < 64; y += 6) {
    display.drawPixel(64, y, SSD1306_WHITE);
  }

  // Paddle
  display.fillRect(
    2,
    paddleY,
    4,
    20,
    SSD1306_WHITE
  );

  // Ball
  display.fillCircle(
    ballX,
    ballY,
    2,
    SSD1306_WHITE
  );

  display.setCursor(82, 55);
  display.print("D12 BACK");

  display.display();
}

// =================================================
// SNAKE
// =================================================

#define MAX_SNAKE 40

int snakeX[MAX_SNAKE];
int snakeY[MAX_SNAKE];

byte snakeLength;

int snakeDX;
int snakeDY;

int foodX;
int foodY;

int snakeScore;

unsigned long snakeTimer;

bool snakeButtonOld = HIGH;

void startSnake() {

  snakeLength = 4;

  snakeDX = 1;
  snakeDY = 0;

  snakeScore = 0;

  for (byte i = 0; i < 4; i++) {

    snakeX[i] = 48 - i * 4;
    snakeY[i] = 32;
  }

  randomSeed(analogRead(A0));

  foodX = random(2, 30) * 4;
  foodY = random(3, 15) * 4;

  snakeTimer = millis();

  snakeButtonOld = HIGH;

  beep();
}

void snakeGame() {

  bool button = digitalRead(NEXT);

  // Turn
  if (button == LOW && snakeButtonOld == HIGH) {

    int oldDX = snakeDX;

    snakeDX = -snakeDY;
    snakeDY = oldDX;

    beep();
  }

  snakeButtonOld = button;

  // Move
  if (millis() - snakeTimer >= 180) {

    snakeTimer = millis();

    for (int i = snakeLength - 1; i > 0; i--) {

      snakeX[i] = snakeX[i - 1];
      snakeY[i] = snakeY[i - 1];
    }

    snakeX[0] += snakeDX * 4;
    snakeY[0] += snakeDY * 4;

    // Walls
    if (snakeX[0] < 0)
      snakeX[0] = 124;

    if (snakeX[0] >= 128)
      snakeX[0] = 0;

    if (snakeY[0] < 10)
      snakeY[0] = 60;

    if (snakeY[0] >= 64)
      snakeY[0] = 10;

    // Food
    if (snakeX[0] == foodX &&
        snakeY[0] == foodY) {

      if (snakeLength < MAX_SNAKE)
        snakeLength++;

      snakeScore++;

      foodX = random(0, 32) * 4;
      foodY = random(3, 15) * 4;

      beep();
    }

    // Self collision
    for (byte i = 1; i < snakeLength; i++) {

      if (snakeX[0] == snakeX[i] &&
          snakeY[0] == snakeY[i]) {

        snakeLength = 4;

        snakeDX = 1;
        snakeDY = 0;

        snakeScore = 0;

        for (byte j = 0; j < 4; j++) {

          snakeX[j] = 48 - j * 4;
          snakeY[j] = 32;
        }

        beep();

        break;
      }
    }
  }

  // Draw
  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(2, 0);
  display.print("SNAKE");

  display.setCursor(95, 0);
  display.print(snakeScore);

  // Food
  display.fillRect(
    foodX,
    foodY,
    4,
    4,
    SSD1306_WHITE
  );

  // Snake
  for (byte i = 0; i < snakeLength; i++) {

    display.fillRect(
      snakeX[i],
      snakeY[i],
      4,
      4,
      SSD1306_WHITE
    );
  }

  display.setCursor(78, 55);
  display.print("D10 TURN");

  display.display();
}

// =================================================
// REACTION
// =================================================

byte reactionState = 0;

unsigned long reactionTimer;
unsigned long reactionStart;

int reactionTime;

void startReaction() {

  reactionState = 1;

  randomSeed(analogRead(A0));

  reactionTimer = millis();

  reactionStart = 0;

  display.clearDisplay();

  display.setTextSize(2);
  display.setCursor(25, 20);
  display.print("WAIT");

  display.display();
}

void reactionGame() {

  // Waiting
  if (reactionState == 1) {

    // Too early
    if (digitalRead(NEXT) == LOW) {

      display.clearDisplay();

      display.setTextSize(2);
      display.setCursor(8, 20);
      display.print("TOO EARLY");

      display.display();

      beep();

      delay(1000);

      startReaction();

      return;
    }

    // Random wait
    if (millis() - reactionTimer >= 2000) {

      reactionState = 2;

      reactionStart = millis();

      beep();

      display.clearDisplay();

      display.setTextSize(3);
      display.setCursor(35, 20);
      display.print("GO!");

      display.display();
    }
  }

  // GO
  else if (reactionState == 2) {

    if (digitalRead(NEXT) == LOW) {

      reactionTime = millis() - reactionStart;

      reactionState = 3;

      display.clearDisplay();

      display.setTextSize(1);
      display.setCursor(25, 5);
      display.print("REACTION");

      display.setTextSize(2);
      display.setCursor(25, 25);
      display.print(reactionTime);
      display.print("ms");

      display.setTextSize(1);
      display.setCursor(20, 52);
      display.print("D10 AGAIN");

      display.display();

      beep();

      delay(500);
    }
  }

  // Result
  else if (reactionState == 3) {

    if (digitalRead(NEXT) == LOW) {

      delay(200);

      startReaction();
    }
  }
}

// =================================================
// TIMER
// =================================================

void timerScreen() {

  int remaining = timerValue;

  if (timerRunning) {

    unsigned long passed =
      (millis() - timerStart) / 1000;

    if (passed >= timerValue) {

      remaining = 0;

      timerRunning = false;

      beep();
      delay(100);
      beep();
      delay(100);
      beep();

    } else {

      remaining = timerValue - passed;
    }
  }

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(45, 0);
  display.print("TIMER");

  display.setTextSize(3);

  display.setCursor(42, 20);

  if (remaining < 10)
    display.print("0");

  display.print(remaining);

  display.setTextSize(1);

  display.setCursor(15, 53);

  if (timerRunning)
    display.print("RUNNING");

  else
    display.print("D12 START");

  display.display();
}

// =================================================
// SETTINGS
// =================================================

void settingsScreen() {

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(38, 0);
  display.print("SETTINGS");

  display.setCursor(20, 20);
  display.print("Sound: ON");

  display.setCursor(20, 34);
  display.print("OLED: 128x64");

  display.setCursor(20, 48);
  display.print("D12 = BACK");

  display.display();
}

// =================================================
// BUTTON HANDLER
// =================================================

void buttons() {

  bool next = digitalRead(NEXT);
  bool select = digitalRead(SELECT);

  // ---------------- D10 ----------------

  if (next == LOW && lastNext == HIGH) {

    if (screen == MENU) {

      menuIndex++;

      if (menuIndex >= 4)
        menuIndex = 0;

      beep();
    }

    else if (screen == GAMES) {

      gameIndex++;

      if (gameIndex >= 4)
        gameIndex = 0;

      beep();
    }

    delay(120);
  }

  // ---------------- D12 ----------------

  if (select == LOW && lastSelect == HIGH) {

    if (screen == HOME) {

      screen = MENU;

      beep();
    }

    else if (screen == MENU) {

      beep();

      if (menuIndex == 0)
        screen = CLOCK;

      else if (menuIndex == 1)
        screen = GAMES;

      else if (menuIndex == 2)
        screen = TIMER;

      else
        screen = SETTINGS;
    }

    else if (screen == CLOCK) {

      screen = MENU;
      beep();
    }

    else if (screen == GAMES) {

      beep();

      if (gameIndex == 0) {

        screen = PONG;
        startPong();
      }

      else if (gameIndex == 1) {

        screen = SNAKE;
        startSnake();
      }

      else if (gameIndex == 2) {

        screen = REACTION;
        startReaction();
      }

      else {

        screen = MENU;
      }
    }

    else if (screen == PONG) {

      screen = GAMES;
      beep();
    }

    else if (screen == SNAKE) {

      screen = GAMES;
      beep();
    }

    else if (screen == REACTION) {

      screen = GAMES;
      beep();
    }

    else if (screen == TIMER) {

      if (!timerRunning) {

        timerRunning = true;
        timerStart = millis();

        beep();
      }
    }

    else if (screen == SETTINGS) {

      screen = MENU;
      beep();
    }

    delay(150);
  }

  lastNext = next;
  lastSelect = select;
}

// =================================================
// SETUP
// =================================================

void setup() {

  pinMode(NEXT, INPUT_PULLUP);
  pinMode(SELECT, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);

  digitalWrite(BUZZER, LOW);

  // OLED
  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        0x3C)) {

    while (true) {
      // OLED error
    }
  }

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  randomSeed(analogRead(A0));

  clockMillis = millis();

  homeScreen();
}

// =================================================
// LOOP
// =================================================

void loop() {

  updateClock();

  buttons();

  if (screen == HOME) {

    homeScreen();
  }

  else if (screen == MENU) {

    menuScreen();
  }

  else if (screen == CLOCK) {

    clockScreen();
  }

  else if (screen == GAMES) {

    gamesScreen();
  }

  else if (screen == TIMER) {

    timerScreen();
  }

  else if (screen == SETTINGS) {

    settingsScreen();
  }

  else if (screen == PONG) {

    pongGame();
  }

  else if (screen == SNAKE) {

    snakeGame();
  }

  else if (screen == REACTION) {

    reactionGame();
  }

  delay(15);
}