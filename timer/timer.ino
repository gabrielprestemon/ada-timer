#include <Adafruit_CircuitPlayground.h>

bool beepOnSec = false;
uint8_t lengths[] = {1, 3, 6, 9, 12};
uint8_t len = 0;
uint8_t t;

// right button resets countdown
void resetCycle() {
  for (uint8_t p = 0; p < 10; p++) {
    CircuitPlayground.setPixelColor(p,0,192,0);
  }
  t = 0;
}

void checkState() {
  // switch enables/disables beep on second
  beepOnSec = !CircuitPlayground.slideSwitch();
  // left button resets cycle
  if (CircuitPlayground.leftButton()) {
    t = 127;
  }
  // right button increments countdown length
  if (CircuitPlayground.rightButton()) {
    len = (len + 1) % 5;
    t = 127;
  }
}

void setup() {
  CircuitPlayground.begin();
  resetCycle();
}

void loop() {
  checkState();
  // check for reset or regular tick
  if (t >= (lengths[len] * 10) - 1) {
    resetCycle();
    CircuitPlayground.speaker.enable(true);
    CircuitPlayground.playTone(550, 500, false);
    delay(500);
  }
  else {
    tick();
  }
}

void tick() {
  if (t % lengths[len] == 0) {
    CircuitPlayground.setPixelColor(t / lengths[len], 0, 0, 0);
  }

  if (beepOnSec){
    CircuitPlayground.speaker.enable(true);
    CircuitPlayground.playTone(440, 50, false);
  }
  else {
    CircuitPlayground.speaker.enable(false);
  }
  // wait for 1s (tone pauses for duration)
  delay(900 + (beepOnSec ? 0 : 50));
  // completed a tick
  t++;
}
