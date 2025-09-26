#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <unistd.h>

void merge(int arr[], int izq, int medio, int der) {
    int n1 = medio - izq + 1;
    int n2 = der - medio;

    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[izq + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[medio + 1 + j];

    int i = 0, j = 0, k = izq;

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

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void merge_sort(int arr[], int izq, int der) {
    if (izq < der) {
        int medio = izq + (der - izq) / 2;

        merge_sort(arr, izq, medio);
        merge_sort(arr, medio + 1, der);

        merge(arr, izq, medio, der);
    }
}

long obtener_memoria_uso() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss; // En KB en Linux, bytes en macOS
}

void llenar_arreglo_aleatorio(int arr[], int n) {
    srand(42); // Semilla fija para resultados reproducibles
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (n * 10);
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

    printf("Análisis de Complejidad - Merge Sort\n");
    printf("Tamaño\t\tTiempo (ms)\tMemoria (KB)\n");
    printf("------\t\t-----------\t------------\n");

    for (int i = 0; i < num_tamanios; i++) {
        int n = tamanios[i];
        int *arr = (int*)malloc(n * sizeof(int));

        if (arr == NULL) {
            printf("Error: No se pudo asignar memoria para n=%d\n", n);
            continue;
        }

        llenar_arreglo_aleatorio(arr, n);

        long memoria_inicial = obtener_memoria_uso();

        clock_t inicio = clock();

        merge_sort(arr, 0, n - 1);

        clock_t fin = clock();

        long memoria_final = obtener_memoria_uso();

        double tiempo_ms = ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000.0;

        printf("%d\t\t%.3f\t\t%ld\n", n, tiempo_ms, memoria_final);

        free(arr);
    }

    return 0;
}