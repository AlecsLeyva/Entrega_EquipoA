#include <iostream>
#include <stack>
#include <string>

// Este programa simula la pila de acciones (deshacer/rehacer) en un editor de texto
// usando la estructura de datos 'stack' de la STL de C++.

void mostrar_estado(const std::stack<std::string>& pila) {
    //std::cout << "Estado actual de la pila: ";
    if (pila.empty()) {
        std::cout << "La pila esta vacia." << std::endl;
        return;
    }
    std::stack<std::string> temp = pila; // Usamos una copia para no modificar la original
    while (!temp.empty()) {
        std::cout << temp.top() << " | ";
        temp.pop();
    }
    std::cout << std::endl;
}

int main() {
    std::stack<std::string> pilaAcciones; // Declaramos una pila para guardar strings
    std::string datos[] = {"Carlos", "Ana", "Diego", "Elena", "Bruno", "Fabián", "Laura", "Miguel", "Sofía"};

    std::cout << '\n' <<"--- Demostracion de Pila (LIFO) ---" << std::endl;

    std::cout << "Lista de elementos a insertar en la pila" << std::endl << '\n';
    std::cout << "Carlos, Ana, Diego, Elena, Bruno, Fabián, Laura, Miguel, Sofía" << std::endl << '\n';

    // 1. Simulación de acciones (push)
    std::cout << "\n1. Agregando elementos a la pila (push):" << std::endl << '\n';
    std::cout << "Agregando elementos...\n" << std::endl;
    for (const auto& nombre : datos) {
        pilaAcciones.push(nombre); 
        mostrar_estado(pilaAcciones);
    }
    std::cout << '\n';
    std::cout << "- Pila despues de agregar todos los elementos:" << std::endl << '\n';
    mostrar_estado(pilaAcciones);
    std::cout << '\n' <<"El ultimo en entrar fue: " << pilaAcciones.top() << std::endl << '\n';

    // 2. Revisar el elemento superior (peek/top)
    std::cout << "\n2. Revisando el elemento en la cima (top):" << std::endl;
    if (!pilaAcciones.empty()) { // Verifica si la pila no esta vacia
        std::cout << "El elemento en la cima de la pila es: " << pilaAcciones.top() << std::endl;
    }

    // 3. Eliminando elementos (pop)
    std::cout << "\n3. Eliminando elementos de la pila (pop): \n" << std::endl;
    while (!pilaAcciones.empty()) { // Elimina elementos hasta que la pila este vacia
        std::string elementoBorrado = pilaAcciones.top(); // Obtiene el elemento superior
        pilaAcciones.pop(); // Lo elimina de la pila
        mostrar_estado(pilaAcciones);
    }

    // 4. Verificar si esta vacia (isEmpty/empty)
    std::cout << "\n4. Verificando si la pila esta vacia (empty):\n" << std::endl;
    if (pilaAcciones.empty()) { // Retorna 'true' si la pila no tiene elementos
        std::cout << "La pila esta vacia. Se han eliminado todos los elementos\n" << std::endl;
    }

    return 0;
}