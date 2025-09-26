#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import seaborn as sns

# Configurar estilo de las gráficas
plt.style.use('seaborn-v0_8')
sns.set_palette("husl")

def leer_datos_archivo(nombre_archivo):
    """Lee los datos de un archivo CSV"""
    try:
        return pd.read_csv(nombre_archivo)
    except FileNotFoundError:
        print(f"Archivo {nombre_archivo} no encontrado")
        return None

def crear_grafica_comparativa_tiempo():
    """Crea gráfica comparativa de tiempo para todos los algoritmos"""

    # Leer datos de cada algoritmo
    busqueda_lineal = leer_datos_archivo('resultados_busqueda_lineal.txt')
    busqueda_binaria = leer_datos_archivo('resultados_busqueda_binaria.txt')
    burbuja = leer_datos_archivo('resultados_burbuja.txt')
    merge_sort = leer_datos_archivo('resultados_merge_sort.txt')

    plt.figure(figsize=(12, 8))

    if busqueda_lineal is not None:
        plt.plot(busqueda_lineal['Tamano'], busqueda_lineal['Tiempo_ms'],
                'o-', linewidth=2, markersize=8, label='Búsqueda Lineal O(n)')

    if busqueda_binaria is not None:
        plt.plot(busqueda_binaria['Tamano'], busqueda_binaria['Tiempo_ms'],
                's-', linewidth=2, markersize=8, label='Búsqueda Binaria O(log n)')

    if burbuja is not None:
        plt.plot(burbuja['Tamano'], burbuja['Tiempo_ms'],
                '^-', linewidth=2, markersize=8, label='Ordenamiento Burbuja O(n²)')

    if merge_sort is not None:
        plt.plot(merge_sort['Tamano'], merge_sort['Tiempo_ms'],
                'd-', linewidth=2, markersize=8, label='Merge Sort O(n log n)')

    plt.xlabel('Tamaño del Arreglo (n)', fontsize=12)
    plt.ylabel('Tiempo de Ejecución (ms)', fontsize=12)
    plt.title('Comparación de Complejidad Temporal - Algoritmos de Búsqueda y Ordenamiento', fontsize=14, fontweight='bold')
    plt.legend(fontsize=11)
    plt.grid(True, alpha=0.3)
    plt.yscale('log')  # Escala logarítmica para mejor visualización
    plt.xscale('log')

    # Agregar anotaciones de complejidad
    plt.annotate('O(n)', xy=(50000, 0.1), fontsize=10, ha='center')
    plt.annotate('O(log n)', xy=(50000, 0.01), fontsize=10, ha='center')
    plt.annotate('O(n²)', xy=(10000, 100), fontsize=10, ha='center')
    plt.annotate('O(n log n)', xy=(50000, 10), fontsize=10, ha='center')

    plt.tight_layout()
    plt.savefig('comparacion_tiempo_algoritmos.png', dpi=300, bbox_inches='tight')
    plt.show()

def crear_grafica_memoria():
    """Crea gráfica comparativa de uso de memoria"""

    # Leer datos de cada algoritmo
    busqueda_lineal = leer_datos_archivo('resultados_busqueda_lineal.txt')
    busqueda_binaria = leer_datos_archivo('resultados_busqueda_binaria.txt')
    burbuja = leer_datos_archivo('resultados_burbuja.txt')
    merge_sort = leer_datos_archivo('resultados_merge_sort.txt')

    plt.figure(figsize=(12, 8))

    if busqueda_lineal is not None:
        plt.plot(busqueda_lineal['Tamano'], busqueda_lineal['Memoria_KB'],
                'o-', linewidth=2, markersize=8, label='Búsqueda Lineal')

    if busqueda_binaria is not None:
        plt.plot(busqueda_binaria['Tamano'], busqueda_binaria['Memoria_KB'],
                's-', linewidth=2, markersize=8, label='Búsqueda Binaria')

    if burbuja is not None:
        plt.plot(burbuja['Tamano'], burbuja['Memoria_KB'],
                '^-', linewidth=2, markersize=8, label='Ordenamiento Burbuja')

    if merge_sort is not None:
        plt.plot(merge_sort['Tamano'], merge_sort['Memoria_KB'],
                'd-', linewidth=2, markersize=8, label='Merge Sort')

    plt.xlabel('Tamaño del Arreglo (n)', fontsize=12)
    plt.ylabel('Uso de Memoria (KB)', fontsize=12)
    plt.title('Comparación de Uso de Memoria - Algoritmos de Búsqueda y Ordenamiento', fontsize=14, fontweight='bold')
    plt.legend(fontsize=11)
    plt.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig('comparacion_memoria_algoritmos.png', dpi=300, bbox_inches='tight')
    plt.show()

