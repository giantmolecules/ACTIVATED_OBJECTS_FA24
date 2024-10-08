//----------------------------------------------------------------//
//
// SAIC Activated Objects Fall 2024
// Brett Ian Balogh
// https://github.com/giantmolecules/ACTIVATED_OBJECTS_FA24
//
// DRV8833_one_motor.ino
//
// Demonstrates driving a DC gearmotor
// Uses PWM to vary speed.
// Use 2.0.14 version of ESP32 board!
//
//----------------------------------------------------------------//

// Include libraries for TFT
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define IN1 9
#define IN2 10
#define IN3 11
#define IN4 12

// Create a TFT object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Set paramaters for PWM
const int freq = 500;
const int resolution = 8;

// Set PWM bounds
int minPWM = 0;
int maxPWM = pow(2, resolution);


//----{SETUP}-----------------------------------------------------//

void setup() {

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
  tft.init(135, 240);  // Init ST7789 240x135
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);

  // default text size
  tft.setTextSize(4);

  // disable text wrap
  tft.setTextWrap(false);

  // set text foreground and background colors
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  // Configure PWM
  analogWriteResolution(resolution);
  analogWriteFrequency(freq);

  // You might have to use this if you get an error:
  // Make sure ESP32 by Espressif version is 2.0.14!

  // Set pin modes
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

//----{LOOP}------------------------------------------------------//

void loop() {

  // Set IN1 low, and PWM IN2
  digitalWrite(IN1, LOW);

  for (int i = minPWM; i <= maxPWM; i++) {
    analogWrite(IN2, i);
    tftPrint(0, i);
    delay(1);
  }
  for (int i = maxPWM; i > minPWM; i--) {
    analogWrite(IN2, i);
    tftPrint(0, i);
    delay(1);
  }
  // Set IN2 low, and PWM IN1
  digitalWrite(IN2, LOW);

  for (int i = minPWM; i <= maxPWM; i++) {
    analogWrite(IN1, i);
    tftPrint(i, 0);
    delay(1);
  }
  for (int i = maxPWM; i > minPWM; i--) {
    analogWrite(IN1, i);
    tftPrint(i, 0);
    delay(1);
  }
}

//----{FUNC}------------------------------------------------------//

void tftPrint(int a, int b) {
  tft.setCursor(0, 0);
  tft.println("IN1   IN2");
  tft.print(a);
  tft.print("     ");
  tft.print(b);
  tft.print(" ");
}

//----{END}------------------------------------------------------//
