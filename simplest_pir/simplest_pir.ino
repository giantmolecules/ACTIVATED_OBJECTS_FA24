void setup() {
  // put your setup code here, to run once:
  pinMode(9, INPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(9)){
    digitalWrite(5, HIGH);
  }
  else{
    digitalWrite(5, LOW);
  }
}
