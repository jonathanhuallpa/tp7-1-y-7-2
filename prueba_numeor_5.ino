#include <Stepper.h>

int stepsPerRevolution = 2048;  
int motSpeed = 12;              

// Definimos dos motores paso a paso en 4 pines
Stepper motor1(stepsPerRevolution, 8, 10, 9, 11);   
Stepper motor2(stepsPerRevolution, 4, 6, 5, 7);    

// Pines del sensor ultrasonido
int trigPin = 13;
int echoPin = 12;
int pingTravelTime;

void setup() {
  // Configuración de los pines
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

  // Configuración de la velocidad para ambos motores
  motor1.setSpeed(motSpeed);
  motor2.setSpeed(motSpeed);

  // Primera vuelta: carga la miel y coloca un vaso nuevo
  Serial.println("Primera vuelta: cargando miel y colocando un vaso nuevo...");
  moverMotores(-1, stepsPerRevolution * 2.1);
  delay(9000);

  // Segunda vuelta: el segundo vaso se mueve para cargar miel
  Serial.println("Segunda vuelta: moviendo el segundo vaso para cargar miel...");
  moverMotores(-1, stepsPerRevolution * 2.2);
  delay(2000);  // Pausa para cargar

  // Tercera vuelta: el primer vaso pasa al chequeo
  Serial.println("Tercera vuelta: moviendo el primer vaso al chequeo...");
  moverMotores(-1, stepsPerRevolution *0.8 );
  delay(5000);

  // Realizamos la evaluación de la distancia
  long distance = measureDistance();
  Serial.print("Distancia inicial medida: ");
  Serial.println(distance);

  // Evaluamos la distancia para tomar decisiones
  evaluateAndAct(distance);

  // Cuarta vuelta: el segundo vaso pasa al chequeo
  Serial.println("Cuarta vuelta: moviendo el segundo vaso al chequeo...");
  moverMotores(-1, stepsPerRevolution * 2.1);
  delay(5000);
  
  // Realizamos la evaluación de la distancia
  long distane = measureDistance();
  Serial.print("Distancia inicial medida: ");
  Serial.println(distance);

  // Evaluamos la distancia para tomar decisiones
  evaluateAndAct(distance);

  // Quinta vuelta: el segundo vaso avanza hasta el fin de la cinta
  Serial.println("Quinta vuelta: moviendo el segundo vaso hasta el fin de la cinta...");
  moverMotores(-1, stepsPerRevolution * 2.1);

  // Los motores se detienen aquí
  Serial.println("Proceso completo. Los motores se detienen.");
}

void loop() {
  
}

// Función para mover ambos motores en una dirección específica por un número de pasos
void moverMotores(int direccion, int pasos) {
  for (int i = 0; i < pasos; i++) {
    motor1.step(direccion);
    motor2.step(direccion);
  }
}

// Función para medir la distancia usando el sensor ultrasonido
long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pingTravelTime = pulseIn(echoPin, HIGH);

  // Convertir el tiempo a distancia (en cm)
  long distance = pingTravelTime * 0.0343 / 2;
  return distance;
}

// Función para evaluar la distancia y actuar en consecuencia
void evaluateAndAct(long distance) {
  if (distance >= 6.5 && distance <= 9) {
    Serial.println("Distancia entre 6.5 y 9 cm, el vaso va a retroceder...");
    moverMotores(1, stepsPerRevolution * 2.8);
  } 
 
  else if (distance >= 3 && distance <= 6.49) {
    Serial.println("Distancia entre 3 y 6.49 cm, avanzando...");
    moverMotores(-1, stepsPerRevolution * 2.9);
  } 
  else {
    Serial.println("Distancia menor a 3 cm, retrocediendo...");
    moverMotores(-1, stepsPerRevolution * 2.1);
  }
  delay(5000);
}
