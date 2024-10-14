//----------------------------------------------------------------//
//
// SAIC Activated Objects Fall 2024
// Brett Ian Balogh
// https://github.com/giantmolecules/ACTIVATED_OBJECTS_FA24
//
// DRV8833_stepper_motor.ino
//
// Demonstrates driving a stepper motor.
// 
//
//----------------------------------------------------------------//

// Include libraries for TFT
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Stepper.h>

// Define names for pins
#define IN1 5  // Orange
#define IN2 6 // Purple
#define IN3 9 // Yellow
#define IN4 10 // Blue

// Connect Red to GND

// Create a TFT object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Set steps per revolution: 32 full steps * 64 (1/64 gear reduction)
const int stepsPerRevolution = 2048;

// Create a stepper object
Stepper myStepper(stepsPerRevolution, IN1, IN2, IN3, IN4);

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

  // Set stepper speed. Max = 13 for 
  myStepper.setSpeed(13);

}

//----{LOOP}------------------------------------------------------//

void loop() {

  // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);

}

//----{FUNC}------------------------------------------------------//



//----{END}------------------------------------------------------//
