#include <SoftwareSerial.h>
SoftwareSerial BT(2,3);

// Definición pines EnA y EnB para el control de la velocidad
int VelocidadMotor1 = 6; 
int VelocidadMotor2 = 5;

// Definición de los pines de control de giro de los motores In1, In2, In3 e In4
int Motor1A = 11; //11 Q 
int Motor1B = 12;  //12
int Motor2C = 10; // 9
int Motor2D = 9; //8

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  // Establecemos modo de los pines del control de motores
  pinMode(Motor1A,OUTPUT);
  pinMode(Motor1B,OUTPUT);
  pinMode(Motor2C,OUTPUT);
  pinMode(Motor2D,OUTPUT);
  pinMode(VelocidadMotor1, OUTPUT);
  pinMode(VelocidadMotor2, OUTPUT);

  // Configuramos los dos motores a velocidad 150/255
  analogWrite(VelocidadMotor1, 150); 
  analogWrite(VelocidadMotor2,  150);  

  // Configuramos sentido de giro
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2C, LOW);
  digitalWrite(Motor2D, LOW);
}

char ADELANTE = 'w';
char ATRAS = 's';
char DERECHA = 'd';
char IZQUIERDA = 'a';

void loop() {
   
    if(BT.available()){

      char comando = BT.read();
      Serial.write(comando);
      
      
      //      
      if(comando == ADELANTE){
        Serial.println("ADELANTE");
        
        digitalWrite(Motor1A, HIGH);
        digitalWrite(Motor2D, HIGH);
                              
      }
    
      else if(comando == IZQUIERDA){ 
        Serial.println("IZQUIERDA");
        
        digitalWrite(Motor1A,LOW);
        digitalWrite(Motor2D, HIGH);
        
      }
      
      
      else if(comando == DERECHA ){  
        Serial.println("DERECHA");
        
        digitalWrite(Motor2D,LOW);
        digitalWrite(Motor1A, HIGH);
        
      }  
      
      else if(comando == ATRAS){ 
        Serial.println("ATRAS");

        digitalWrite(Motor1B, HIGH);
        digitalWrite(Motor2C, HIGH);
        
      }
      else {
        Serial.println("DETENIDO");
        
        digitalWrite(Motor1A, LOW);
        digitalWrite(Motor1B, LOW);
        digitalWrite(Motor2C, LOW);
        digitalWrite(Motor2D, LOW);

      }
              
    }

};