# Makefile para Práctica de Complejidad Algorítmica
# Compilador
CC = gcc

# Flags de compilación
CFLAGS = -Wall -Wextra -std=c99 -O2

# Librerías para Windows
ifeq ($(OS),Windows_NT)
    LIBS = -lpsapi
else
    LIBS = 
endif

# Directorios
SRC_DIR = src
RESULTADOS_DIR = resultados

# Archivos fuente
MEDICION_SRC = $(SRC_DIR)/medicion.c
MEDICION_H = $(SRC_DIR)/medicion.h

# Ejecutables
EJECUTABLES = busqueda_lineal busqueda_binaria bubble_sort merge_sort fibonacci main

# Regla por defecto
all: $(EJECUTABLES)

# Crear directorio de resultados
$(RESULTADOS_DIR):
	mkdir -p $(RESULTADOS_DIR)

# Búsqueda Lineal
busqueda_lineal: busqueda_lineal/busqueda_lineal.c $(MEDICION_SRC) $(MEDICION_H) | $(RESULTADOS_DIR)
	$(CC) $(CFLAGS) -o busqueda_lineal busqueda_lineal/busqueda_lineal.c $(MEDICION_SRC) $(LIBS)

# Búsqueda Binaria
busqueda_binaria: busqueda_binaria/busqueda_binaria.c $(MEDICION_SRC) $(MEDICION_H) | $(RESULTADOS_DIR)
	$(CC) $(CFLAGS) -o busqueda_binaria busqueda_binaria/busqueda_binaria.c $(MEDICION_SRC) $(LIBS)

# Bubble Sort
bubble_sort: bubble_sort/bubble_sort.c $(MEDICION_SRC) $(MEDICION_H) | $(RESULTADOS_DIR)
	$(CC) $(CFLAGS) -o bubble_sort bubble_sort/bubble_sort.c $(MEDICION_SRC) $(LIBS)

# Merge Sort
merge_sort: merge_sort/merge_sort.c $(MEDICION_SRC) $(MEDICION_H) | $(RESULTADOS_DIR)
	$(CC) $(CFLAGS) -o merge_sort merge_sort/merge_sort.c $(MEDICION_SRC) $(LIBS)

# Fibonacci
fibonacci: fibonacci/fibonacci.c $(MEDICION_SRC) $(MEDICION_H) | $(RESULTADOS_DIR)
	$(CC) $(CFLAGS) -o fibonacci fibonacci/fibonacci.c $(MEDICION_SRC) $(LIBS)

# Programa principal
main: main.c $(MEDICION_SRC) $(MEDICION_H) | $(RESULTADOS_DIR)
	$(CC) $(CFLAGS) -o main main.c $(MEDICION_SRC) $(LIBS)

# Ejecutar todas las pruebas
run-all: main
	./main

# Ejecutar pruebas individuales
run-busqueda-lineal: busqueda_lineal
	./busqueda_lineal

run-busqueda-binaria: busqueda_binaria
	./busqueda_binaria

run-bubble-sort: bubble_sort
	./bubble_sort

run-merge-sort: merge_sort
	./merge_sort

run-fibonacci: fibonacci
	./fibonacci

# Limpiar archivos compilados
clean:
	rm -f $(EJECUTABLES)
	rm -f *.exe
	rm -rf $(RESULTADOS_DIR)

# Limpiar solo resultados
clean-results:
	rm -rf $(RESULTADOS_DIR)

# Mostrar ayuda
help:
	@echo "Makefile para Práctica de Complejidad Algorítmica"
	@echo ""
	@echo "Comandos disponibles:"
	@echo "  all              - Compilar todos los programas"
	@echo "  main             - Compilar solo el programa principal"
	@echo "  busqueda_lineal  - Compilar solo búsqueda lineal"
	@echo "  busqueda_binaria - Compilar solo búsqueda binaria"
	@echo "  bubble_sort      - Compilar solo bubble sort"
	@echo "  merge_sort       - Compilar solo merge sort"
	@echo "  fibonacci        - Compilar solo fibonacci"
	@echo ""
	@echo "  run-all          - Ejecutar todas las pruebas"
	@echo "  run-busqueda-lineal  - Ejecutar solo búsqueda lineal"
	@echo "  run-busqueda-binaria - Ejecutar solo búsqueda binaria"
	@echo "  run-bubble-sort      - Ejecutar solo bubble sort"
	@echo "  run-merge-sort       - Ejecutar solo merge sort"
	@echo "  run-fibonacci        - Ejecutar solo fibonacci"
	@echo ""
	@echo "  clean            - Limpiar archivos compilados"
	@echo "  clean-results    - Limpiar solo archivos de resultados"
	@echo "  help             - Mostrar esta ayuda"

# Marcar como phony
.PHONY: all clean clean-results help run-all run-busqueda-lineal run-busqueda-binaria run-bubble-sort run-merge-sort run-fibonacci
