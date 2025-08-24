# ---------------------------------------------------------------------------
# Prueba de Concepto (PoC) para la Cola de Impresión en Python.
# ---------------------------------------------------------------------------

import time  # Librería para medir el tiempo, equivalente a <chrono>
from collections import deque # Esta es la librería estándar para colas en Python

# ===========================================================================
# PARTE 1: IMPLEMENTACIÓN MANUAL DE UNA COLA
# ===========================================================================

# En Python usamos clases
class Nodo:
    # El método __init__ es el "constructor" en Python.
    def __init__(self, dato):
        self.dato = dato
        # En lugar de un puntero, es una referencia al siguiente objeto.
        # 'None' es el equivalente de 'nullptr' en Python.
        self.siguiente = None

# La clase que maneja la lógica de la cola.
class ColaManual:
    def __init__(self):
        self.inicio = None
        self.final = None

    def esta_vacia(self):
        return self.inicio is None

    # En Python, los nombres de funciones suelen usar guiones bajos
    def agregar(self, valor):
        nuevo_nodo = Nodo(valor)
        if self.esta_vacia():
            self.inicio = nuevo_nodo
            self.final = nuevo_nodo
        else:
            self.final.siguiente = nuevo_nodo
            self.final = nuevo_nodo

    def eliminar(self):
        if self.esta_vacia():
            return
        self.inicio = self.inicio.siguiente
        if self.inicio is None:
            self.final = None

    def ver_inicio(self):
        if self.esta_vacia():
            return "Cola vacia"
        return self.inicio.dato

    def imprimir(self):
        if self.esta_vacia():
            print("  -> [COLA VACIA]")
            return
        actual = self.inicio
        # La f'' antes de un string permite meter variables dentro con {}
        print(f"  -> [Inicio] ", end="")
        while actual is not None:
            print(f"{actual.dato} - ", end="")
            actual = actual.siguiente
        print("[Final]")

# ===========================================================================
# PARTE 2: FUNCIONES PARA LAS PRUEBAS
# ===========================================================================

# Función para leer los datos de un archivo. Es más simple en Python.
def cargar_datos(nombre_archivo):
    try:
        # 'with open' abre el archivo y se asegura de cerrarlo automáticamente.
        with open(nombre_archivo, 'r') as archivo:
            # Esto lee todas las líneas y quita los saltos de línea del final.
            datos = [linea.strip() for linea in archivo]
        return datos
    except FileNotFoundError:
        print(f"!!! ERROR: No se pudo encontrar el archivo '{nombre_archivo}'.")
        print("!!! Asegurate de que este en la carpeta correcta.")
        return [] # Devuelve una lista vacía.

# --- Función para la DEMOSTRACIÓN FUNCIONAL ---
def probar_dataset_normal():
    print("\nCargando datos desde 'dataset.txt'...")
    dataset = cargar_datos("dataset.txt")

    if not dataset: # Forma de Python de checar si una lista está vacía
        return
    # --- 1. Demostración de la Cola Manual ---
    print("\n--- 1. Probando la Cola Manual ---")
    mi_cola = ColaManual()
    print("Agregando trabajos a la cola:")
    for nombre in dataset:
        mi_cola.agregar(nombre)
    mi_cola.imprimir()
    print("\nProcesando todos los trabajos de la cola manual...")
    while not mi_cola.esta_vacia():
        print(f"Atendiendo a: {mi_cola.ver_inicio()}")
        mi_cola.eliminar()
        mi_cola.imprimir()

    # --- 2. Demostración de la Cola de Librería (deque) ---
    print("\n\n--- 2. Probando la Cola con Libreria (collections.deque) ---")
    # 'deque' es una cola de dos extremos (double-ended queue), súper eficiente.
    cola_libreria = deque()
    print("Agregando trabajos a la cola (con append):")
    for nombre in dataset:
        cola_libreria.append(nombre) # El equivalente a 'push' o 'agregar'
    
    print(f"  -> Se agregaron {len(cola_libreria)} trabajos.")
    
    print("\nProcesando todos los trabajos de la cola de libreria...")
    while cola_libreria: # Mientras la cola no esté vacía...
        # 'popleft' quita y devuelve el elemento de la izquierda (el inicio)
        print(f"Atendiendo a: {cola_libreria.popleft()}")
        print(f"  -> Quedan {len(cola_libreria)} trabajos.")

# --- Función para la PRUEBA DE RENDIMIENTO ---
def probar_rendimiento(nombre_archivo, cantidad):
    print(f"\nCargando datos desde '{nombre_archivo}'...")
    dataset_grande = cargar_datos(nombre_archivo)

    if not dataset_grande:
        return
    
    print(f"Dataset de {len(dataset_grande)} elementos cargado.")

    # Medir tiempo de la Cola Manual
    # time.perf_counter() es el reloj más preciso para medir rendimiento en Python
    inicio_manual = time.perf_counter()
    cola_manual_test = ColaManual()
    for dato in dataset_grande:
        cola_manual_test.agregar(dato)
    fin_manual = time.perf_counter()
    # El resultado ya viene en segundos, lo multiplicamos para tener microsegundos
    duracion_manual = (fin_manual - inicio_manual) * 1_000_000

    # Medir tiempo de la Cola de Librería
    inicio_libreria = time.perf_counter()
    cola_libreria_test = deque()
    for dato in dataset_grande:
        cola_libreria_test.append(dato)
    fin_libreria = time.perf_counter()
    duracion_libreria = (fin_libreria - inicio_libreria) * 1_000_000

    # Imprimir la tabla comparativa
    print(f"\n--- TABLA COMPARATIVA DE RENDIMIENTO (INSERCION {cantidad}) ---")
    print("----------------------------------------------------")
    print("| Implementacion      | Tiempo (microsegundos)     |")
    print("----------------------------------------------------")
    # :.2f formatea el número para que solo muestre 2 decimales
    print(f"| Cola Manual         | {duracion_manual:.2f} us")
    print(f"| Cola Libreria (deque) | {duracion_libreria:.2f} us")
    print("----------------------------------------------------")

# --- Función para mostrar el menú ---
def mostrar_menu():
    print("\n*****************************************************")
    print("      PRUEBA DE CONCEPTO: COLA DE IMPRESION (PYTHON)")
    print("*****************************************************")
    print("1. Probar con dataset normal (desde dataset.txt)")
    print("2. Probar rendimiento con 1000 datos (desde dataset1000.txt)")
    print("3. Probar rendimiento con 20000 datos (desde dataset20000.txt)")
    print("4. Salir")

# ===========================================================================
# FUNCIÓN PRINCIPAL CON EL MENÚ
# ===========================================================================

# Esta es la forma estándar en Python de definir el punto de entrada del programa.
def main():
    while True: # Un bucle infinito que romperemos con 'break'
        mostrar_menu()
        opcion = input("Elige una opcion: ")

        if opcion == '1':
            probar_dataset_normal()
        elif opcion == '2':
            probar_rendimiento("dataset1000.txt", "1,000")
        elif opcion == '3':
            probar_rendimiento("datasetX.txt", "20,000")
        elif opcion == '4':
            print("\nSaliendo del programa...")
            break # Rompe el bucle while
        else:
            print("\nOpcion no valida. Intentalo de nuevo.")

        input("\nPresiona Enter para continuar...")

# Esta construcción asegura que la función main() solo se ejecute
# cuando corres el script directamente.
if __name__ == "__main__":
    main()