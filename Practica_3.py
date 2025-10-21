import random
import time
import tracemalloc
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import warnings

warnings.simplefilter("ignore", UserWarning)

# -> Decorador <-

# creamos un decorador para trazar llamadas recursivas.
class TrazaRecursiva:
    """
    Decorador que imprime la traza de llamadas de una función recursiva.
    Muestra la entrada, salida y profundidad de cada llamada.
    """

    # Inicializa el decorador con la función a decorar.
    def __init__(self, funcion):
        self.funcion = funcion # Guardamos la función original.
        self.profundidad = 0  # Este contador es crucial para saber qué tan "adentro" estamos en la cadena de llamadas recursivas.
    
    # Método que se llama cuando se invoca la función decorada.
    def __call__(self, *args, **kwargs):
        """
        Llama a la función decorada, imprimiendo la traza de llamadas.
        Args:
            self: Instancia del decorador.
            *args: Argumentos posicionales para la función.
            **kwargs: Argumentos nombrados para la función."""
        # Paso 1: Anuncia la entrada.
        # Crear la indentación y mostrar la entrada a la función.
        indentacion = "  " * self.profundidad
        print(f"{indentacion}--> Llamando a {self.funcion.__name__}{args}")

        # Paso 2: Aumentar la profundidad antes de la llamada recursiva.
        self.profundidad += 1
        
        # Paso 3: Ejecutar la función original y guarda el resultado original
        resultado = self.funcion(*args, **kwargs)
        
        # Paso 4: Disminuir la profundidad después de la llamada.
        self.profundidad -= 1
        
        # Paso 5: Mostrar la salida y el valor de retorno.
        print(f"{indentacion}<-- Saliendo de {self.funcion.__name__}, devuelve: {resultado}")
        
        return resultado

# -> Funciones de suma <-

def suma_digitos_iterativa(numero):
    """Calcula la suma de los dígitos de un número de forma iterativa."""
    suma_total = 0
    # Nos aseguramos de trabajar con un número positivo.
    if numero < 0:
        numero = -numero
    
    while numero > 0:
        #  Obtenemos el último dígito con el módulo %.
        ultimo_digito = numero % 10
        #  Lo sumamos al total.
        suma_total += ultimo_digito
        #  Quitamos el último dígito con la división entera //.
        numero = numero // 10
        
    return suma_total

# Decoramos la función recursiva para trazar sus llamadas.
@TrazaRecursiva
def suma_digitos_recursiva(numero):
    """Calcula la suma de los dígitos de un número de forma recursiva."""
    # Nos aseguramos de trabajar con un número positivo.
    if numero < 0:
        numero = -numero

    # CASO BASE: La condición para detener la recursión.
    # Si el número tiene un solo dígito, la suma es el propio número.
    if numero < 10:
        return numero
    
    # PASO RECURSIVO: La función se llama a sí misma con un problema más pequeño.
    else:
        ultimo_digito = numero % 10
        resto_del_numero = numero // 10
        # Sumamos el último dígito + el resultado de la suma para el resto.
        return ultimo_digito + suma_digitos_recursiva(resto_del_numero)

# Versión sin decorador para pruebas de rendimiento. 
def suma_digitos_rec_perf(numero):
    if numero < 0: 
        numero = -numero
    if numero < 10: 
        return numero
    else: 
        ultimo_digito = numero % 10
        resto_del_numero = numero // 10
        return ultimo_digito + suma_digitos_rec_perf(resto_del_numero)

# -> MODO DE USO <-
"""num_usuario = int(input("Ingrese un número para sumar sus dígitos: "))
resultado_iterativo = suma_digitos_iterativa(num_usuario)
resultado_recursivo = suma_digitos_recursiva(num_usuario)
print(f"Suma iterativa de los dígitos: {resultado_iterativo}")
print(f"Suma recursiva de los dígitos: {resultado_recursivo}")
"""
# --> Funciones de invertir cadenas <--

