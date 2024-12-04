// Definición de pines
const int trigPin = 13;    // Pin Trigger del HC-SR04
const int echoPin = 12;   // Pin Echo del HC-SR04

long duration;             // Duración del pulso
float distancia;           // Distancia calculada en centímetros

void setup() {
  // Inicializar los pines del sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Inicializar la comunicación serial
  Serial.begin(9600);  // Configura la velocidad de la comunicación serial
}

void loop() {
  // Enviar un pulso de 10 microsegundos al pin Trigger para iniciar la medición
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Leer la duración del pulso de retorno del pin Echo
  duration = pulseIn(echoPin, HIGH);
  
  // Calcular la distancia en centímetros
  distancia = duration * 0.0344/2 ;  // Velocidad del sonido en cm/us, dividido por 2 por el viaje de ida y vuelta
  
  // Enviar la distancia al puerto serial
  Serial.println(distancia);
  
  // Esperar un poco antes de realizar la siguiente medición
  delay(1000);  // Espera 1 segundo antes de realizar otra medición
}
