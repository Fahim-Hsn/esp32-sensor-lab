#include <U8g2lib.h>
#include <Wire.h>

// OLED: 1.3" SSD1306 I2C
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Buttons
#define BTN_UP     32
#define BTN_DOWN   33
#define BTN_LEFT   25
#define BTN_RIGHT  26
#define BTN_RESET  27

// Grid & Layout
#define GRID_SIZE 4
#define MAX_LENGTH 100
#define BORDER 2
#define PLAY_COLS ((128 - BORDER * 2) / GRID_SIZE)  // 31
#define PLAY_ROWS ((64  - BORDER * 2) / GRID_SIZE)  // 15
#define PLAY_WIDTH  (PLAY_COLS * GRID_SIZE)         // 124
#define PLAY_HEIGHT (PLAY_ROWS * GRID_SIZE)         // 60

// Snake state
int snakeX[MAX_LENGTH], snakeY[MAX_LENGTH];
int snakeLength = 3;
int dirX = GRID_SIZE, dirY = 0;
bool gameOver = false;
int score = 0;

// Food
int foodX, foodY;

// Timing
unsigned long lastMove = 0;
int moveDelay = 150;

void setupButtons() {
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  pinMode(BTN_RESET, INPUT_PULLUP);
}

void setup() {
  u8g2.begin();
  setupButtons();
  resetGame();
  randomSeed(analogRead(0));
}

void resetGame() {
  snakeLength = 3;
  score = 0;
  for (int i = 0; i < snakeLength; i++) {
    snakeX[i] = BORDER + 40 - i * GRID_SIZE;
    snakeY[i] = BORDER + 20;
  }
  dirX = GRID_SIZE;
  dirY = 0;
  gameOver = false;
  spawnFood();
}

void spawnFood() {
  foodX = BORDER + (random(0, PLAY_COLS)) * GRID_SIZE;
  foodY = BORDER + (random(0, PLAY_ROWS)) * GRID_SIZE;
}

void checkButtons() {
  if (!digitalRead(BTN_UP) && dirY == 0) {
    dirX = 0; dirY = -GRID_SIZE;
  } else if (!digitalRead(BTN_DOWN) && dirY == 0) {
    dirX = 0; dirY = GRID_SIZE;
  } else if (!digitalRead(BTN_LEFT) && dirX == 0) {
    dirX = -GRID_SIZE; dirY = 0;
  } else if (!digitalRead(BTN_RIGHT) && dirX == 0) {
    dirX = GRID_SIZE; dirY = 0;
  } else if (!digitalRead(BTN_RESET)) {
    resetGame();
  }
}

void moveSnake() {
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  snakeX[0] += dirX;
  snakeY[0] += dirY;

  // Border collision
  if (snakeX[0] < BORDER || snakeX[0] >= (BORDER + PLAY_WIDTH) ||
      snakeY[0] < BORDER || snakeY[0] >= (BORDER + PLAY_HEIGHT)) {
    gameOver = true;
    return;
  }

  // Self collision
  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameOver = true;
      return;
    }
  }

  // Eat food
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    if (snakeLength < MAX_LENGTH) {
      snakeLength++;
      score++;
    }
    spawnFood();
  }
}

void drawGame() {
  u8g2.clearBuffer();

  // Border
  u8g2.drawFrame(BORDER, BORDER, PLAY_WIDTH, PLAY_HEIGHT);

  if (gameOver) {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(30, 28, "GAME OVER");
    u8g2.setFont(u8g2_font_5x8_tr);
    u8g2.drawStr(20, 46, "Press RESET to play");
  } else {
    // Snake
    for (int i = 0; i < snakeLength; i++) {
      u8g2.drawBox(snakeX[i], snakeY[i], GRID_SIZE, GRID_SIZE);
    }

    // Food
    u8g2.drawBox(foodX, foodY, GRID_SIZE, GRID_SIZE);

    // Score
    u8g2.setFont(u8g2_font_5x8_tr);
    u8g2.setCursor(2, 10);
    u8g2.print("Score: ");
    u8g2.print(score);
  }

  u8g2.sendBuffer();
}

void loop() {
  checkButtons();

  if (!gameOver && millis() - lastMove > moveDelay) {
    moveSnake();
    lastMove = millis();
  }

  drawGame();
}
