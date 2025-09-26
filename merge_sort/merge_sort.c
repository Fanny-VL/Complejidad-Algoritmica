#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src/medicion.h"

/**
 * Función auxiliar para combinar dos subarreglos ordenados
 * @param arr: arreglo principal
 * @param izquierda: índice izquierdo
 * @param medio: índice medio
 * @param derecha: índice derecho
 */
void combinar(int* arr, int izquierda, int medio, int derecha) {
    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;
    
    // Crear arreglos temporales
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    
    if (L == NULL || R == NULL) {
        printf("Error: No se pudo asignar memoria para los arreglos temporales\n");
        if (L) free(L);
        if (R) free(R);
        return;
    }
    
    // Copiar datos a los arreglos temporales
    for (int i = 0; i < n1; i++) {
        L[i] = arr[izquierda + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[medio + 1 + j];
    }
    
    // Combinar los arreglos temporales de vuelta en arr[izquierda..derecha]
    int i = 0;  // Índice inicial del primer subarreglo
    int j = 0;  // Índice inicial del segundo subarreglo
    int k = izquierda;  // Índice inicial del subarreglo combinado
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copiar los elementos restantes de L[], si los hay
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copiar los elementos restantes de R[], si los hay
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // Liberar memoria de los arreglos temporales
    free(L);
    free(R);
}

/**
 * Algoritmo de Merge Sort
 * Complejidad temporal: O(n log n)
 * Complejidad espacial: O(n)
 * 
 * Divide el arreglo en mitades, ordena recursivamente y combina
 * @param arr: arreglo a ordenar
 * @param izquierda: índice izquierdo
 * @param derecha: índice derecho
 */
void merge_sort(int* arr, int izquierda, int derecha) {
    if (izquierda < derecha) {
        // Encontrar el punto medio
        int medio = izquierda + (derecha - izquierda) / 2;
        
        // Ordenar la primera y segunda mitad
        merge_sort(arr, izquierda, medio);
        merge_sort(arr, medio + 1, derecha);
        
        // Combinar las mitades ordenadas
        combinar(arr, izquierda, medio, derecha);
    }
}

/**
 * Función wrapper para merge_sort que toma solo el arreglo y su tamaño
 */
void merge_sort_wrapper(int* arr, int n) {
    merge_sort(arr, 0, n - 1);
}

/**
 * Función para probar el algoritmo de Merge Sort
 * con diferentes tamaños de arreglo
 */
void probar_merge_sort() {
    printf("=== PRUEBAS DE MERGE SORT ===\n");
    
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
        
        // Ejecutar merge sort
        merge_sort_wrapper(arr, n);
        
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
        printf("  Memoria usada: %lu bytes\n", (unsigned long)memoria_usada);
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
    guardar_resultados("merge_sort", mediciones, num_tamanos);
    
    // Mostrar resumen
    printf("\n=== RESUMEN MERGE SORT ===\n");
    printf("Tamaño\tTiempo(ms)\tMemoria(bytes)\n");
    for (int i = 0; i < num_tamanos; i++) {
        printf("%d\t%.6f\t%lu\n", 
               mediciones[i].tamano_entrada,
               mediciones[i].tiempo_ejecucion,
               (unsigned long)mediciones[i].memoria_usada);
    }
    
    free(mediciones);
}

/**
 * Función para demostrar el algoritmo con un ejemplo pequeño
 */
void demostrar_merge_sort() {
    printf("\n=== DEMOSTRACIÓN MERGE SORT ===\n");
    
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Arreglo original: ");
    imprimir_arreglo(arr, n);
    
    merge_sort_wrapper(arr, n);
    
    printf("Arreglo ordenado: ");
    imprimir_arreglo(arr, n);
}

/**
 * Función principal para ejecutar las pruebas
 */
int main() {
    printf("Algoritmo: Merge Sort\n");
    printf("Complejidad temporal: O(n log n)\n");
    printf("Complejidad espacial: O(n)\n\n");
    
    // Demostración con ejemplo pequeño
    demostrar_merge_sort();
    
    // Pruebas con diferentes tamaños
    probar_merge_sort();
    
    return 0;
}
