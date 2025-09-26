#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <string.h>

// Declaración de funciones de algoritmos
int busqueda_lineal(int arr[], int n, int objetivo);
int busqueda_binaria(int arr[], int izquierda, int derecha, int objetivo);
void ordenamiento_burbuja(int arr[], int n);
void merge_sort(int arr[], int izq, int der);
void merge(int arr[], int izq, int medio, int der);
long long fibonacci_recursivo(int n);

// Función para obtener uso de memoria
long obtener_memoria_uso() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

// Funciones auxiliares
void llenar_arreglo_ordenado(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
}

void llenar_arreglo_reverso(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

void llenar_arreglo_aleatorio(int arr[], int n) {
    srand(42);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (n * 10);
    }
}

// Implementaciones de algoritmos
int busqueda_lineal(int arr[], int n, int objetivo) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == objetivo) {
            return i;
        }
    }
    return -1;
}

int busqueda_binaria(int arr[], int izquierda, int derecha, int objetivo) {
    if (derecha >= izquierda) {
        int medio = izquierda + (derecha - izquierda) / 2;
        if (arr[medio] == objetivo) return medio;
        if (arr[medio] > objetivo)
            return busqueda_binaria(arr, izquierda, medio - 1, objetivo);
        return busqueda_binaria(arr, medio + 1, derecha, objetivo);
    }
    return -1;
}

void ordenamiento_burbuja(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void merge(int arr[], int izq, int medio, int der) {
    int n1 = medio - izq + 1;
    int n2 = der - medio;
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[izq + i];
    for (int j = 0; j < n2; j++) R[j] = arr[medio + 1 + j];

    int i = 0, j = 0, k = izq;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k] = L[i++];
        else arr[k] = R[j++];
        k++;
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L); free(R);
}

void merge_sort(int arr[], int izq, int der) {
    if (izq < der) {
        int medio = izq + (der - izq) / 2;
        merge_sort(arr, izq, medio);
        merge_sort(arr, medio + 1, der);
        merge(arr, izq, medio, der);
    }
}

long long fibonacci_recursivo(int n) {
    if (n <= 1) return n;
    return fibonacci_recursivo(n - 1) + fibonacci_recursivo(n - 2);
}