def crear_grafica_fibonacci():
    """Crea gráfica específica para Fibonacci recursivo"""

    fibonacci = leer_datos_archivo('resultados_fibonacci.txt')

    if fibonacci is None:
        print("No se encontraron datos de Fibonacci")
        return

    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 10))

    # Gráfica de tiempo
    ax1.plot(fibonacci['N'], fibonacci['Tiempo_ms'], 'ro-', linewidth=2, markersize=8)
    ax1.set_xlabel('Valor de n', fontsize=12)
    ax1.set_ylabel('Tiempo de Ejecución (ms)', fontsize=12)
    ax1.set_title('Fibonacci Recursivo - Tiempo de Ejecución O(2ⁿ)', fontsize=14, fontweight='bold')
    ax1.set_yscale('log')  # Escala logarítmica
    ax1.grid(True, alpha=0.3)
    ax1.annotate('Crecimiento Exponencial O(2ⁿ)',
                xy=(15, 10), fontsize=10, ha='center',
                bbox=dict(boxstyle="round,pad=0.3", facecolor="yellow", alpha=0.7))

    # Gráfica de memoria
    ax2.plot(fibonacci['N'], fibonacci['Memoria_KB'], 'bo-', linewidth=2, markersize=8)
    ax2.set_xlabel('Valor de n', fontsize=12)
    ax2.set_ylabel('Uso de Memoria (KB)', fontsize=12)
    ax2.set_title('Fibonacci Recursivo - Uso de Memoria', fontsize=14, fontweight='bold')
    ax2.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig('fibonacci_analisis.png', dpi=300, bbox_inches='tight')
    plt.show()

def crear_tabla_comparativa():
    """Crea tabla comparativa de complejidades teóricas vs observadas"""

    # Datos teóricos de complejidad
    datos_comparativos = {
        'Algoritmo': ['Búsqueda Lineal', 'Búsqueda Binaria', 'Ordenamiento Burbuja', 'Merge Sort', 'Fibonacci Recursivo'],
        'Complejidad Temporal': ['O(n)', 'O(log n)', 'O(n²)', 'O(n log n)', 'O(2ⁿ)'],
        'Complejidad Espacial': ['O(1)', 'O(log n)', 'O(1)', 'O(n)', 'O(n)'],
        'Mejor Caso': ['O(1)', 'O(1)', 'O(n)', 'O(n log n)', 'O(2ⁿ)'],
        'Peor Caso': ['O(n)', 'O(log n)', 'O(n²)', 'O(n log n)', 'O(2ⁿ)'],
        'Caso Promedio': ['O(n)', 'O(log n)', 'O(n²)', 'O(n log n)', 'O(2ⁿ)']
    }

    df = pd.DataFrame(datos_comparativos)

    # Crear gráfica de tabla
    fig, ax = plt.subplots(figsize=(14, 6))
    ax.axis('tight')
    ax.axis('off')

    tabla = ax.table(cellText=df.values,
                     colLabels=df.columns,
                     cellLoc='center',
                     loc='center',
                     colWidths=[0.2, 0.15, 0.15, 0.15, 0.15, 0.15])

    tabla.auto_set_font_size(False)
    tabla.set_fontsize(10)
    tabla.scale(1, 2)

    # Colorear encabezados
    for i in range(len(df.columns)):
        tabla[(0, i)].set_facecolor('#4CAF50')
        tabla[(0, i)].set_text_props(weight='bold', color='white')

    plt.title('Tabla Comparativa de Complejidades Algorítmicas',
              fontsize=16, fontweight='bold', pad=20)

    plt.savefig('tabla_comparativa_complejidades.png', dpi=300, bbox_inches='tight')
    plt.show()

def generar_informe_completo():
    """Genera un informe completo con todas las gráficas"""

    print("Generando análisis gráfico completo...")
    print("=" * 50)

    print("1. Creando gráfica comparativa de tiempo...")
    crear_grafica_comparativa_tiempo()

    print("2. Creando gráfica de uso de memoria...")
    crear_grafica_memoria()

    print("3. Creando análisis de Fibonacci...")
    crear_grafica_fibonacci()

    print("4. Creando tabla comparativa...")
    crear_tabla_comparativa()

    print("=" * 50)
    print("¡Análisis gráfico completado!")
    print("Se generaron las siguientes imágenes:")
    print("- comparacion_tiempo_algoritmos.png")
    print("- comparacion_memoria_algoritmos.png")
    print("- fibonacci_analisis.png")
    print("- tabla_comparativa_complejidades.png")

if __name__ == "__main__":
    generar_informe_completo()