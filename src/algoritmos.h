#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "medicion.h"

// Declaraciones de funciones de los algoritmos
int busqueda_lineal(int* arr, int n, int objetivo);
int busqueda_binaria(int* arr, int n, int objetivo);
void bubble_sort(int* arr, int n);
void merge_sort_wrapper(int* arr, int n);
long long fibonacci_recursivo(int n);

// Declaraciones de funciones de prueba
void probar_busqueda_lineal();
void probar_busqueda_binaria();
void probar_bubble_sort();
void probar_merge_sort();
void probar_fibonacci_recursivo();

#endif
