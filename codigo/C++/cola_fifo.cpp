#include <iostream>
#include <queue>
#include <string>

// Este programa simula una cola de impresion (FIFO)
// usando la estructura de datos 'queue' de la STL de C++.

void mostrar_estado(const std::queue<std::string>& cola) {
    if (cola.empty()) {
        return;
    }
    std::queue<std::string> temp = cola; // Usamos una copia para no modificar la original
    while (!temp.empty()) {
        std::cout << temp.front() << " | ";
        temp.pop();
    }
    std::cout << std::endl;
}

int main() {
    std::queue<std::string> colaImpresion; // Declaramos una cola para guardar strings
    std::string datos[] = {"Carlos", "Ana", "Diego", "Elena", "Bruno", "Fabián", "Laura", "Miguel", "Sofía"};

    std::cout << "--- Demostracion de Cola (FIFO) ---" << std::endl;

    std::cout << "\nLista de elementos a insertar en la cola" << std::endl << '\n';
    std::cout << "Carlos, Ana, Diego, Elena, Bruno, Fabián, Laura, Miguel, Sofía" << std::endl << '\n';

    // 1. Encolar elementos (enqueue/push)
    std::cout << "\n1. Agregando elementos a la cola (push):" << std::endl;
    std::cout << "Agregando elementos...\n" << std::endl;
    for (const auto& nombre : datos) {
        //std::cout << "Agregando '" << nombre << "' a la cola..." << std::endl;
        colaImpresion.push(nombre); // Agrega un elemento al final de la cola
        mostrar_estado(colaImpresion);
    }
    std::cout << "\nCola despues de agregar todos los elementos:\n" << std::endl;
    mostrar_estado(colaImpresion);
    std::cout << "\nEl primero en la cola es: " << colaImpresion.front() << std::endl;

    // 2. Revisar el elemento frontal (front)
    std::cout << "\n2. Revisando el elemento al frente (front):" << std::endl;
    if (!colaImpresion.empty()) {
        std::cout << "El elemento al frente de la cola es: " << colaImpresion.front() << std::endl;
    }

    // 3. Desencolar elementos (dequeue/pop)
    std::cout << "\n3. Eliminando elementos de la cola (pop):\n" << std::endl;
    while (!colaImpresion.empty()) { // Elimina elementos hasta que la cola este vacia
        std::string elementoBorrado = colaImpresion.front(); // Obtiene el elemento del frente
        colaImpresion.pop(); // Lo elimina de la cola
        mostrar_estado(colaImpresion);
    }

    // 4. Verificar si esta vacia (isEmpty/empty)
    std::cout << "\n4. Verificando si la cola esta vacia (empty):\n" << std::endl;
    if (colaImpresion.empty()) {
        std::cout << "La cola esta vacia. Todos los documentos han sido impresos\n" << std::endl;
    }

    return 0;
}