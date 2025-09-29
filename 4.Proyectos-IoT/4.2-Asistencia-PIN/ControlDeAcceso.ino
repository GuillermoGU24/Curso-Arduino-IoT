#include <WiFi.h>
#include <HTTPClient.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// === WiFi ===
const char* ssid = "GP24";
const char* password = "123456789";
const char* serverUrl = "https://registroasistenciaconpin-production.up.railway.app/api/verificar-pin";

// === Pantalla LCD I2C ===
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Dirección 0x27, tamaño 16x2

// === Teclado ===
const byte ROWS = 4;
const byte COLS = 3;


char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {1, 2, 3, 4}; // Ajusta según conexión
byte colPins[COLS] = {9, 8, 7};       // Ajusta según conexión

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// === Variables ===
String pinBuffer = "";
bool esperandoRespuesta = false;

void setup() {
  Serial.begin(115200);

  // Pantalla
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Conectando...");

  // WiFi
  WiFi.disconnect();
  delay(100);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado al WiFi");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ingrese PIN:");
}

void loop() {
  if (esperandoRespuesta) return; // Bloquea mientras se espera respuesta

  char key = keypad.getKey();
  if (key) {
    Serial.print("Tecla: ");
    Serial.println(key);

    if (key >= '0' && key <= '9') {
      if (pinBuffer.length() < 5) {
        pinBuffer += key;
        actualizarPantalla(pinBuffer);
      }
    } else if (key == '*') {
      pinBuffer = "";
      actualizarPantalla(pinBuffer);
    }

    if (pinBuffer.length() == 5) {
      esperandoRespuesta = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Verificando...");
      verificarPin(pinBuffer);
      pinBuffer = ""; // Limpiar para nuevo intento
      esperandoRespuesta = false;
      lcd.setCursor(0, 0);
      lcd.print("Ingrese PIN:");
    }
  }
}

void actualizarPantalla(String texto) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PIN: " + texto);
}

void verificarPin(String pin) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    String jsonPayload = "{\"pin\":\"" + pin + "\"}";

    int httpResponseCode = http.POST(jsonPayload);

    lcd.clear();
    lcd.setCursor(0, 0);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Respuesta del servidor:");
      Serial.println(response);
      lcd.print("Servidor:");
      lcd.setCursor(0, 1);
      lcd.print(response.substring(0, 16)); // Trunca a 16 caracteres
      delay(3000);
      lcd.clear();
    } else {
      Serial.printf("Error HTTP: %s\n", http.errorToString(httpResponseCode).c_str());
      lcd.print("Error HTTP");
    }

    http.end();
    delay(3000); // Mostrar mensaje 3 segundos
  } else {
    lcd.clear();
    lcd.print("WiFi no conectado");
    Serial.println("Error: WiFi no conectado");
    delay(3000);
  }
}