// Función principal de análisis
void ejecutar_analisis() {
    int tamanios[] = {1000, 10000, 100000};
    int num_tamanios = sizeof(tamanios) / sizeof(tamanios[0]);

    printf("=== ANÁLISIS COMPLETO DE COMPLEJIDAD ALGORÍTMICA ===\n\n");

    // 1. Búsqueda Lineal
    printf("1. BÚSQUEDA LINEAL\n");
    printf("Tamaño\t\tTiempo (ms)\tMemoria (KB)\n");
    printf("------\t\t-----------\t------------\n");

    FILE *archivo_busqueda_lineal = fopen("resultados_busqueda_lineal.txt", "w");
    fprintf(archivo_busqueda_lineal, "Tamano,Tiempo_ms,Memoria_KB\n");

    for (int i = 0; i < num_tamanios; i++) {
        int n = tamanios[i];
        int *arr = (int*)malloc(n * sizeof(int));
        llenar_arreglo_ordenado(arr, n);

        long memoria_inicial = obtener_memoria_uso();
        clock_t inicio = clock();
        int resultado = busqueda_lineal(arr, n, n); // Peor caso
        clock_t fin = clock();
        long memoria_final = obtener_memoria_uso();

        double tiempo_ms = ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000.0;
        printf("%d\t\t%.3f\t\t%ld\n", n, tiempo_ms, memoria_final);
        fprintf(archivo_busqueda_lineal, "%d,%.3f,%ld\n", n, tiempo_ms, memoria_final);

        free(arr);
    }
    fclose(archivo_busqueda_lineal);

    // 2. Búsqueda Binaria
    printf("\n2. BÚSQUEDA BINARIA\n");
    printf("Tamaño\t\tTiempo (ms)\tMemoria (KB)\n");
    printf("------\t\t-----------\t------------\n");

    FILE *archivo_busqueda_binaria = fopen("resultados_busqueda_binaria.txt", "w");
    fprintf(archivo_busqueda_binaria, "Tamano,Tiempo_ms,Memoria_KB\n");

    for (int i = 0; i < num_tamanios; i++) {
        int n = tamanios[i];
        int *arr = (int*)malloc(n * sizeof(int));
        llenar_arreglo_ordenado(arr, n);

        long memoria_inicial = obtener_memoria_uso();
        clock_t inicio = clock();
        int resultado = busqueda_binaria(arr, 0, n - 1, n);
        clock_t fin = clock();
        long memoria_final = obtener_memoria_uso();

        double tiempo_ms = ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000.0;
        printf("%d\t\t%.3f\t\t%ld\n", n, tiempo_ms, memoria_final);
        fprintf(archivo_busqueda_binaria, "%d,%.3f,%ld\n", n, tiempo_ms, memoria_final);

        free(arr);
    }
    fclose(archivo_busqueda_binaria);

    // 3. Ordenamiento Burbuja
    printf("\n3. ORDENAMIENTO BURBUJA\n");
    printf("Tamaño\t\tTiempo (ms)\tMemoria (KB)\n");
    printf("------\t\t-----------\t------------\n");

    FILE *archivo_burbuja = fopen("resultados_burbuja.txt", "w");
    fprintf(archivo_burbuja, "Tamano,Tiempo_ms,Memoria_KB\n");

    for (int i = 0; i < num_tamanios; i++) {
        int n = tamanios[i];
        int *arr = (int*)malloc(n * sizeof(int));
        llenar_arreglo_reverso(arr, n); // Peor caso

        long memoria_inicial = obtener_memoria_uso();
        clock_t inicio = clock();
        ordenamiento_burbuja(arr, n);
        clock_t fin = clock();
        long memoria_final = obtener_memoria_uso();

        double tiempo_ms = ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000.0;
        printf("%d\t\t%.3f\t\t%ld\n", n, tiempo_ms, memoria_final);
        fprintf(archivo_burbuja, "%d,%.3f,%ld\n", n, tiempo_ms, memoria_final);

        free(arr);
    }
    fclose(archivo_burbuja);

    // 4. Merge Sort
    printf("\n4. MERGE SORT\n");
    printf("Tamaño\t\tTiempo (ms)\tMemoria (KB)\n");
    printf("------\t\t-----------\t------------\n");

    FILE *archivo_merge = fopen("resultados_merge_sort.txt", "w");
    fprintf(archivo_merge, "Tamano,Tiempo_ms,Memoria_KB\n");

    for (int i = 0; i < num_tamanios; i++) {
        int n = tamanios[i];
        int *arr = (int*)malloc(n * sizeof(int));
        llenar_arreglo_aleatorio(arr, n);

        long memoria_inicial = obtener_memoria_uso();
        clock_t inicio = clock();
        merge_sort(arr, 0, n - 1);
        clock_t fin = clock();
        long memoria_final = obtener_memoria_uso();

        double tiempo_ms = ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000.0;
        printf("%d\t\t%.3f\t\t%ld\n", n, tiempo_ms, memoria_final);
        fprintf(archivo_merge, "%d,%.3f,%ld\n", n, tiempo_ms, memoria_final);

        free(arr);
    }
    fclose(archivo_merge);

    // 5. Fibonacci Recursivo
    printf("\n5. FIBONACCI RECURSIVO (n=1 a 20)\n");
    printf("N\t\tResultado\t\tTiempo (ms)\t\tMemoria (KB)\n");
    printf("--\t\t---------\t\t-----------\t\t------------\n");

    FILE *archivo_fibonacci = fopen("resultados_fibonacci.txt", "w");
    fprintf(archivo_fibonacci, "N,Resultado,Tiempo_ms,Memoria_KB\n");

    for (int n = 1; n <= 20; n++) {
        long memoria_inicial = obtener_memoria_uso();
        clock_t inicio = clock();
        long long resultado = fibonacci_recursivo(n);
        clock_t fin = clock();
        long memoria_final = obtener_memoria_uso();

        double tiempo_ms = ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000.0;
        printf("%d\t\t%lld\t\t\t%.3f\t\t\t%ld\n", n, resultado, tiempo_ms, memoria_final);
        fprintf(archivo_fibonacci, "%d,%lld,%.3f,%ld\n", n, resultado, tiempo_ms, memoria_final);
    }
    fclose(archivo_fibonacci);
}

int main() {
    printf("Iniciando análisis completo de complejidad algorítmica...\n\n");
    ejecutar_analisis();
    printf("\n=== ANÁLISIS COMPLETADO ===\n");
    printf("Los resultados se han guardado en archivos .txt para generar gráficas.\n");

    return 0;
}