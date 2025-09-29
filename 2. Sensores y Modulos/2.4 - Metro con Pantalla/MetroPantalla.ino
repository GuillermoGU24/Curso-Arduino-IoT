#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Dirección I2C del LCD (generalmente 0x27 o 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define TRIG_PIN 10
#define ECHO_PIN 9

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("Distancia:");
}

void loop() {
  // Generar pulso en TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Leer tiempo del eco
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Convertir tiempo a distancia en metros
  float distance = (duration * 0.000343) / 2;

  // Mostrar en pantalla
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" m   "); // Espacios para borrar caracteres previos

  // Mostrar en consola serial
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" m");

  delay(500);
}
