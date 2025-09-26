#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "src/medicion.h"
#include "src/algoritmos.h"

// Función para ejecutar todas las pruebas
void ejecutar_todas_las_pruebas() {
    printf("========================================\n");
    printf("    PRÁCTICA: COMPLEJIDAD ALGORÍTMICA\n");
    printf("========================================\n");
    printf("Materia: Análisis y Diseño de Algoritmos\n");
    printf("Escuela: ESCOM\n");
    printf("Carrera: Licenciatura en Ciencia de Datos\n");
    printf("Grupo: 3AV1\n");
    printf("Integrantes:\n");
    printf("- Valderrama López Fanny\n");
    printf("- Elena Carmina Mata González\n");
    printf("========================================\n\n");
    
    // Crear directorio de resultados si no existe
    system("if not exist resultados mkdir resultados");
    
    printf("Iniciando pruebas de todos los algoritmos...\n\n");
    
    // 1. Búsqueda Lineal
    printf("1. BÚSQUEDA LINEAL\n");
    printf("==================\n");
    probar_busqueda_lineal();
    printf("\n");
    
    // 2. Búsqueda Binaria
    printf("2. BÚSQUEDA BINARIA\n");
    printf("===================\n");
    probar_busqueda_binaria();
    printf("\n");
    
    // 3. Bubble Sort
    printf("3. ORDENAMIENTO POR BURBUJA\n");
    printf("============================\n");
    probar_bubble_sort();
    printf("\n");
    
    // 4. Merge Sort
    printf("4. MERGE SORT\n");
    printf("=============\n");
    probar_merge_sort();
    printf("\n");
    
    // 5. Fibonacci Recursivo
    printf("5. FIBONACCI RECURSIVO\n");
    printf("======================\n");
    probar_fibonacci_recursivo();
    printf("\n");
    
    printf("========================================\n");
    printf("TODAS LAS PRUEBAS COMPLETADAS\n");
    printf("========================================\n");
    printf("Los resultados se han guardado en la carpeta 'resultados/'\n");
    printf("Revisa los archivos .txt para ver los datos detallados.\n");
}


// Función principal
int main() {
    ejecutar_todas_las_pruebas();
    return 0;
}
