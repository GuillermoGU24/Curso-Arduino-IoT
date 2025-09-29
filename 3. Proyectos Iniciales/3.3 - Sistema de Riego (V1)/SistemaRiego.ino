const int agua = D1;
const int sensorPin = A0;
int valorSensor = 0;

void setup() {
Serial.begin(115200);
  
  
  pinMode(agua,OUTPUT);
  digitalWrite(agua,HIGH);  

}

void loop() {

  valorSensor = analogRead(sensorPin);
  Serial.println(valorSensor);

  bool bombear = valorSensor < 100;

  if(bombear){
    digitalWrite(agua,LOW);  
  }
  else {
    digitalWrite(agua,HIGH);
  }
  delay(1000);
  //digitalWrite(agua,HIGH);
    
}