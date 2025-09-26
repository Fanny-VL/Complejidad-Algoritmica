# Análisis de Complejidad Algorítmica

Este proyecto implementa y analiza la complejidad temporal y espacial de algoritmos fundamentales de búsqueda y ordenamiento en lenguaje C.

## 📋 Algoritmos Implementados

### 🔍 Algoritmos de Búsqueda
1. **Búsqueda Lineal** - `busqueda_lineal.c`
   - Complejidad temporal: O(n)
   - Complejidad espacial: O(1)

2. **Búsqueda Binaria** - `busqueda_binaria.c`
   - Complejidad temporal: O(log n)
   - Complejidad espacial: O(log n) - versión recursiva

### 🔄 Algoritmos de Ordenamiento
3. **Ordenamiento Burbuja** - `ordenamiento_burbuja.c`
   - Complejidad temporal: O(n²)
   - Complejidad espacial: O(1)

4. **Merge Sort** - `merge_sort.c`
   - Complejidad temporal: O(n log n)
   - Complejidad espacial: O(n)

### 🔢 Algoritmo Matemático
5. **Fibonacci Recursivo** - `fibonacci_recursivo.c`
   - Complejidad temporal: O(2ⁿ)
   - Complejidad espacial: O(n)

## 🚀 Instrucciones de Uso

### Prerequisitos
- Compilador GCC
- Python 3 (para generar gráficas)
- Make (opcional, para usar Makefile)

### Opción 1: Usando Makefile (Recomendado)

```bash
# Compilar todos los programas
make compile

# Ejecutar análisis completo
make run-all

# Instalar dependencias de Python para gráficas
make install-python-deps

# Generar gráficas
make graficas

# Análisis completo con gráficas
make analysis

# Ver todas las opciones disponibles
make help
```

### Opción 2: Compilación Manual

```bash
# Compilar programas individuales
gcc -Wall -Wextra -O2 -o busqueda_lineal busqueda_lineal.c
gcc -Wall -Wextra -O2 -o busqueda_binaria busqueda_binaria.c
gcc -Wall -Wextra -O2 -o ordenamiento_burbuja ordenamiento_burbuja.c
gcc -Wall -Wextra -O2 -o merge_sort merge_sort.c
gcc -Wall -Wextra -O2 -o fibonacci_recursivo fibonacci_recursivo.c

# Compilar programa de análisis completo
gcc -Wall -Wextra -O2 -o analisis_completo analisis_completo.c

# Ejecutar análisis completo
./analisis_completo

# Generar gráficas
python3 generar_graficas.py
```

## 📊 Tamaños de Prueba

### Para Algoritmos de Búsqueda y Ordenamiento:
- n = 1,000 elementos
- n = 10,000 elementos
- n = 100,000 elementos

### Para Fibonacci Recursivo:
- Valores de n entre 1 y 20

## 📈 Análisis de Resultados

### Mediciones Realizadas
1. **Tiempo de Ejecución**: Medido en milisegundos usando `clock()`
2. **Uso de Memoria**: Medido en KB usando `getrusage()`

### Archivos de Salida
- `resultados_busqueda_lineal.txt`
- `resultados_busqueda_binaria.txt`
- `resultados_burbuja.txt`
- `resultados_merge_sort.txt`
- `resultados_fibonacci.txt`

### Gráficas Generadas
- `comparacion_tiempo_algoritmos.png`
- `comparacion_memoria_algoritmos.png`
- `fibonacci_analisis.png`
- `tabla_comparativa_complejidades.png`

## 🔬 Análisis Teórico vs Observado

### Complejidades Temporales Esperadas
| Algoritmo | Mejor Caso | Caso Promedio | Peor Caso |
|-----------|------------|---------------|-----------|
| Búsqueda Lineal | O(1) | O(n) | O(n) |
| Búsqueda Binaria | O(1) | O(log n) | O(log n) |
| Burbuja | O(n) | O(n²) | O(n²) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) |
| Fibonacci | O(2ⁿ) | O(2ⁿ) | O(2ⁿ) |

### Observaciones Esperadas
1. **Búsqueda Lineal**: Crecimiento lineal con el tamaño del arreglo
2. **Búsqueda Binaria**: Crecimiento logarítmico, muy eficiente
3. **Burbuja**: Crecimiento cuadrático, ineficiente para arreglos grandes
4. **Merge Sort**: Crecimiento n log n, eficiente y estable
5. **Fibonacci**: Crecimiento exponencial, se vuelve impracticable rápidamente

## 📋 Casos de Prueba

### Búsquedas
- **Lineal**: Busca el último elemento (peor caso)
- **Binaria**: Busca el último elemento en arreglo ordenado

### Ordenamientos
- **Burbuja**: Arreglo en orden descendente (peor caso)
- **Merge Sort**: Arreglo aleatorio (caso promedio)

### Fibonacci
- Valores incrementales de 1 a 20 para observar crecimiento exponencial

## 🔧 Compilación y Optimización

### Flags de Compilación Utilizados
- `-Wall`: Mostrar todas las advertencias
- `-Wextra`: Advertencias adicionales
- `-O2`: Optimización nivel 2
- `-std=c99`: Estándar C99

### Consideraciones de Medición
- Se utiliza `clock()` para medir tiempo de CPU
- Se utiliza `getrusage()` para medir uso máximo de memoria
- Los arreglos se llenan de manera determinística para consistencia
- Se realizan mediciones antes y después de cada algoritmo

## 📚 Dependencias de Python

Para generar las gráficas se requieren:
```bash
pip3 install matplotlib pandas seaborn numpy
```

## 🧹 Limpieza

```bash
# Limpiar ejecutables
make clean

# Limpiar datos y gráficas
make clean-data

# Limpieza completa
make clean-all
```

## 📝 Estructura del Proyecto

```
Complejidad-Algoritmica/
├── README.md
├── Makefile
├── busqueda_lineal.c
├── busqueda_binaria.c
├── ordenamiento_burbuja.c
├── merge_sort.c
├── fibonacci_recursivo.c
├── analisis_completo.c
├── generar_graficas.py
└── [archivos generados]
    ├── resultados_*.txt
    └── *.png
```

## 🎯 Objetivos de Aprendizaje

1. Comprender las diferencias prácticas entre complejidades teóricas
2. Observar cómo el crecimiento del tamaño de entrada afecta el rendimiento
3. Comparar uso de memoria entre diferentes algoritmos
4. Identificar cuándo un algoritmo se vuelve impracticable
5. Relacionar teoría de complejidad con mediciones empíricas