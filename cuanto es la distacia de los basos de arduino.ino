#include <Stepper.h>

int stepsPerRevolution = 2048;  // Pasos por vuelta del motor
int motSpeed = 12;              // Velocidad del motor en RPM

// Definimos dos motores paso a paso en 4 pines
Stepper motor1(stepsPerRevolution, 8, 10, 9, 11);   // Motor 1
Stepper motor2(stepsPerRevolution, 4, 6, 5, 7);     // Motor 2

void setup() {
  // Configuramos la velocidad para ambos motores
  motor1.setSpeed(motSpeed);
  motor2.setSpeed(motSpeed);

  // Primera vuelta:   carga la miel y se coloca un baso nuevo
  for (int i = 0; i < (stepsPerRevolution * 2.1); i++) {
    motor1.step(-1);  // Motor 1 retrocede un paso
    motor2.step(-1);  // Motor 2 retrocede un paso
  }
  delay(9000);  // Pausa de 5 segundos
    // segunda  vuelta: hacemos que el segundo vaso valla ah cargar la miel
  for (int i = 0; i < (stepsPerRevolution *2.1); i++) {
    motor1.step(-1);  // Motor 1 retrocede un paso
    motor2.step(-1);  // Motor 2 retrocede un paso
  }
  delay(2000);  // se detiene para cargar 

  // tercera vuelta : hace que el primer vaso pase el chequeo 
  for (int i = 0; i < (stepsPerRevolution * 1.0); i++) {

    motor1.step(1);  // Motor 1 retrocede un paso
    motor2.step(11);  // Motor 2 retrocede un paso
  }
  delay(2000);  
  // cuarta vuelt vuelta:hace que el segundo vaso haga el chequeo 
  for (int i = 0; i < (stepsPerRevolution * 2.1 ); i++) {
    motor1.step(-1);  // Motor 1 retrocede un paso
    motor2.step(-1);  // Motor 2 retrocede un paso
  }
  delay(2000);  // Pausa de 2 segundos
  // Los motores se detienen aquí
}

void loop() {
  // No hacemos nada en loop; el programa termina después de setup().
}
