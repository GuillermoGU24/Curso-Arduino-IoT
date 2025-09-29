#include <Servo.h>

const int ldrPin = A0;
const int servoPin = 11;

Servo myServo;

void setup() {
  myServo.attach(servoPin);
  pinMode(ldrPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);

  if (ldrValue < 600) {
    myServo.write(0);
  }

  delay(10);
  myServo.write(90);
}
