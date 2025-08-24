// ---------------------------------------------------------------------------
//Prueba de Concepto (PoC) para la Cola de Impresión.
// ---------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <queue>
#include <chrono>
#include <fstream>  // Librería para manejar archivos (file stream).
#include <vector>   // Necesario para guardar los datos leídos del archivo.

using namespace std;

// ===========================================================================
// IMPLEMENTACIÓN MANUAL
// ===========================================================================
struct Nodo {
    string dato;
    Nodo* siguiente;
    Nodo(string d) {
        dato = d;
        siguiente = nullptr;
    }
};

class ColaManual {
private:
    Nodo* inicio;
    Nodo* final;
public:
    ColaManual() {
        inicio = nullptr;
        final = nullptr;
    }
    ~ColaManual() {
        while(!estaVacia()) {
            eliminar();
        }
    }
    bool estaVacia() {
        return inicio == nullptr;
    }
    void agregar(string valor) {
        Nodo* nuevo = new Nodo(valor);
        if (estaVacia()) {
            inicio = nuevo;
            final = nuevo;
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }
    }
    void eliminar() {
        if (estaVacia()) return;
        Nodo* temp = inicio;
        inicio = inicio->siguiente;
        if (inicio == nullptr) final = nullptr;
        delete temp;
    }
    string verInicio() {
        if (estaVacia()) return "Cola vacia";
        return inicio->dato;
    }
    void imprimir() {
        if (estaVacia()) {
            cout << "  -> [COLA VACIA]" << endl;
            return;
        }
        Nodo* actual = inicio;
        cout << "  -> [Inicio] ";
        while (actual != nullptr) {
            cout << actual->dato << " - ";
            actual = actual->siguiente;
        }
        cout << "[Final]" << endl;
    }
};

// ===========================================================================
// FUNCIONES PARA LAS PRUEBAS
// ===========================================================================

// ---Función que ayuda a leer nombres desde un archivo de texto ---
vector<string> cargarDatos(string nombreArchivo) {
    vector<string> datos; // Creamos un vector para guardar los nombres.
    ifstream archivo;     // 'ifstream' es para leer archivos (input file stream).

    archivo.open(nombreArchivo); // Intentamos abrir el archivo.

    // Es MUY importante verificar si el archivo se pudo abrir.
    if (!archivo.is_open()) {
        cout << "!!! ERROR: No se pudo encontrar el archivo '" << nombreArchivo << "'." << endl;
        cout << "!!! Asegurate de que este en la carpeta correcta." << endl;
        return datos; // Devolvemos el vector vacío.
    }

    string linea;
    // Este bucle lee el archivo línea por línea hasta que se acaba.
    while (getline(archivo, linea)) {
        datos.push_back(linea); // Cada línea leída se agrega al final de nuestro vector.
    }

    archivo.close(); // Siempre hay que cerrar el archivo cuando terminamos.
    return datos;
}


// --- Función para la demostración con el dataset normal ---
void probarDatasetNormal() {
    cout << "\nCargando datos desde 'dataset.txt'..." << endl;
    vector<string> dataset = cargarDatos("dataset.txt");

    // Si el archivo no se pudo leer, el vector estará vacío y no hacemos nada.
    if (dataset.empty()) {
        return;
    }
    
    cout << "\n--- 1. Probando la Cola Manual ---" << endl;
    ColaManual miCola;
    cout << "Agregando trabajos a la cola:" << endl;
    for (int i = 0; i < dataset.size(); i++) {
        miCola.agregar(dataset[i]);
    }
    miCola.imprimir();
    
    cout << "\nProcesando todos los trabajos de la cola manual..." << endl;
    while (!miCola.estaVacia()) {
        cout << "Atendiendo a: " << miCola.verInicio() << endl;
        miCola.eliminar();
        miCola.imprimir(); // Muestra el estado después de cada elemento procesado
    }

    cout << "\n\n--- 2. Probando la Cola con Libreria (std::queue) ---" << endl;
    queue<string> colaLibreria;
    cout << "Agregando trabajos a la cola (con push):" << endl;
    for (int i = 0; i < dataset.size(); i++) {
        colaLibreria.push(dataset[i]);
    }
    cout << "  -> Se agregaron " << colaLibreria.size() << " trabajos." << endl;

    // Procesamos todos los elementos hasta que la cola esté vacía
    cout << "\nProcesando todos los trabajos de la cola de libreria..." << endl;
    while (!colaLibreria.empty()) {
        cout << "Atendiendo a: " << colaLibreria.front() << endl; // Muestra el del frente
        colaLibreria.pop(); // Lo saca
        cout << "  -> Quedan " << colaLibreria.size() << " trabajos." << endl; // Muestra cuántos quedan
    }
}