def invertir_cadena_iterativa(cadena):
    """Invierte una cadena de texto usando slicing.
       slicing es una técnica de Python que permite acceder a partes de una secuencia (como una cadena, lista o tupla) mediante índices.
       La sintaxis básica de slicing es: secuencia[inicio:fin:paso]"""
    return cadena[::-1]

# Decoramos la función recursiva para trazar sus llamadas.
@TrazaRecursiva
def invertir_cadena_recursiva(cadena):
    """Invierte una cadena de texto usando recursividad."""
    # CASO BASE: Si la cadena está vacía, no hay nada que invertir.
    if len(cadena) == 0:
        return ""
    
    # PASO RECURSIVO:
    # Tomamos el primer carácter y lo ponemos al final.
    # Luego, llamamos a la función con el resto de la cadena.
    else:
        primer_caracter = cadena[0]
        resto_de_la_cadena = cadena[1:]
        return invertir_cadena_recursiva(resto_de_la_cadena) + primer_caracter

# Versión sin decorador para pruebas de rendimiento.   
def invertir_cadena_rec_perf(cadena):
    if len(cadena) == 0: 
        return ""
    else:
        primer_caracter = cadena[0]
        resto_de_la_cadena = cadena[1:] 
        return invertir_cadena_rec_perf(resto_de_la_cadena) + primer_caracter

# -> MODO DE USO <-
"""cadena_usuario = input("Ingrese una cadena para invertir: ")
cadena_invertida_ietartiva = invertir_cadena_iterativa(cadena_usuario)
cadena_invertida_recursivo = invertir_cadena_recursiva(cadena_usuario)
print(f"La cadena invertida iterativa es: {cadena_invertida_ietartiva}")
print(f"La cadena invertida recursiva es: {cadena_invertida_recursivo}")  
"""
# -> Funciones de busqueda binaria <-

def busqueda_binaria_iterativa(lista, valor):
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

# Función principal para iniciar la búsqueda binaria recursiva.
def busqueda_binaria_recursiva(lista, valor):
    """Función principal que inicia la búsqueda binaria recursiva."""
    # Llama a una función auxiliar con los límites iniciales de la lista (0 y el último índice).
    return _busqueda_recursiva_helper(lista, valor, 0, len(lista) - 1)

# Decoramos la función recursiva para trazar sus llamadas.
@TrazaRecursiva
def _busqueda_recursiva_helper(lista, valor, inicio, fin):
    """Función auxiliar que contiene la lógica recursiva."""
    # CASO BASE: Si el inicio supera al fin, el rango es inválido y el elemento no está.
    if inicio > fin:
        return -1

    # Calculamos el punto medio del rango actual.
    medio = (inicio + fin) // 2

    # Si encontramos el valor en el medio, devolvemos su índice. 
    if lista[medio] == valor:
        return medio
    
    # PASO RECURSIVO: Si no lo encontramos, decidimos a qué mitad llamar.
    elif valor < lista[medio]:
        # El valor está en la mitad izquierda, ajustamos el fin.
        return _busqueda_recursiva_helper(lista, valor, inicio, medio - 1)
    else:
        # El valor está en la mitad derecha, ajustamos el inicio.
        return _busqueda_recursiva_helper(lista, valor, medio + 1, fin)

# Versión sin decorador para pruebas de rendimiento.
def busqueda_binaria_rec_perf(lista, valor):
    return _busqueda_rec_helper_perf(lista, valor, 0, len(lista) - 1)

def _busqueda_rec_helper_perf(lista, valor, inicio, fin):
    if inicio > fin: 
        return -1
    medio = (inicio + fin) // 2
    if lista[medio] == valor: 
        return medio
    elif valor < lista[medio]: 
        return _busqueda_rec_helper_perf(lista, valor, inicio, medio - 1)
    else: 
        return _busqueda_rec_helper_perf(lista, valor, medio + 1, fin)

