//----------------------------------------------------------------//
//
// SAIC Activated Objects Fall 2024
// Brett Ian Balogh
// https://github.com/giantmolecules/ACTIVATED_OBJECTS_FA24
//
// marching_leds.ino
//
// This example shows how to sequence 5 LEDs
//
//----------------------------------------------------------------//

// Include libraries for TFT
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// Create a TFT object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Create an array for pin numbers
const int pins[] = { 11, 10, 9, 6, 5 };

// How long to wait on / off
const int delayTime = 100;

//----{SETUP}-----------------------------------------------------//

void setup() {

  // Start Serial COM
  Serial.begin(115200);

  // Set pin modes
  for (int i = 0; i < 5; i++) {
    pinMode(pins[i], OUTPUT);
  }

  // turn on backlite
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  // turn on the TFT / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  // initialize TFT
  tft.init(135, 240);  // Init ST7789 240x135
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);

  // default text size
  tft.setTextSize(5);

  // set text foreground and background colors
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  Serial.println(F("TFT Initialized"));
}

//----{LOOP}------------------------------------------------------//

void loop() {
  for(int i = 0; i < 5; i++){

    // Print to the tft
    tft.setCursor(0,0);
    tft.print("PIN: ");
    tft.print(pins[i]);
    tft.print("  ");

    digitalWrite(pins[i], HIGH);
    delay(delayTime);
    digitalWrite(pins[i], LOW);
    delay(delayTime);
  }
}

//----{END}------------------------------------------------------//
