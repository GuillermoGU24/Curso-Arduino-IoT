#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define SERVO_PIN 6  // Pin donde está conectado el servo

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo puerta;
boolean abierto;

// UID autorizado (puedes cambiarlo por el UID de tu tarjeta)
byte tarjetaAutorizada[] = {0x0A, 0x76, 0x41, 0x05};

bool compararUID(byte *uid) {
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (uid[i] != tarjetaAutorizada[i]) return false;
  }
  return true;
}

void abrirPuerta() {
  puerta.write(90); // Abre (ajusta según tu servo)
  abierto=true;
}
void cerrarPuerta(){
  puerta.write(0);
  abierto=false;
  }
void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  puerta.attach(SERVO_PIN);
  puerta.write(0); // Posición inicial (cerrado)

  Serial.println("Sistema RFID con Servo listo.");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("UID detectado: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  if (compararUID(mfrc522.uid.uidByte)) {
    Serial.println("Acceso autorizado. Abriendo puerta...");
    if(!abierto)abrirPuerta();
    else cerrarPuerta();
 
  } else {
    cerrarPuerta();
    Serial.println("Acceso denegado.");
  }

  // Finaliza comunicación con la tarjeta
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}