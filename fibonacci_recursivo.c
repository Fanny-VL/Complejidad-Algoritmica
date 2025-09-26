#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <unistd.h>

long long fibonacci_recursivo(int n) {
    if (n <= 1)
        return n;
    return fibonacci_recursivo(n - 1) + fibonacci_recursivo(n - 2);
}

long obtener_memoria_uso() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss; // En KB en Linux, bytes en macOS
}

int main() {
    printf("Análisis de Complejidad - Fibonacci Recursivo\n");
    printf("N\t\tResultado\t\tTiempo (ms)\t\tMemoria (KB)\n");
    printf("--\t\t---------\t\t-----------\t\t------------\n");

    for (int n = 1; n <= 20; n++) {
        long memoria_inicial = obtener_memoria_uso();

        clock_t inicio = clock();

        long long resultado = fibonacci_recursivo(n);

        clock_t fin = clock();

        long memoria_final = obtener_memoria_uso();

        double tiempo_ms = ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000.0;

        printf("%d\t\t%lld\t\t\t%.3f\t\t\t%ld\n", n, resultado, tiempo_ms, memoria_final);

        // Para valores grandes, agregar un pequeño delay para ver el crecimiento
        if (n > 30) {
            printf("Calculando...\n");
        }
    }

    printf("\nNota: El tiempo crece exponencialmente. Para n>40 puede tomar varios minutos.\n");

    return 0;
}