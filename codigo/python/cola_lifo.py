# Este programa simula una cola de impresion (FIFO).
from collections import deque

def mostrar_estado(cola):
    print("Estado actual de la cola:", " | ".join(list(cola)) if cola else "La cola esta vacia.")

# 1. Encolar elementos (enqueue/push)
print("--- Demostracion de Cola (FIFO) ---")
cola_impresion = deque()  # Creamos una cola usando deque
datos = ["Carlos", "Ana", "Diego", "Elena", "Bruno", "Fabián", "Laura", "Miguel", "Sofía"]

print("\n1. Agregando elementos a la cola (enqueue):")
for nombre in datos:
    print(f"Agregando '{nombre}' a la cola...")
    cola_impresion.append(nombre)  # Agrega un elemento al final de la cola
    mostrar_estado(cola_impresion)

print("\n2. Revisando el elemento frontal (front):")
if cola_impresion:
    print(f"El elemento al frente de la cola es: {cola_impresion[0]}") # El primer elemento de la cola

# 3. Desencolar elementos (dequeue)
print("\n3. Eliminando elementos de la cola (dequeue):")
while cola_impresion:
    elemento_borrado = cola_impresion.popleft() # Elimina y retorna el elemento del frente de la cola
    print(f"Imprimiendo y eliminando '{elemento_borrado}'...")
    mostrar_estado(cola_impresion)

# 4. Verificar si esta vacia (isEmpty)
print("\n4. Verificando si la cola esta vacia:")
if not cola_impresion:
    print("La cola esta vacia. Todos los documentos han sido impresos.")