# Instrucciones de Compilación y Ejecución

## Requisitos del Sistema

- **Compilador C:** GCC (GNU Compiler Collection)
- **Sistema Operativo:** Windows, Linux o macOS
- **Herramientas:** Make (opcional, pero recomendado)

## Instalación de Requisitos

### Windows
1. Instalar MinGW-w64 o MSYS2
2. Asegurarse de que `gcc` esté en el PATH del sistema
3. Para Make, instalar MSYS2 o usar el comando `mingw32-make`

### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install gcc make
```

### macOS
```bash
# Instalar Xcode Command Line Tools
xcode-select --install
```

## Compilación

### Opción 1: Usando Makefile (Recomendado)

```bash
# Compilar todos los programas
make all

# O simplemente
make

# Compilar solo el programa principal
make main

# Compilar programas individuales
make busqueda_lineal
make busqueda_binaria
make bubble_sort
make merge_sort
make fibonacci
```

### Opción 2: Compilación Manual

```bash
# Compilar programa principal
gcc -Wall -Wextra -std=c99 -O2 -o main main.c src/medicion.c

# Compilar búsqueda lineal
gcc -Wall -Wextra -std=c99 -O2 -o busqueda_lineal busqueda_lineal/busqueda_lineal.c src/medicion.c

# Compilar búsqueda binaria
gcc -Wall -Wextra -std=c99 -O2 -o busqueda_binaria busqueda_binaria/busqueda_binaria.c src/medicion.c

# Compilar bubble sort
gcc -Wall -Wextra -std=c99 -O2 -o bubble_sort bubble_sort/bubble_sort.c src/medicion.c

# Compilar merge sort
gcc -Wall -Wextra -std=c99 -O2 -o merge_sort merge_sort/merge_sort.c src/medicion.c

# Compilar fibonacci
gcc -Wall -Wextra -std=c99 -O2 -o fibonacci fibonacci/fibonacci.c src/medicion.c
```

## Ejecución

### Ejecutar Todas las Pruebas

```bash
# Usando Makefile
make run-all

# O ejecutar directamente
./main
```

### Ejecutar Pruebas Individuales

```bash
# Búsqueda lineal
make run-busqueda-lineal
# o
./busqueda_lineal

# Búsqueda binaria
make run-busqueda-binaria
# o
./busqueda_binaria

# Bubble sort
make run-bubble-sort
# o
./bubble_sort

# Merge sort
make run-merge-sort
# o
./merge_sort

# Fibonacci
make run-fibonacci
# o
./fibonacci
```

## Estructura de Resultados

Los resultados se guardan automáticamente en la carpeta `resultados/`:

```
resultados/
├── busqueda_lineal_resultados.txt
├── busqueda_binaria_resultados.txt
├── bubble_sort_resultados.txt
├── merge_sort_resultados.txt
└── fibonacci_recursivo_resultados.txt
```

Cada archivo contiene:
- Tamaño de entrada
- Tiempo de ejecución en milisegundos
- Memoria usada en bytes

## Comandos Útiles

### Limpiar Archivos Compilados
```bash
make clean
```

### Limpiar Solo Resultados
```bash
make clean-results
```

### Ver Ayuda
```bash
make help
```

## Solución de Problemas

### Error de Compilación en Windows
Si encuentras errores relacionados con `gettimeofday` o `psapi.h`:

1. Asegúrate de usar MinGW-w64 o MSYS2
2. Verifica que las librerías estén instaladas correctamente

### Error de Memoria
Si el programa se queda sin memoria:
- Reduce los tamaños de prueba en el código
- Asegúrate de tener suficiente RAM disponible

### Resultados Inconsistentes
- Ejecuta el programa varias veces para obtener promedios
- Cierra otras aplicaciones que puedan interferir

## Interpretación de Resultados

### Tiempo de Ejecución
- **Búsqueda Lineal:** Debe crecer linealmente O(n)
- **Búsqueda Binaria:** Debe crecer logarítmicamente O(log n)
- **Bubble Sort:** Debe crecer cuadráticamente O(n²)
- **Merge Sort:** Debe crecer como O(n log n)
- **Fibonacci:** Debe crecer exponencialmente O(2^n)

### Memoria
- **Algoritmos in-place:** Memoria constante
- **Algoritmos con arrays auxiliares:** Memoria proporcional al tamaño
- **Algoritmos recursivos:** Memoria proporcional a la profundidad

## Notas Importantes

1. **Fibonacci Recursivo:** Para valores grandes (>20), el tiempo de ejecución puede ser muy largo debido a la complejidad exponencial.

2. **Medición de Memoria:** En Windows, la medición de memoria puede variar según el sistema.

3. **Optimización:** Los programas están compilados con `-O2` para optimización, lo que puede afectar las mediciones de tiempo.

4. **Reproducibilidad:** Para resultados consistentes, ejecuta en un sistema sin carga y cierra otras aplicaciones.
