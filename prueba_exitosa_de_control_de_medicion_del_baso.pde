import processing.serial.*;

Serial myPort;  // Objeto para la comunicación serial
float distancia = 0.0;  // Variable para almacenar la distancia
float porcentaje = 0.0;  // Variable para almacenar el porcentaje del vaso
color circuloColor = color(255);  // Color inicial del círculo (blanco)

void setup() {
  size(400, 400);  // Tamaño de la ventana
  background(200);  // Fondo gris claro

  // Obtener y mostrar los puertos disponibles
  String[] listaDePuertos = Serial.list();
  println(listaDePuertos);  // Ver los puertos disponibles
  String portName = listaDePuertos[0];  // Seleccionar el primer puerto
  myPort = new Serial(this, portName, 9600);  // Abrir el puerto con velocidad de 9600 baudios
  myPort.bufferUntil('\n');  // Leer hasta el salto de línea
}

void draw() {
  background(200);  // Fondo gris claro
  
  // Mostrar el círculo con el color correspondiente
  fill(circuloColor);  // Rellenar con el color actual
  ellipse(100, 200, 100, 100);  // Círculo

  // Mostrar el texto "Distancia:" y el valor debajo del círculo con 2 decimales
  fill(0);
  textSize(16);
  textAlign(CENTER, CENTER);
  text("Distancia: " + nf(distancia, 1, 2) + " cm", 100, 270);  // Mostrar la distancia debajo del círculo

  // Dibujar el vaso con dimensiones fijas: base 70 y parte superior 80
  fill(0, 0, 255);  // Color azul
  beginShape();
  vertex(250, 250);  // Parte inferior del vaso
  vertex(320, 250);  // Parte inferior derecha del vaso
  vertex(340, 250 - (porcentaje / 100) * 80);  // Parte superior derecha del vaso (depende del porcentaje)
  vertex(230, 250 - (porcentaje / 100) * 80);  // Parte superior izquierda del vaso
  endShape(CLOSE);  // Cerrar el vaso

  // Mostrar el porcentaje dentro del vaso
  fill(0);
  textSize(16);
  textAlign(CENTER, CENTER);
  text(porcentaje + "%", 285, 250 - (porcentaje / 100) * 40);  // Mostrar el porcentaje en la parte superior del vaso

  // Mostrar el porcentaje debajo del vaso
  text(nf(porcentaje, 1, 0) + "%", 285, 270);  // Mostrar el porcentaje debajo del vaso
  
  // Mostrar el mensaje de "Retrocede" o "Avanza" debajo del vaso
  textSize(18);
  if (porcentaje == 100) {
    text("Avanza", 285, 300);  // Si el porcentaje es 100%
  } else if (porcentaje == 25 || porcentaje == 50) {
    text("Retrocede", 285, 300);  // Si el porcentaje es 25% o 50%
  } else {
    text("Esperando...", 285, 300);  // Si el porcentaje es 0%
  }
}

// Función que se llama cuando llegan datos del puerto serial
void serialEvent(Serial myPort) {
  String data = myPort.readStringUntil('\n');  // Leer hasta el salto de línea
  if (data != null) {
    data = trim(data);  // Eliminar espacios en blanco
    println("Recibido: " + data);  // Mostrar los datos recibidos para depuración

    try {
      distancia = float(data);  // Convertir la distancia a un número flotante
      // Actualizar el porcentaje y el color del círculo según la distancia
      actualizarPorcentajeYColor();
    } catch (Exception e) {
      println("Error al convertir la distancia");
    }
  }
}

void actualizarPorcentajeYColor() {
  // Actualizar el porcentaje y el color basado en la distancia
  if (distancia >= 8.12 && distancia <= 8.24) {
    circuloColor = color(255, 0, 0);  // Rojo
    porcentaje = 0;  // Vaso vacío
  } else if (distancia >= 6.48 && distancia <=6.60)  {
    circuloColor = color(255, 165, 0);  // Naranja
    porcentaje = 25;  // 25%
  } else if (distancia >= 6.83 && distancia <= 6.93) {
    circuloColor = color(255, 255, 0);  // Amarillo
    porcentaje = 50;  // 50%
  } else if (distancia >= 5.50 && distancia <= 5.62) {
    circuloColor = color(0, 255, 0);  // Verde
    porcentaje = 100;  // 100%
  } else {
    circuloColor = color(255);  // Si no está en el rango, mantener color blanco
    porcentaje = 0;  // No hay agua
  }
}
