#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src/medicion.h"

/**
 * Algoritmo de Ordenamiento por Burbuja (Bubble Sort)
 * Complejidad temporal: O(n²)
 * Complejidad espacial: O(1)
 * 
 * Compara elementos adyacentes e intercambia si están en orden incorrecto
 * @param arr: arreglo a ordenar
 * @param n: tamaño del arreglo
 */
void bubble_sort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        // Flag para optimización: si no hay intercambios, el arreglo está ordenado
        int intercambiado = 0;
        
        for (int j = 0; j < n - i - 1; j++) {
            // Si el elemento actual es mayor que el siguiente, intercambiar
            if (arr[j] > arr[j + 1]) {
                // Intercambiar elementos
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                intercambiado = 1;
            }
        }
        
        // Si no hubo intercambios en esta pasada, el arreglo está ordenado
        if (!intercambiado) {
            break;
        }
    }
}

/**
 * Función para probar el algoritmo de ordenamiento por burbuja
 * con diferentes tamaños de arreglo
 */
void probar_bubble_sort() {
    printf("=== PRUEBAS DE ORDENAMIENTO POR BURBUJA ===\n");
    
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
        
        // Crear una copia para verificar el ordenamiento
        int* arr_copia = (int*)malloc(n * sizeof(int));
        if (arr_copia == NULL) {
            printf("  Error: No se pudo crear copia del arreglo\n");
            liberar_arreglo(arr);
            continue;
        }
        
        // Copiar arreglo original
        for (int j = 0; j < n; j++) {
            arr_copia[j] = arr[j];
        }
        
        // Medir memoria antes de la ejecución
        size_t memoria_inicial = obtener_memoria_usada();
        
        // Medir tiempo de ejecución
        double tiempo_inicio = obtener_tiempo_actual();
        
        // Ejecutar bubble sort
        bubble_sort(arr, n);
        
        double tiempo_fin = obtener_tiempo_actual();
        size_t memoria_final = obtener_memoria_usada();
        
        // Calcular mediciones
        double tiempo_ejecucion = tiempo_fin - tiempo_inicio;
        size_t memoria_usada = memoria_final - memoria_inicial;
        
        // Verificar que el arreglo está ordenado
        int ordenado = esta_ordenado(arr, n);
        if (!ordenado) {
            printf("  Error: El arreglo no está ordenado correctamente\n");
        }
        
        // Almacenar medición
        mediciones[i].tamano_entrada = n;
        mediciones[i].tiempo_ejecucion = tiempo_ejecucion;
        mediciones[i].memoria_usada = memoria_usada;
        
        // Mostrar resultados
        printf("  Tiempo de ejecución: %.6f ms\n", tiempo_ejecucion);
        printf("  Memoria usada: %zu bytes\n", memoria_usada);
        printf("  Arreglo ordenado correctamente: %s\n", ordenado ? "Sí" : "No");
        
        // Mostrar algunos elementos del arreglo ordenado (solo para arreglos pequeños)
        if (n <= 20) {
            printf("  Arreglo ordenado: ");
            imprimir_arreglo(arr, n);
        } else {
            printf("  Primeros 10 elementos: ");
            for (int k = 0; k < 10 && k < n; k++) {
                printf("%d ", arr[k]);
            }
            printf("\n");
        }
        
        // Liberar memoria
        liberar_arreglo(arr);
        liberar_arreglo(arr_copia);
    }
    
    // Guardar resultados en archivo
    guardar_resultados("bubble_sort", mediciones, num_tamanos);
    
    // Mostrar resumen
    printf("\n=== RESUMEN ORDENAMIENTO POR BURBUJA ===\n");
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
 * Función para demostrar el algoritmo con un ejemplo pequeño
 */
void demostrar_bubble_sort() {
    printf("\n=== DEMOSTRACIÓN BUBBLE SORT ===\n");
    
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Arreglo original: ");
    imprimir_arreglo(arr, n);
    
    bubble_sort(arr, n);
    
    printf("Arreglo ordenado: ");
    imprimir_arreglo(arr, n);
}

/**
 * Función principal para ejecutar las pruebas
 */
int main() {
    printf("Algoritmo: Ordenamiento por Burbuja (Bubble Sort)\n");
    printf("Complejidad temporal: O(n²)\n");
    printf("Complejidad espacial: O(1)\n\n");
    
    // Demostración con ejemplo pequeño
    demostrar_bubble_sort();
    
    // Pruebas con diferentes tamaños
    probar_bubble_sort();
    
    return 0;
}