# -> Funciones de potencia <-

def potencia_iterativa(base, exponente):
    """Calcula la potencia de un número de forma iterativa."""
    # Caso especial: cualquier número elevado a 0 es 1.
    if exponente == 0:
        return 1

    # Guardamos el exponente original para saber si era negativo
    exp_original = exponente
    # Usamos el valor absoluto para que el bucle funcione con negativos
    exponente = abs(exponente)
    # Empezamos con el resultado en 1 para poder multiplicar
    resultado = 1
    # Multiplicamos la base por sí misma 'exponente' veces
    for _ in range(exponente):
        resultado *= base
    
    # Si el exponente original era negativo, devolvemos el inverso
    if exp_original < 0:
        return 1 / resultado
    else:
        return resultado

# Decoramos la función recursiva para trazar sus llamadas.
@TrazaRecursiva
def potencia_recursiva(base, exponente):
    """Calcula la potencia de un número de forma recursiva."""

    # CASO BASE: Cualquier número elevado a 0 es 1.
    if exponente < 0:
        # Si el exponente es negativo, calculamos la potencia con el exponente positivo y luego tomamos el inverso.
        return 1 / potencia_recursiva(base, -exponente)
    # Si el exponente es 0, devolvemos 1.
    elif exponente == 0:
        return 1
    # Si el exponente es 1, devolvemos la base.
    elif exponente == 1:
        return base
    # PASO RECURSIVO: Multiplicamos la base por la potencia de la base con el exponente reducido en 1.
    else:
        # Llamada recursiva con el exponente reducido en 1.
        return base * potencia_recursiva(base, exponente - 1)
    
# Versión sin decorador para pruebas de rendimiento.
def potencia_rec_perf(base, exponente):
    if exponente < 0: 
        return 1 / potencia_rec_perf(base, -exponente)
    elif exponente == 0: 
        return 1
    elif exponente == 1:
        return base
    else: 
        return base * potencia_rec_perf(base, exponente - 1)
    
# -> MODO DE USO <-
"""base_usuario = float(input("Ingrese la base: "))
exponente_usuario = int(input("Ingrese el exponente: "))    
resultado_potencia_iterativa = potencia_iterativa(base_usuario, exponente_usuario)
resultado_potencia_recursiva = potencia_recursiva(base_usuario, exponente_usuario)
print(f"Resultado de la potencia iterativa: {resultado_potencia_iterativa}")    
print(f"Resultado de la potencia recursiva: {resultado_potencia_recursiva}")
"""

# -> Preparacion de datos de prueba <-

# Definir los tamaños de los arreglos.
tamaños = [10, 10**3, 10**4, 10**5]

# Generar los arreglos con números aleatorios.
arreglos = {} 
for n in tamaños: 
    # Crea una lista de 'n' números enteros aleatorios entre 1 y 1,000,000.
    arreglos[n] = [random.randint(1, 1000000) for _ in range(n)]

# Acceso a los arreglos generados.
arreglo_10 = arreglos[10]
arreglo_1000 = arreglos[1000]
arreglo_10000 = arreglos[10000]
arreglo_100000 = arreglos[100000]

# -> Función para medir rendimiento <-
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
    
    # Ejecuta la función con sus argumentos.
    resultado_funcion = funcion(*args, **kwargs) 
    
    tiempo_fin = time.perf_counter() 
    
    # 1. Obtenemos la memoria PICO ANTES de detener el rastreo.
    memoria_pico_bytes = tracemalloc.get_traced_memory()[1]
    
    tracemalloc.stop()
    
    # 2. Calculamos los resultados finales.
    tiempo_ejecucion_segundos = tiempo_fin - tiempo_inicio
    memoria_pico_kb = memoria_pico_bytes / 1024
    
    # 3. Devolvemos un diccionario para mayor claridad.
    return {
        "resultado": resultado_funcion,
        "tiempo_s": tiempo_ejecucion_segundos,
        "memoria_pico_kb": memoria_pico_kb
    }

