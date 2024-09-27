#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
	int id;
	char evento[50];
	float medicion;
	int prioridad;
	time_t tiempoMedicion;
	struct Nodo* siguiente;
} Nodo;

size_t memoriaAsignada = 0;

void* miMalloc(size_t tamano) {
	void* ptr = malloc(tamano);
	if (ptr) {
		memoriaAsignada += tamano;
	}
	return ptr;
}

void miFree(void* ptr, size_t tamano) {
	if (ptr) {
		memoriaAsignada -= tamano;
		free(ptr);
	}
}

size_t obtenerMemoriaAsignada() {
	return memoriaAsignada;
}


Nodo* crearNodo(int id, const char* evento, float medicion, int prioridad, time_t tiempoMedicion) {
	
	Nodo* nuevoNodo = (Nodo*)miMalloc(sizeof(Nodo));
	if (!nuevoNodo) {
		printf("Error al asignar memoria\n");
		exit(1);
	}
	nuevoNodo->id = id;
	strcpy(nuevoNodo->evento, evento);
	nuevoNodo->medicion = medicion;
	nuevoNodo->prioridad = prioridad;
	nuevoNodo->tiempoMedicion = tiempoMedicion;
	nuevoNodo->siguiente = NULL;
	return nuevoNodo;
}

