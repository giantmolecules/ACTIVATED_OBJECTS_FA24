//----------------------------------------------------------------//
//
// SAIC Activated Objects Fall 2024
// Brett Ian Balogh
// https://github.com/giantmolecules/ACTIVATED_OBJECTS_FA24
//
// neopixel_template.ino
//
// This example shows how to use neopixels.
// Use as a template for other neopixel projects.
// Uses Adafruit Neopixel v1.12.2 library
// Uses ESP32 v3.0.5
//
//----------------------------------------------------------------//

// Required Libraries
#include <Adafruit_NeoPixel.h>

// Which pin are the neopixels connected to
#define LED_PIN 5

// How many neopixels are there?
#define LED_COUNT 10

// Create neopixel strip.
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

//----{SETUP}-----------------------------------------------------//

void setup() {

  // Serial for debugging
  Serial.begin(115200);

  strip.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();             // Turn OFF all pixels ASAP
  strip.setBrightness(50);  // Set BRIGHTNESS to about 1/5 (max = 255)
}

//----{LOOP}------------------------------------------------------//

void loop() {

  //This is a test. This is only a test.
  for (int i = 0 ; i < 10; i++) {
    Serial.println("For Loop");
    // (N, R, G, B, W) all 0-255
    strip.setPixelColor(i, 255, 0, 255, 0);
    // Display the change
    strip.show();
    // Delay 1s
    delay(100);
    // Turn pixel off
    strip.clear();
    // Display the change
    strip.show();
  }

  Serial.println("Main Loop");

}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    strip.rainbow(firstPixelHue);
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    strip.show();  // Update strip with new contents
    delay(wait);   // Pause for a moment
  }
}

//----{END}------------------------------------------------------//
