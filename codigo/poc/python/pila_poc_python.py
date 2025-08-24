# ---------------------------------------------------------------------------
# Prueba de Concepto (PoC) para la Pila de Acciones (Deshacer/Rehacer)
# ---------------------------------------------------------------------------

import time

# ===========================================================================
# PARTE 1: IMPLEMENTACIÓN MANUAL DE UNA PILA
# ===========================================================================

class Nodo:
    def __init__(self, dato):
        self.dato = dato
        self.siguiente = None

class PilaManual:
    def __init__(self):
        # En una pila, solo necesitamos una referencia a la cima.
        self.cima = None

    def esta_vacia(self):
        return self.cima is None

    # 'agregar' a una pila es hacer 'push' en la cima.
    def agregar(self, valor):
        nuevo_nodo = Nodo(valor)
        nuevo_nodo.siguiente = self.cima
        self.cima = nuevo_nodo

    # 'eliminar' de una pila es hacer 'pop' de la cima.
    def eliminar(self):
        if self.esta_vacia():
            return
        self.cima = self.cima.siguiente

    def ver_cima(self):
        if self.esta_vacia():
            return "PILA VACIA"
        return self.cima.dato

    def imprimir(self):
        if self.esta_vacia():
            print("  -> [PILA VACIA]")
            return
        actual = self.cima
        print("  -> [Cima] ", end="")
        while actual is not None:
            print(f"{actual.dato} | ", end="")
            actual = actual.siguiente
        print("[Fondo]")

# ===========================================================================
# PARTE 2: FUNCIONES PARA LAS PRUEBAS
# ===========================================================================

def cargar_datos(nombre_archivo):
    try:
        with open(nombre_archivo, 'r') as archivo:
            datos = [linea.strip() for linea in archivo]
        return datos
    except FileNotFoundError:
        print(f"!!! ERROR: No se pudo encontrar el archivo '{nombre_archivo}'.")
        return []

# --- Función para la DEMOSTRACIÓN FUNCIONAL ---
def demostrar_pila_normal():
    print("\nCargando datos desde 'dataset.txt'...")
    dataset = cargar_datos("dataset.txt")
    if not dataset: return

    # --- 1. Demostración con Pila Manual ---
    print("\n--- 1. Probando la Pila Manual ---")
    deshacer_manual = PilaManual()
    rehacer_manual = PilaManual()

    print("a) Realizando acciones (agregando nombres):")
    for nombre in dataset:
        deshacer_manual.agregar(nombre)
    print("Pila Deshacer:"); deshacer_manual.imprimir()
    print("Pila Rehacer:"); rehacer_manual.imprimir()

    print("\nb) Deshaciendo la ultima accion:")
    accion_movida = deshacer_manual.ver_cima()
    rehacer_manual.agregar(accion_movida)
    deshacer_manual.eliminar()
    print("Pila Deshacer:"); deshacer_manual.imprimir()
    print("Pila Rehacer:"); rehacer_manual.imprimir()

    print("\nc) Rehaciendo la accion:")
    accion_movida = rehacer_manual.ver_cima()
    deshacer_manual.agregar(accion_movida)
    rehacer_manual.eliminar()
    print("Pila Deshacer:"); deshacer_manual.imprimir()
    print("Pila Rehacer:"); rehacer_manual.imprimir()

    # --- 2. Demostración con Pila de Librería (listas de Python) ---
    print("\n\n--- 2. Probando la Pila de Libreria (listas) ---")
    # Una lista normal de Python funciona como una pila.
    deshacer_libreria = []
    rehacer_libreria = []

    print("a) Realizando acciones (con .append):")
    for nombre in dataset:
        deshacer_libreria.append(nombre) # .append() es el 'push'
    print(f"  -> {len(deshacer_libreria)} acciones en Deshacer, {len(rehacer_libreria)} en Rehacer.")

    print("\nb) Deshaciendo la ultima accion (con .pop):")
    # [-1] nos da el último elemento (la cima) sin quitarlo.
    accion_movida = deshacer_libreria[-1]
    rehacer_libreria.append(accion_movida)
    deshacer_libreria.pop() # .pop() sin argumentos quita el último elemento.
    print(f"  -> {len(deshacer_libreria)} acciones en Deshacer, {len(rehacer_libreria)} en Rehacer.")

    print("\nc) Rehaciendo la accion:")
    accion_movida = rehacer_libreria.pop()
    deshacer_libreria.append(accion_movida)
    print(f"  -> {len(deshacer_libreria)} acciones en Deshacer, {len(rehacer_libreria)} en Rehacer.")

# --- Función para la PRUEBA DE RENDIMIENTO ---
def probar_rendimiento_pila():
    print("\nCargando datos desde 'dataset1000.txt'...")
    dataset_grande = cargar_datos("dataset1000.txt")
    if not dataset_grande: return

    print(f"Dataset de {len(dataset_grande)} elementos cargado.")

    # Medir tiempo de la Pila Manual
    inicio_manual = time.perf_counter()
    pila_manual_test = PilaManual()
    for dato in dataset_grande:
        pila_manual_test.agregar(dato)
    fin_manual = time.perf_counter()
    duracion_manual = (fin_manual - inicio_manual) * 1_000_000

    # Medir tiempo de la Pila de Librería (lista)
    inicio_libreria = time.perf_counter()
    pila_libreria_test = []
    for dato in dataset_grande:
        pila_libreria_test.append(dato)
    fin_libreria = time.perf_counter()
    duracion_libreria = (fin_libreria - inicio_libreria) * 1_000_000

    # Imprimir la tabla comparativa
    print("\n--- TABLA COMPARATIVA DE RENDIMIENTO (PUSH EN PILA) ---")
    print("----------------------------------------------------")
    print("| Implementacion      | Tiempo (microsegundos)     |")
    print("----------------------------------------------------")
    print(f"| Pila Manual         | {duracion_manual:.2f} us")
    print(f"| Pila Libreria (lista) | {duracion_libreria:.2f} us")
    print("----------------------------------------------------")

# --- Función para mostrar el menú ---
def mostrar_menu_pila():
    print("\n*****************************************************")
    print("      PRUEBA DE CONCEPTO: PILA DESHACER/REHACER (PYTHON)")
    print("*****************************************************")
    print("1. Demostracion funcional (dataset.txt)")
    print("2. Comparacion de rendimiento (dataset1000.txt)")
    print("3. Salir")

# ===========================================================================
# FUNCIÓN PRINCIPAL CON EL MENÚ
# ===========================================================================

def main():
    while True:
        mostrar_menu_pila()
        opcion = input("Elige una opcion: ")

        if opcion == '1':
            demostrar_pila_normal()
        elif opcion == '2':
            probar_rendimiento_pila()
        elif opcion == '3':
            print("\nSaliendo del programa...")
            break
        else:
            print("\nOpcion no valida. Intentalo de nuevo.")

        input("\nPresiona Enter para continuar...")

if __name__ == "__main__":
    main()