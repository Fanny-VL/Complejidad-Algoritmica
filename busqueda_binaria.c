#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <unistd.h>

int busqueda_binaria(int arr[], int izquierda, int derecha, int objetivo) {
    if (derecha >= izquierda) {
        int medio = izquierda + (derecha - izquierda) / 2;

        if (arr[medio] == objetivo)
            return medio;

        if (arr[medio] > objetivo)
            return busqueda_binaria(arr, izquierda, medio - 1, objetivo);

        return busqueda_binaria(arr, medio + 1, derecha, objetivo);
    }

    return -1;
}

long obtener_memoria_uso() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss; // En KB en Linux, bytes en macOS
}

void llenar_arreglo_ordenado(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
}

int main() {
    int tamanios[] = {1000, 10000, 100000};
    int num_tamanios = sizeof(tamanios) / sizeof(tamanios[0]);

    printf("Análisis de Complejidad - Búsqueda Binaria\n");
    printf("Tamaño\t\tTiempo (ms)\tMemoria (KB)\n");
    printf("------\t\t-----------\t------------\n");

    for (int i = 0; i < num_tamanios; i++) {
        int n = tamanios[i];
        int *arr = (int*)malloc(n * sizeof(int));

        if (arr == NULL) {
            printf("Error: No se pudo asignar memoria para n=%d\n", n);
            continue;
        }

        llenar_arreglo_ordenado(arr, n);

        long memoria_inicial = obtener_memoria_uso();

        clock_t inicio = clock();

        // Buscar el último elemento (caso donde más comparaciones se hacen)
        int resultado = busqueda_binaria(arr, 0, n - 1, n);

        clock_t fin = clock();

        long memoria_final = obtener_memoria_uso();

        double tiempo_ms = ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000.0;

        printf("%d\t\t%.3f\t\t%ld\n", n, tiempo_ms, memoria_final);

        free(arr);
    }

    return 0;
}