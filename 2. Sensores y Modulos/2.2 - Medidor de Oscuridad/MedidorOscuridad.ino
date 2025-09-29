const int ldrPin = A0;
const int ledPin = 13;
const int umbralLuz = 500;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int valorLuz = analogRead(ldrPin);
  Serial.println(valorLuz);

  if (valorLuz <= umbralLuz) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(200);
}
