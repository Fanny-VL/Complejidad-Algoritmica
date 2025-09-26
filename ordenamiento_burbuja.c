#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <unistd.h>

void ordenamiento_burbuja(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Intercambiar elementos
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

long obtener_memoria_uso() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss; // En KB en Linux, bytes en macOS
}

void llenar_arreglo_reverso(int arr[], int n) {
    // Llenar en orden descendente (peor caso para burbuja)
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

void imprimir_arreglo(int arr[], int n) {
    if (n <= 20) {
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}

int main() {
    int tamanios[] = {1000, 10000, 100000};
    int num_tamanios = sizeof(tamanios) / sizeof(tamanios[0]);

    printf("Análisis de Complejidad - Ordenamiento Burbuja\n");
    printf("Tamaño\t\tTiempo (ms)\tMemoria (KB)\n");
    printf("------\t\t-----------\t------------\n");

    for (int i = 0; i < num_tamanios; i++) {
        int n = tamanios[i];
        int *arr = (int*)malloc(n * sizeof(int));

        if (arr == NULL) {
            printf("Error: No se pudo asignar memoria para n=%d\n", n);
            continue;
        }

        llenar_arreglo_reverso(arr, n);

        long memoria_inicial = obtener_memoria_uso();

        clock_t inicio = clock();

        ordenamiento_burbuja(arr, n);

        clock_t fin = clock();

        long memoria_final = obtener_memoria_uso();

        double tiempo_ms = ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000.0;

        printf("%d\t\t%.3f\t\t%ld\n", n, tiempo_ms, memoria_final);

        free(arr);
    }

    return 0;
}