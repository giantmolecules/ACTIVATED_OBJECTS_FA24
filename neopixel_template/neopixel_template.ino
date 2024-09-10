#include <Adafruit_NeoPixel.h>

#define LED_PIN 33

#define LED_COUNT 1

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

}

void loop() {
  for (int i = 0; i < 255; i++) {
    strip.setPixelColor(0, strip.Color(0, i, 255 - i));
    strip.setPixelColor(1, strip.Color(0, 255 - i, i));
    strip.show();
    delay(10);
  }
  for (int i = 255; i > 0; i--) {
    strip.setPixelColor(0, strip.Color(0, i, 255 - i));
    strip.setPixelColor(1, strip.Color(0, 255 - i, i));
    strip.show();
    delay(10);
  }
}
