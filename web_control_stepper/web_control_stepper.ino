//----------------------------------------------------------------//
//
// SAIC Activated Objects Fall 2024
// Brett Ian Balogh
// https://github.com/giantmolecules/ACTIVATED_OBJECTS_FA24
//
// web_control_stepper.ino
//
// Shows how to serve a webpage from ESP32 with a form that controls
// the position of a stepper motor. Uses regular stepper library and 
// a DRV8833 motor controller.
//
//----------------------------------------------------------------//

/*
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete project details at https://RandomNerdTutorials.com/stepper-motor-esp32-web-server/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"
#include <Arduino_JSON.h>
#include <ESP32Servo.h>
#include <Stepper.h>

// Define names for pins
#define IN1 5   // Orange
#define IN2 6   // Purple
#define IN3 9   // Yellow
#define IN4 10  // Blue

// Connect Red to GND

// Set steps per revolution: 32 full steps * 64 (1/64 gear reduction)
const int stepsPerRevolution = 2048;

// Create a stepper object
Stepper myStepper(stepsPerRevolution, IN1, IN2, IN3, IN4);

// Replace with your network credentials
const char* ssid = "SONGBIRD";
const char* password = "quietcartoon195";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Search for parameter in HTTP POST request
const char* PARAM_INPUT_1 = "direction";
const char* PARAM_INPUT_2 = "steps";

//Variables to save values from HTML form
String direction;
String steps;

bool newRequest = false;

// Initialize LittleFS
void initLittleFS() {
  if (!LittleFS.begin(true)) {
    Serial.println("An error has occurred while mounting LittleFS");
  } else {
    Serial.println("LittleFS mounted successfully");
  }
}

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  while (!Serial)
    ;
  initWiFi();
  initLittleFS();

  // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(LittleFS, "/index.html", "text/html");
  });

  server.serveStatic("/", LittleFS, "/");

  server.on("/", HTTP_POST, [](AsyncWebServerRequest* request) {
    int params = request->params();
    for (int i = 0; i < params; i++) {
      const AsyncWebParameter* p = request->getParam(i);
      if (p->isPost()) {
        // HTTP POST input1 value
        if (p->name() == PARAM_INPUT_1) {
          direction = p->value().c_str();
          Serial.print("Direction set to: ");
          Serial.println(direction);
        }
        // HTTP POST input2 value
        if (p->name() == PARAM_INPUT_2) {
          steps = p->value().c_str();
          Serial.print("Number of steps set to: ");
          Serial.println(steps);
          // Write file to save value
        }
        newRequest = true;
        //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
      }
    }
    request->send(LittleFS, "/index.html", "text/html");
  });

  server.begin();

  // Set stepper speed. Max = 13 for
  myStepper.setSpeed(13);
  
}

void loop() {
  if (newRequest) {
    if (direction == "CW") {
      myStepper.step(steps.toInt());
      Serial.print("CW");
    } else {
      myStepper.step(-steps.toInt());
    }
    newRequest = false;
  }
}
