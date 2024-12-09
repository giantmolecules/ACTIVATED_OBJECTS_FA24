//----------------------------------------------------------------//
//
// SAIC Activated Objects Fall 2024
// Brett Ian Balogh
// https://github.com/giantmolecules/ACTIVATED_OBJECTS_FA24
//
// servo_sweep.ino
//
// Moves a servo back and forth in it's range of motion.
// Uses ESP32Servo.h, not the default arduino servo library.
//
//----------------------------------------------------------------//

// Include libraries for TFT
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
// Include the ESP32 Arduino Servo Library instead of the original Arduino Servo Library
#include <ESP32Servo.h>

// Create a TFT object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Create servo object to control a servo
Servo myServo1;
Servo myServo2;

// Possible PWM GPIO pins on the ESP32: 0(used by on-board button),2,4,5(used by on-board LED),12-19,21-23,25-27,32-33
int servoPin1 = 12;  // GPIO pin used to connect the servo control (digital out)
int servoPin2 = 13;
// Variable to hold servo position
int pos1 = 0;
int pos2 = 0;
int delay1 = 0;
int delay2 = 0;


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

  // Turn off word wrapping
  tft.setTextWrap(false);

  // default text size
  tft.setTextSize(4);

  // set text foreground and background colors
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myServo1.setPeriodHertz(50);           // Standard 50hz servo
  myServo2.setPeriodHertz(50);
  myServo1.attach(servoPin1, 500, 2400);  // attaches the servo on pin 18 to the servo object
  myServo2.attach(servoPin2, 500, 2400);
  // using SG90 servo min/max of 500us and 2400us
  // for MG995 large servo, use 1000us and 2000us,
  // which are the defaults, so this line could be
  // "myservo.attach(servoPin);"
}

//----{LOOP}------------------------------------------------------//

void loop() {

  pos1 = random(60, 120);
  pos2 = random(60, 120);

  delay1 = random(50,100);
  delay2 = random(50, 100);

  myServo1.write(pos1);
  delay(delay1);

  myServo2.write(pos2);
  delay(delay2);

}

//----{END}------------------------------------------------------//
