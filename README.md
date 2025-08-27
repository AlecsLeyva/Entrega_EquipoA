<<<<<<< HEAD
PROYECTO FINAL - ESTRUCTURAS DE DATOS APLICADAS
EQUIPO A - PILAS Y COLAS
Integrantes:

GARCIA ESTRADA DORIAN (23311521)

GUTIERREZ MORALES ANGEL ALEXIS (24110865)

LARREA TORRES CESAR MARTIN (24210459)

LEYVA ORTEGA MARTIN ALEJANDRO (22310257)

Enlace al Repositorio de Git:

https://github.com/AlecsLeyva/Entrega_EquipoA

SECCIÓN 5: PRUEBA DE CONCEPTO (PoC) - DESCRIPCIÓN Y GUÍA
Este documento detalla la implementación y ejecución de las Pruebas de Concepto para las estructuras de datos Pila y Cola, desarrolladas tanto en C++ como en Python.

1. ESTRUCTURA DE CARPETAS
Para mantener el proyecto organizado y separar claramente el código fuente de los productos compilados, se adoptó la siguiente estructura:

/proyecto-raiz
|
|--- codigo/
|    |--- poc/
|         |--- cpp/
|         |    |--- cola_poc_cpp.cpp      (PoC para la Cola en C++)
|         |    |--- pila_poc_cpp.cpp      (PoC para la Pila en C++)
|         |
|         |--- python/
|              |--- cola_poc_python.py    (PoC para la Cola en Python)
|              |--- pila_poc_python.py    (PoC para la Pila en Python)
|
|--- ejecutables/
|    |--- poc/
|         |--- (Aquí se guardarán los .exe compilados)
|
|--- dataset.txt             (Dataset con 9 nombres para demostración)
|--- dataset1000.txt           (Dataset con 1,000 nombres para rendimiento)
|--- dataset20000.txt          (Dataset con 20,000 nombres para rendimiento)
|
|--- .gitignore              (Archivo para que Git ignore la carpeta de ejecutables)
|--- README.md               (Este archivo)

2. INSTRUCCIONES DE COMPILACIÓN Y EJECUCIÓN
IMPORTANTE: Todos los comandos deben ejecutarse desde la carpeta raíz del proyecto para que los programas puedan encontrar los archivos de dataset (.txt).

Prerrequisitos:

Para C++: Tener un compilador como g++ instalado y accesible desde la terminal.

Para Python: Tener Python 3 instalado.

2.1. Programas en C++
Compilación:

Para la PoC de la Cola:

g++ codigo/poc/cpp/cola_poc_cpp.cpp -o ejecutables/poc/cola_poc.exe -std=c++11

Para la PoC de la Pila:

g++ codigo/poc/cpp/pila_poc_cpp.cpp -o ejecutables/poc/pila_poc.exe -std=c++11

Ejecución:

Para la PoC de la Cola:

./ejecutables/poc/cola_poc.exe

Para la PoC de la Pila:

./ejecutables/poc/pila_poc.exe

2.2. Programas en Python
Ejecución (no requiere compilación):

Para la PoC de la Cola:

python codigo/poc/python/cola_poc_python.py

Para la PoC de la Pila:

python codigo/poc/python/pila_poc_python.py

3. DESCRIPCIÓN DE LAS PRUEBAS DE CONCEPTO
Cada programa (tanto en C++ como en Python) presenta un menú interactivo para separar la demostración funcional de la prueba de rendimiento.

PoC 1: Cola de Impresión

Opción 1 (Demostración Funcional): Carga 9 nombres de dataset.txt. Muestra paso a paso cómo se llena y se vacía la cola, tanto en la implementación manual como en la de librería, demostrando el comportamiento FIFO (First-In, First-Out).

Opciones 2 y 3 (Rendimiento): Cargan 1,000 y 20,000 nombres respectivamente. Miden el tiempo de inserción (llenado de la cola) para ambas implementaciones y presentan una tabla comparativa.

*Nota: Unicamente en esta prueba se utiliza un dataset de 20,000 nombres ya que con el de 1,000 no muestra diferencia en tiempos de ejecución.

PoC 2: Pila Deshacer/Rehacer

Opción 1 (Demostración Funcional): Carga 9 nombres de dataset.txt simulando acciones en un editor. Muestra visualmente cómo las acciones se mueven entre una pila "deshacer" y una pila "rehacer", demostrando el comportamiento LIFO (Last-In, First-Out).

Opción 2 (Rendimiento): Carga 1,000 nombres. Mide el tiempo que toma apilar (push) todas las acciones en ambas implementaciones y presenta la tabla comparativa.

4. ANÁLISIS DE RENDIMIENTO Y CONCLUSIONES
A continuación se presentan los resultados obtenidos al ejecutar las pruebas de rendimiento en un sistema de prueba.

Resultados para la Cola (Inserción de 20,000 elementos):

Implementación

Tiempo (microsegundos)

Cola Manual (C++)

1850 us (aprox.)

Cola Librería (std)

950 us (aprox.)

Cola Manual (Python)

4200 us (aprox.)

Cola Librería (deque)

180 us (aprox.)

Resultados para la Pila (Inserción de 1,000 elementos):

Implementación

Tiempo (microsegundos)

Pila Manual (C++)

80 us (aprox.)

Pila Librería (std)

45 us (aprox.)

Pila Manual (Python)

210 us (aprox.)

Pila Librería (lista)

95 us (aprox.)

Conclusión General: En todos los casos, las implementaciones que utilizan las librerías estándar de cada lenguaje demostraron ser significativamente más rápidas que nuestras implementaciones manuales. Esto se debe a que las librerías estándar están altamente optimizadas a bajo nivel, utilizando estructuras de datos y algoritmos de gestión de memoria muy eficientes que superan a una implementación directa con nodos enlazados.

Una diferencia funcional notable se observó en la Cola Manual, la cual permite una fácil visualización de su contenido completo, mientras que std::queue en C++ está encapsulada y no ofrece esta funcionalidad, demostrando un compromiso entre control y abstracción.
=======
Esto es una prueba para el primer commit

>>>>>>> e43e6fcc1241693794d58e1d6d7cc08d1e0f6228
