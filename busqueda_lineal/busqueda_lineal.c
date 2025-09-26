#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src/medicion.h"

/**
 * Algoritmo de Búsqueda Lineal
 * Complejidad temporal: O(n)
 * Complejidad espacial: O(1)
 * 
 * Busca un elemento en un arreglo de forma secuencial
 * @param arr: arreglo donde buscar
 * @param n: tamaño del arreglo
 * @param objetivo: elemento a buscar
 * @return: índice del elemento si se encuentra, -1 si no se encuentra
 */
int busqueda_lineal(int* arr, int n, int objetivo) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == objetivo) {
            return i;  // Elemento encontrado
        }
    }
    return -1;  // Elemento no encontrado
}

/**
 * Función para probar el algoritmo de búsqueda lineal
 * con diferentes tamaños de arreglo
 */
void probar_busqueda_lineal() {
    printf("=== PRUEBAS DE BÚSQUEDA LINEAL ===\n");
    
    // Tamaños de prueba según las instrucciones
    int tamanos[] = {1000, 10000, 100000};  // 10³, 10⁴, 10⁵
    int num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);
    
    Medicion* mediciones = (Medicion*)malloc(num_tamanos * sizeof(Medicion));
    
    for (int i = 0; i < num_tamanos; i++) {
        int n = tamanos[i];
        printf("\nProbando con arreglo de tamaño %d...\n", n);
        
        // Generar arreglo aleatorio
        int* arr = generar_arreglo_aleatorio(n);
        if (arr == NULL) continue;
        
        // Elemento a buscar (que sabemos que existe)
        int objetivo = arr[n/2];  // Buscar elemento en la mitad
        
        // Medir memoria antes de la ejecución
        size_t memoria_inicial = obtener_memoria_usada();
        
        // Medir tiempo de ejecución
        double tiempo_inicio = obtener_tiempo_actual();
        
        // Ejecutar búsqueda lineal
        int resultado = busqueda_lineal(arr, n, objetivo);
        
        double tiempo_fin = obtener_tiempo_actual();
        size_t memoria_final = obtener_memoria_usada();
        
        // Calcular mediciones
        double tiempo_ejecucion = tiempo_fin - tiempo_inicio;
        size_t memoria_usada = memoria_final - memoria_inicial;
        
        // Almacenar medición
        mediciones[i].tamano_entrada = n;
        mediciones[i].tiempo_ejecucion = tiempo_ejecucion;
        mediciones[i].memoria_usada = memoria_usada;
        
        // Mostrar resultados
        printf("  Tiempo de ejecución: %.6f ms\n", tiempo_ejecucion);
        printf("  Memoria usada: %zu bytes\n", memoria_usada);
        printf("  Elemento encontrado en índice: %d\n", resultado);
        
        // Liberar memoria
        liberar_arreglo(arr);
    }
    
    // Guardar resultados en archivo
    guardar_resultados("busqueda_lineal", mediciones, num_tamanos);
    
    // Mostrar resumen
    printf("\n=== RESUMEN BÚSQUEDA LINEAL ===\n");
    printf("Tamaño\tTiempo(ms)\tMemoria(bytes)\n");
    for (int i = 0; i < num_tamanos; i++) {
        printf("%d\t%.6f\t%zu\n", 
               mediciones[i].tamano_entrada,
               mediciones[i].tiempo_ejecucion,
               mediciones[i].memoria_usada);
    }
    
    free(mediciones);
}

/**
 * Función principal para ejecutar las pruebas
 */
int main() {
    printf("Algoritmo: Búsqueda Lineal\n");
    printf("Complejidad temporal: O(n)\n");
    printf("Complejidad espacial: O(1)\n\n");
    
    probar_busqueda_lineal();
    
    return 0;
}
