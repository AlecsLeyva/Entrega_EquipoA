// ---------------------------------------------------------------------------
// Prueba de Concepto (PoC) para la Pila de Acciones (Deshacer/Rehacer)
// ---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <chrono>

using namespace std;

// ===========================================================================
// PARTE 1: IMPLEMENTACIÓN MANUAL DE UNA PILA
// ===========================================================================

struct Nodo {
    string dato;
    Nodo* siguiente;
    Nodo(string d) {
        dato = d;
        siguiente = nullptr;
    }
};

class PilaManual {
private:
    Nodo* cima; // En una pila, solo nos importa el elemento de hasta arriba (la cima).

public:
    PilaManual() {
        cima = nullptr;
    }
    ~PilaManual() {
        while(!estaVacia()) {
            eliminar();
        }
    }
    bool estaVacia() {
        return cima == nullptr;
    }
    // "agregar" a una pila es poner un elemento en la cima (push).
    void agregar(string valor) {
        Nodo* nuevo = new Nodo(valor);
        nuevo->siguiente = cima;
        cima = nuevo;
    }
    // "eliminar" de una pila es quitar el elemento de la cima (pop).
    void eliminar() {
        if (estaVacia()) return;
        Nodo* temp = cima;
        cima = cima->siguiente;
        delete temp;
    }
    // "verCima" es ver el elemento de hasta arriba sin quitarlo (top).
    string verCima() {
        if (estaVacia()) return "PILA VACIA";
        return cima->dato;
    }
    void imprimir() {
        if (estaVacia()) {
            cout << "  -> [PILA VACIA]" << endl;
            return;
        }
        Nodo* actual = cima;
        cout << "  -> [Cima] ";
        while (actual != nullptr) {
            cout << actual->dato << " | ";
            actual = actual->siguiente;
        }
        cout << "[Fondo]" << endl;
    }
};

// ===========================================================================
// PARTE 2: FUNCIONES PARA LAS PRUEBAS
// ===========================================================================

// Reutilizamos la misma función para cargar datos desde un archivo.
vector<string> cargarDatos(string nombreArchivo) {
    vector<string> datos;
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "!!! ERROR: No se pudo encontrar el archivo '" << nombreArchivo << "'." << endl;
        return datos;
    }
    string linea;
    while (getline(archivo, linea)) {
        datos.push_back(linea);
    }
    archivo.close();
    return datos;
}

// --- Función para la DEMOSTRACIÓN FUNCIONAL ---
void demostrarPilaNormal() {
    cout << "\nCargando datos desde 'dataset.txt'..." << endl;
    vector<string> dataset = cargarDatos("dataset.txt");
    if (dataset.empty()) return;

    // --- 1. Demostración con Pila Manual ---
    cout << "\n--- 1. Probando la Pila Manual ---" << endl;
    PilaManual deshacerManual;
    PilaManual rehacerManual;

    cout << "a) Realizando acciones (agregando nombres):" << endl;
    for (int i = 0; i < dataset.size(); i++) {
        deshacerManual.agregar(dataset[i]);
    }
    cout << "Pila Deshacer:";
    deshacerManual.imprimir();
    cout << "Pila Rehacer:";
    rehacerManual.imprimir();

    cout << "\nb) Deshaciendo la ultima accion:" << endl;
    string accionMovida = deshacerManual.verCima();
    rehacerManual.agregar(accionMovida);
    deshacerManual.eliminar();
    cout << "Pila Deshacer:";
    deshacerManual.imprimir();
    cout << "Pila Rehacer:";
    rehacerManual.imprimir();

    cout << "\nc) Rehaciendo la accion:" << endl;
    accionMovida = rehacerManual.verCima();
    deshacerManual.agregar(accionMovida);
    rehacerManual.eliminar();
    cout << "Pila Deshacer:";
    deshacerManual.imprimir();
    cout << "Pila Rehacer:";
    rehacerManual.imprimir();

    // --- 2. Demostración con Pila de Librería ---
    cout << "\n\n--- 2. Probando la Pila de Libreria (std::stack) ---" << endl;
    stack<string> deshacerLibreria;
    stack<string> rehacerLibreria;

    cout << "a) Realizando acciones (con push):" << endl;
    for (int i = 0; i < dataset.size(); i++) {
        deshacerLibreria.push(dataset[i]);
    }
    cout << "  -> " << deshacerLibreria.size() << " acciones en Deshacer, " << rehacerLibreria.size() << " en Rehacer." << endl;

    cout << "\nb) Deshaciendo la ultima accion (con top y pop):" << endl;
    rehacerLibreria.push(deshacerLibreria.top());
    deshacerLibreria.pop();
    cout << "  -> " << deshacerLibreria.size() << " acciones en Deshacer, " << rehacerLibreria.size() << " en Rehacer." << endl;

    cout << "\nc) Rehaciendo la accion:" << endl;
    deshacerLibreria.push(rehacerLibreria.top());
    rehacerLibreria.pop();
    cout << "  -> " << deshacerLibreria.size() << " acciones en Deshacer, " << rehacerLibreria.size() << " en Rehacer." << endl;
}

