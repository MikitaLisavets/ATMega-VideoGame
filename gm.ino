#include "core.h"
#include "pong.h"

void setup() {
  for (int i = 0; i < BTNS_COUNT; i++) {
    pinMode(btns[i], INPUT_PULLUP);
  };
  pinMode(X, INPUT);
  pinMode(Y, INPUT);
  pinMode(SOUND, INPUT);

  tft.initR(INITR_144GREENTAB);
  tft.setRotation(3);

  SETUP();
}


void loop() {
  LOOP();
}



