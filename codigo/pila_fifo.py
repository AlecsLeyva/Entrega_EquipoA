# Este programa simula una pila de acciones (deshacer/rehacer) en un editor de texto.

def mostrar_estado(pila):
    print("Estado actual de la pila:", " | ".join(pila) if pila else "La pila esta vacia.")

# 1. Simulación de acciones (push)
print("--- Demostracion de Pila (LIFO) ---")
pila_acciones = []  # Creamos una lista vacia que funcionara como pila
datos = ["Carlos", "Ana", "Diego", "Elena", "Bruno", "Fabián", "Laura", "Miguel", "Sofía"]

print("\n1. Agregando elementos a la pila (push):")
for nombre in datos:
    print(f"Agregando '{nombre}'...")
    pila_acciones.append(nombre)  # Agrega un elemento al final de la lista (cima de la pila)
    mostrar_estado(pila_acciones)

print("\n2. Revisando el elemento superior (peek/top):")
if pila_acciones:
    print(f"El elemento en la cima de la pila es: {pila_acciones[-1]}") # El ultimo elemento de la lista

# 3. Eliminando elementos (pop)
print("\n3. Eliminando elementos de la pila (pop):")
while pila_acciones:
    elemento_borrado = pila_acciones.pop() # Elimina y retorna el ultimo elemento de la lista
    print(f"Eliminando '{elemento_borrado}'...")
    mostrar_estado(pila_acciones)

# 4. Verificar si esta vacia (isEmpty/empty)
print("\n4. Verificando si la pila esta vacia:")
if not pila_acciones:
    print("La pila esta vacia. Se han eliminado todas las acciones.")