#define PI 3.14159
#define CELL 2

#define BLACK rgb(0, 0, 0)
#define WHITE rgb(255, 255, 255)


int ballX = -1;
int ballY = -1;
int ballVelX = -1;
int ballVelY = -1;
int ballSide = 5;
int ballSpeed = 12;

int playerX = -1;
int playerY = -1;
int playerW = ballSide;
int playerH = 20;
int playerStep = 7;
int playerScore = 0;

int aiX = -1;
int aiY = -1;
int aiW = ballSide;
int aiH = 20;
int aiScore = 0;
float aiSpeed = 0.1;


void netDraw() {
  int w = CELL;
  int x = (SCREEN_W - w) * 0.5;
  int y = 0;
  int step = SCREEN_H / 20;
  while (y < SCREEN_H) {
    for (int i = 0; i < CELL; i++) {
     tft.drawFastVLine(x + i, y + step * 0.25, step * 0.5, WHITE); 
    }
    y += step;
  }
}

void scoreDraw() {
  int offset = 6;
  int playerSymWidth = 10 * (1 + playerScore /10);
  int aiSymWidth = 10 * (1 + aiScore /10);
  tft.fillRect((SCREEN_W - CELL) * 0.5 - playerSymWidth - offset, 0, playerSymWidth + offset / 2, 18, BLACK);
  tft.fillRect((SCREEN_W  + CELL) * 0.5 + offset, 0, aiSymWidth + offset / 2, 18, BLACK);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor( (SCREEN_W - CELL) * 0.5 - playerSymWidth - offset, 0);
  tft.println(playerScore);
  tft.setCursor( (SCREEN_W + CELL) * 0.5 + offset, 0);
  tft.println(aiScore);
}

boolean AABBIntersect(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh) {
  return ax < bx+bw && ay < by+bh && bx < ax+aw && by < ay+ah;
}

// player
void playerDraw() {
  int i = 0;
  while(i < playerW) {
    tft.drawFastVLine(playerX + i, playerY, playerH, WHITE);
    i++;
  }
}
void playerEraseDraw() {
  int i = 0;
  while(i < playerW) {
    tft.drawFastVLine(playerX + i, playerY, playerH, BLACK);
    i++;
  }
}

void playerUpdate() {
  playerEraseDraw();
  if (getY() > LIMIT) {
    playerY = playerY + playerStep;
  }
  if (getY() < - LIMIT) {
    playerY = playerY - playerStep;
  }

  playerY = max( min(playerY, SCREEN_H - playerH), 0);
}

// ai
void aiDraw() {
  int i = 0;
  while(i < aiW) {
    tft.drawFastVLine(aiX + i, aiY, aiH, WHITE);
    i++;
  }
}

void aiEraseDraw() {
  int i = 0;
  while(i < aiW) {
    tft.drawFastVLine(aiX + i, aiY, aiH, BLACK);
    i++;
  }
}


void aiUpdate() {
  aiEraseDraw();
  float desty = ballY - (aiH - ballSide) * 0.5;

  aiY = aiY + (desty - aiY) * aiSpeed;
  aiY = max( min(aiY, SCREEN_H - aiH), 0);
}


// ball
void ballDraw() {
  tft.fillRect(ballX, ballY, ballSide, ballSide, WHITE);
}

void ballEraseDraw() {
  tft.fillRect(ballX, ballY, ballSide, ballSide, BLACK);
}

void ballServe(int side) {
  float r = float(random(11)) / 10;
  if (side == 1) {
    ballX = playerX + playerW;
  } else {
    ballX = aiX - ballSide;
  }
  ballY = (SCREEN_H - ballSide) * r;
  
  float phi = 0.1 * PI * (1 - 2 * r);

  ballVelX = side * ballSpeed * cos(phi);
  ballVelY = ballSpeed * sin(phi);
}

void ballUpdate() {
    ballEraseDraw();
    int offset, pdleX, pdleY, pdleW, pdleH;
    float n, smash, phi;
    ballX = ballX + ballVelX;
    ballY = ballY + ballVelY;
    
    if (0 > ballY || ballY + ballSide > SCREEN_H) {
      if (ballVelY < 0) {
        offset = 0 - ballY;
      } else {
        offset = SCREEN_H - (ballY + ballSide);
      }

      ballY = ballY + 2 * offset;
      ballVelY = ballVelY * -1;
    }

    if (ballVelX < 0) {
      pdleX = playerX;
      pdleY = playerY;
      pdleW = playerW;
      pdleH = playerH;
    } else {
      pdleX = aiX;
      pdleY = aiY;
      pdleW = aiW;
      pdleH = aiH;
    }

    if ( AABBIntersect(pdleX, pdleY, pdleW, pdleH, ballX, ballY, ballSide, ballSide) ) { 
      if (pdleX == playerX && pdleY == playerY) {
        ballX = playerX + playerW;
      } else {
        ballX = aiX - ballSide;
      }
      n = float(ballY + ballSide - pdleY) / (pdleH + ballSide);
      phi = 0.25 * PI * ( 2 * n - 1);

      if (abs(phi) > 0.2 * PI) {
        smash = 1.5;
      } else {
        smash = 1;
      }

      if (pdleX == playerX && pdleY == playerY) {
        ballVelX = smash * 1 * ballSpeed * cos(phi);
      } else {
        ballVelX = smash * -1 * ballSpeed * cos(phi);
      }

      ballVelY = smash * ballSpeed * sin(phi);
      playNote(400, 10);
    }

    if (0 > ballX + ballSide || ballX > SCREEN_W) {
      if (pdleX == playerX && pdleY == playerY) {
        aiScore += 1;
        playNote(200, 50);
        delay(250);
        ballServe(1);
      } else {
        playerScore += 1;
        playNote(600, 50);
        delay(250);
        ballServe(-1);
      }
      scoreDraw();
    }
}

void initGame() {
  playerX = playerW;
  playerY = (SCREEN_H - playerH) / 2;

  aiX = SCREEN_W - (playerW + aiW);
  aiY = (SCREEN_H - aiH) / 2;
  
  ballServe(1);
  scoreDraw();
}

void updateGame() {
  ballUpdate();
  playerUpdate();
  aiUpdate();
}

void drawGame() {
  ballDraw();
  playerDraw();
  aiDraw();
  netDraw();
}


void SETUP() {
  splash(VERSION);

  tft.fillScreen(BLACK);
  randomSeed(micros());
  initGame();
}

void LOOP() {
  if(isBtnPressed(SPECIAL)) {
    musicOn = !musicOn;
  }
  updateGame();
  drawGame();
  delay(16);
}