// --- Función para la prueba de rendimiento con 1000 datos ---
void probarRendimiento() {
    cout << "\nCargando datos desde 'dataset1000.txt'..." << endl;
    vector<string> datasetGrande = cargarDatos("dataset1000.txt");

    if (datasetGrande.empty()) {
        return;
    }
    cout << "Dataset de " << datasetGrande.size() << " elementos cargado." << endl;

    // Medir tiempo de la Cola Manual
    ColaManual colaManualTest;
    auto inicioManual = chrono::high_resolution_clock::now();
    for (int i = 0; i < datasetGrande.size(); i++) {
        colaManualTest.agregar(datasetGrande[i]);
    }
    auto finManual = chrono::high_resolution_clock::now();
    auto duracionManual = chrono::duration_cast<chrono::microseconds>(finManual - inicioManual);

    // Medir tiempo de la Cola de Librería
    queue<string> colaLibreriaTest;
    auto inicioLibreria = chrono::high_resolution_clock::now();
    for (int i = 0; i < datasetGrande.size(); i++) {
        colaLibreriaTest.push(datasetGrande[i]);
    }
    auto finLibreria = chrono::high_resolution_clock::now();
    auto duracionLibreria = chrono::duration_cast<chrono::microseconds>(finLibreria - inicioLibreria);

    // Imprimir la tabla comparativa
    cout << "\n--- TABLA COMPARATIVA DE RENDIMIENTO (INSERCION) ---" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "| Implementacion      | Tiempo (microsegundos)     |" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "| Cola Manual         | " << duracionManual.count() << " us" << endl;
    cout << "| Cola Libreria (std) | " << duracionLibreria.count() << " us" << endl;
    cout << "----------------------------------------------------" << endl;
}

void probarRendimiento20mil() {
    cout << "\nCargando datos desde 'datasetX.txt'..." << endl;
    // Le decimos que cargue los datos desde un nuevo archivo que debes crear.
    vector<string> datasetGrande = cargarDatos("datasetX.txt");

    if (datasetGrande.empty()) {
        return;
    }
    cout << "Dataset de " << datasetGrande.size() << " elementos cargado." << endl;

    // Medir tiempo de la Cola Manual
    ColaManual colaManualTest;
    auto inicioManual = chrono::high_resolution_clock::now();
    for (int i = 0; i < datasetGrande.size(); i++) {
        colaManualTest.agregar(datasetGrande[i]);
    }
    auto finManual = chrono::high_resolution_clock::now();
    auto duracionManual = chrono::duration_cast<chrono::microseconds>(finManual - inicioManual);

    // Medir tiempo de la Cola de Librería
    queue<string> colaLibreriaTest;
    auto inicioLibreria = chrono::high_resolution_clock::now();
    for (int i = 0; i < datasetGrande.size(); i++) {
        colaLibreriaTest.push(datasetGrande[i]);
    }
    auto finLibreria = chrono::high_resolution_clock::now();
    auto duracionLibreria = chrono::duration_cast<chrono::microseconds>(finLibreria - inicioLibreria);

    // Imprimir la tabla comparativa
    cout << "\n--- TABLA COMPARATIVA DE RENDIMIENTO ---" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "| Implementacion      | Tiempo (microsegundos)     |" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "| Cola Manual         | " << duracionManual.count() << " us" << endl;
    cout << "| Cola Libreria (std) | " << duracionLibreria.count() << " us" << endl;
    cout << "----------------------------------------------------" << endl;
}

// --- Función para mostrar el menú ---
void mostrarMenu() {
    cout << "\n*****************************************************" << endl;
    cout << "      PRUEBA DE CONCEPTO: COLA DE IMPRESION" << endl;
    cout << "*****************************************************" << endl;
    cout << "1. Probar con dataset normal (desde dataset.txt)" << endl;
    cout << "2. Probar rendimiento con 1000 datos (desde dataset1000.txt)" << endl;
    cout << "3. Probar rendimiento con 20000 datos (desde datasetX.txt)" << endl;
    cout << "4. Salir" << endl;
    cout << "Elige una opcion: ";
}

// ===========================================================================
// FUNCIÓN PRINCIPAL CON EL MENÚ
// ===========================================================================

int main() {
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                probarDatasetNormal();
                break;
            case 2:
                probarRendimiento();
                break;
            case 3:
                probarRendimiento20mil(); // <-- NUEVA LLAMADA
                break;
            case 4: // <-- NÚMERO CAMBIADO
                cout << "\nSaliendo del programa..." << endl;
                break;
            default:
                cout << "\nOpcion no valida. Intentalo de nuevo." << endl;
                break;
        }
        cout << "\nPresiona Enter para continuar...";
        cin.ignore();
        cin.get();

    } while (opcion != 4);

    return 0;
}