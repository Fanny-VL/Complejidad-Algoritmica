#ifndef MEDICION_H
#define MEDICION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <windows.h>  // Para Windows
#include <psapi.h>    // Para medición de memoria en Windows

// Estructura para almacenar mediciones
typedef struct {
    double tiempo_ejecucion;  // en milisegundos
    size_t memoria_usada;     // en bytes
    int tamano_entrada;       // tamaño del arreglo o valor de n
} Medicion;

// Función para obtener tiempo actual en milisegundos
double obtener_tiempo_actual();

// Función para obtener memoria usada por el proceso
size_t obtener_memoria_usada();

// Función para generar arreglo aleatorio
int* generar_arreglo_aleatorio(int n);

// Función para generar arreglo ordenado
int* generar_arreglo_ordenado(int n);

// Función para imprimir arreglo (para debugging)
void imprimir_arreglo(int* arr, int n);

// Función para verificar si un arreglo está ordenado
int esta_ordenado(int* arr, int n);

// Función para liberar memoria de arreglo
void liberar_arreglo(int* arr);

// Función para guardar resultados en archivo
void guardar_resultados(const char* nombre_algoritmo, Medicion* mediciones, int num_mediciones);

#endif
