int xPos = 20;
int yPos = 20;

int xSize = 10;
int ySize = 10;

long c1 = rgb(51, 102, 0);
long c2 = rgb(108, 217, 0);
long c3 = rgb(77, 155, 0);
long c4 = rgb(29, 58, 0);
long c5 = rgb(17, 35, 0);


long pix[] = {
  -1, -1, -1, -1, -1, -1, -1, c1, c1, c1,
  -1, -1, -1, -1, -1, -1, c1, c2, c3, c1,
  -1, -1, -1, -1, -1, c1, c2, c3, c3, c1,
  -1, c4, -1, -1, c1, c2, c3, c3, c1, -1,
  -1, c4, c4, c1, c2, c3, c3, c1, -1, -1,
  -1, c4, c1, c2, c3, c3, c1, -1, -1, -1,
  -1, -1, c4, c1, c3, c1, -1, -1, -1, -1,
  -1, c4, c4, c4, c1, c5, -1, -1, -1, -1,
  c4, c4, c5, -1, c5, c4, c4, -1, -1, -1,
  c4, c5, -1, -1, -1, -1, -1, -1, -1, -1,
};

void game_init() {
  tft.fillScreen(rgb(255, 255, 255));
}


void game_start() {
  
  int x = getX();
  int y = getY();
  if (x > 5 || x < -5 || y > 5 || y < -5) {
    clean(xPos, yPos, xSize, ySize, rgb(255, 255, 255));
    if (x > 5) {
      xPos = xPos + 1;
    } else if (x < -5) {
      xPos = xPos - 1;
    }
    if (y > 5) {
      yPos = yPos + 1;
    } else if (y < -5) {
      yPos = yPos - 1;
    }
  }

  draw(xPos, yPos, xSize, ySize, pix);
}


