#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define POT A0

// Player
int playerX = 60;
int playerY = 55;
int playerWidth = 12;
int playerHeight = 5;

// Enemy
int enemyX;
int enemyY;
int enemySize = 6;

int score = 0;
int speed = 2;

unsigned long lastMove = 0;

void newEnemy() {
  enemyX = random(0, SCREEN_WIDTH - enemySize);
  enemyY = 0;
}

void setup() {

  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  randomSeed(analogRead(A1));

  newEnemy();
}

void loop() {

  // -------------------------
  // READ POTENTIOMETER
  // -------------------------

  int potValue = analogRead(POT);

  // Convert potentiometer to player position
  playerX = map(potValue, 0, 1023, 0, SCREEN_WIDTH - playerWidth);


  // -------------------------
  // MOVE ENEMY
  // -------------------------

  if (millis() - lastMove > 30) {

    enemyY += speed;

    lastMove = millis();
  }


  // -------------------------
  // ENEMY REACHED BOTTOM
  // -------------------------

  if (enemyY > SCREEN_HEIGHT) {

    score++;

    // Increase difficulty
    if (score % 5 == 0) {
      speed++;
    }

    newEnemy();
  }


  // -------------------------
  // COLLISION
  // -------------------------

  if (
    enemyX < playerX + playerWidth &&
    enemyX + enemySize > playerX &&
    enemyY < playerY + playerHeight &&
    enemyY + enemySize > playerY
  ) {

    // GAME OVER

    display.clearDisplay();

    display.setTextSize(2);
    display.setCursor(15, 15);
    display.println("GAME OVER");

    display.setTextSize(1);
    display.setCursor(40, 40);
    display.print("Score: ");
    display.println(score);

    display.display();

    delay(2000);

    // Restart game
    score = 0;
    speed = 2;

    newEnemy();
  }


  // -------------------------
  // DRAW GAME
  // -------------------------

  display.clearDisplay();

  // Score
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Score: ");
  display.print(score);

  // Player
  display.fillRect(
    playerX,
    playerY,
    playerWidth,
    playerHeight,
    SSD1306_WHITE
  );

  // Enemy
  display.fillRect(
    enemyX,
    enemyY,
    enemySize,
    enemySize,
    SSD1306_WHITE
  );

  display.display();
}