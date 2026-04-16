#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_LEDS 10

Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int pos = 0;
int direction = 1;
int colorIndex = 0;

void setup() {
  strip.begin();
  strip.show();
}

void loop() {

  strip.clear();

  // Turn ON 3 LEDs together
  for (int i = 0; i < 3; i++) {
    int ledIndex = pos + i;

    if (ledIndex >= 0 && ledIndex < NUM_LEDS) {
      strip.setPixelColor(ledIndex, Wheel(colorIndex));
    }
  }

  strip.show();
  delay(100);

  pos += direction;

  // RIGHT end
  if (pos >= NUM_LEDS - 3) {
    direction = -1;
    nextColor();
  }

  // LEFT end
  if (pos <= 0) {
    direction = 1;
    nextColor();
  }
}

// Smooth rainbow colors
uint32_t Wheel(byte pos) {
  if (pos < 85) {
    return strip.Color(pos * 3, 255 - pos * 3, 0);
  } 
  else if (pos < 170) {
    pos -= 85;
    return strip.Color(255 - pos * 3, 0, pos * 3);
  } 
  else {
    pos -= 170;
    return strip.Color(0, pos * 3, 255 - pos * 3);
  }
}

// Change color (~50 colors)
void nextColor() {
  colorIndex += 5;
  if (colorIndex >= 255) {
    colorIndex = 0;
  }
}