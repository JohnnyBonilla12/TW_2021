int LedIntegrado = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(LedIntegrado, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LedIntegrado, HIGH);
  delay(1000);
  digitalWrite(LedIntegrado, LOW);
  delay(500);
}
