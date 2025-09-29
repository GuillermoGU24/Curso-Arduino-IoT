#define foco 9
#include <SoftwareSerial.h>
SoftwareSerial BT(3, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BT.begin(9600);

  pinMode(foco, OUTPUT);
  digitalWrite(foco, HIGH);

}

void loop() {
  if (BT.available()) {
    char comando = BT.read();
    if (comando == 'a') {
      digitalWrite(foco, HIGH);
    } else if (comando == 'd') {
      digitalWrite(foco, LOW);

    }

  }
}