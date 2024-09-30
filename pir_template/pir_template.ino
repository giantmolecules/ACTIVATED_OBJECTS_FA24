//----------------------------------------------------------------//
//
// SAIC Activated Objects Fall 2024
// Brett Ian Balogh
// https://github.com/giantmolecules/ACTIVATED_OBJECTS_FA24
//
// pir_template.ino
//
// Demonstrates the use of a passive infrared sensor (PIR). Uses
// interrupts
//
//----------------------------------------------------------------//

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define INTERRUPT_PIN 9

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

//----{SETUP}-----------------------------------------------------//

void setup() {
  Serial.begin(115200);

  // Pin modes
  pinMode(INTERRUPT_PIN, INPUT);

  // Attach interrupts
  attachInterrupt(INTERRUPT_PIN, isr_rising, HIGH);
  attachInterrupt(INTERRUPT_PIN, isr_falling, LOW);

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
  tft.setTextWrap(false);

}

//----{LOOP}------------------------------------------------------//

void loop() {

// Nothing to do here. Interrupts handle everything.

}
//----{ISR}------------------------------------------------------//

void isr_rising() {
  tft.setCursor(0,0);
  tft.println("Motion ");
  tft.print("Detected!");
}

void isr_falling() {
  tft.setCursor(0,0);
  tft.println("No");
  tft.print("Motion...");
}

//----{END}------------------------------------------------------//