// --- Función para la PRUEBA DE RENDIMIENTO ---
void probarRendimientoPila() {
    cout << "\nCargando datos desde 'dataset1000.txt'..." << endl;
    vector<string> datasetGrande = cargarDatos("dataset1000.txt");
    if (datasetGrande.empty()) return;

    cout << "Dataset de " << datasetGrande.size() << " elementos cargado." << endl;

    // Medir tiempo de la Pila Manual
    PilaManual pilaManualTest;
    auto inicioManual = chrono::high_resolution_clock::now();
    for (int i = 0; i < datasetGrande.size(); i++) {
        pilaManualTest.agregar(datasetGrande[i]);
    }
    auto finManual = chrono::high_resolution_clock::now();
    auto duracionManual = chrono::duration_cast<chrono::microseconds>(finManual - inicioManual);

    // Medir tiempo de la Pila de Librería
    stack<string> pilaLibreriaTest;
    auto inicioLibreria = chrono::high_resolution_clock::now();
    for (int i = 0; i < datasetGrande.size(); i++) {
        pilaLibreriaTest.push(datasetGrande[i]);
    }
    auto finLibreria = chrono::high_resolution_clock::now();
    auto duracionLibreria = chrono::duration_cast<chrono::microseconds>(finLibreria - inicioLibreria);

    // Imprimir la tabla comparativa
    cout << "\n--- TABLA COMPARATIVA DE RENDIMIENTO (PUSH EN PILA) ---" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "| Implementacion      | Tiempo (microsegundos)     |" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "| Pila Manual         | " << duracionManual.count() << " us" << endl;
    cout << "| Pila Libreria (std) | " << duracionLibreria.count() << " us" << endl;
    cout << "----------------------------------------------------" << endl;
}

void mostrarMenuPila() {
    cout << "\n*****************************************************" << endl;
    cout << "      PRUEBA DE CONCEPTO: PILA DESHACER/REHACER" << endl;
    cout << "*****************************************************" << endl;
    cout << "1. Demostracion funcional (dataset.txt)" << endl;
    cout << "2. Comparacion de rendimiento (dataset1000.txt)" << endl;
    cout << "3. Salir" << endl;
    cout << "Elige una opcion: ";
}

// ===========================================================================
// FUNCIÓN PRINCIPAL CON EL MENÚ
// ===========================================================================

int main() {
    int opcion;
    do {
        mostrarMenuPila();
        cin >> opcion;

        switch (opcion) {
            case 1:
                demostrarPilaNormal();
                break;
            case 2:
                probarRendimientoPila();
                break;
            case 3:
                cout << "\nSaliendo del programa..." << endl;
                break;
            default:
                cout << "\nOpcion no valida. Intentalo de nuevo." << endl;
                break;
        }
        cout << "\nPresiona Enter para continuar...";
        cin.ignore();
        cin.get();

    } while (opcion != 3);

    return 0;
}