#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src/medicion.h"

/**
 * Algoritmo de Búsqueda Binaria
 * Complejidad temporal: O(log n)
 * Complejidad espacial: O(1)
 * 
 * Busca un elemento en un arreglo ordenado dividiendo por la mitad
 * @param arr: arreglo ordenado donde buscar
 * @param n: tamaño del arreglo
 * @param objetivo: elemento a buscar
 * @return: índice del elemento si se encuentra, -1 si no se encuentra
 */
int busqueda_binaria(int* arr, int n, int objetivo) {
    int izquierda = 0;
    int derecha = n - 1;
    
    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        
        // Si el elemento está en el medio
        if (arr[medio] == objetivo) {
            return medio;
        }
        
        // Si el elemento es mayor, ignorar la mitad izquierda
        if (arr[medio] < objetivo) {
            izquierda = medio + 1;
        }
        // Si el elemento es menor, ignorar la mitad derecha
        else {
            derecha = medio - 1;
        }
    }
    
    return -1;  // Elemento no encontrado
}

/**
 * Función auxiliar para ordenar un arreglo usando QuickSort
 * (Necesario para preparar el arreglo para búsqueda binaria)
 */
void intercambiar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particion(int* arr, int bajo, int alto) {
    int pivote = arr[alto];
    int i = (bajo - 1);
    
    for (int j = bajo; j <= alto - 1; j++) {
        if (arr[j] < pivote) {
            i++;
            intercambiar(&arr[i], &arr[j]);
        }
    }
    intercambiar(&arr[i + 1], &arr[alto]);
    return (i + 1);
}

void quick_sort(int* arr, int bajo, int alto) {
    if (bajo < alto) {
        int pi = particion(arr, bajo, alto);
        quick_sort(arr, bajo, pi - 1);
        quick_sort(arr, pi + 1, alto);
    }
}

/**
 * Función para probar el algoritmo de búsqueda binaria
 * con diferentes tamaños de arreglo
 */
void probar_busqueda_binaria() {
    printf("=== PRUEBAS DE BÚSQUEDA BINARIA ===\n");
    
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
        
        // Ordenar el arreglo (requisito para búsqueda binaria)
        printf("  Ordenando arreglo...\n");
        quick_sort(arr, 0, n - 1);
        
        // Verificar que está ordenado
        if (!esta_ordenado(arr, n)) {
            printf("  Error: El arreglo no está ordenado correctamente\n");
            liberar_arreglo(arr);
            continue;
        }
        
        // Elemento a buscar (que sabemos que existe)
        int objetivo = arr[n/2];  // Buscar elemento en la mitad
        
        // Medir memoria antes de la ejecución
        size_t memoria_inicial = obtener_memoria_usada();
        
        // Medir tiempo de ejecución
        double tiempo_inicio = obtener_tiempo_actual();
        
        // Ejecutar búsqueda binaria
        int resultado = busqueda_binaria(arr, n, objetivo);
        
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
        printf("  Memoria usada: %lu bytes\n", (unsigned long)memoria_usada);
        printf("  Elemento encontrado en índice: %d\n", resultado);
        
        // Liberar memoria
        liberar_arreglo(arr);
    }
    
    // Guardar resultados en archivo
    guardar_resultados("busqueda_binaria", mediciones, num_tamanos);
    
    // Mostrar resumen
    printf("\n=== RESUMEN BÚSQUEDA BINARIA ===\n");
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
 * Función principal para ejecutar las pruebas
 */
int main() {
    printf("Algoritmo: Búsqueda Binaria\n");
    printf("Complejidad temporal: O(log n)\n");
    printf("Complejidad espacial: O(1)\n\n");
    
    probar_busqueda_binaria();
    
    return 0;
}
