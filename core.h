#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ST7735.h"

Adafruit_ST7735 tft = Adafruit_ST7735(3, 4, 5, 6, 2);

#define VERSION 2.01
#define SCREEN_W 128
#define SCREEN_H 128

#define BTNS_COUNT 8
#define TRIANGLE 0 
#define CIRCLE 1
#define CROSS 2
#define SQUARE 3
#define START 4
#define SELECT 5
#define SPECIAL 6
#define ANALOG 7

#define LIMIT 5

#define Y A1
#define X A2 
#define SOUND A3

int btns[BTNS_COUNT] = {7,8,9,10,11,12,13,A0};
boolean btnsStatus[BTNS_COUNT];
int axesStatus[2];
boolean musicOn = true;


// functions
void playNote(int note, int duration) {
  if (musicOn) {
    tone(SOUND, note, duration);
  }
}
void stopNote() {
  noTone(SOUND);
}

void checkBtns() {
  int status;
  for (int i=0; i <= BTNS_COUNT; i++){
    status = digitalRead(btns[i]);
    if (status == LOW) {
      btnsStatus[i] = true;
    } else {
      btnsStatus[i] = false;
    }
 } 
}
boolean isBtnPressed(int btn) {
  int status = digitalRead(btns[btn]);
  if (status == LOW) {
    btnsStatus[btn] = true;
  } else {
    btnsStatus[btn] = false;
  }
  return btnsStatus[btn];
}

int getX() {
  axesStatus[0] = map(analogRead(X), 1023, 0, -10, 10);
  return axesStatus[0];
}
int getY() {
  axesStatus[1] = map(analogRead(Y), 1023, 0, 10, -10);
  return axesStatus[1];
}

word rgb( byte R, byte G, byte B) {
  return ( ((R & 0xF8) << 8) | ((G & 0xFC) << 3) | (B >> 3) );
}

void draw(int xPos, int yPos, int w, int h, long coords[]) {
  int size = w * h;
  for (int i = 0; i <= size; i++) {
    if (coords[i] >= 0) {
      tft.drawPixel(xPos + (i % w), yPos + (i / w), coords[i]);
    }
  }
}

void clean(int xPos, int yPos, int w, int h, long color) {
  for (int i = 0; i <= h; i++) {
    tft.drawFastHLine(xPos, yPos + i, w, color);
  }
}

void splash(float version) {
  tft.fillScreen(ST7735_BLACK);
  tft.fillRect(10, (SCREEN_H / 2) - 20, SCREEN_W-20, 1, ST7735_WHITE);
  tft.fillRect(10, (SCREEN_H / 2) + 32, SCREEN_W-20, 1, ST7735_WHITE);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(3);
  tft.setCursor( ((SCREEN_W / 2))-(6*9), (SCREEN_H / 2) - 16);
  tft.println("Game");
  tft.setTextSize(3);
  tft.setCursor( (SCREEN_W / 2)-(6*9), (SCREEN_H / 2) + 8);
  tft.println("Master");
  tft.setTextSize(0);
  tft.setCursor( 10, (SCREEN_H / 2) - 28);
  tft.println("v");
  tft.setCursor( 18, (SCREEN_H / 2) - 28);
  tft.println(version);
  tft.setCursor( (SCREEN_W / 2) - (12*3) - 1, (SCREEN_H / 2) + 40);
  tft.println("press start");
  while (1) {
    // wait for push button
    if ( isBtnPressed(START) ) break;
  }
}

