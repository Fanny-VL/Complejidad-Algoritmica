#include "algoritmos.h"

/**
 * Algoritmo de Búsqueda Lineal
 * Complejidad temporal: O(n)
 * Complejidad espacial: O(1)
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
 * Algoritmo de Búsqueda Binaria
 * Complejidad temporal: O(log n)
 * Complejidad espacial: O(1)
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
 * Algoritmo de Ordenamiento por Burbuja (Bubble Sort)
 * Complejidad temporal: O(n²)
 * Complejidad espacial: O(1)
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
 * Función auxiliar para combinar dos subarreglos ordenados
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
 * Algoritmo Recursivo de Fibonacci
 * Complejidad temporal: O(2^n)
 * Complejidad espacial: O(n)
 */
long long fibonacci_recursivo(int n) {
    // Casos base
    if (n <= 1) {
        return n;
    }
    
    // Llamada recursiva
    return fibonacci_recursivo(n - 1) + fibonacci_recursivo(n - 2);
}

// Implementaciones de las funciones de prueba
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
        
        printf("  Tiempo: %.6f ms, Memoria: %lu bytes, Índice: %d\n", 
               mediciones[i].tiempo_ejecucion, (unsigned long)mediciones[i].memoria_usada, resultado);
        
        liberar_arreglo(arr);
    }
    
    guardar_resultados("busqueda_lineal", mediciones, num_tamanos);
    free(mediciones);
}

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
        
        printf("  Tiempo: %.6f ms, Memoria: %lu bytes, Índice: %d\n", 
               mediciones[i].tiempo_ejecucion, (unsigned long)mediciones[i].memoria_usada, resultado);
        
        liberar_arreglo(arr);
    }
    
    guardar_resultados("busqueda_binaria", mediciones, num_tamanos);
    free(mediciones);
}

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
        printf("  Tiempo: %.6f ms, Memoria: %lu bytes, Ordenado: %s\n", 
               mediciones[i].tiempo_ejecucion, (unsigned long)mediciones[i].memoria_usada, 
               ordenado ? "Sí" : "No");
        
        liberar_arreglo(arr);
    }
    
    guardar_resultados("bubble_sort", mediciones, num_tamanos);
    free(mediciones);
}

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
        printf("  Tiempo: %.6f ms, Memoria: %lu bytes, Ordenado: %s\n", 
               mediciones[i].tiempo_ejecucion, (unsigned long)mediciones[i].memoria_usada, 
               ordenado ? "Sí" : "No");
        
        liberar_arreglo(arr);
    }
    
    guardar_resultados("merge_sort", mediciones, num_tamanos);
    free(mediciones);
}

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
        
        printf("  Tiempo: %.6f ms, Memoria: %lu bytes, Resultado: %lld\n", 
               mediciones[i].tiempo_ejecucion, (unsigned long)mediciones[i].memoria_usada, resultado);
    }
    
    guardar_resultados("fibonacci_recursivo", mediciones, num_valores);
    free(mediciones);
}
