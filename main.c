#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "src/medicion.h"

// Declaraciones de funciones de los algoritmos
int busqueda_lineal(int* arr, int n, int objetivo);
int busqueda_binaria(int* arr, int n, int objetivo);
void bubble_sort(int* arr, int n);
void merge_sort_wrapper(int* arr, int n);
long long fibonacci_recursivo(int n);

// Función para ejecutar todas las pruebas
void ejecutar_todas_las_pruebas() {
    printf("========================================\n");
    printf("    PRÁCTICA: COMPLEJIDAD ALGORÍTMICA\n");
    printf("========================================\n");
    printf("Materia: Análisis y Diseño de Algoritmos\n");
    printf("Escuela: ESCOM\n");
    printf("Carrera: Licenciatura en Ciencia de Datos\n");
    printf("Grupo: 3AV1\n");
    printf("Integrantes:\n");
    printf("- Valderrama López Fanny\n");
    printf("- Elena Carmina Mata González\n");
    printf("========================================\n\n");
    
    // Crear directorio de resultados si no existe
    system("if not exist resultados mkdir resultados");
    
    printf("Iniciando pruebas de todos los algoritmos...\n\n");
    
    // 1. Búsqueda Lineal
    printf("1. BÚSQUEDA LINEAL\n");
    printf("==================\n");
    probar_busqueda_lineal();
    printf("\n");
    
    // 2. Búsqueda Binaria
    printf("2. BÚSQUEDA BINARIA\n");
    printf("===================\n");
    probar_busqueda_binaria();
    printf("\n");
    
    // 3. Bubble Sort
    printf("3. ORDENAMIENTO POR BURBUJA\n");
    printf("============================\n");
    probar_bubble_sort();
    printf("\n");
    
    // 4. Merge Sort
    printf("4. MERGE SORT\n");
    printf("=============\n");
    probar_merge_sort();
    printf("\n");
    
    // 5. Fibonacci Recursivo
    printf("5. FIBONACCI RECURSIVO\n");
    printf("======================\n");
    probar_fibonacci_recursivo();
    printf("\n");
    
    printf("========================================\n");
    printf("TODAS LAS PRUEBAS COMPLETADAS\n");
    printf("========================================\n");
    printf("Los resultados se han guardado en la carpeta 'resultados/'\n");
    printf("Revisa los archivos .txt para ver los datos detallados.\n");
}

// Función para probar búsqueda lineal
void probar_busqueda_lineal() {
    printf("Complejidad temporal: O(n)\n");
    printf("Complejidad espacial: O(1)\n\n");
    
    int tamanos[] = {1000, 10000, 100000};
    int num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);
    
    Medicion* mediciones = (Medicion*)malloc(num_tamanos * sizeof(Medicion));
    
    for (int i = 0; i < num_tamanos; i++) {
        int n = tamanos[i];
        printf("Probando con arreglo de tamaño %d...\n", n);
        
        int* arr = generar_arreglo_aleatorio(n);
        if (arr == NULL) continue;
        
        int objetivo = arr[n/2];
        
        size_t memoria_inicial = obtener_memoria_usada();
        double tiempo_inicio = obtener_tiempo_actual();
        
        int resultado = busqueda_lineal(arr, n, objetivo);
        
        double tiempo_fin = obtener_tiempo_actual();
        size_t memoria_final = obtener_memoria_usada();
        
        mediciones[i].tamano_entrada = n;
        mediciones[i].tiempo_ejecucion = tiempo_fin - tiempo_inicio;
        mediciones[i].memoria_usada = memoria_final - memoria_inicial;
        
        printf("  Tiempo: %.6f ms, Memoria: %zu bytes, Índice: %d\n", 
               mediciones[i].tiempo_ejecucion, mediciones[i].memoria_usada, resultado);
        
        liberar_arreglo(arr);
    }
    
    guardar_resultados("busqueda_lineal", mediciones, num_tamanos);
    free(mediciones);
}

// Función para probar búsqueda binaria
void probar_busqueda_binaria() {
    printf("Complejidad temporal: O(log n)\n");
    printf("Complejidad espacial: O(1)\n\n");
    
    int tamanos[] = {1000, 10000, 100000};
    int num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);
    
    Medicion* mediciones = (Medicion*)malloc(num_tamanos * sizeof(Medicion));
    
    for (int i = 0; i < num_tamanos; i++) {
        int n = tamanos[i];
        printf("Probando con arreglo de tamaño %d...\n", n);
        
        int* arr = generar_arreglo_ordenado(n);
        if (arr == NULL) continue;
        
        int objetivo = arr[n/2];
        
        size_t memoria_inicial = obtener_memoria_usada();
        double tiempo_inicio = obtener_tiempo_actual();
        
        int resultado = busqueda_binaria(arr, n, objetivo);
        
        double tiempo_fin = obtener_tiempo_actual();
        size_t memoria_final = obtener_memoria_usada();
        
        mediciones[i].tamano_entrada = n;
        mediciones[i].tiempo_ejecucion = tiempo_fin - tiempo_inicio;
        mediciones[i].memoria_usada = memoria_final - memoria_inicial;
        
        printf("  Tiempo: %.6f ms, Memoria: %zu bytes, Índice: %d\n", 
               mediciones[i].tiempo_ejecucion, mediciones[i].memoria_usada, resultado);
        
        liberar_arreglo(arr);
    }
    
    guardar_resultados("busqueda_binaria", mediciones, num_tamanos);
    free(mediciones);
}

