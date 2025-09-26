import random
import time
import tracemalloc
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import warnings

# Funcion busqueda lineal
def Bbusqueda_lineal(lista, objetivo):
    """Busca el elemento 'objetivo' en la 'lista' y devuelve su indice o -1 si no lo encuentra"""
    for i in range(len(lista)):
        if lista[i] == objetivo:
            return i 
    return -1

# Funcion busqueda binaria
def busqueda_binaria(lista, valor):
    """Busca el elemento 'valor' en la 'lista' ordenada y devuelve su indice o -1 si no lo encuentra"""
    inicio = 0
    fin = len(lista) - 1

    while inicio <= fin:
        medio = (inicio + fin) // 2

        if lista[medio] == valor:
            return medio
        elif valor < lista[medio]:
            fin = medio - 1
        else:
            fin = medio + 1
    return -1

# Funcion Ordenamiento Burbuja
def ordenamiento_burbuja(lista):
    """Ordena la 'lista' usando el algoritmo de burbuja y devuelve la lista ordenada"""
    n = len(lista)
    for i in range(n - 1):
        for j in range(0, n -i -1):
            if lista [j] > lista[j + 1]:
                lista[j], lista[j + 1] = lista[j + 1], lista[j]
                #print(lista) si se quiere ver el proceso de ordenamiento
    return lista

# Funcion Merge Sort
def merge_sort(lista):
    """Divide la lista en mitades, se ordena a sí mismo en cada mitad y luego fusiona las mitades ordenadas.
    Devuelve la lista ordenada"""
    if len(lista) > 1:
        mid = len(lista) // 2
        izquierda = lista[:mid]
        derecha = lista[mid:]

        merge_sort(izquierda)
        merge_sort(derecha)

        i = j = k = 0

        while i < len(izquierda) and j < len(derecha):
            if izquierda[i] < derecha[j]:
                lista[k] = izquierda[i]
                i += 1
            else:
                lista[k] = derecha[j]
                j += 1

        while i < len(izquierda):
            lista[k] = izquierda[i]
            i += 1
            k += 1
        
        while j < len(derecha):
            lista[k] = derecha[j]
            j += 1
            k += 1
    return lista

# Funcion recursivo Fibonacci
def fibonacci(n):
    """Devuelve el n-esimo numero de Fibonacci usando recursividad"""
    if n <= 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fibonacci(n - 1) + fibonacci(n - 2)  
    
# -> Preparacion de datos de prueba <-

# Definir los tamaños de los arreglos
tamaños = [10**3, 10**4, 10**5]

# Generar los arreglos con números aleatorios
arreglos = {} 
for n in tamaños: 
    # Crea una lista de 'n' números enteros aleatorios entre 1 y 1,000,000
    arreglos[n] = [random.randint(1, 1000000) for _ in range(n)]

# Acceso a los arreglos generados
arreglo_1000 = arreglos[1000]
arreglo_10000 = arreglos[10000]
arreglo_100000 = arreglos[100000]

# Generar los números de prueba para Fibonacci
valores_fibonacci = list(range(1, 21)) # Esto crea una lista [1, 2, 3, ..., 20]

# medicion de tiempo y memoria, para cada funcion (busqueda lineal, busqueda binaria, ordenamiento burbuja, merge sort, fibonacci)
def medir_rendimiento(funcion, *args, **kwargs):
    """
    Mide el tiempo de ejecución y el uso pico de memoria de una función.
    
    Devuelve un diccionario con el resultado de la función, el tiempo y la memoria.
    Args:
        funcion: La función a medir.
        *args: Argumentos posicionales para la función.
        **kwargs: Argumentos nombrados para la función.
    """
    tracemalloc.start() 
    
    tiempo_inicio = time.perf_counter() 
    
    # Ejecuta la función con sus argumentos
    resultado_funcion = funcion(*args, **kwargs) 
    
    tiempo_fin = time.perf_counter() 
    
    # 1. Obtenemos la memoria PICO ANTES de detener el rastreo
    memoria_pico_bytes = tracemalloc.get_traced_memory()[1]
    
    tracemalloc.stop()
    
    # 2. Calculamos los resultados finales
    tiempo_ejecucion_segundos = tiempo_fin - tiempo_inicio
    memoria_pico_kb = memoria_pico_bytes / 1024
    
    # 3. Devolvemos un diccionario para mayor claridad
    return {
        "resultado": resultado_funcion,
        "tiempo_s": tiempo_ejecucion_segundos,
        "memoria_pico_kb": memoria_pico_kb
    }

