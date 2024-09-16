//----------------------------------------------------------------//
//
// Brett Ian Balogh
// https://github.com/giantmolecules/captive_cinema.git
//
// garfield-demo-spiffs-image-reader.ino
//
// Demonstrates loading a jpeg from SPIFFS and displaying it on the TFT
// Images should be 240x135 max. Put them in the sketch data folder.
// This code will not compile with latest BusIO. Use v1.15.1
// !! Use No OTA 2MB App 2MB SPIFFS partition scheme in tools menu !!
//
//----------------------------------------------------------------//

// Required libraries
#include <SPIFFS.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPIFFS_ImageReader.h>

// Create a TFT object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Image reader
SPIFFS_ImageReader reader;


void setup() {

  Serial.begin(115200);

  /*
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  */
  
  // initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS initialisation failed!");
    while (1);
  }

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
  tft.setTextSize(1);

  // set text foreground and background colors
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  Serial.println(F("TFT Initialized"));

  // draw image
  ImageReturnCode code = reader.drawBMP("/Garfield_the_Cat.bmp", tft, 0, 0);
  Serial.print(code);
}

void loop() {

}
