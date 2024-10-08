//----------------------------------------------------------------//
//
// SAIC Activated Objects Fall 2024
// Brett Ian Balogh
// https://github.com/giantmolecules/ACTIVATED_OBJECTS_FA24
//
// dc_motor_tip122_pwm.ino
//
// Shows how to turn motor on/of
//
//----------------------------------------------------------------//

// Include libraries for TFT
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define MOTOR_PIN 5

// Create a TFT object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

//----{SETUP}-----------------------------------------------------//

void setup() {

  // Start Serial COM
  Serial.begin(115200);

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

  // Turn off word wrapping
  tft.setTextWrap(false);

  // default text size
  tft.setTextSize(4);

  // set text foreground and background colors
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  Serial.println(F("TFT Initialized"));

  // Set pin mode to putput
  pinMode(MOTOR_PIN, OUTPUT);

  analogWriteFrequency(500);
  analogWriteResolution(8);
  // You may have to use this if errors:
  //  analogWriteFrequency(MOTOR_PIN,500);
  //  analogWriteResolution(MOTOR_PIN, 8);

}

//----{LOOP}------------------------------------------------------//

void loop() {

// Counting UP = speed increases
  for (int i = 0; i <= 255; i++) {
    analogWrite(MOTOR_PIN, i);
    tft.setCursor(0, 0);
    tft.print("Speed:");
    tft.print(i);
    tft.print("    ");
    delay(10);
  }

//Counting DOWN = speed decreases
  for (int i = 255; i > 0; i--) {
    analogWrite(MOTOR_PIN, i);
    tft.setCursor(0, 0);
    tft.print("Speed:");
    tft.print(i);
    tft.print("    ");
    delay(10);
  }

}

//----{END}------------------------------------------------------//
