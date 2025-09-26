#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src/medicion.h"

/**
 * Algoritmo Recursivo de Fibonacci
 * Complejidad temporal: O(2^n)
 * Complejidad espacial: O(n)
 * 
 * Calcula el n-ésimo número de Fibonacci usando recursión
 * @param n: posición en la secuencia de Fibonacci
 * @return: n-ésimo número de Fibonacci
 */
long long fibonacci_recursivo(int n) {
    // Casos base
    if (n <= 1) {
        return n;
    }
    
    // Llamada recursiva
    return fibonacci_recursivo(n - 1) + fibonacci_recursivo(n - 2);
}

/**
 * Algoritmo Iterativo de Fibonacci (para comparación)
 * Complejidad temporal: O(n)
 * Complejidad espacial: O(1)
 * 
 * Calcula el n-ésimo número de Fibonacci usando iteración
 * @param n: posición en la secuencia de Fibonacci
 * @return: n-ésimo número de Fibonacci
 */
long long fibonacci_iterativo(int n) {
    if (n <= 1) {
        return n;
    }
    
    long long a = 0, b = 1, temp;
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

/**
 * Función para probar el algoritmo recursivo de Fibonacci
 * con diferentes valores de n (entre 1 y 20 según las instrucciones)
 */
void probar_fibonacci_recursivo() {
    printf("=== PRUEBAS DE FIBONACCI RECURSIVO ===\n");
    
    // Valores de prueba según las instrucciones (1 a 20)
    int valores[] = {1, 5, 10, 15, 20};
    int num_valores = sizeof(valores) / sizeof(valores[0]);
    
    Medicion* mediciones = (Medicion*)malloc(num_valores * sizeof(Medicion));
    
    for (int i = 0; i < num_valores; i++) {
        int n = valores[i];
        printf("\nProbando Fibonacci(%d)...\n", n);
        
        // Medir memoria antes de la ejecución
        size_t memoria_inicial = obtener_memoria_usada();
        
        // Medir tiempo de ejecución
        double tiempo_inicio = obtener_tiempo_actual();
        
        // Ejecutar fibonacci recursivo
        long long resultado = fibonacci_recursivo(n);
        
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
        printf("  Fibonacci(%d) = %lld\n", n, resultado);
    }
    
    // Guardar resultados en archivo
    guardar_resultados("fibonacci_recursivo", mediciones, num_valores);
    
    // Mostrar resumen
    printf("\n=== RESUMEN FIBONACCI RECURSIVO ===\n");
    printf("n\tTiempo(ms)\tMemoria(bytes)\tResultado\n");
    for (int i = 0; i < num_valores; i++) {
        long long resultado = fibonacci_recursivo(valores[i]);
        printf("%d\t%.6f\t%lu\t\t%lld\n", 
               mediciones[i].tamano_entrada,
               mediciones[i].tiempo_ejecucion,
               (unsigned long)mediciones[i].memoria_usada,
               resultado);
    }
    
    free(mediciones);
}

/**
 * Función para comparar Fibonacci recursivo vs iterativo
 */
void comparar_fibonacci() {
    printf("\n=== COMPARACIÓN FIBONACCI RECURSIVO VS ITERATIVO ===\n");
    
    int valores[] = {1, 5, 10, 15, 20};
    int num_valores = sizeof(valores) / sizeof(valores[0]);
    
    printf("n\tRecursivo(ms)\tIterativo(ms)\tRecursivo\tIterativo\n");
    printf("-\t-------------\t-------------\t---------\t---------\n");
    
    for (int i = 0; i < num_valores; i++) {
        int n = valores[i];
        
        // Medir tiempo recursivo
        double tiempo_inicio = obtener_tiempo_actual();
        long long resultado_rec = fibonacci_recursivo(n);
        double tiempo_fin = obtener_tiempo_actual();
        double tiempo_rec = tiempo_fin - tiempo_inicio;
        
        // Medir tiempo iterativo
        tiempo_inicio = obtener_tiempo_actual();
        long long resultado_iter = fibonacci_iterativo(n);
        tiempo_fin = obtener_tiempo_actual();
        double tiempo_iter = tiempo_fin - tiempo_inicio;
        
        printf("%d\t%.6f\t%.6f\t\t%lld\t\t%lld\n", 
               n, tiempo_rec, tiempo_iter, resultado_rec, resultado_iter);
    }
}

/**
 * Función para demostrar la secuencia de Fibonacci
 */
void demostrar_secuencia_fibonacci() {
    printf("\n=== SECUENCIA DE FIBONACCI (n=1 a 20) ===\n");
    
    printf("n\tFibonacci(n)\n");
    printf("-\t------------\n");
    
    for (int n = 1; n <= 20; n++) {
        long long resultado = fibonacci_iterativo(n);  // Usar iterativo para evitar demoras
        printf("%d\t%lld\n", n, resultado);
    }
}

/**
 * Función para mostrar la complejidad exponencial del Fibonacci recursivo
 */
void mostrar_complejidad_exponencial() {
    printf("\n=== ANÁLISIS DE COMPLEJIDAD EXPONENCIAL ===\n");
    printf("Observa cómo el tiempo crece exponencialmente:\n\n");
    
    int valores[] = {1, 5, 10, 15, 20};
    int num_valores = sizeof(valores) / sizeof(valores[0]);
    
    printf("n\tTiempo(ms)\tCrecimiento\n");
    printf("-\t----------\t----------\n");
    
    double tiempo_anterior = 0;
    for (int i = 0; i < num_valores; i++) {
        int n = valores[i];
        
        double tiempo_inicio = obtener_tiempo_actual();
        fibonacci_recursivo(n);
        double tiempo_fin = obtener_tiempo_actual();
        double tiempo_actual = tiempo_fin - tiempo_inicio;
        
        double factor_crecimiento = (tiempo_anterior > 0) ? tiempo_actual / tiempo_anterior : 1.0;
        
        printf("%d\t%.6f\t%.2fx\n", n, tiempo_actual, factor_crecimiento);
        tiempo_anterior = tiempo_actual;
    }
}

/**
 * Función principal para ejecutar las pruebas
 */
int main() {
    printf("Algoritmo: Fibonacci Recursivo\n");
    printf("Complejidad temporal: O(2^n)\n");
    printf("Complejidad espacial: O(n)\n\n");
    
    // Demostración de la secuencia
    demostrar_secuencia_fibonacci();
    
    // Pruebas con diferentes valores
    probar_fibonacci_recursivo();
    
    // Comparación recursivo vs iterativo
    comparar_fibonacci();
    
    // Análisis de complejidad exponencial
    mostrar_complejidad_exponencial();
    
    printf("\n=== NOTA IMPORTANTE ===\n");
    printf("El algoritmo recursivo de Fibonacci tiene complejidad O(2^n),\n");
    printf("lo que significa que el tiempo de ejecución crece exponencialmente.\n");
    printf("Para valores grandes de n, el algoritmo se vuelve muy lento.\n");
    printf("Se recomienda usar el algoritmo iterativo para valores grandes.\n");
    
    return 0;
}