// Función para probar bubble sort
void probar_bubble_sort() {
    printf("Complejidad temporal: O(n²)\n");
    printf("Complejidad espacial: O(1)\n\n");
    
    int tamanos[] = {1000, 10000, 100000};
    int num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);
    
    Medicion* mediciones = (Medicion*)malloc(num_tamanos * sizeof(Medicion));
    
    for (int i = 0; i < num_tamanos; i++) {
        int n = tamanos[i];
        printf("Probando con arreglo de tamaño %d...\n", n);
        
        int* arr = generar_arreglo_aleatorio(n);
        if (arr == NULL) continue;
        
        size_t memoria_inicial = obtener_memoria_usada();
        double tiempo_inicio = obtener_tiempo_actual();
        
        bubble_sort(arr, n);
        
        double tiempo_fin = obtener_tiempo_actual();
        size_t memoria_final = obtener_memoria_usada();
        
        mediciones[i].tamano_entrada = n;
        mediciones[i].tiempo_ejecucion = tiempo_fin - tiempo_inicio;
        mediciones[i].memoria_usada = memoria_final - memoria_inicial;
        
        int ordenado = esta_ordenado(arr, n);
        printf("  Tiempo: %.6f ms, Memoria: %zu bytes, Ordenado: %s\n", 
               mediciones[i].tiempo_ejecucion, mediciones[i].memoria_usada, 
               ordenado ? "Sí" : "No");
        
        liberar_arreglo(arr);
    }
    
    guardar_resultados("bubble_sort", mediciones, num_tamanos);
    free(mediciones);
}

// Función para probar merge sort
void probar_merge_sort() {
    printf("Complejidad temporal: O(n log n)\n");
    printf("Complejidad espacial: O(n)\n\n");
    
    int tamanos[] = {1000, 10000, 100000};
    int num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);
    
    Medicion* mediciones = (Medicion*)malloc(num_tamanos * sizeof(Medicion));
    
    for (int i = 0; i < num_tamanos; i++) {
        int n = tamanos[i];
        printf("Probando con arreglo de tamaño %d...\n", n);
        
        int* arr = generar_arreglo_aleatorio(n);
        if (arr == NULL) continue;
        
        size_t memoria_inicial = obtener_memoria_usada();
        double tiempo_inicio = obtener_tiempo_actual();
        
        merge_sort_wrapper(arr, n);
        
        double tiempo_fin = obtener_tiempo_actual();
        size_t memoria_final = obtener_memoria_usada();
        
        mediciones[i].tamano_entrada = n;
        mediciones[i].tiempo_ejecucion = tiempo_fin - tiempo_inicio;
        mediciones[i].memoria_usada = memoria_final - memoria_inicial;
        
        int ordenado = esta_ordenado(arr, n);
        printf("  Tiempo: %.6f ms, Memoria: %zu bytes, Ordenado: %s\n", 
               mediciones[i].tiempo_ejecucion, mediciones[i].memoria_usada, 
               ordenado ? "Sí" : "No");
        
        liberar_arreglo(arr);
    }
    
    guardar_resultados("merge_sort", mediciones, num_tamanos);
    free(mediciones);
}

// Función para probar fibonacci recursivo
void probar_fibonacci_recursivo() {
    printf("Complejidad temporal: O(2^n)\n");
    printf("Complejidad espacial: O(n)\n\n");
    
    int valores[] = {1, 5, 10, 15, 20};
    int num_valores = sizeof(valores) / sizeof(valores[0]);
    
    Medicion* mediciones = (Medicion*)malloc(num_valores * sizeof(Medicion));
    
    for (int i = 0; i < num_valores; i++) {
        int n = valores[i];
        printf("Probando Fibonacci(%d)...\n", n);
        
        size_t memoria_inicial = obtener_memoria_usada();
        double tiempo_inicio = obtener_tiempo_actual();
        
        long long resultado = fibonacci_recursivo(n);
        
        double tiempo_fin = obtener_tiempo_actual();
        size_t memoria_final = obtener_memoria_usada();
        
        mediciones[i].tamano_entrada = n;
        mediciones[i].tiempo_ejecucion = tiempo_fin - tiempo_inicio;
        mediciones[i].memoria_usada = memoria_final - memoria_inicial;
        
        printf("  Tiempo: %.6f ms, Memoria: %zu bytes, Resultado: %lld\n", 
               mediciones[i].tiempo_ejecucion, mediciones[i].memoria_usada, resultado);
    }
    
    guardar_resultados("fibonacci_recursivo", mediciones, num_valores);
    free(mediciones);
}

// Función principal
int main() {
    ejecutar_todas_las_pruebas();
    return 0;
}