# -> Ejecucion de pruebas y recopilacion de resultados <-
if __name__ == "__main__":
    warnings.filterwarnings("ignore")  # Ignorar advertencias para una salida más limpia.

    # -> REPRESENTACIÓN DE LA PILA DE LLAMADAS (CON DECORADOR) <-
  
    # En esta sección, llamamos a las funciones recursivas (que ya tienen
    # el decorador @TrazaRecursiva) con valores pequeños para ver su
    # comportamiento paso a paso.

    print("--- INICIO DE LA DEMOSTRACIÓN DE PILA DE LLAMADAS ---\n")

    print("--- Traza para: suma_digitos_recursiva(142) ---")
    suma_digitos_recursiva(142)
    print("-" * 50)

    print("\n--- Traza para: invertir_cadena_recursiva('amor') ---")
    invertir_cadena_recursiva("amor")
    print("-" * 50)

    print("\n--- Traza para: Potencia_recursiva(3, 4) ---")
    potencia_recursiva(3, 4)
    print("-" * 50)

    print("\n--- Traza para: busqueda_binaria_recursiva en un arreglo de 10 elementos ---")

    # Usamos el arreglo pequeño para la demostración.
    arreglo_10_ordenado = sorted(arreglo_10)
    # Buscamos un valor que sí exista en el arreglo.
    valor_a_buscar = arreglo_10_ordenado[6] 
    print(f"Buscando el valor {valor_a_buscar} en la lista: {arreglo_10_ordenado}")
    busqueda_binaria_recursiva(arreglo_10_ordenado, valor_a_buscar)
    print("-" * 50)

    print("\n--- FIN DE LA DEMOSTRACIÓN DE PILA ---\n")
    input("Presiona Enter para continuar con las pruebas de rendimiento...")

    # -> ESPACIO DE PRUEBAS DE RENDIMIENTO (SIN DECORADOR) <-

    # Para una medición justa, escribimos las funciones sin el decorador
    # @TrazaRecursiva. Esto evita que el costo de
    # la función print() afecte los resultados.

    # -> Inician las pruebas de rendimiento <-
    print("\n--- INICIANDO PRUEBAS DE RENDIMIENTO (ESTO PUEDE TARDAR UN MOMENTO) ---\n")
    resultados_completos = []

    # Prueba de Suma con número grande
    numero_grande = random.randint(10**500, 10**501 - 1)

    # Diccionarios para almacenar resultados
    resultados_completos.append({ 
        "Algoritmo": "Suma Dígitos", "Tipo": "Iterativa",
        "Tiempo (μs)": medir_rendimiento(suma_digitos_iterativa, numero_grande)['tiempo_s'] * 1e6,
        "Memoria (KB)": medir_rendimiento(suma_digitos_iterativa, numero_grande)['memoria_pico_kb']
    })
    resultados_completos.append({
        "Algoritmo": "Suma Dígitos", "Tipo": "Recursiva",
        "Tiempo (μs)": medir_rendimiento(suma_digitos_rec_perf, numero_grande)['tiempo_s'] * 1e6,
        "Memoria (KB)": medir_rendimiento(suma_digitos_rec_perf, numero_grande)['memoria_pico_kb']
    })

    # La cadena para la versión iterativa puede ser grande
    cadena_grande_iterativa = ''.join(random.choices('abcdefghijklmnopqrstuvwxyz', k=10000))
    # La cadena para la recursiva debe ser más pequeña para evitar el error
    cadena_segura_recursiva = ''.join(random.choices('abcdefghijklmnopqrstuvwxyz', k=900))

    # Diccionarios para almacenar resultados
    resultados_completos.append({
        "Algoritmo": "Invertir Cadena", "Tipo": "Iterativa",
        "Tiempo (μs)": medir_rendimiento(invertir_cadena_iterativa, cadena_grande_iterativa)['tiempo_s'] * 1e6,
        "Memoria (KB)": medir_rendimiento(invertir_cadena_iterativa, cadena_grande_iterativa)['memoria_pico_kb']
    })
    resultados_completos.append({
        "Algoritmo": "Invertir Cadena", "Tipo": "Recursiva",
        "Tiempo (μs)": medir_rendimiento(invertir_cadena_rec_perf, cadena_segura_recursiva)['tiempo_s'] * 1e6,
        "Memoria (KB)": medir_rendimiento(invertir_cadena_rec_perf, cadena_segura_recursiva)['memoria_pico_kb']
    })  

    # Prueba de Búsqueda Binaria en varios tamaños
    for n in [10**3, 10**4, 10**5]:
        lista = arreglos[n]
        lista.sort()
        valor_a_buscar = -1
        
        resultados_completos.append({
            "Algoritmo": f"Búsqueda Binaria ({n/1000:.0f}k)", "Tipo": "Iterativa",
            "Tiempo (μs)": medir_rendimiento(busqueda_binaria_iterativa, lista, valor_a_buscar)['tiempo_s'] * 1e6,
            "Memoria (KB)": medir_rendimiento(busqueda_binaria_iterativa, lista, valor_a_buscar)['memoria_pico_kb']
        })
        resultados_completos.append({
            "Algoritmo": f"Búsqueda Binaria ({n/1000:.0f}k)", "Tipo": "Recursiva",
            "Tiempo (μs)": medir_rendimiento(busqueda_binaria_rec_perf, lista, valor_a_buscar)['tiempo_s'] * 1e6,
            "Memoria (KB)": medir_rendimiento(busqueda_binaria_rec_perf, lista, valor_a_buscar)['memoria_pico_kb']
        })
    
    # Prueba de Potencia con base y exponente grandes
    base_grande = random.uniform(1, 10) # Base entre 1 y 10 
    exponente_grande = random.randint(100, 200) # Exponente entre 100 y 200 

    # Diccionarios para almacenar resultados
    resultados_completos.append({
        "Algoritmo": "Potencia", "Tipo": "Iterativa",
        "Tiempo (μs)": medir_rendimiento(potencia_iterativa, base_grande, exponente_grande)['tiempo_s'] * 1e6,
        "Memoria (KB)": medir_rendimiento(potencia_iterativa, base_grande, exponente_grande)['memoria_pico_kb']
    })      
    resultados_completos.append({
        "Algoritmo": "Potencia", "Tipo": "Recursiva",
        "Tiempo (μs)": medir_rendimiento(potencia_rec_perf, base_grande, exponente_grande)['tiempo_s'] * 1e6,
        "Memoria (KB)": medir_rendimiento(potencia_rec_perf, base_grande, exponente_grande)['memoria_pico_kb']
    })

    # --- Visualización de Resultados ---
    df_resultados = pd.DataFrame(resultados_completos)
    print("\n--- TABLA DE RENDIMIENTO ---")
    print(df_resultados.to_string())

    sns.set_style("whitegrid")
    fig, axes = plt.subplots(1, 2, figsize=(18, 7))
    fig.suptitle('Análisis de Rendimiento: Iterativo vs. Recursivo', fontsize=16)

    sns.barplot(data=df_resultados, x="Algoritmo", y="Tiempo (μs)", hue="Tipo", ax=axes[0])
    axes[0].set_title('Tiempo de Ejecución')
    axes[0].tick_params(axis='x', rotation=45)

    sns.barplot(data=df_resultados, x="Algoritmo", y="Memoria (KB)", hue="Tipo", ax=axes[1])
    axes[1].set_title('Pico de Memoria Utilizada')
    axes[1].tick_params(axis='x', rotation=45)

    plt.tight_layout(rect=[0, 0, 1, 0.96])
    plt.show()
    print("\n--- FIN DE LAS PRUEBAS DE RENDIMIENTO ---\n")