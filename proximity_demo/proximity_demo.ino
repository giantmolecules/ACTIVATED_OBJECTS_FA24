//----------------------------------------------------------------//
//
// SAIC Activated Objects Fall 2024
// Brett Ian Balogh
// https://github.com/giantmolecules/ACTIVATED_OBJECTS_FA24
//
// proximity_demo.ino
//
// Demonstrates the use of a passive infrared sensor (PIR). Uses
// interrupts. Uses board version 2.0.14 and GFX version 1.11.0
//
//----------------------------------------------------------------//

void setup() {
  pinMode(9, INPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  if(digitalRead(9)){
    digitalWrite(5, HIGH);
  }
  else{
    digitalWrite(5, LOW);
  }
}