# -> Ejecucion de pruebas y recopilacion de resultados <-
if __name__ == "__main__":
    resultados = [] 
    
    # -> Pruebas para Búsqueda y Ordenamiento <- 
    algoritmos = { 
        "Búsqueda Lineal": Bbusqueda_lineal,
        "Búsqueda Binaria": busqueda_binaria,
        "Ordenamiento Burbuja": ordenamiento_burbuja,
        "Merge Sort": merge_sort 
    } 

    for nombre, funcion in algoritmos.items():
        for n in tamaños:
            print(f"Ejecutando {nombre} con n={n}...")
            
            # Usamos una copia para no modificar los arreglos originales
            arreglo_prueba = arreglos[n][:]
            
            # Argumentos específicos para cada función
            if "Búsqueda" in nombre:
                # Para la búsqueda binaria, el arreglo debe estar ordenado
                if nombre == "Búsqueda Binaria":
                    arreglo_prueba.sort()
                # Peor caso: buscar un elemento que no existe
                args = (arreglo_prueba, -1)
            else: # Algoritmos de ordenamiento
                args = (arreglo_prueba,)

            # Medir rendimiento
            medicion = medir_rendimiento(funcion, *args)
            
            # Guardar resultados
            resultados.append({
                "Algoritmo": nombre,
                "Tamaño (n)": n, 
                "Tiempo (s)": medicion["tiempo_s"], 
                "Memoria (KB)": medicion["memoria_pico_kb"]
            })

    # -> Pruebas para Fibonacci (recursivo) <-
    print("Ejecutando Fibonacci...")
    for n in valores_fibonacci:
        medicion = medir_rendimiento(fibonacci, n)
        resultados.append({ 
            "Algoritmo": "Fibonacci",
            "Tamaño (n)": n,
            "Tiempo (s)": medicion["tiempo_s"],
            "Memoria (KB)": medicion["memoria_pico_kb"]
        })

    # Convertir la lista de resultados en un DataFrame de pandas
    df_resultados = pd.DataFrame(resultados)
    
    # Separar los datos para facilitar el graficado
    df_busq_ord = df_resultados[df_resultados["Algoritmo"] != "Fibonacci"]
    df_fibonacci = df_resultados[df_resultados["Algoritmo"] == "Fibonacci"]

    # -> Generar Tabla Comparativa <-
    print("\n--- TABLA COMPARATIVA DE RESULTADOS ---")
    print(df_resultados.set_index(["Algoritmo", "Tamaño (n)"]))

    # -> Creación de todas las gráficas <-

    # Gráfica Tiempos de Búsqueda y Ordenamiento
    fig1, ax1 = plt.subplots(figsize=(10, 6))
    sns.lineplot(data=df_busq_ord, x="Tamaño (n)", y="Tiempo (s)", hue="Algoritmo", marker="o", ax=ax1)
    ax1.set_title('Tiempo de Ejecución vs. Tamaño de Entrada (n)')
    ax1.set_xlabel('Tamaño del Arreglo (n)')
    ax1.set_ylabel('Tiempo de Ejecución (segundos)')
    ax1.set_xscale('log')
    ax1.legend(title='Algoritmo')
    plt.tight_layout()
    plt.savefig("grafica_tiempos.png")
    print("Gráfica de tiempos de búsqueda y ordenamiento guardada como 'grafica_tiempos.png'")

    # -> Gráfica solo para los algoritmos rápidos <-
    print("\nGenerando gráfica comparativa de algoritmos rápidos...")

    # Filtramos el DataFrame para quitar el Ordenamiento Burbuja
    df_rapidos = df_busq_ord[df_busq_ord['Algoritmo'] != 'Ordenamiento Burbuja']

    fig, ax = plt.subplots(figsize=(10, 6))
    sns.lineplot(data=df_rapidos, x="Tamaño (n)", y="Tiempo (s)", hue="Algoritmo", marker="o", ax=ax)

    ax.set_title('Tiempo de Ejecución (Algoritmos Rápidos)')
    ax.set_xlabel('Tamaño del Arreglo (n)')
    ax.set_ylabel('Tiempo de Ejecución (segundos)')

    # Ajusta el eje Y para hacer un "zoom" automático y dejar un margen
    ax.set_ylim(0, max(df_rapidos['Tiempo (s)']) * 1.2)

    plt.tight_layout()
    plt.savefig("grafica_tiempos_rapidos.png")
    print("Gráfica de tiempos de algoritmos rápidos guardada como 'grafica_tiempos_rapidos.png'")

    # Gráfica Tiempos de Fibonacci
    fig2, ax2 = plt.subplots(figsize=(10, 6))
    sns.lineplot(data=df_fibonacci, x="Tamaño (n)", y="Tiempo (s)", marker="o", color="purple", ax=ax2)
    ax2.set_title('Tiempo de Ejecución de Fibonacci Recursivo')
    ax2.set_xlabel('Número de Fibonacci (n)')
    ax2.set_ylabel('Tiempo de Ejecución (segundos)')
    plt.tight_layout()
    plt.savefig("grafica_tiempos_fibonacci.png")
    print("Gráfica de tiempos de Fibonacci guardada como 'grafica_tiempos_fibonacci.png'")  

    # Gráfica Memoria de Búsqueda y Ordenamiento
    fig3, ax3 = plt.subplots(figsize=(10, 6))
    sns.lineplot(data=df_busq_ord, x="Tamaño (n)", y="Memoria (KB)", hue="Algoritmo", marker="o", ax=ax3)
    ax3.set_title('Consumo de Memoria vs. Tamaño de Entrada (n)')
    ax3.set_xlabel('Tamaño del Arreglo (n)')
    ax3.set_ylabel('Memoria Pico (KB)')
    ax3.set_xscale('log')
    ax3.legend(title='Algoritmo')
    plt.tight_layout()
    plt.savefig("grafica_memoria.png")
    print("Gráfica de memoria de búsqueda y ordenamiento guardada como 'grafica_memoria.png'")  

    # -> Gráfica solo para los algoritmos eficientes en memoria <-
    print("\nGenerando gráfica de memoria para algoritmos eficientes...")

    # Filtramos para quitar Merge Sort, que consume mucho
    df_memoria_eficiente = df_busq_ord[df_busq_ord['Algoritmo'] != 'Merge Sort']

    fig, ax = plt.subplots(figsize=(10, 6))
    sns.lineplot(data=df_memoria_eficiente, x="Tamaño (n)", y="Memoria (KB)", hue="Algoritmo", marker="o", ax=ax)

    ax.set_title('Consumo de Memoria (Algoritmos Eficientes en Espacio)')
    ax.set_xlabel('Tamaño del Arreglo (n)')
    ax.set_ylabel('Memoria Pico (KB)')

    # Ajusta el eje Y para hacer un "zoom" automático y dejar un margen
    ax.set_ylim(0, max(df_memoria_eficiente['Memoria (KB)']) * 1.2) 

    plt.tight_layout()
    plt.savefig("grafica_memoria_eficientes.png")
    print("Gráfica de memoria de algoritmos eficientes guardada como 'grafica_memoria_eficientes.png'")

    # Gráfica Memoria de Fibonacci
    fig4, ax4 = plt.subplots(figsize=(10, 6))
    sns.lineplot(data=df_fibonacci, x="Tamaño (n)", y="Memoria (KB)", marker="o", color="green", ax=ax4)
    ax4.set_title('Consumo de Memoria de Fibonacci Recursivo')
    ax4.set_xlabel('Número de Fibonacci (n)')
    ax4.set_ylabel('Memoria Pico (KB)')
    plt.tight_layout()
    plt.savefig("grafica_memoria_fibonacci.png")
    print("Gráfica de memoria de Fibonacci guardada como 'grafica_memoria_fibonacci.png'")  

    # -> Mostrar todas las ventanas de las gráficas al final <-
    print("\nAnálisis completado. Las gráficas se han guardado como archivos .png")
    print("Mostrando ventanas de gráficas...")
    plt.show()
    warnings.filterwarnings("ignore")  # Ignorar advertencias de seaborn/matplotlib