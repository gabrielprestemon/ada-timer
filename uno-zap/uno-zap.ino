int relay7 = 7;

bool alert = false;

void setup() {
  pinMode(relay7, OUTPUT);
  digitalWrite(relay7, LOW);

  Serial.begin(9600);
  Serial.println("Ready");
}

void loop() {
  if (Serial.available() > 0) {
    Serial.read();
    alert = true;
  }

  if (alert) {
    trigger();
    alert = false;
  }
}

void trigger() {
  Serial.println("ZAP");
  digitalWrite(relay7, HIGH);
  delay(500);
  digitalWrite(relay7, LOW);
}
