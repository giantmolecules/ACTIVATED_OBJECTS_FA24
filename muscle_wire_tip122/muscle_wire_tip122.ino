//----------------------------------------------------------------//
//
// SAIC Activated Objects Fall 2024
// Brett Ian Balogh
// https://github.com/giantmolecules/ACTIVATED_OBJECTS_FA24
//
// muscle_wire_tip122.ino
//
// Actuate some muscle wire.
// Uses PWM.
//
//----------------------------------------------------------------//

// Include libraries for TFT
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define PWM_PIN 5

// Create a TFT object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Set paramaters for PWM peripheral
const int freq = 5000;
const int resolution = 10;


//----{SETUP}-----------------------------------------------------//

void setup() {

  // Configure PWM: channel, frequency, resolution
  ledcSetup(0, freq, resolution);
  // Attach pin, channel
  ledcAttachPin(5, 0);

  // Start Serial COM for debugging
  Serial.begin(115200);

  // turn on backlite
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  // turn on the TFT / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  // initialize TFT
  tft.init(135, 240); // Init ST7789 240x135
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);

  // default text size
  tft.setTextSize(3);

  // set wrap off
  tft.setTextWrap(false);

  // set text foreground and background colors
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

}

//----{LOOP}------------------------------------------------------//

void loop() {

analogWrite(PWM_PIN, 100);
tft.setCursor(0,0);
tft.print("ON: 100 ");
delay(500);
analogWrite(PWM_PIN, 0);
tft.setCursor(0,0);
tft.print("OFF: 0 ");
delay(2000);

}

//----{END}------------------------------------------------------//
