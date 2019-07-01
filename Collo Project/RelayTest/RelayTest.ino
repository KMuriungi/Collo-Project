void setup() {
  pinMode(53, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(53, HIGH);   
  delay(5000);                       // wait for a second
  digitalWrite(53, LOW);   
  delay(5000);                       // wait for a second
}
