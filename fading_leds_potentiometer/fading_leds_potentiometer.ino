//----------------------------------------------------------------//
//
// SAIC Activated Objects Fall 2024
// Brett Ian Balogh
// https://github.com/giantmolecules/ACTIVATED_OBJECTS_FA24
//
// fading_leds_potentiometer.ino
//
// This example shows how to fade 5 LEDs in sequence by turning a potentiometer.
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
const int delayTime = 1;

//----{SETUP}-----------------------------------------------------//

void setup() {

  // Start Serial COM
  Serial.begin(115200);

  // Set pin modes
  for (int i = 0; i < 5; i++) {
    pinMode(pins[i], OUTPUT);
  }

  // Set attenuation for ADC (0-2.5V)
  analogSetAttenuation(ADC_11db);

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

  // Set text wrap
  tft.setTextWrap(false);

  // set text foreground and background colors
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  Serial.println(F("TFT Initialized"));
}

//----{LOOP}------------------------------------------------------//

void loop() {

  // Read analog Pin 17
  int value = analogRead(17);

  // ESP32-S2 ADC Resolution = 13 bits (2^13 = 8192)
  int index = map(value, 0, 8192, 0, 5);

  tft.setCursor(0,0);
  tft.print("ADC:");
  tft.print(value);
  tft.println("  ");
  tft.print("PIN:");
  tft.print(index);
  tft.println("  ");

  digitalWrite(pins[index], HIGH);
  for(int i = 0; i < 5; i++){
    if(i != index){
      digitalWrite(pins[i], LOW);
    }
  }
}

//----{END}------------------------------------------------------//
