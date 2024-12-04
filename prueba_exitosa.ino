#include <Stepper.h>

// Definición de pines para los motores paso a paso
int stepsPerRevolution = 2048;  // Pasos por vuelta del motor
int motSpeed = 12;              // Velocidad del motor en RPM
Stepper motor1(stepsPerRevolution, 8, 10, 9, 11);   // Motor 1
Stepper motor2(stepsPerRevolution, 4, 6, 5, 7);     // Motor 2

// Definición de pines para el sensor de ultrasonido
const int trigPin = 13;    // Pin Trigger del HC-SR04
const int echoPin = 12;    // Pin Echo del HC-SR04

long duration;             // Duración del pulso
float distancia;           // Distancia calculada en centímetros

void setup() {
  Serial.begin(9600);  // Inicializar la comunicación serial
  
  // Inicializar los pines de los motores
  motor1.setSpeed(motSpeed);
  motor2.setSpeed(motSpeed);

  // Inicializar los pines del sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Enviar un pulso al sensor de ultrasonido
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Leer la duración del pulso de retorno del pin Echo
  duration = pulseIn(echoPin, HIGH);
  
  // Calcular la distancia en centímetros
  distancia = duration * 0.0344 / 2;  // Velocidad del sonido en cm/us, dividido por 2 por el viaje de ida y vuelta
  
  // Enviar la distancia al puerto serial
  Serial.println(distancia);
  
  // Esperar un poco antes de realizar la siguiente medición
  delay(1000);  // Espera 1 segundo

  // Verificar los comandos seriales y mover los motores en función de la entrada del usuario
  if (Serial.available()) {
    char command = Serial.read();

    // Comando 'A' para que avance
    if (command == 'A') {
      for (int i = 0; i < (stepsPerRevolution * 2.1); i++) {
        motor1.step(-1);  // Motor 1 avanza un paso
        motor2.step(-1);  // Motor 2 avanza un paso
      }
    }
    // Comando 'R' para retroceder una vuelta
    else if (command == 'R') {
      for (int i = 0; i < (stepsPerRevolution * 2.1); i++) {
        motor1.step(1);  // Motor 1 retrocede un paso
        motor2.step(1);  // Motor 2 retrocede un paso
      }
    }
    // Comando 'H' para avanzar medio paso
    else if (command == 'H') {
      for (int i = 0; i < (stepsPerRevolution * 0.8); i++) {
        motor1.step(-1);  // Motor 1 avanza medio paso
        motor2.step(-1);  // Motor 2 avanza medio paso
      }
    }
    // Comando 'G' para retroceder medio paso
    else if (command == 'G') {
      for (int i = 0; i < (stepsPerRevolution * 0.8); i++) {
        motor1.step(1);  // Motor 1 retrocede medio paso
        motor2.step(1);  // Motor 2 retrocede medio paso
      }
    }
  }
}
