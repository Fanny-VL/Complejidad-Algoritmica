#include "medicion.h"

// Función para obtener tiempo actual en milisegundos
double obtener_tiempo_actual() {
#ifdef _WIN32
    // Para Windows
    FILETIME ft;
    ULARGE_INTEGER uli;
    GetSystemTimeAsFileTime(&ft);
    uli.LowPart = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;
    return (double)(uli.QuadPart / 10000.0); // Convertir a milisegundos
#else
    // Para Linux/macOS
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
#endif
}

// Función para obtener memoria usada por el proceso
size_t obtener_memoria_usada() {
#ifdef _WIN32
    // Para Windows
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize;
    }
    return 0;
#else
    // Para Linux/macOS - implementación básica
    FILE* file = fopen("/proc/self/status", "r");
    if (file == NULL) return 0;
    
    char line[256];
    size_t memory = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "VmRSS:", 6) == 0) {
            sscanf(line, "VmRSS: %zu kB", &memory);
            memory *= 1024; // Convertir de kB a bytes
            break;
        }
    }
    fclose(file);
    return memory;
#endif
}

// Función para generar arreglo aleatorio
int* generar_arreglo_aleatorio(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Error: No se pudo asignar memoria para el arreglo\n");
        return NULL;
    }
    
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;  // Números aleatorios entre 0 y 999
    }
    
    return arr;
}

// Función para generar arreglo ordenado
int* generar_arreglo_ordenado(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Error: No se pudo asignar memoria para el arreglo\n");
        return NULL;
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;  // Arreglo ordenado: 1, 2, 3, ..., n
    }
    
    return arr;
}

// Función para imprimir arreglo (para debugging)
void imprimir_arreglo(int* arr, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

// Función para verificar si un arreglo está ordenado
int esta_ordenado(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i-1]) {
            return 0;  // No está ordenado
        }
    }
    return 1;  // Está ordenado
}

// Función para liberar memoria de arreglo
void liberar_arreglo(int* arr) {
    if (arr != NULL) {
        free(arr);
    }
}

// Función para guardar resultados en archivo
void guardar_resultados(const char* nombre_algoritmo, Medicion* mediciones, int num_mediciones) {
    char nombre_archivo[100];
    sprintf(nombre_archivo, "resultados/%s_resultados.txt", nombre_algoritmo);
    
    FILE* archivo = fopen(nombre_archivo, "w");
    if (archivo == NULL) {
        printf("Error: No se pudo crear el archivo de resultados\n");
        return;
    }
    
    fprintf(archivo, "Resultados para %s\n", nombre_algoritmo);
    fprintf(archivo, "=====================================\n");
    fprintf(archivo, "Tamaño\tTiempo(ms)\tMemoria(bytes)\n");
    
    for (int i = 0; i < num_mediciones; i++) {
        fprintf(archivo, "%d\t%.6f\t%lu\n", 
                mediciones[i].tamano_entrada,
                mediciones[i].tiempo_ejecucion,
                (unsigned long)mediciones[i].memoria_usada);
    }
    
    fclose(archivo);
    printf("Resultados guardados en: %s\n", nombre_archivo);
}
