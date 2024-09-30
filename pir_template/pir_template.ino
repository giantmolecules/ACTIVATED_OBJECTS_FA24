//----------------------------------------------------------------//
//
// SAIC Activated Objects Fall 2024
// Brett Ian Balogh
// https://github.com/giantmolecules/ACTIVATED_OBJECTS_FA24
//
// pir_template.ino
//
// Demonstrates the use of a passive infrared sensor (PIR). Uses
// interrupts. Uses board version 2.0.14 and GFX version 1.11.10
//
//----------------------------------------------------------------//

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define INTERRUPT_PIN 9

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

boolean event = false;
boolean change = false;

//----{SETUP}-----------------------------------------------------//

void setup() {
  Serial.begin(115200);

  // Pin modes
  pinMode(INTERRUPT_PIN, INPUT);

  // Attach interrupts
  attachInterrupt(INTERRUPT_PIN, isr_change, CHANGE);

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
}

//----{LOOP}------------------------------------------------------//

void loop() {
  if (event) {
    if (change) {
      tft.fillScreen(ST77XX_BLACK);
      tft.setCursor(0, 0);
      tft.println("Motion ");
      tft.print("Detected!");
      delay(2000);
      change = false;
    }

    if (!change) {
      tft.fillScreen(ST77XX_BLACK);
      tft.setCursor(0, 0);
      tft.println("No");
      tft.print("Motion...");
      //change = false;
    }
    event = false;
  }
}
//----{ISR}------------------------------------------------------//

void isr_change() {

  event = true;
  change = true;

}

//----{END}------------------------------------------------------//
