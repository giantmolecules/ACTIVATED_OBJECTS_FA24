//----------------------------------------------------------------//
//
// SAIC Tactical Media Fall 2024
// Brett Ian Balogh
// https://github.com/giantmolecules/TACTICAL_MEDIA_FA24
//
// NWS_forecast_Chicago.ino
//
// Uses NWS API to get weather conditions.
//
//----------------------------------------------------------------//

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_Protomatter.h>
#include <SPIFFS_ImageReader.h>
#include "images.h"

// Create a TFT object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

/* ----------------------------------------------------------------------
  The RGB matrix must be wired to VERY SPECIFIC pins, different for each
  microcontroller board. This first section sets that up for a number of
  supported boards. Notes have been moved to the bottom of the code.
  ------------------------------------------------------------------------- */

uint8_t rgbPins[] = { 6, 5, 9, 11, 10, 12 };
uint8_t addrPins[] = { A5, A4, A3, A2 };
uint8_t clockPin = 13;  // Must be on same port as rgbPins
uint8_t latchPin = RX;
uint8_t oePin = TX;

Adafruit_Protomatter matrix(
  64,                         // Width of matrix (or matrix chain) in pixels
  4,                          // Bit depth, 1-6
  1, rgbPins,                 // # of matrix chains, array of 6 RGB pins for each
  4, addrPins,                // # of address pins (height is inferred), array of pins
  clockPin, latchPin, oePin,  // Other matrix control pins
  false);                     // No double-buffering here (see "doublebuffer" example)

// Not sure if WiFiClientSecure checks the validity date of the certificate.
// Setting clock just to be sure...
String setClock() {
  configTime(0, 0, "pool.ntp.org");

  Serial.print(F("Waiting for NTP time sync: "));
  time_t nowSecs = time(nullptr);
  while (nowSecs < 8 * 3600 * 2) {
    delay(500);
    Serial.print(F("."));
    yield();
    nowSecs = time(nullptr);
  }

  Serial.println();
  struct tm timeinfo;
  gmtime_r(&nowSecs, &timeinfo);
  Serial.print(F("Current time: "));
  Serial.print(asctime(&timeinfo));
  return asctime(&timeinfo);
}

// Variables

WiFiMulti WiFiMulti;
JSONVar myObject;
String forecast = "";
int timeNow = 0;
int timeThen = 0;
int errorCounter = 0;
boolean firstTime = 1;
int pastPrintTime = 0;
int printInterval = 5000;
String condition = "";

/************************************************/

// Keywords to search for in forecast

String keywords[] = {"Sun", "Cloud", "Rain", "Wind", "Clear"};

/************************************************/

// Interval to check forecast in milliseconds. 1s = 1000ms

int interval = 3600000;  //1 hour

/************************************************/


void setup() {

  Serial.begin(115200);

  /************************************************/

  WiFi.mode(WIFI_STA);

  /************************************************/

  // Change for your wifi credentials

  //WiFiMulti.addAP("SAIC-Guest", "wifi@saic");

  WiFiMulti.addAP("SONGBIRD", "quietcartoon195");

  /************************************************/


  // wait for WiFi connection
  Serial.print("Waiting for WiFi to connect...");
  while ((WiFiMulti.run() != WL_CONNECTED)) {
    Serial.print(".");
  }
  Serial.println(" connected");

  setClock();

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
  tft.setTextSize(2);

  // set text foreground and background colors
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  Serial.println(F("TFT Initialized"));

  // Initialize matrix...
  ProtomatterStatus status = matrix.begin();
  Serial.print("Protomatter begin() status: ");
  Serial.println((int)status);
  if (status != PROTOMATTER_OK) {
    // DO NOT CONTINUE if matrix setup encountered an error.
    for (;;)
      ;
  }

}

void loop() {
  // Print to TFT
  if (millis() - pastPrintTime > printInterval) {
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0, 0);
    tft.setTextSize(3);
    tft.println(setClock());
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    tft.print(forecast);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
    pastPrintTime = millis();
  }

  timeNow = millis();
  if (timeNow - timeThen > interval || firstTime) {
    WiFiClientSecure *client = new WiFiClientSecure;

    if (client) {
      //client -> setCACert(rootCACertificate);
      client->setInsecure();
      {
        // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is
        HTTPClient https;

        Serial.print("[HTTPS] begin...\n");
        if (https.begin(*client, "https://api.weather.gov/gridpoints/LOT/76,73/forecast")) {  // Chicago
          Serial.print("[HTTPS] GET...\n");
          // start connection and send HTTP header
          int httpCode = https.GET();

          // httpCode will be negative on error
          if (httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

            // file found at server
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
              String jsonString = https.getString();
              Serial.print("jsonString Length: ");
              Serial.println(jsonString.length());
              Serial.println(jsonString);
              myObject = JSON.parse(jsonString);
              Serial.print("Output: ");
              Serial.println(myObject["properties"]["periods"][0]["shortForecast"]);
              forecast = JSON.stringify(myObject["properties"]["periods"][0]["shortForecast"]);
              //forecast = "Sunny";
              processForecast(forecast);
            }
          } else {
            Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
            errorCounter++;

            // if we get too many connection errors, restart the ESP

            if (errorCounter >= 3) {
              ESP.restart();
            }
          }

          https.end();
        } else {
          Serial.printf("[HTTPS] Unable to connect\n");
        }

        // End extra scoping block
      }

      delete client;
    } else {
      Serial.println("Unable to create client");
    }

    Serial.println();
    Serial.println("Waiting 1h before the next round...");
    //delay(90000);
    if (firstTime) {
      firstTime = 0;
    }
    timeThen = millis();
  }
}

/* This function displays an image based on the forecast. It takes the actual forecast
   and compares it to a list of keywords such as sunny, cloudy, etc. If the keyword is found in
   the forecast string, an image is displayed.
*/

void processForecast(String fcast) {

  for (int j = 0; j < 5; j++) {

    
    // The following looks for the keyword in the forecast. If it isn't there, it returns -1
    // Otherwise, it returns the position in the string.
    int result = fcast.indexOf(keywords[j]);

    if (result > -1) {
      condition = keywords[j];
      Serial.print("Forecast: ");
      Serial.print(fcast);
      Serial.print("     ");
      Serial.print("Condition: ");
      Serial.println(condition);
      if (j == 0) {
        matrix.drawRGBBitmap(0, 0, sun, 64, 32);
        matrix.show();  // Copy data to matrix buffers
      }
      if (j == 1) {
        matrix.drawRGBBitmap(0, 0, cloud, 64, 32);
        matrix.show();  // Copy data to matrix buffers
      }
      if (j == 2) {
        matrix.drawRGBBitmap(0, 0, rain, 64, 32);
        matrix.show();  // Copy data to matrix buffers
      }
    }
  }
}
