# Makefile para compilar y ejecutar análisis de complejidad algorítmica

CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99
PYTHON = python3

# Nombres de los archivos ejecutables
BUSQUEDA_LINEAL = busqueda_lineal
BUSQUEDA_BINARIA = busqueda_binaria
ORDENAMIENTO_BURBUJA = ordenamiento_burbuja
MERGE_SORT = merge_sort
FIBONACCI = fibonacci_recursivo
ANALISIS_COMPLETO = analisis_completo

# Archivos fuente
BUSQUEDA_LINEAL_SRC = busqueda_lineal.c
BUSQUEDA_BINARIA_SRC = busqueda_binaria.c
ORDENAMIENTO_BURBUJA_SRC = ordenamiento_burbuja.c
MERGE_SORT_SRC = merge_sort.c
FIBONACCI_SRC = fibonacci_recursivo.c
ANALISIS_COMPLETO_SRC = analisis_completo.c

# Objetivos principales
all: compile

# Compilar todos los programas
compile: $(BUSQUEDA_LINEAL) $(BUSQUEDA_BINARIA) $(ORDENAMIENTO_BURBUJA) $(MERGE_SORT) $(FIBONACCI) $(ANALISIS_COMPLETO)
	@echo "Todos los programas han sido compilados exitosamente."

# Reglas de compilación individuales
$(BUSQUEDA_LINEAL): $(BUSQUEDA_LINEAL_SRC)
	$(CC) $(CFLAGS) -o $(BUSQUEDA_LINEAL) $(BUSQUEDA_LINEAL_SRC)

$(BUSQUEDA_BINARIA): $(BUSQUEDA_BINARIA_SRC)
	$(CC) $(CFLAGS) -o $(BUSQUEDA_BINARIA) $(BUSQUEDA_BINARIA_SRC)

$(ORDENAMIENTO_BURBUJA): $(ORDENAMIENTO_BURBUJA_SRC)
	$(CC) $(CFLAGS) -o $(ORDENAMIENTO_BURBUJA) $(ORDENAMIENTO_BURBUJA_SRC)

$(MERGE_SORT): $(MERGE_SORT_SRC)
	$(CC) $(CFLAGS) -o $(MERGE_SORT) $(MERGE_SORT_SRC)

$(FIBONACCI): $(FIBONACCI_SRC)
	$(CC) $(CFLAGS) -o $(FIBONACCI) $(FIBONACCI_SRC)

$(ANALISIS_COMPLETO): $(ANALISIS_COMPLETO_SRC)
	$(CC) $(CFLAGS) -o $(ANALISIS_COMPLETO) $(ANALISIS_COMPLETO_SRC)

# Ejecutar programas individuales
run-busqueda-lineal: $(BUSQUEDA_LINEAL)
	@echo "Ejecutando análisis de búsqueda lineal..."
	./$(BUSQUEDA_LINEAL)

run-busqueda-binaria: $(BUSQUEDA_BINARIA)
	@echo "Ejecutando análisis de búsqueda binaria..."
	./$(BUSQUEDA_BINARIA)

run-burbuja: $(ORDENAMIENTO_BURBUJA)
	@echo "Ejecutando análisis de ordenamiento burbuja..."
	./$(ORDENAMIENTO_BURBUJA)

run-merge: $(MERGE_SORT)
	@echo "Ejecutando análisis de merge sort..."
	./$(MERGE_SORT)

run-fibonacci: $(FIBONACCI)
	@echo "Ejecutando análisis de fibonacci recursivo..."
	./$(FIBONACCI)

# Ejecutar análisis completo
run-all: $(ANALISIS_COMPLETO)
	@echo "Ejecutando análisis completo de todos los algoritmos..."
	./$(ANALISIS_COMPLETO)

# Generar gráficas (requiere Python y matplotlib)
graficas: run-all
	@echo "Generando gráficas con Python..."
	@echo "Nota: Requiere Python3 con matplotlib, pandas y seaborn"
	$(PYTHON) generar_graficas.py

# Instalar dependencias de Python (Ubuntu/Debian)
install-python-deps:
	@echo "Instalando dependencias de Python..."
	pip3 install matplotlib pandas seaborn numpy

# Ejecutar análisis completo con gráficas
analysis: compile run-all graficas
	@echo "Análisis completo finalizado. Revisa las imágenes generadas."

# Limpiar archivos compilados
clean:
	@echo "Limpiando archivos ejecutables..."
	rm -f $(BUSQUEDA_LINEAL) $(BUSQUEDA_BINARIA) $(ORDENAMIENTO_BURBUJA) $(MERGE_SORT) $(FIBONACCI) $(ANALISIS_COMPLETO)

# Limpiar archivos de datos y gráficas
clean-data:
	@echo "Limpiando archivos de datos y gráficas..."
	rm -f *.txt *.png

# Limpiar todo
clean-all: clean clean-data
	@echo "Limpieza completa realizada."

# Mostrar ayuda
help:
	@echo "Makefile para Análisis de Complejidad Algorítmica"
	@echo "=================================================="
	@echo "Objetivos disponibles:"
	@echo ""
	@echo "  compile              - Compila todos los programas"
	@echo "  run-all              - Ejecuta el análisis completo"
	@echo "  analysis             - Ejecuta análisis completo + genera gráficas"
	@echo "  graficas             - Genera gráficas (requiere Python)"
	@echo "  install-python-deps  - Instala dependencias de Python"
	@echo ""
	@echo "Programas individuales:"
	@echo "  run-busqueda-lineal  - Ejecuta solo búsqueda lineal"
	@echo "  run-busqueda-binaria - Ejecuta solo búsqueda binaria"
	@echo "  run-burbuja          - Ejecuta solo ordenamiento burbuja"
	@echo "  run-merge            - Ejecuta solo merge sort"
	@echo "  run-fibonacci        - Ejecuta solo fibonacci recursivo"
	@echo ""
	@echo "Limpieza:"
	@echo "  clean                - Elimina archivos ejecutables"
	@echo "  clean-data           - Elimina datos y gráficas"
	@echo "  clean-all            - Limpieza completa"
	@echo ""
	@echo "  help                 - Muestra esta ayuda"

# Hacer que algunos targets no sean archivos
.PHONY: all compile run-all analysis graficas clean clean-data clean-all help install-python-deps run-busqueda-lineal run-busqueda-binaria run-burbuja run-merge run-fibonacci