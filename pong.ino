#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Buttons
#define UP_BUTTON   10
#define DOWN_BUTTON 12

// Player paddle
int playerY = 25;
int paddleHeight = 14;

// CPU paddle
int cpuY = 25;

// Ball
int ballX = 64;
int ballY = 32;

int ballDX = 2;
int ballDY = 1;

// Score
int playerScore = 0;
int cpuScore = 0;

void resetBall() {
  ballX = 64;
  ballY = 32;

  ballDX = -ballDX;

  if (ballDX == 0) {
    ballDX = 2;
  }
}

void setup() {

  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }

  display.clearDisplay();
  display.display();
}

void loop() {

  // ---------------- PLAYER ----------------

  if (digitalRead(UP_BUTTON) == LOW) {
    playerY -= 3;
  }

  if (digitalRead(DOWN_BUTTON) == LOW) {
    playerY += 3;
  }

  // Keep player paddle inside screen
  if (playerY < 0) {
    playerY = 0;
  }

  if (playerY > SCREEN_HEIGHT - paddleHeight) {
    playerY = SCREEN_HEIGHT - paddleHeight;
  }


  // ---------------- CPU ----------------

  if (ballY > cpuY + paddleHeight / 2) {
    cpuY += 2;
  }

  if (ballY < cpuY + paddleHeight / 2) {
    cpuY -= 2;
  }

  if (cpuY < 0) {
    cpuY = 0;
  }

  if (cpuY > SCREEN_HEIGHT - paddleHeight) {
    cpuY = SCREEN_HEIGHT - paddleHeight;
  }


  // ---------------- BALL ----------------

  ballX += ballDX;
  ballY += ballDY;


  // Top / bottom wall

  if (ballY <= 8 || ballY >= SCREEN_HEIGHT - 2) {
    ballDY = -ballDY;
  }


  // ---------------- PLAYER COLLISION ----------------

  if (ballX <= 7 &&
      ballY >= playerY &&
      ballY <= playerY + paddleHeight) {

    ballDX = -ballDX;
    ballX = 8;
  }


  // ---------------- CPU COLLISION ----------------

  if (ballX >= 121 &&
      ballY >= cpuY &&
      ballY <= cpuY + paddleHeight) {

    ballDX = -ballDX;
    ballX = 120;
  }


  // ---------------- SCORE ----------------

  if (ballX < 0) {

    cpuScore++;

    resetBall();

    delay(500);
  }

  if (ballX > SCREEN_WIDTH) {

    playerScore++;

    resetBall();

    delay(500);
  }


  // ---------------- DISPLAY ----------------

  display.clearDisplay();

  // Score
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(45, 0);
  display.print(playerScore);

  display.setCursor(78, 0);
  display.print(cpuScore);

  // Center dividing line
  for (int y = 10; y < 64; y += 4) {
    display.drawPixel(64, y, SSD1306_WHITE);
  }

  // Player paddle
  display.fillRect(2, playerY, 3, paddleHeight, SSD1306_WHITE);

  // CPU paddle
  display.fillRect(123, cpuY, 3, paddleHeight, SSD1306_WHITE);

  // Ball
  display.fillCircle(ballX, ballY, 2, SSD1306_WHITE);

  display.display();

  delay(20);
}