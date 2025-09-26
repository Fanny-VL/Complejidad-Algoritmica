# Práctica: Complejidad Algorítmica

## Información General

**Materia:** Análisis y Diseño de Algoritmos  
**Escuela:** Escuela Superior de Cómputo (ESCOM)  
**Carrera:** Licenciatura en Ciencia de Datos  
**Grupo:** 3AV1  

### Integrantes del Equipo
- **Valderrama López Fanny**
- **Elena Carmina Mata González**

---

## Objetivo de la Práctica

Analizar y comparar la complejidad algorítmica de diferentes algoritmos de búsqueda, ordenamiento y recursión mediante la medición de tiempo de ejecución y consumo de memoria.

---

## Algoritmos a Implementar

### 1. Búsqueda Lineal
- **Complejidad temporal:** O(n)
- **Complejidad espacial:** O(1)
- **Descripción:** Búsqueda secuencial elemento por elemento

### 2. Búsqueda Binaria
- **Complejidad temporal:** O(log n)
- **Complejidad espacial:** O(1)
- **Descripción:** Búsqueda en arreglo ordenado dividiendo por la mitad

### 3. Ordenamiento por Burbuja (Bubble Sort)
- **Complejidad temporal:** O(n²)
- **Complejidad espacial:** O(1)
- **Descripción:** Compara elementos adyacentes e intercambia si están en orden incorrecto

### 4. Merge Sort
- **Complejidad temporal:** O(n log n)
- **Complejidad espacial:** O(n)
- **Descripción:** Divide el arreglo en mitades, ordena recursivamente y combina

### 5. Algoritmo Recursivo de Fibonacci
- **Complejidad temporal:** O(2^n)
- **Complejidad espacial:** O(n)
- **Descripción:** Calcula el n-ésimo número de Fibonacci usando recursión

---

## Metodología de Análisis

### Tamaños de Prueba
- **Arreglos:** n = 10³, 10⁴, 10⁵ elementos
- **Fibonacci:** Valores de n entre 1 y 20

### Métricas a Medir
1. **Tiempo de Ejecución**
   - Medición en milisegundos/microsegundos
   - Múltiples ejecuciones para obtener promedio
   - Análisis de comportamiento asintótico

2. **Consumo de Memoria**
   - Memoria utilizada durante la ejecución
   - Análisis de complejidad espacial
   - Comparación entre algoritmos

### Herramientas de Análisis
- **Gráficas de Tiempo vs Tamaño de Entrada**
- **Gráficas de Memoria vs Tamaño de Entrada**
- **Tablas Comparativas**
- **Análisis de Comportamiento Asintótico**

---

## Estructura del Proyecto

```
Complejidad-Algoritmica/
├── README.md
├── src/
│   ├── busqueda_lineal/
│   ├── busqueda_binaria/
│   ├── bubble_sort/
│   ├── merge_sort/
│   └── fibonacci/
├── resultados/
│   ├── graficas_tiempo/
│   ├── graficas_memoria/
│   └── tablas_comparativas/
└── docs/
    └── analisis_complejidad.md
```

---

## Lenguajes de Programación

Se implementarán los algoritmos en los siguientes lenguajes:
- **Python**
- **Java**
- **C++**

---

## Criterios de Evaluación

### Implementación (40%)
- Correctitud de los algoritmos
- Manejo de casos edge
- Documentación del código

### Análisis Experimental (40%)
- Precisión en las mediciones
- Calidad de las gráficas
- Interpretación de resultados

### Reporte (20%)
- Análisis de complejidad teórica vs experimental
- Conclusiones y observaciones
- Comparación entre lenguajes

---

## Instrucciones de Ejecución

### Requisitos
- Python 3.8+
- Java 11+
- Compilador C++ (g++, clang++)
- Herramientas de medición de memoria

### Pasos para Ejecutar
1. Clonar/descargar el repositorio
2. Navegar al directorio del algoritmo deseado
3. Compilar/ejecutar según el lenguaje
4. Revisar resultados en la carpeta `resultados/`

---

## Resultados Esperados

### Análisis de Tiempo
- **Búsqueda Lineal:** Crecimiento lineal O(n)
- **Búsqueda Binaria:** Crecimiento logarítmico O(log n)
- **Bubble Sort:** Crecimiento cuadrático O(n²)
- **Merge Sort:** Crecimiento n log n O(n log n)
- **Fibonacci:** Crecimiento exponencial O(2^n)

### Análisis de Memoria
- **Algoritmos in-place:** Memoria constante
- **Algoritmos con arrays auxiliares:** Memoria proporcional al tamaño
- **Algoritmos recursivos:** Memoria proporcional a la profundidad de recursión

---

## Conclusiones Esperadas

1. **Correlación Teórica vs Experimental:** Verificar que los resultados experimentales coincidan con el análisis teórico de complejidad.

2. **Diferencias entre Lenguajes:** Observar variaciones en rendimiento entre Python, Java y C++.

3. **Comportamiento de Memoria:** Analizar si el consumo de memoria sigue patrones similares al tiempo de ejecución.

4. **Escalabilidad:** Identificar qué algoritmos son más eficientes para diferentes tamaños de entrada.

---

## Fecha de Entrega
**Por definir según calendario académico**

---

## Notas Adicionales

- Todos los algoritmos deben incluir comentarios explicativos
- Las mediciones deben ser precisas y repetibles
- Las gráficas deben ser claras y profesionales
- El análisis debe incluir observaciones sobre el comportamiento de cada algoritmo

---

*Este proyecto forma parte de la materia Análisis y Diseño de Algoritmos de la carrera de Licenciatura en Ciencia de Datos en ESCOM.*
