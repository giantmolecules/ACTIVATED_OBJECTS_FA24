//----------------------------------------------------------------//
//
// SAIC Activated Objects Fall 2024
// Brett Ian Balogh
// https://github.com/giantmolecules/ACTIVATED_OBJECTS_FA24
//
// many_neopixels.ino
//
// This example shows how to use a lot of neopixels (144).
// Neopixels draw a lot of current. You will need an external 5V supply at full brightness.
// If brightness is low, it's ok to power from USB pin.
// This will crash with the latest esp32 core. Use v2.0.14 in boards manager.
// Uses Adafruit Neopixel v1.12.2 library
//
//----------------------------------------------------------------//

// Required Libraries
#include <Adafruit_NeoPixel.h>
#include "images.h"

// Which pin are the neopixels connected to
#define LED_PIN 5

// How many neopixels are there?
//#define LED_COUNT 10
#define LED_COUNT 256
// Create neopixel strip.
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

//----{SETUP}-----------------------------------------------------//

void setup() {

  // Start serial port over USB
  Serial.begin(115200);

  // Set debugging to true
  Serial.setDebugOutput(true);

  // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.begin();

  // Turn OFF all pixels ASAP
  strip.show();

  // Set BRIGHTNESS to 10 (max = 255)
  strip.setBrightness(10);
  strip.fill(0xffff00);
  strip.show();
  delay(3000);
  for(int i = 0; i <256; i++){
    strip.setPixelColor(i, sun[i]);
  }
  strip.show();
  while(1);
}

//----{LOOP}------------------------------------------------------//

void loop() {

  //This is a test. This is only a test.
  rainbow(10);
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

// Function to convert RGB hex to GRB hex
uint32_t rgbToGrb(uint32_t rgbColor) {
    // Extract RGB components
    uint8_t r = (rgbColor >> 16) & 0xFF; // Red component
    uint8_t g = (rgbColor >> 8) & 0xFF;  // Green component
    uint8_t b = rgbColor & 0xFF;         // Blue component

    // Rearrange to GRB
    uint32_t grbColor = (g << 16) | (r << 8) | b;
    
    return grbColor;
}


//----{END}------------------------------------------------------//
